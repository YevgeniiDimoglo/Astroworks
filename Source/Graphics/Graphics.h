#pragma once

// All rendering
#include "Utilities.h"

#include "Texture.h"
#include "Light.h"
#include "Particle.h"

#include "../Camera/Camera.h"

// - Vulkan structs
struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsAndComputeFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsAndComputeFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class Graphics
{
public:
	Graphics() {}
	~Graphics() {}

	Graphics(const Graphics&) = delete;
	Graphics& operator =(const Graphics&) = delete;

public:

	void init();

	void draw(HighResolutionTimer timer, float elapsedTime);

	void update(HighResolutionTimer timer, float elapsedTime, Camera* camera);

	void finalize();

	GLFWwindow* getWindow() const { return window; }
	VkExtent2D getExtent() const { return swapChainExtent; }

	bool drawUI = true;
	bool wireframe = false;

private:
	// - Main functions
	// -- Init functions

	void initWindow();

	void initTextures();

	void initModels();

	void initSprites();

	void initLights();

	void initVulkan();

	void InitResources();

	// -- Draw functions
	void drawFrame(HighResolutionTimer timer, float elapsedTime);

	// -- Cleanup functions
	void cleanup();

private:
	// - Vulkan Setup
	//
	// -- Create Functions
	void createInstance();
	void createSurface();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createBottomLevelAccelerationStructure();
	void createTopLevelAccelerationStructure();
	void createDescriptorSetLayout();
	void createComputeDescriptorSetLayout();
	void createRayTracingDescriptorSetLayout();
	void createGraphicsPipelines();
	void createComputePipeline();
	void createRayTracingPipeline();
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createCommandPool();
	void createaDepthResources();
	void createShaderStorageBuffers();
	void createUniformBuffers();
	void createDescriptorPool();
	void createComputeDescriptorSets();
	void createDescriptorSets();
	void createCommandBuffers();
	void createComputeCommandBuffers();
	void createSyncObjects();

	void recreateSwapChain();

	// -- Record & Update Functions

	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, HighResolutionTimer timer);
	void recordComputeCommandBuffer(VkCommandBuffer computeCommandBuffer, HighResolutionTimer timer);
	void updateUniformBuffer(HighResolutionTimer timer, float elapsedTime, uint32_t currentImage, Camera* camera);

	// -- Prepare Functions

	void prepareOffscreen();
	void prepareFinalTexture();
	void prepareOITColorAccum();
	void prepareOITColorReveal();
	void prepareOITResult();
	void prepareLuminance();
	void prepareBlur();

	// -- Cleanup Function

	void cleanupSwapChain();

	// -- Check Functions
	void checkAvailableExtensions();
	bool checkValidationLayerSupport();
	bool checkDeviceExtensionsSupport(VkPhysicalDevice device);

	// -- Helper Functions
	std::vector<const char*> getRequiredExtensions();
	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSampleCountFlagBits getMaxUsableSampleCount();
	static std::vector<char> readFile(const std::string& filename);

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto app = reinterpret_cast<Graphics*>(glfwGetWindowUserPointer(window));
		app->framebufferResized = true;
	};

	// -- Choose Functions
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	// --- Debug Helpers
	void populateDebugMessengerCreateInfo(
		VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger);
	static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator);

private:
	// - GLFW variables
	GLFWwindow* window;

	// - Vulkan variables
	VkInstance instance;

	// - Debug varuables
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;

	// - Device varialbes
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkSurfaceKHR surface;
	VkDevice device;

	// - Queue variables
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkQueue computeQueue;

	// - Swapchain variables
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	// - Pipeline variables
	// -- Graphics pipeline variables
	std::vector<VkPipelineLayout> pipelineLayouts;
	VkPhysicalDeviceDynamicRenderingFeaturesKHR dynamicRenderingFeaturesKHR{};
	VkRenderPass renderPass = VK_NULL_HANDLE;
	std::vector<VkPipeline> graphicsPipelines;

	// -- Computer pipeline variables
	VkPipelineLayout computePipelineLayout;
	VkPipeline computePipeline;

	VkPipelineLayout rayTracingPipelineLayout;
	VkPipeline rayTracingPipeline;

	VkDescriptorPool rayTracingDescriptorPool;
	VkDescriptorSetLayout rayTracingDescriptorSetLayout;
	std::vector<VkDescriptorSet> rayTracingDescriptorSets;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkCommandBuffer> computeCommandBuffers;

	// - Syncronization variables
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkSemaphore> computeFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> computeInFlightFences;

	// - Buffer variables
	// -- Uniform buffer variables
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	// -- Computer buffer variables
	std::vector<VkBuffer> shaderStorageBuffers;
	std::vector<VkDeviceMemory> shaderStorageBuffersMemory;

	// - Descroptor variables
	// - Uniform descriptor variables
	VkDescriptorPool descriptorPool;
	VkDescriptorSetLayout descriptorSetLayout;
	std::vector<VkDescriptorSet> descriptorSets;

	// - Texture descriptor variables
	VkDescriptorPool samplerDescriptorPool;
	VkDescriptorSetLayout samplerSetLayout;

	// - Default descriptor variables
	VkDescriptorPool dynamicTextureSamplerDescriptorPool;
	VkDescriptorSetLayout dynamicTextureSamplerSetLayout;

	// - Transparency descriptor variables
	VkDescriptorPool OITDescriptorPool;
	VkDescriptorSetLayout OITDescriptorSetLayout;
	VkDescriptorSet OITDescriptor;

	// - Postprocess descriptor varialbes
	VkDescriptorPool postEffectPool;
	VkDescriptorSetLayout postEffectSetLayout;

	// - Computer descriptor variables
	VkDescriptorPool computeDescriptorPool;
	VkDescriptorSetLayout computeDescriptorSetLayout;
	std::vector<VkDescriptorSet> computeDescriptorSets;

	// - Custom framebuffers
	Framebuffer FinalTexture;
	Framebuffer Luminance;
	Framebuffer Blur;
	Framebuffer OITColorAccum;
	Framebuffer OITColorReveal;
	Framebuffer OITResult;
	Framebuffer offscreen;

	// - Cubemap variables
	CubeMap skybox;
	CubeMap skyboxIrr;

	// - Depth variables
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	VkFormat depthFormat;
	VkSampler depthSampler;

	// - Scene lights
	std::vector<std::unique_ptr<Light>> sceneLights;

	// - Logic variables
	uint32_t currentFrame = 0;
	bool framebufferResized = false;
	bool isTransparentRender = false;
	bool isParticleRender = false;

	// RayTrace members
	PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
	PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
	PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
	PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
	PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
	PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
	PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
	PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
	PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
	PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;

	VkPhysicalDeviceRayTracingPipelinePropertiesKHR  rayTracingPipelineProperties{};
	VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures{};

	VkPhysicalDeviceBufferDeviceAddressFeatures enabledBufferDeviceAddresFeatures{};
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR enabledRayTracingPipelineFeatures{};
	VkPhysicalDeviceAccelerationStructureFeaturesKHR enabledAccelerationStructureFeatures{};

	AccelerationStructure bottomLevelAS{};
	AccelerationStructure topLevelAS{};

	std::vector<VkRayTracingShaderGroupCreateInfoKHR> shaderGroups{};

	uint32_t indexCount;
};