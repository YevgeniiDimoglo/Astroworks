#include "Texture.h"

void CubeMap::CreateCubeMap(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkCommandPool transferCommandPool, VkQueue transferQueue, std::string filePath)
{
	int width, height;
	int channels;

	const float* tempimage = stbi_loadf(
		filePath.c_str(),
		&width,
		&height,
		&channels,
		3
	);

	if (tempimage == nullptr)
	{
		throw std::runtime_error(
			"Failed to load texture image: " +
			filePath
		);
	}

	std::vector<float> image32(width * height * 4);
	float24to32(width, height, tempimage, image32.data());

	stbi_image_free((void*)tempimage);

	Bitmap in(width, height, 4, BitmapFormat::BitmapFormatFloat, image32.data());
	Bitmap out = ConvertEquirectangularMapToVerticalCross(in);

	Bitmap cubemap = ConvertVerticalCrossToCubeMapFaces(out);

	uint8_t* data = cubemap.data.data();

	uint32_t cubeimageSize = (
		cubemap.w *
		cubemap.h *
		4 *
		Bitmap::GetBytesPerComponent(cubemap.fmt) *
		6
		);

	VkBuffer imageStagingBuffer;
	VkDeviceMemory imageStagingBufferMemory;
	createBuffer(newPhysicalDevice, newLogicalDevice, cubeimageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, imageStagingBuffer, imageStagingBufferMemory);

	void* bufferdata;
	vkMapMemory(newLogicalDevice, imageStagingBufferMemory, 0, cubeimageSize, 0, &bufferdata);
	memcpy(bufferdata, data, static_cast<size_t>(cubeimageSize));
	vkUnmapMemory(newLogicalDevice, imageStagingBufferMemory);

	VkImageCreateInfo imageInfo{};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = cubemap.w;
	imageInfo.extent.height = cubemap.h;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 6;
	imageInfo.format = VK_FORMAT_R32G32B32A32_SFLOAT;
	imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;

	VkImage image;
	VK_CHECK(vkCreateImage(newLogicalDevice, &imageInfo, nullptr, &image));

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(newLogicalDevice, image, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(newPhysicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	VK_CHECK(vkAllocateMemory(newLogicalDevice, &allocInfo, nullptr, &cubeMap.deviceMemory));

	vkBindImageMemory(newLogicalDevice, image, cubeMap.deviceMemory, 0);

	transitionImageLayout(newLogicalDevice, transferCommandPool, transferQueue, image, VK_FORMAT_R32G32B32A32_SFLOAT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 6);
	copyBufferToImage(newLogicalDevice, transferCommandPool, transferQueue, imageStagingBuffer, image, static_cast<uint32_t>(cubemap.w), static_cast<uint32_t>(cubemap.h), 6);
	transitionImageLayout(newLogicalDevice, transferCommandPool, transferQueue, image, VK_FORMAT_R32G32B32A32_SFLOAT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 6);

	vkDestroyBuffer(newLogicalDevice, imageStagingBuffer, nullptr);
	vkFreeMemory(newLogicalDevice, imageStagingBufferMemory, nullptr);

	cubeMap.image = image;

	VkSamplerCreateInfo samplerInfo{};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;

	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.addressModeV = samplerInfo.addressModeU;
	samplerInfo.addressModeW = samplerInfo.addressModeU;

	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 1.0f;
	samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_NEVER;

	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;

	VkSampler imageSampler;
	VK_CHECK(vkCreateSampler(newLogicalDevice, &samplerInfo, nullptr, &imageSampler));

	cubeMap.sampler = imageSampler;

	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
	viewInfo.format = VK_FORMAT_R32G32B32A32_SFLOAT;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 6;

	VkImageView imageView;
	VK_CHECK(vkCreateImageView(newLogicalDevice, &viewInfo, nullptr, &imageView));

	cubeMap.view = imageView;
}

glm::vec3 CubeMap::FaceCoordsToXYZ(int i, int j, int faceID, int faceSize)
{
	const float A = 2.0f * float(i) / faceSize;
	const float B = 2.0f * float(j) / faceSize;

	if (faceID == 0) return glm::vec3(-1.0f, A - 1.0f, B - 1.0f);
	if (faceID == 1) return glm::vec3(A - 1.0f, -1.0f, 1.0f - B);
	if (faceID == 2) return glm::vec3(1.0f, A - 1.0f, 1.0f - B);
	if (faceID == 3) return glm::vec3(1.0f - A, 1.0f, 1.0f - B);
	if (faceID == 4) return glm::vec3(B - 1.0f, A - 1.0f, 1.0f);
	if (faceID == 5) return glm::vec3(1.0f - B, A - 1.0f, -1.0f);

	return glm::vec3();
}

Bitmap CubeMap::ConvertVerticalCrossToCubeMapFaces(const Bitmap& bp)
{
	const int faceWidth = bp.w / 3;
	const int faceHeight = bp.h / 4;

	Bitmap cubemap(faceWidth, faceHeight, 6, bp.comp, bp.fmt);
	cubemap.type = BitmapType::BitmapTypeCube;

	const uint8_t* src = bp.data.data();
	uint8_t* dst = cubemap.data.data();

	const int pixelSize = (
		cubemap.comp * Bitmap::GetBytesPerComponent(cubemap.fmt)
		);

	for (int face = 0; face != 6; ++face)
	{
		for (int j = 0; j != faceHeight; ++j)
		{
			for (int i = 0; i != faceWidth; ++i)
			{
				int x = 0;
				int y = 0;

				switch (face)
				{
					// POSITIVE_X
				case 0:
					x = i;
					y = faceHeight + j;
					break;

					// NEGATIVE_X
				case 1:
					x = 2 * faceWidth + i;
					y = 1 * faceHeight + j;
					break;

					// POSITIVE_Y
				case 2:
					x = 2 * faceWidth - (i + 1);
					y = 1 * faceHeight - (j + 1);
					break;

					// NEGATIVE_Y
				case 3:
					x = 2 * faceWidth - (i + 1);
					y = 3 * faceHeight - (j + 1);
					break;

					// POSITIVE_Z
				case 4:
					x = 2 * faceWidth - (i + 1);
					y = bp.h - (j + 1);
					break;

					// NEGATIVE_Z
				case 5:
					x = faceWidth + i;
					y = faceHeight + j;
					break;
				}

				memcpy(dst, src + (y * bp.w + x) * pixelSize, pixelSize);

				dst += pixelSize;
			}
		}
	}

	return cubemap;
}

Bitmap CubeMap::ConvertEquirectangularMapToVerticalCross(const Bitmap& bp)
{
	const int faceSize = bp.w / 4;

	const int w = faceSize * 3;
	const int h = faceSize * 4;

	Bitmap result(w, h, bp.comp, bp.fmt);

	const glm::ivec2 kFaceOffsets[] =
	{
	  glm::ivec2(faceSize, faceSize * 3),
		glm::ivec2(0, faceSize),
		glm::ivec2(faceSize, faceSize),
		glm::ivec2(faceSize * 2, faceSize),
		glm::ivec2(faceSize, 0),
		glm::ivec2(faceSize, faceSize * 2)
	};

	const int clampW = bp.w - 1;
	const int clampH = bp.h - 1;

	for (int face = 0; face != 6; face++)
	{
		for (int i = 0; i != faceSize; i++)
		{
			for (int j = 0; j != faceSize; j++)
			{
				const glm::vec3 P = FaceCoordsToXYZ(i, j, face, faceSize);
				const float R = std::hypot(P.x, P.y);
				const float theta = std::atan2(P.y, P.x);
				const float phi = std::atan2(P.z, R);

				const float Uf = float(
					2.0f *
					faceSize *
					(theta + MATH_PI) / MATH_PI
					);
				const float Vf = float(
					2.0f *
					faceSize *
					(MATH_PI / 2.0f - phi) / MATH_PI
					);

				const int U1 = std::clamp(int(std::floor(Uf)), 0, clampW);
				const int V1 = std::clamp(int(std::floor(Vf)), 0, clampH);
				const int U2 = std::clamp(U1 + 1, 0, clampW);
				const int V2 = std::clamp(V1 + 1, 0, clampH);

				const float s = Uf - U1;
				const float t = Vf - V1;

				const glm::vec4 A = bp.GetPixel(U1, V1);
				const glm::vec4 B = bp.GetPixel(U2, V1);
				const glm::vec4 C = bp.GetPixel(U1, V2);
				const glm::vec4 D = bp.GetPixel(U2, V2);

				const glm::vec4 color = (
					A * (1 - s) * (1 - t) +
					B * (s) * (1 - t) +
					C * (1 - s) * t +
					D * (s) * (t)
					);
				result.SetPixel(
					i + kFaceOffsets[face].x, j + kFaceOffsets[face].y, color
				);
			}
		};
	}

	return result;
}