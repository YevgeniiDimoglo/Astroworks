#include "Texture.h"

void CubeMap::createCubeMap(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkCommandPool transferCommandPool, VkQueue transferQueue, std::string filePath)
{
	int width, height;
	int channels;

	const float* image = stbi_loadf(
		filePath.c_str(),
		&width,
		&height,
		&channels,
		3
	);

	if (image == nullptr)
	{
		throw std::runtime_error(
			"Failed to load texture image: " +
			filePath
		);
	}

	std::vector<float> image32(width * height * 4);
	float24to32(width, height, image, image32.data());

	stbi_image_free((void*)image);

	//VkBuffer imageStagingBuffer;
	//VkDeviceMemory imageStagingBufferMemory;
	//createBuffer(newPhysicalDevice, newLogicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
	//	VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
	//	imageStagingBuffer, imageStagingBufferMemory);

	//// Copy image data to staging buffer
	//void* data;
	//vkMapMemory(newLogicalDevice, imageStagingBufferMemory, 0, bufferSize, 0, &data);
	//memcpy(data, image, static_cast<size_t>(bufferSize));
	//vkUnmapMemory(newLogicalDevice, imageStagingBufferMemory);

	//VkImageCreateInfo imageInfo = {};
	//imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	//imageInfo.imageType = VK_IMAGE_TYPE_2D;
	//imageInfo.extent.width = static_cast<uint32_t>(width);
	//imageInfo.extent.height = static_cast<uint32_t>(height);
	//imageInfo.extent.depth = 1;
	//imageInfo.mipLevels = 1;
	//imageInfo.arrayLayers = 6; // 6 faces for cubemap
	//imageInfo.format = VK_FORMAT_R32G32B32_SFLOAT; // Assuming HDRI image format
	//imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	//imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	//imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	//imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	//imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	//imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT; // Enable cubemap compatibility

	//// Create image to hold final texture
	//VkImage texImage;
	//VkDeviceMemory texImageMemory;
	//texImage = createImage(newPhysicalDevice, newLogicalDevice,
	//	width, height, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL,
	//	VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, texImageMemory);

	//// Copy data to image
	//// Transition image to be DST for copy operation
	//transitionImageLayout(newLogicalDevice, transferCommandPool, transferQueue,
	//	texImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	//// Copy image data
	//copyBufferToImage(newLogicalDevice, transferCommandPool, transferQueue, imageStagingBuffer, texImage, width, height);

	//// Transition image to be shader readable for shader usage
	//transitionImageLayout(newLogicalDevice, transferCommandPool, transferQueue,
	//	texImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	//// Destroy staging buffers
	//vkDestroyBuffer(newLogicalDevice, imageStagingBuffer, nullptr);
	//vkFreeMemory(newLogicalDevice, imageStagingBufferMemory, nullptr);

	//VkSamplerCreateInfo samplerInfo{};
	//samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	//samplerInfo.magFilter = VK_FILTER_LINEAR;
	//samplerInfo.minFilter = VK_FILTER_LINEAR;

	//samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	//samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	//samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

	//samplerInfo.anisotropyEnable = VK_TRUE;
	//samplerInfo.maxAnisotropy = 1.0f;
	//samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	//samplerInfo.unnormalizedCoordinates = VK_FALSE;
	//samplerInfo.compareEnable = VK_FALSE;
	//samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

	//samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	//samplerInfo.mipLodBias = 0.0f;
	//samplerInfo.minLod = 0.0f;
	//samplerInfo.maxLod = 0.0f;

	//VkSampler imageSampler;
	//if (vkCreateSampler(newLogicalDevice, &samplerInfo, nullptr, &imageSampler) != VK_SUCCESS)
	//{
	//	throw std::runtime_error("Failed to create texture sampler");
	//}

	//image.sampler = imageSampler;

	//VkImageViewCreateInfo viewInfo{};
	//viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	//viewInfo.image = texImage;
	//viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	//viewInfo.format = format;
	//viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	//viewInfo.subresourceRange.baseMipLevel = 0;
	//viewInfo.subresourceRange.levelCount = 1;
	//viewInfo.subresourceRange.baseArrayLayer = 0;
	//viewInfo.subresourceRange.layerCount = 1;

	//VkImageView imageView;
	//if (vkCreateImageView(newLogicalDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
	//{
	//	throw std::runtime_error("Failed to create texture image view");
	//}

	//image.view = imageView;

	//VkDescriptorSet descriptorSet;

	//// Descriptor set allocation info
	//VkDescriptorSetAllocateInfo setAllocInfo = {};
	//setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	//setAllocInfo.descriptorPool = samplerDescriptorPool;
	//setAllocInfo.descriptorSetCount = 1;
	//setAllocInfo.pSetLayouts = &samplerSetLayout;

	//// Allocate descriptor sets
	//VkResult result = vkAllocateDescriptorSets(newLogicalDevice, &setAllocInfo, &descriptorSet);
	//if (result != VK_SUCCESS)
	//{
	//	throw std::runtime_error("Failed to allocate texture descriptor sets");
	//}

	//// Texture image info
	//VkDescriptorImageInfo imageInfo = {};
	//imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;							// Image layout when image in use
	//imageInfo.imageView = imageView;															// Image to bind to set
	//imageInfo.sampler = imageSampler;															// Sampler to use for set

	//image.descriptor = imageInfo;

	//// Descriptor write info
	//VkWriteDescriptorSet descriptorWrite = {};
	//descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	//descriptorWrite.dstSet = descriptorSet;
	//descriptorWrite.dstBinding = 0;
	//descriptorWrite.dstArrayElement = 0;
	//descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	//descriptorWrite.descriptorCount = 1;
	//descriptorWrite.pImageInfo = &imageInfo;

	//// Update new descriptor set
	//vkUpdateDescriptorSets(newLogicalDevice, 1, &descriptorWrite, 0, nullptr);

	//image.descriptorSet = descriptorSet;
}