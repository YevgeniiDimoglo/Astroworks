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

#include "Macros.h"

#define DISCRETE

static const int MAX_FRAMES_IN_FLIGHT = 2;
static const int MAX_OBJECTS = 512;

static const uint32_t PARTICLE_COUNT = 256;

static const uint32_t WIDTH = 1920;
static const uint32_t HEIGHT = 1080;

static const int syncInterval = 0;

enum class Pipelines
{
	ShadowMapPipeline,

	DebugDrawingPipeline,

	UnlitPipeline,
	PhongPipeline,
	PBRPipeline,
	PBRIBLPipeline,

	UIPipeline,

	OffscreenPipeline,
	OffscreenPipeline2,

	OITColorAccumPipeline,
	OITColorRevealPipeline,
	OITResultPipeline,
	DemoOITColorAccumPipeline,
	DemoOITColorRevealPipeline,
	DemoOITResultPipeline,

	SkyboxPipeline,

	LuminancePipeline,
	BlurPipeline,

	WaterPipeline,
	FirePipeline,

	ComputeParticlePipeline,

	EnumCount
};

enum class ShaderType
{
	Unlit,
	Flat,
	Phong,
	PBR,
	PBRIBL,

	OITColorAccum,
	OITColorReveal,
	OITResult,

	Skybox,

	Sprite,

	Water,
	Fireball,

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

	LUT,

	GlobalTexture1,
	NoiseTexture1,
	NoiseTexture2,

	EnumCount
};

struct ImageBuffer
{
	VkImage					image;
	VkImageLayout			imageLayout;
	VkDeviceMemory			deviceMemory;
	VkImageView				view;
	uint32_t				width, height;
	VkDescriptorImageInfo	descriptor;
	VkSampler				sampler;
	VkDescriptorSet			descriptorSet;
};

struct FrameBufferAttachment {
	VkImage image;
	VkDeviceMemory mem;
	VkImageView view;
};

struct Framebuffer
{
	int32_t width, height;
	FrameBufferAttachment offscreenColorAttachment, offscreenDepthAttachment;
	VkSampler sampler;
	VkDescriptorImageInfo descriptor;
	VkDescriptorSet			descriptorSet;
};

extern std::vector<ImageBuffer>& getTexturesVector();
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

	std::string domain;
	std::string shader;

	std::string controller;
};

enum class CursorMode
{
	Normal = 0,
	Hidden = 1,
	Locked = 2
};

enum class KeyState
{
	None = -1,
	Pressed,
	Held,
	Released
};

enum class MouseButton
{
	Left = 0,
	Right = 1,
	Middle = 2
};

enum class KeyCode
{
	Escape = 0,
	Enter = 1,
	Space = 2,
	Tab = 3,
	Backspace = 4,
	Left = 5,
	Right = 6,
	Up = 7,
	Down = 8,
	LeftShift = 9,
	D0 = 10,
	D1 = 11,
	D2 = 12,
	D3 = 13,
	D4 = 14,
	D5 = 15,
	D6 = 16,
	D7 = 17,
	D8 = 18,
	D9 = 19,
	LeftAlt = 20,
	F1 = 21,
	F2 = 22,
	F3 = 23,
	F4 = 24,
	F5 = 25,
	F6 = 26,
	F7 = 27,
	F8 = 28,
	F9 = 29,
	F10 = 30,
	F11 = 31,
	F12 = 32,
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