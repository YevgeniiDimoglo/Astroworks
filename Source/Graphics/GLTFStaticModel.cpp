#include "GLTFStaticModel.h"

GLTFStaticModel::GLTFStaticModel(std::string filePath)
{
	std::size_t found = filePath.find_last_of("/\\");
	std::string filePathTemp = filePath.substr(0, found);
	std::string fileNameType = filePath.substr(found + 1);

	found = fileNameType.find_last_of(".");
	std::string fileName = fileNameType.substr(0, found);
	std::string fileType = fileNameType.substr(found + 1);

	this->filePath = filePath;
	this->fileName = fileName;
	this->fileType = fileType;
}

void GLTFStaticModel::loadImages(tinygltf::Model& input)
{
	images.resize(input.images.size());
	for (size_t i = 0; i < input.images.size(); i++)
	{
		tinygltf::Image& glTFImage = input.images[i];

		unsigned char* buffer = nullptr;
		VkDeviceSize bufferSize = 0;
		bool deleteBuffer = false;

		if (glTFImage.component == 3)
		{
			bufferSize = glTFImage.width * glTFImage.height * 4;
			buffer = new unsigned char[bufferSize];
			unsigned char* rgba = buffer;
			unsigned char* rgb = &glTFImage.image[0];
			for (size_t i = 0; i < glTFImage.width * glTFImage.height; i++)
			{
				memcpy(rgba, rgb, sizeof(unsigned char) * 3);
				rgba += 4;
				rgb += 3;
			}
			deleteBuffer = true;
		}
		else
		{
			buffer = &glTFImage.image[0];
			bufferSize = glTFImage.image.size();
		}

		images[i] = createTextureFromBuffer(buffer, bufferSize, VK_FORMAT_R8G8B8A8_SRGB, glTFImage.width, glTFImage.height, newPhysicalDevice, newLogicalDevice, commandPool, transferQueue);

		if (deleteBuffer)
		{
			delete[] buffer;
		}
	}

	if (images.size() == 0)
	{
		createDummyTextures(newPhysicalDevice, newLogicalDevice, commandPool, transferQueue);
	}
}

void GLTFStaticModel::loadTextures(tinygltf::Model& input)
{
	textures.resize(input.textures.size());
	for (size_t i = 0; i < input.textures.size(); i++)
	{
		textures[i].imageIndex = input.textures[i].source;
	}
}

void GLTFStaticModel::loadMaterials(tinygltf::Model& input)
{
	materials.resize(input.materials.size());
	for (size_t i = 0; i < input.materials.size(); i++)
	{
		tinygltf::Material glTFMaterial = input.materials[i];
		if (glTFMaterial.values.find("baseColorFactor") != glTFMaterial.values.end())
		{
			materials[i].baseColorFactor = glm::make_vec4(glTFMaterial.values["baseColorFactor"].ColorFactor().data());
		}
		if (glTFMaterial.values.find("baseColorTexture") != glTFMaterial.values.end())
		{
			materials[i].baseColorTextureIndex = glTFMaterial.values["baseColorTexture"].TextureIndex();
		}
	}
}

