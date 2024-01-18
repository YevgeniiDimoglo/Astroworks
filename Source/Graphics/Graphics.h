#pragma once

// All rendering

#include "Utilities.h"
#include "Macros.h"

// - Vulkan structs
struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value();
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

private:
	// - Main functions
	void initWindow();

	void initTextures();

	void initModels();

	void initSprites();

	void initLights();

	void initVulkan();

	void InitResources();

	void drawFrame(HighResolutionTimer timer, float elapsedTime);

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
	void createDescriptorSetLayout();
	void createGraphicsPipelines();
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createCommandPool();
	void createaDepthResources();
	void createUniformBuffers();
	void createDescriptorPool();
	void createDescriptorSets();
	void createCommandBuffers();
	void createSyncObjects();

	void recreateSwapChain();

	// -- Record & Update Functions

	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, HighResolutionTimer timer);
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
	// - GLFW members
	GLFWwindow* window;

	// - Vulkan members
	VkInstance instance;

	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;

	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkSurfaceKHR surface;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	std::vector<VkPipelineLayout> pipelineLayouts;
	VkPhysicalDeviceDynamicRenderingFeaturesKHR dynamicRenderingFeaturesKHR{};
	VkRenderPass renderPass = VK_NULL_HANDLE;
	std::vector<VkPipeline> graphicsPipelines;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	VkDescriptorPool descriptorPool;
	VkDescriptorSetLayout descriptorSetLayout;
	std::vector<VkDescriptorSet> descriptorSets;

	VkDescriptorPool samplerDescriptorPool;
	VkDescriptorSetLayout samplerSetLayout;

	VkDescriptorPool dynamicTextureSamplerDescriptorPool;
	VkDescriptorSetLayout dynamicTextureSamplerSetLayout;

	VkDescriptorPool OITDescriptorPool;
	VkDescriptorSetLayout OITDescriptorSetLayout;
	VkDescriptorSet OITDescriptor;

	VkDescriptorPool postEffectPool;
	VkDescriptorSetLayout postEffectSetLayout;

	Offscreen FinalTexture;
	Offscreen Luminance;
	Offscreen Blur;
	Offscreen OITColorAccum;
	Offscreen OITColorReveal;
	Offscreen OITResult;
	Offscreen offscreen;

	CubeMap skybox;
	CubeMap skyboxIrr;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	VkFormat depthFormat;
	VkSampler depthSampler;

	std::vector<std::unique_ptr<Light>> sceneLights;

	uint32_t currentFrame = 0;
	bool framebufferResized = false;
};