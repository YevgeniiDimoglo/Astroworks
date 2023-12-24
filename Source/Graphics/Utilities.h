#pragma once

// Common headers, functions, structures

#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include <toml.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>

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

#include "../Misc/HighResolutionTimer.h"
#include "../Misc/Math.h";

#include "../Graphics/Texture.h"

#include "../Camera/Camera.h"

#define DISCRETE

static const int MAX_FRAMES_IN_FLIGHT = 2;
static const int MAX_OBJECTS = 2048;

static const uint32_t WIDTH = 1920;
static const uint32_t HEIGHT = 1080;

static const int syncInterval = 0;

enum class ShaderType
{
	Phong,
	PBR,
	PhongDissolve,
	PhongTransparency,
	Flat,
	Sprite,
	Water,
	Fireball,
	OITColorAccum,
	OITColorReveal,
	OITResult,
	EnumCount
};

enum class TextureType
{
	Albedo = 0,
	Normal,
	Metalness,
	Roughness,
	AmbientOcclussion,
	Emissive,
	GlobalTexture1,
	NoiseTexture1,
	NoiseTexture2,
	EnumCount
};

extern Camera* playerCamera;

extern std::vector<ImageBuffer>& getGlobalVector();
extern glm::vec2 BloomValues;

struct PushConstants {
	glm::mat4 model;
	glm::vec4 baseColor;
	glm::vec4 timer;
	glm::vec4 additionalValues;
};

struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
	alignas(16) glm::mat4 lightMVP;
	alignas(16) glm::vec4 lightDirection;
	alignas(16) glm::vec4 lightColor;

	alignas(16) glm::vec4 cameraPosition;

	alignas(16) glm::vec4 timeConstants;
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

	std::string controller;
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