void GLTFStaticModel::loadNode(const tinygltf::Node& inputNode, const tinygltf::Model& input, GLTFStaticModel::Node* parent, std::vector<uint32_t>& indexBuffer, std::vector<GLTFStaticModel::Vertex>& vertexBuffer)
{
	GLTFStaticModel::Node* node = new GLTFStaticModel::Node{};
	node->matrix = glm::mat4(1.0f);
	node->parent = parent;

	if (inputNode.translation.size() == 3)
	{
		if (nodes.size() <= 1)
		{
			node->matrix = glm::translate(node->matrix, glm::vec3(0.f, 0.f, 0.f));
		}
		else
		{
			node->matrix = glm::translate(node->matrix, glm::vec3(glm::make_vec3(inputNode.translation.data())));
		}
	}
	if (inputNode.rotation.size() == 4)
	{
		glm::quat q = glm::make_quat(inputNode.rotation.data());
		node->matrix *= glm::mat4(q);
	}
	if (inputNode.scale.size() == 3)
	{
		node->matrix = glm::scale(node->matrix, glm::vec3(glm::make_vec3(inputNode.scale.data())));
	}
	if (inputNode.matrix.size() == 16)
	{
		node->matrix = glm::make_mat4x4(inputNode.matrix.data());
	}

	if (inputNode.children.size() > 0)
	{
		for (size_t i = 0; i < inputNode.children.size(); i++)
		{
			loadNode(input.nodes[inputNode.children[i]], input, node, indexBuffer, vertexBuffer);
		}
	}

	if (inputNode.mesh > -1)
	{
		const tinygltf::Mesh mesh = input.meshes[inputNode.mesh];

		for (size_t i = 0; i < mesh.primitives.size(); i++)
		{
			const tinygltf::Primitive& glTFPrimitive = mesh.primitives[i];
			uint32_t firstIndex = static_cast<uint32_t>(indexBuffer.size());
			uint32_t vertexStart = static_cast<uint32_t>(vertexBuffer.size());
			uint32_t indexCount = 0;

			// Vertices
			{
				const float* positionBuffer = nullptr;
				const float* normalsBuffer = nullptr;
				const float* texCoordsBuffer = nullptr;
				size_t vertexCount = 0;

				if (glTFPrimitive.attributes.find("POSITION") != glTFPrimitive.attributes.end())
				{
					const tinygltf::Accessor& accessor = input.accessors[glTFPrimitive.attributes.find("POSITION")->second];
					const tinygltf::BufferView& view = input.bufferViews[accessor.bufferView];
					positionBuffer = reinterpret_cast<const float*>(&(input.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]));
					vertexCount = accessor.count;
				}

				if (glTFPrimitive.attributes.find("NORMAL") != glTFPrimitive.attributes.end())
				{
					const tinygltf::Accessor& accessor = input.accessors[glTFPrimitive.attributes.find("NORMAL")->second];
					const tinygltf::BufferView& view = input.bufferViews[accessor.bufferView];
					normalsBuffer = reinterpret_cast<const float*>(&(input.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]));
				}

				if (glTFPrimitive.attributes.find("TEXCOORD_0") != glTFPrimitive.attributes.end())
				{
					const tinygltf::Accessor& accessor = input.accessors[glTFPrimitive.attributes.find("TEXCOORD_0")->second];
					const tinygltf::BufferView& view = input.bufferViews[accessor.bufferView];
					texCoordsBuffer = reinterpret_cast<const float*>(&(input.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]));
				}

				for (size_t v = 0; v < vertexCount; v++)
				{
					Vertex vert{};
					vert.pos = glm::vec4(glm::make_vec3(&positionBuffer[v * 3]), 1.0f);
					vert.normal = glm::normalize(glm::vec3(normalsBuffer ? glm::make_vec3(&normalsBuffer[v * 3]) : glm::vec3(0.0f)));
					vert.uv = texCoordsBuffer ? glm::make_vec2(&texCoordsBuffer[v * 2]) : glm::vec3(0.0f);
					vertexBuffer.push_back(vert);
				}
			}

			// Indices
			{
				const tinygltf::Accessor& accessor = input.accessors[glTFPrimitive.indices];
				const tinygltf::BufferView& bufferView = input.bufferViews[accessor.bufferView];
				const tinygltf::Buffer& buffer = input.buffers[bufferView.buffer];

				indexCount += static_cast<uint32_t>(accessor.count);

				switch (accessor.componentType)
				{
				case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT:
				{
					const uint32_t* buf = reinterpret_cast<const uint32_t*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);
					for (size_t index = 0; index < accessor.count; index++)
					{
						indexBuffer.push_back(buf[index] + vertexStart);
					}
					break;
				}

				case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT:
				{
					const uint16_t* buf = reinterpret_cast<const uint16_t*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);
					for (size_t index = 0; index < accessor.count; index++)
					{
						indexBuffer.push_back(buf[index] + vertexStart);
					}
					break;
				}

				case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE:
				{
					const uint8_t* buf = reinterpret_cast<const uint8_t*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);
					for (size_t index = 0; index < accessor.count; index++)
					{
						indexBuffer.push_back(buf[index] + vertexStart);
					}
					break;
				}

				default:
					std::cerr << "Index component type" << accessor.componentType << " not supported" << std::endl;
					return;
				}
			}

			Primitive primitive{};
			primitive.firstIndex = firstIndex;
			primitive.indexCount = indexCount;
			primitive.materialIndex = glTFPrimitive.material;
			node->mesh.primitives.push_back(primitive);
		}
	}

	if (parent)
	{
		parent->children.push_back(node);
	}
	else
	{
		nodes.push_back(node);
	}
}

