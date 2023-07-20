#pragma once

// Common headers, functions, structures

#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include <toml.hpp>

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <stb_image.h>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <utility>
#include <limits>
#include <optional>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <list>
#include <unordered_map>

#define DISCRETE

static const int MAX_FRAMES_IN_FLIGHT = 2;
static const int MAX_OBJECTS = 2048;
static const int DUMMIES = 1;

static const uint32_t WIDTH = 800;
static const uint32_t HEIGHT = 600;

static const int syncInterval = 0;

enum class ShaderType
{
	Phong,
	PhongTransparency,
	PhongDissolve,
	Sprite,

	EnumCount
};

struct PushConstants {
	glm::mat4 model;
	glm::vec4 baseColor;
};

struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
	alignas(16) glm::vec4 lightDirection;
	alignas(16) glm::vec4 lightColor;
	alignas(16) glm::vec4 cameraPosition;
};

struct ActorOnScreen
{
	std::string name;

	glm::vec3 position = { 0, 0, 0 };
	glm::quat rotation = { 0, 0, 0, 1 };
	glm::vec3 euler = { 0,0,0 };
	glm::vec3 scale = { 1, 1, 1 };

	std::string filePath;

	std::string type;
	std::string typeName;
};

class IObserver {
public:
	virtual ~IObserver() {};
	virtual void notify(std::string name, int action) = 0;
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

static const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
};

static const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME,
		VK_KHR_MAINTENANCE2_EXTENSION_NAME,
		VK_KHR_MULTIVIEW_EXTENSION_NAME,
		VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME,
		VK_KHR_DEPTH_STENCIL_RESOLVE_EXTENSION_NAME
};

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
};

static bool hasStencilComponent(VkFormat format)
{
	return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

static uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties))
		{
			return i;
		}
	}

	throw std::runtime_error("Failed to find suitable memory type");
};

static void createBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create vertex buffer");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate vertex buffer memory");
	}

	vkBindBufferMemory(device, buffer, bufferMemory, 0);
};

static VkCommandBuffer beginSingleTimeCommands(VkDevice device, VkCommandPool commandPool)
{
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	return commandBuffer;
};

static void endSingleTimeCommands(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkCommandBuffer commandBuffer)
{
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(graphicsQueue);

	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
};

static void copyBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(device, commandPool);

	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = 0;
	copyRegion.dstOffset = 0;
	copyRegion.size = size;

	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	endSingleTimeCommands(device, commandPool, graphicsQueue, commandBuffer);
};

static void createImage(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory)
{
	VkImageCreateInfo imageInfo{};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = usage;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.flags = 0;

	if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create image");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(device, image, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate image memory");
	}

	vkBindImageMemory(device, image, imageMemory, 0);
};

static VkImage createImage(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkDeviceMemory& imageMemory)
{
	VkImageCreateInfo imageInfo{};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = usage;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.flags = 0;

	VkImage image;
	if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create image");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(device, image, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate image memory");
	}

	vkBindImageMemory(device, image, imageMemory, 0);

	return image;
};

static VkImageView createImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFalgs)
{
	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = aspectFalgs;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;
	if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create texture image view");
	}

	return imageView;
}

static void copyBufferToImage(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(device, commandPool);

	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;

	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = { width, height, 1 };

	vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	endSingleTimeCommands(device, commandPool, graphicsQueue, commandBuffer);
}

static void transitionImageLayout(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(device, commandPool);

	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
	{
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

		if (hasStencilComponent(format))
		{
			barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
		}
	}
	else
	{
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	}

	if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
	{
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
	{
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
	{
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	}
	else
	{
		throw std::invalid_argument("Unsupported layout transition");
	}

	vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

	endSingleTimeCommands(device, commandPool, graphicsQueue, commandBuffer);
};

static float Lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}

static float RandomRange(float min, float max)
{
	return min + (max - min) * (rand() / static_cast<float>(RAND_MAX));
}