void GLTFStaticModel::drawNode(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, GLTFStaticModel::Node* node)
{
	if (node->mesh.primitives.size() > 0)
	{
		glm::mat4 nodeMatrix = node->matrix;
		GLTFStaticModel::Node* currentParent = node->parent;
		while (currentParent)
		{
			nodeMatrix = currentParent->matrix * nodeMatrix;
			currentParent = currentParent->parent;
		}

		for (GLTFStaticModel::Primitive& primitive : node->mesh.primitives)
		{
			PushConstants pushConstants;
			pushConstants.baseColor = materials[primitive.materialIndex].baseColorFactor * baseColor;
			pushConstants.model = sceneValues * nodeMatrix;
			vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(PushConstants), &pushConstants);

			if (primitive.indexCount > 0)
			{
				// Create dummy texture
				if (dummyTextureImages.empty())
				{
					GLTFStaticModel::Texture texture = textures[materials[primitive.materialIndex].baseColorTextureIndex];
					vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &images[texture.imageIndex].descriptorSet, 0, nullptr);
				}
				else
				{
					GLTFStaticModel::Texture texture = GLTFStaticModel::Texture{ 0 };
					vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &dummyTextureImages[texture.imageIndex].descriptorSet, 0, nullptr);
				}
				vkCmdDrawIndexed(commandBuffer, primitive.indexCount, 1, primitive.firstIndex, 0, 0);
			}
		}
	}

	for (auto& child : node->children)
	{
		drawNode(commandBuffer, pipelineLayout, child);
	}
}

void GLTFStaticModel::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	VkDeviceSize offsets[1] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertices.buffer, offsets);
	vkCmdBindIndexBuffer(commandBuffer, indices.buffer, 0, VK_INDEX_TYPE_UINT32);

	for (auto& node : nodes)
	{
		drawNode(commandBuffer, pipelineLayout, node);
	}
}

void GLTFStaticModel::loadglTFFile(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout)
{
	this->newPhysicalDevice = newPhysicalDevice;
	this->newLogicalDevice = newLogicalDevice;
	this->transferQueue = transferQueue;
	this->commandPool = transferCommandPool;
	this->samplerDescriptorPool = samplerDescriptorPool;
	this->samplerSetLayout = samplerSetLayout;

	tinygltf::Model		glTFInput;
	tinygltf::TinyGLTF	gltfContext;
	std::string error, warning;

	bool fileLoaded = false;

	if (fileType == "glb")
	{
		fileLoaded = gltfContext.LoadBinaryFromFile(&glTFInput, &error, &warning, filePath);
	}
	else
	{
		fileLoaded = gltfContext.LoadASCIIFromFile(&glTFInput, &error, &warning, filePath);
	}

	std::vector<uint32_t>					indexBuffer;
	std::vector<GLTFStaticModel::Vertex>	vertexBuffer;

	if (fileLoaded)
	{
		this->loadImages(glTFInput);
		this->loadMaterials(glTFInput);
		this->loadTextures(glTFInput);
		const tinygltf::Scene& scene = glTFInput.scenes[0];
		for (size_t i = 0; i < scene.nodes.size(); i++)
		{
			const tinygltf::Node node = glTFInput.nodes[scene.nodes[i]];
			this->loadNode(node, glTFInput, nullptr, indexBuffer, vertexBuffer);
		}
	}
	else
	{
		throw std::runtime_error("Failed to open the glRF file");
	}

	indices.count = static_cast<uint32_t>(indexBuffer.size());

	createVertexBuffer(newPhysicalDevice, newLogicalDevice, transferQueue, transferCommandPool, &vertexBuffer);
	createIndexBuffer(newPhysicalDevice, newLogicalDevice, transferQueue, transferCommandPool, &indexBuffer);
}

void GLTFStaticModel::cleanupResourses(VkDevice newLogicalDevice)
{
	for (auto i = 0; i < images.size(); i++)
	{
		vkDestroyImageView(newLogicalDevice, images[i].view, nullptr);
		vkDestroyImage(newLogicalDevice, images[i].image, nullptr);
		vkFreeMemory(newLogicalDevice, images[i].deviceMemory, nullptr);
		vkDestroySampler(newLogicalDevice, images[i].sampler, nullptr);
	}

	for (auto i = 0; i < dummyTextureImages.size(); i++)
	{
		vkDestroyImageView(newLogicalDevice, dummyTextureImages[i].view, nullptr);
		vkDestroyImage(newLogicalDevice, dummyTextureImages[i].image, nullptr);
		vkFreeMemory(newLogicalDevice, dummyTextureImages[i].deviceMemory, nullptr);
		vkDestroySampler(newLogicalDevice, dummyTextureImages[i].sampler, nullptr);
	}

	vkDestroyBuffer(newLogicalDevice, vertices.buffer, nullptr);
	vkFreeMemory(newLogicalDevice, vertices.memory, nullptr);

	vkDestroyBuffer(newLogicalDevice, indices.buffer, nullptr);
	vkFreeMemory(newLogicalDevice, indices.memory, nullptr);
}

void GLTFStaticModel::createVertexBuffer(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<GLTFStaticModel::Vertex>* vertices)
{
	VkDeviceSize bufferSize = sizeof(GLTFStaticModel::Vertex) * vertices->size();

	// Temporary buffer to "stage" vertex data before transfering to GPU
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	// Create Staging buffer and allocate memory to it
	createBuffer(newPhysicalDevice, newLogicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, stagingBufferMemory);

	// Map memory to vertex buffer
	void* data;																					// 1. Create pointer to a point in normal memory
	vkMapMemory(newLogicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);							// 2, "Map" the vertex buffer memory to that point
	memcpy(data, vertices->data(), bufferSize);													// 3. Copy memory from vertices vector to the point
	vkUnmapMemory(newLogicalDevice, stagingBufferMemory);													// 4. Unmap the vertex buffer memory

	// Create buffer with TRANSFER_DST_BIT to mark as recipient of transfer data ( also VERTEX buffer)
	// Buffer memory is to be DEVICE_LOCAL_BIT meaning memory is on the GPU and only accessible by it and not CPU (host)
	createBuffer(newPhysicalDevice, newLogicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, this->vertices.buffer, this->vertices.memory);

	// Copy staging	buffer to vertex buffer on GPU
	copyBuffer(newLogicalDevice, transferCommandPool, transferQueue, stagingBuffer, this->vertices.buffer, bufferSize);

	vkDestroyBuffer(newLogicalDevice, stagingBuffer, nullptr);
	vkFreeMemory(newLogicalDevice, stagingBufferMemory, nullptr);
}

void GLTFStaticModel::createIndexBuffer(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<uint32_t>* indices)
{
	// Get size of buffer needed for index
	VkDeviceSize bufferSize = sizeof(uint32_t) * indices->size();

	// Temporary buffer to "stage" index data before transfering to GPU
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	// Create Staging buffer and allocate memory to it
	createBuffer(newPhysicalDevice, newLogicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, stagingBufferMemory);

	// Map memory to index  buffer
	void* data;
	vkMapMemory(newLogicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, indices->data(), (size_t)bufferSize);
	vkUnmapMemory(newLogicalDevice, stagingBufferMemory);

	// Create buffer for Index data on GPU access only area
	createBuffer(newPhysicalDevice, newLogicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, this->indices.buffer, this->indices.memory);

	// Copy staging	buffer to vertex buffer on GPU
	copyBuffer(newLogicalDevice, transferCommandPool, transferQueue, stagingBuffer, this->indices.buffer, bufferSize);

	// Destoy + release Staging buffer resources
	vkDestroyBuffer(newLogicalDevice, stagingBuffer, nullptr);
	vkFreeMemory(newLogicalDevice, stagingBufferMemory, nullptr);
}

GLTFStaticModel::Image GLTFStaticModel::createTextureFromBuffer(void* buffer, VkDeviceSize bufferSize, VkFormat format, uint32_t texWidth, uint32_t texHeight, VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkCommandPool transferCommandPool, VkQueue transferQueue)
{
	assert(buffer);

	GLTFStaticModel::Image image;

	image.width = texWidth;
	image.height = texHeight;

	VkBuffer imageStagingBuffer;
	VkDeviceMemory imageStagingBufferMemory;
	createBuffer(newPhysicalDevice, newLogicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		imageStagingBuffer, imageStagingBufferMemory);

	// Copy image data to staging buffer
	void* data;
	vkMapMemory(newLogicalDevice, imageStagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, buffer, static_cast<size_t>(bufferSize));
	vkUnmapMemory(newLogicalDevice, imageStagingBufferMemory);

	// Create image to hold final texture
	VkImage texImage;
	VkDeviceMemory texImageMemory;
	texImage = createImage(newPhysicalDevice, newLogicalDevice,
		texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, texImageMemory);

	// Copy data to image
	// Transition image to be DST for copy operation
	transitionImageLayout(newLogicalDevice, transferCommandPool, transferQueue,
		texImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	// Copy image data
	copyBufferToImage(newLogicalDevice, transferCommandPool, transferQueue, imageStagingBuffer, texImage, texWidth, texHeight);

	// Transition image to be shader readable for shader usage
	transitionImageLayout(newLogicalDevice, transferCommandPool, transferQueue,
		texImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	// Add texture data to vector for reference
	image.image = texImage;
	image.deviceMemory = texImageMemory;

	// Destroy staging buffers
	vkDestroyBuffer(newLogicalDevice, imageStagingBuffer, nullptr);
	vkFreeMemory(newLogicalDevice, imageStagingBufferMemory, nullptr);

	VkSamplerCreateInfo samplerInfo{};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;

	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 1.0f;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;

	VkSampler imageSampler;
	if (vkCreateSampler(newLogicalDevice, &samplerInfo, nullptr, &imageSampler) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create texture sampler");
	}

	image.sampler = imageSampler;

	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = texImage;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;
	if (vkCreateImageView(newLogicalDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create texture image view");
	}

	image.view = imageView;

	VkDescriptorSet descriptorSet;

	// Descriptor set allocation info
	VkDescriptorSetAllocateInfo setAllocInfo = {};
	setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocInfo.descriptorPool = samplerDescriptorPool;
	setAllocInfo.descriptorSetCount = 1;
	setAllocInfo.pSetLayouts = &samplerSetLayout;

	// Allocate descriptor sets
	VkResult result = vkAllocateDescriptorSets(newLogicalDevice, &setAllocInfo, &descriptorSet);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate texture descriptor sets");
	}

	// Texture image info
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;							// Image layout when image in use
	imageInfo.imageView = imageView;															// Image to bind to set
	imageInfo.sampler = imageSampler;															// Sampler to use for set

	image.descriptor = imageInfo;

	// Descriptor write info
	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = descriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pImageInfo = &imageInfo;

	// Update new descriptor set
	vkUpdateDescriptorSets(newLogicalDevice, 1, &descriptorWrite, 0, nullptr);

	image.descriptorSet = descriptorSet;

	return image;
}

void GLTFStaticModel::createDummyTextures(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkCommandPool transferCommandPool, VkQueue transferQueue)
{
	dummyTextureImages.resize(DUMMIES);

	for (size_t i = 0; i < dummyTextureImages.size(); i++)
	{
		int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load("./Data/Textures/Dummy.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		VkDeviceSize imageSize = texWidth * texHeight * 4;

		if (!pixels)
		{
			throw std::runtime_error("failed to load texture image");
		}

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		createBuffer(newPhysicalDevice, newLogicalDevice, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(newLogicalDevice, stagingBufferMemory, 0, imageSize, 0, &data);
		memcpy(data, pixels, static_cast<size_t>(imageSize));
		vkUnmapMemory(newLogicalDevice, stagingBufferMemory);

		stbi_image_free(pixels);

		VkImageLayout imageLayout{};

		VkImage texImage;
		VkDeviceMemory texImageMemory;
		texImage = createImage(newPhysicalDevice, newLogicalDevice, texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, texImageMemory);
		transitionImageLayout(newLogicalDevice, transferCommandPool, transferQueue, texImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		copyBufferToImage(newLogicalDevice, transferCommandPool, transferQueue, stagingBuffer, texImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
		transitionImageLayout(newLogicalDevice, transferCommandPool, transferQueue, texImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

		vkDestroyBuffer(newLogicalDevice, stagingBuffer, nullptr);
		vkFreeMemory(newLogicalDevice, stagingBufferMemory, nullptr);

		VkSamplerCreateInfo samplerInfo{};
		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerInfo.magFilter = VK_FILTER_LINEAR;
		samplerInfo.minFilter = VK_FILTER_LINEAR;

		samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

		samplerInfo.anisotropyEnable = VK_TRUE;
		samplerInfo.maxAnisotropy = 1.0f;
		samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable = VK_FALSE;
		samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

		samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerInfo.mipLodBias = 0.0f;
		samplerInfo.minLod = 0.0f;
		samplerInfo.maxLod = 0.0f;

		VkSampler imageSampler;
		if (vkCreateSampler(newLogicalDevice, &samplerInfo, nullptr, &imageSampler) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create texture sampler");
		}

		VkImageViewCreateInfo viewInfo{};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = texImage;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		VkImageView imageView;
		if (vkCreateImageView(newLogicalDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create texture image view");
		}

		VkDescriptorSet descriptorSet;

		// Descriptor set allocation info
		VkDescriptorSetAllocateInfo setAllocInfo = {};
		setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		setAllocInfo.descriptorPool = samplerDescriptorPool;
		setAllocInfo.descriptorSetCount = 1;
		setAllocInfo.pSetLayouts = &samplerSetLayout;

		// Allocate descriptor sets
		VkResult result = vkAllocateDescriptorSets(newLogicalDevice, &setAllocInfo, &descriptorSet);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate texture descriptor sets");
		}

		// Texture image info
		VkDescriptorImageInfo imageInfo = {};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;							// Image layout when image in use
		imageInfo.imageView = imageView;															// Image to bind to set
		imageInfo.sampler = imageSampler;															// Sampler to use for set

		// Descriptor write info
		VkWriteDescriptorSet descriptorWrite = {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSet;
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pImageInfo = &imageInfo;

		// Update new descriptor set
		vkUpdateDescriptorSets(newLogicalDevice, 1, &descriptorWrite, 0, nullptr);

		Image dummyImage;
		dummyImage.image = texImage;
		dummyImage.imageLayout = imageLayout;
		dummyImage.deviceMemory = texImageMemory;
		dummyImage.view = imageView;
		dummyImage.width = texWidth;
		dummyImage.height = texHeight;
		dummyImage.descriptor = imageInfo;
		dummyImage.sampler = imageSampler;
		dummyImage.descriptorSet = descriptorSet;

		dummyTextureImages.resize(dummyTextureImages.size() - 1);
		dummyTextureImages.push_back(dummyImage);
	}
}