#include "Graphics.h"

#include "../UI/UI.h"
#include "../Actor/Actor.h"

Camera* playerCamera;

void Graphics::init()
{
	LOG("Start of initializaion\n");

	initWindow();

	initVulkan();

	LOG("End of initialization\n");
}

void Graphics::draw(HighResolutionTimer timer, float elapsedTime)
{
	// Draw whole frame
	drawFrame(timer, elapsedTime);
}

void Graphics::finalize()
{
	// Clean up all vulkan relates recources
	cleanup();
}

void Graphics::initWindow()
{
	LOG("Initializaon of Window\n");
	// TODO: Remove from graphics to own class
	// Init library for handling window
	glfwInit();

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	window = glfwCreateWindow(mode->width, mode->height, "Vulkan", nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void Graphics::initTextures()
{
	LOG("Initialization of Textures\n");

	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/Dummy.png"));
	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/DummyNormal.png"));
	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/DummyMetalness.png"));
	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/DummyRoughness.png"));
	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/DummyAO.png"));
	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/DummyEmissive.png"));

	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/HDRI/lut_ggx.png"));

	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/Fire_alpha.png"));

	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/TextureNoise.png"));
	getTexturesVector().push_back(createTexture(physicalDevice, device, commandPool, graphicsQueue, dynamicTextureSamplerDescriptorPool, dynamicTextureSamplerSetLayout, "./Data/Textures/TextureNoise2.png"));

	skybox.CreateCubeMap(physicalDevice, device, commandPool, graphicsQueue, "./Data/HDRI/puresky.hdr");
	skyboxIrr.CreateCubeMap(physicalDevice, device, commandPool, graphicsQueue, "./Data/HDRI/pureskyirr2.hdr");
}

void Graphics::initModels()
{
	LOG("Initialization of Models\n");
	// TODO: Change loading to loading on a fly
	ActorManager::Instance().loadFiles(physicalDevice, device, graphicsQueue, commandPool, samplerDescriptorPool, samplerSetLayout);
}

void Graphics::initSprites()
{
	LOG("Initialization of Sprites\n");
	// TODO: Change loading to loading on a fly
	UI::Instance().loadFiles(physicalDevice, device, graphicsQueue, commandPool, samplerDescriptorPool, samplerSetLayout);
}

void Graphics::initLights()
{
	std::unique_ptr<Light> sun = std::make_unique<DirectionalLight>();
	static_cast<DirectionalLight*>(sun.get())->InitLight(1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		10.0f, 15.0f, 12.0f,
		120.0f, 100.0f, -0.5f, 0.5f);
	sceneLights.push_back(std::move(sun));
}

void Graphics::initVulkan()
{
	LOG("Initialization of Vulkan\n");
	// Instance for whole application
	createInstance();
	LOG("Instance created successfully\n");
	// Debug messages in console
	setupDebugMessenger();
	LOG("DebugMessenger created successfully\n");
	// Drawing canvas for rendering
	createSurface();
	LOG("Surface created successfully\n");
	// Setup best suitable device
	pickPhysicalDevice();
	LOG("PhysicalDevice found successfully\n");
	// Interface for physical device
	createLogicalDevice();
	LOG("LogicalDevice created successfully\n");
	// Create swapchain
	createSwapChain();
	LOG("Spawchain created successfully\n");
	// Create image for rendering
	createImageViews();
	LOG("ImageViews created successfully\n");
	// Create input layout
	createDescriptorSetLayout();
	LOG("DescriptorLayouts created successfully\n");
	// Create compute input layout
	createComputeDescriptorSetLayout();
	LOG("Compute DescriptorLayouts created successfully\n");
	// Create pipelines for different rendering
	createGraphicsPipelines();
	LOG("GraphicsPipelines created successfully\n");
	// Create compute pipelines
	createComputePipeline();
	LOG("ComputePipelines created successfully\n");
	// Create pools for commands
	createCommandPool();
	LOG("CommandPool created successfully\n");
	// Create image for depth
	createaDepthResources();
	LOG("DepthResources created successfully\n");
	// Create storage buffers
	createShaderStorageBuffers();
	LOG("StorageBuffers created successfully\n");
	// Create uniform buffers
	createUniformBuffers();
	LOG("UniformBuffers created successfully\n");
	// Create description for descriptors
	createDescriptorPool();
	LOG("DescriptoPools created successfully\n");
	// Create descriptors
	////
	InitResources();
	LOG("Resources created successfully\n");
	createDescriptorSets();
	LOG("DescriptorSets created successfully\n");
	// Create compute descriptors
	createComputeDescriptorSets();
	LOG("Compute DescriptorSets created successfully\n");
	// Create offscreen buffers
	LOG("OffscreenBuffer created successfully\n");
	prepareOITColorAccum();
	prepareOITColorReveal();
	LOG("OIT buffers created successfully\n");
	prepareFinalTexture();
	LOG("Final Texture created successfully\n");
	prepareOITResult();
	LOG("OIT Result created successfully\n");
	prepareLuminance();
	LOG("Prerare offscreen texture\n");
	prepareBlur();
	LOG("Prerare offscreen texture\n");
	prepareOffscreen();
	LOG("Prerare offscreen texture\n");
	// Create command buffers for commands
	createCommandBuffers();
	LOG("CommandBuffers created successfully\n");
	// Create compute command buffers for commands
	createComputeCommandBuffers();
	LOG("Compute CommandBuffers created successfully\n");
	// Create synchronisation on GPU side
	createSyncObjects();
	LOG("SyncronizationObjects created successfully\n");
}

void Graphics::InitResources()
{
	initTextures();

	initModels();

	initSprites();

	initLights();
}

void Graphics::drawFrame(HighResolutionTimer timer, float elapsedTime)
{
	//// Compute
	vkWaitForFences(device, 1, &computeInFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

	vkResetFences(device, 1, &computeInFlightFences[currentFrame]);

	vkResetCommandBuffer(computeCommandBuffers[currentFrame], 0);
	recordComputeCommandBuffer(computeCommandBuffers[currentFrame], timer);

	VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;

	VkSubmitInfo computeSubmintInfo{};
	computeSubmintInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	computeSubmintInfo.commandBufferCount = 1;
	computeSubmintInfo.pCommandBuffers = &computeCommandBuffers[currentFrame];
	computeSubmintInfo.pWaitDstStageMask = &waitStageMask;
	computeSubmintInfo.signalSemaphoreCount = 1;
	computeSubmintInfo.pSignalSemaphores = &computeFinishedSemaphores[currentFrame];

	if (vkQueueSubmit(computeQueue, 1, &computeSubmintInfo, computeInFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit compute command buffer!");
	};

	//// Graphics
	// Wait for given fence to signal (open) from last draw before continuing
	vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

	// Get index of next image to be drawn to, and signal semaphore when ready to be drawn to
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		recreateSwapChain();

		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		throw std::runtime_error("Failed to acquire swap chain image");
	}

	vkResetFences(device, 1, &inFlightFences[currentFrame]);

	// Clean comand buffer for next frame information
	vkResetCommandBuffer(commandBuffers[currentFrame], 0);
	// Record all drawing commands
	recordCommandBuffer(commandBuffers[currentFrame], imageIndex, timer);

	// Submit command buffer to queue for exec, making sure it waits for one image to be signalled as available before drawing and signals when it has finished rendering
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	VkSemaphore waitSemaphores[] = { computeFinishedSemaphores[currentFrame], imageAvailableSemaphores[currentFrame] };
	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	submitInfo.waitSemaphoreCount = 2;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[currentFrame];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to submit draw command buffer");
	}

	//Present image to screen when it has signaled finished rendering
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;

	result = vkQueuePresentKHR(presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized)
	{
		framebufferResized = false;
		recreateSwapChain();
	}
	else if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to present swap chain image");
	}

	// Get next frame
	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Graphics::update(HighResolutionTimer timer, float elapsedTime, Camera* camera)
{
	ActorManager::Instance().loadFiles(physicalDevice, device, graphicsQueue, commandPool, samplerDescriptorPool, samplerSetLayout);

	playerCamera = camera;

	// Update camera values in shader
	updateUniformBuffer(timer, elapsedTime, currentFrame, camera);
}

void Graphics::cleanup()
{
	vkDeviceWaitIdle(device);

	cleanupSwapChain();

	vkDestroyImageView(device, depthImageView, nullptr);
	vkDestroyImage(device, depthImage, nullptr);
	vkFreeMemory(device, depthImageMemory, nullptr);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroyBuffer(device, uniformBuffers[i], nullptr);
		vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
	}

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroyBuffer(device, shaderStorageBuffers[i], nullptr);
		vkFreeMemory(device, shaderStorageBuffersMemory[i], nullptr);
	}

	ActorManager::Instance().cleanup(device);

	UI::Instance().cleanup(device);

	vkDestroyImageView(device, skybox.cubeMap.view, nullptr);
	vkDestroyImage(device, skybox.cubeMap.image, nullptr);
	vkFreeMemory(device, skybox.cubeMap.deviceMemory, nullptr);

	vkDestroyImageView(device, skyboxIrr.cubeMap.view, nullptr);
	vkDestroyImage(device, skyboxIrr.cubeMap.image, nullptr);
	vkFreeMemory(device, skyboxIrr.cubeMap.deviceMemory, nullptr);

	for (auto it : getTexturesVector())
	{
		vkDestroyImageView(device, it.view, nullptr);
		vkDestroyImage(device, it.image, nullptr);
		vkFreeMemory(device, it.deviceMemory, nullptr);
		vkDestroySampler(device, it.sampler, nullptr);
	}

	vkDestroySampler(device, skyboxIrr.cubeMap.sampler, nullptr);
	vkDestroySampler(device, skybox.cubeMap.sampler, nullptr);
	vkDestroySampler(device, offscreen.sampler, nullptr);
	vkDestroySampler(device, Luminance.sampler, nullptr);
	vkDestroySampler(device, Blur.sampler, nullptr);
	vkDestroySampler(device, OITColorAccum.sampler, nullptr);
	vkDestroySampler(device, OITColorReveal.sampler, nullptr);
	vkDestroySampler(device, OITResult.sampler, nullptr);
	vkDestroySampler(device, FinalTexture.sampler, nullptr);
	vkDestroySampler(device, depthSampler, nullptr);

	vkDestroyDescriptorPool(device, descriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

	vkDestroyDescriptorPool(device, dynamicTextureSamplerDescriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(device, dynamicTextureSamplerSetLayout, nullptr);

	vkDestroyDescriptorPool(device, samplerDescriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(device, samplerSetLayout, nullptr);

	vkDestroyDescriptorPool(device, OITDescriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(device, OITDescriptorSetLayout, nullptr);

	vkDestroyDescriptorPool(device, postEffectPool, nullptr);
	vkDestroyDescriptorSetLayout(device, postEffectSetLayout, nullptr);

	vkDestroyDescriptorPool(device, computeDescriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(device, computeDescriptorSetLayout, nullptr);

	for (Pipelines pipelineName = static_cast<Pipelines>(0);
		pipelineName != Pipelines::EnumCount;
		pipelineName = static_cast<Pipelines>(static_cast<int>(pipelineName) + 1))
	{
		vkDestroyPipeline(device, graphicsPipelines[static_cast<int>(pipelineName)], nullptr);
		vkDestroyPipelineLayout(device, pipelineLayouts[static_cast<int>(pipelineName)], nullptr);
	}

	vkDestroyPipeline(device, computePipeline, nullptr);
	vkDestroyPipelineLayout(device, computePipelineLayout, nullptr);

	vkFreeCommandBuffers(device, commandPool, 1, computeCommandBuffers.data());
	vkFreeCommandBuffers(device, commandPool, 1, commandBuffers.data());

	vkDestroyCommandPool(device, commandPool, nullptr);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
		vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(device, computeFinishedSemaphores[i], nullptr);

		vkDestroyFence(device, inFlightFences[i], nullptr);
		vkDestroyFence(device, computeInFlightFences[i], nullptr);
	}

	vkDestroyDevice(device, nullptr);

	if (enableValidationLayers)
	{
		DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}

	vkDestroySurfaceKHR(instance, surface, nullptr);

	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
}

void Graphics::createInstance()
{
	// --- Check for validation layers (aka debug info)
	if (enableValidationLayers && !checkValidationLayerSupport())
	{
		throw std::runtime_error("Validation layers requested, but not available");
	}

	// Information about the application itself
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "RTSRevenge";
	appInfo.applicationVersion = VK_MAKE_API_VERSION(1, 3, 243, 0);
	appInfo.pEngineName = "ReVE";
	appInfo.engineVersion = VK_MAKE_API_VERSION(1, 3, 243, 0);
	appInfo.apiVersion = VK_API_VERSION_1_3;

	// Creation information for a VkInstance (Vulkan Instance)
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	checkAvailableExtensions();

	// Set up extensions Instance will use
	std::vector<const char*> extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	// --- Enable validation layers
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else
	{
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
	}

	// Create instance
	VK_CHECK(vkCreateInstance(&createInfo, nullptr, &instance));
}

void Graphics::createSurface()
{
	// Create a surface ( creating a surface, create info struct, runs the create surface function, returns result)
	VK_CHECK(glfwCreateWindowSurface(instance, window, nullptr, &surface));
}

void Graphics::createLogicalDevice()
{
	// Get the queue family indices for the chosen Physical Device
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	// Vector for queue creation information, and set for family indices
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsAndComputeFamily.value(),
	indices.presentFamily.value() };

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		// Queues the logical device needs to create and info to do so
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	// Physical Device Feature the Logical Device will be using
	VkPhysicalDeviceFeatures deviceFeatures{};
	deviceFeatures.samplerAnisotropy = VK_TRUE;
	deviceFeatures.fillModeNonSolid = VK_TRUE;

	// Information to create logical device
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pNext = &dynamicRenderingFeaturesKHR;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	// Create the logical device for the given physical device
	VK_CHECK(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device));
	// From given logical devices, of given	Queue Family, of given Queue Index , place reference in given VkQueue
	vkGetDeviceQueue(device, indices.graphicsAndComputeFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.graphicsAndComputeFamily.value(), 0, &computeQueue);
	vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}

void Graphics::createSwapChain()
{
	// Get Swap Chain details so we can pick best settings
	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

	// Find optimal surface values for our swap chain
	// Choose best surface format
	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	// Choose best presentation mode
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	// Choose swap chain image resolution
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	// How many images are in the swap chain
	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

	// If imageCount higher than max, then clamp down to max
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
	{
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	// Creation information for swap chain
	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;

	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	// Get Queue Family Indices
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	uint32_t queueFamilyIndices[] = { indices.graphicsAndComputeFamily.value(), indices.presentFamily.value() };

	// If Graphics and Presentation	families are different, then swapchain must	let images be shared between families
	if (indices.graphicsAndComputeFamily != indices.presentFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;

	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;

	// If old swapchain been destroyed and this one replace it, then link old one to quickly hand over responsibilities
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	// Create Swapchain
	VK_CHECK(vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain));

	// Get Swapchain images (first count, then values)
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;
}

void Graphics::createImageViews()
{
	swapChainImageViews.resize(swapChainImages.size());

	for (uint32_t i = 0; i < swapChainImages.size(); i++)
	{
		swapChainImageViews[i] = createImageView(device, swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
	}
}

void Graphics::createDescriptorSetLayout()
{
	// Uniform values descriptor set layout
	// UboViewProjection Binding Info
	std::vector<VkDescriptorSetLayoutBinding> uboLayoutBindings = {
				{ 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr},
				{ 3, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr},
				{ 4, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr},
	};

	// Create Descriptor Set Layout
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(uboLayoutBindings.size());
	layoutInfo.pBindings = uboLayoutBindings.data();

	VK_CHECK(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout));

	////////

	std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
				{ 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 3, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 4, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 5, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 6, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
	};

	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
	descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutCreateInfo.pBindings = setLayoutBindings.data();
	descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(setLayoutBindings.size());

	VK_CHECK(vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &samplerSetLayout));

	////////

	VkDescriptorSetLayoutBinding dissolveSamplerLayoutBinding{};

	// Create texture sampler descriptor set layout
	// Texture binding info
	dissolveSamplerLayoutBinding.binding = 0;
	dissolveSamplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	dissolveSamplerLayoutBinding.descriptorCount = 1;
	dissolveSamplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
	dissolveSamplerLayoutBinding.pImmutableSamplers = nullptr;

	// Create a descriptor set layout with given binding for texture
	VkDescriptorSetLayoutCreateInfo dissolveTextureLayoutCreateInfo = {};
	dissolveTextureLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	dissolveTextureLayoutCreateInfo.bindingCount = 1;
	dissolveTextureLayoutCreateInfo.pBindings = &dissolveSamplerLayoutBinding;

	// Create Descriptor set layout
	VK_CHECK(vkCreateDescriptorSetLayout(device, &dissolveTextureLayoutCreateInfo, nullptr, &dynamicTextureSamplerSetLayout));

	////////

	std::vector<VkDescriptorSetLayoutBinding> OITLayoutBindings = {
				{ 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
	};

	VkDescriptorSetLayoutCreateInfo OITdescriptorSetLayoutCreateInfo{};
	OITdescriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	OITdescriptorSetLayoutCreateInfo.pBindings = setLayoutBindings.data();
	OITdescriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(setLayoutBindings.size());

	VK_CHECK(vkCreateDescriptorSetLayout(device, &OITdescriptorSetLayoutCreateInfo, nullptr, &OITDescriptorSetLayout));

	////////

	std::vector<VkDescriptorSetLayoutBinding> postEffectSetLayoutBindings = {
				{ 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
				{ 1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
	};

	VkDescriptorSetLayoutCreateInfo postEffectSetLayoutCreateInfo{};
	postEffectSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	postEffectSetLayoutCreateInfo.pBindings = postEffectSetLayoutBindings.data();
	postEffectSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(postEffectSetLayoutBindings.size());

	VK_CHECK(vkCreateDescriptorSetLayout(device, &postEffectSetLayoutCreateInfo, nullptr, &postEffectSetLayout));
}

void Graphics::createComputeDescriptorSetLayout()
{
	std::array<VkDescriptorSetLayoutBinding, 3> layoutBindings{};
	layoutBindings[0].binding = 0;
	layoutBindings[0].descriptorCount = 1;
	layoutBindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	layoutBindings[0].pImmutableSamplers = nullptr;
	layoutBindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

	layoutBindings[1].binding = 1;
	layoutBindings[1].descriptorCount = 1;
	layoutBindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	layoutBindings[1].pImmutableSamplers = nullptr;
	layoutBindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

	layoutBindings[2].binding = 2;
	layoutBindings[2].descriptorCount = 1;
	layoutBindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	layoutBindings[2].pImmutableSamplers = nullptr;
	layoutBindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 3;
	layoutInfo.pBindings = layoutBindings.data();

	VK_CHECK(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &computeDescriptorSetLayout));
}

void Graphics::createGraphicsPipelines()
{
	graphicsPipelines.resize(static_cast<int>(Pipelines::EnumCount));
	pipelineLayouts.resize(static_cast<int>(Pipelines::EnumCount));

	for (Pipelines pipelineName = static_cast<Pipelines>(0);
		pipelineName != Pipelines::EnumCount;
		pipelineName = static_cast<Pipelines>(static_cast<int>(pipelineName) + 1))
	{
		// -- Pipeline constants

		// - Shaders
		std::vector<char> vertShaderCode;
		std::vector<char> fragShaderCode;

		// - Rasetrizer
		VkCullModeFlagBits cullingFlag = VK_CULL_MODE_BACK_BIT;
		VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;

		// - DepthStencil
		auto depthWrite = VK_TRUE;
		auto depthTest = VK_TRUE;

		// - ColorAttachment
		VkFormat pipelineColorAttachmentFormat = swapChainImageFormat;

		// - Blend Mode
		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

		switch (pipelineName)
		{
		case Pipelines::ShadowMapPipeline:
			vertShaderCode = readFile("./Shaders/shadowMapCasterVS.spv");
			fragShaderCode = readFile("./Shaders/shadowMapCasterPS.spv");
			break;
		case Pipelines::DebugDrawingPipeline:
			vertShaderCode = readFile("./Shaders/flatVS.spv");
			fragShaderCode = readFile("./Shaders/flatPS.spv");
			polygonMode = VK_POLYGON_MODE_LINE;
			break;
		case Pipelines::UnlitPipeline:
			vertShaderCode = readFile("./Shaders/flatVS.spv");
			fragShaderCode = readFile("./Shaders/flatPS.spv");
			break;
		case Pipelines::PhongPipeline:
			vertShaderCode = readFile("./Shaders/phongVS.spv");
			fragShaderCode = readFile("./Shaders/phongPS.spv");
			break;
		case Pipelines::PBRPipeline:
			vertShaderCode = readFile("./Shaders/PBRVS.spv");
			fragShaderCode = readFile("./Shaders/PBROnlyPS.spv");
			break;
		case Pipelines::PBRIBLPipeline:
			vertShaderCode = readFile("./Shaders/PBRVS.spv");
			fragShaderCode = readFile("./Shaders/PBRIBLPS.spv");
			break;
		case Pipelines::UIPipeline:
			vertShaderCode = readFile("./Shaders/spriteVS.spv");
			fragShaderCode = readFile("./Shaders/spritePS.spv");

			cullingFlag = VK_CULL_MODE_NONE;
			depthTest = VK_FALSE;
			break;
		case Pipelines::OffscreenPipeline:
			vertShaderCode = readFile("./Shaders/postEffectVS.spv");
			fragShaderCode = readFile("./Shaders/postEffectPS.spv");

			cullingFlag = VK_CULL_MODE_NONE;
			colorBlendAttachment.blendEnable = VK_FALSE;
			break;
		case Pipelines::OffscreenPipeline2:
			vertShaderCode = readFile("./Shaders/quad2VS.spv");
			fragShaderCode = readFile("./Shaders/quad2PS.spv");

			cullingFlag = VK_CULL_MODE_NONE;
			colorBlendAttachment.blendEnable = VK_FALSE;
			break;

		case Pipelines::OITColorAccumPipeline:
			vertShaderCode = readFile("./Shaders/OITVS.spv");
			fragShaderCode = readFile("./Shaders/OITColorPS.spv");

			depthWrite = VK_FALSE;
			pipelineColorAttachmentFormat = VK_FORMAT_R16G16B16A16_SFLOAT;
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		case Pipelines::OITColorRevealPipeline:
			vertShaderCode = readFile("./Shaders/OITVS.spv");
			fragShaderCode = readFile("./Shaders/OITRevealPS.spv");

			depthWrite = VK_FALSE;
			pipelineColorAttachmentFormat = VK_FORMAT_R16_SFLOAT;
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		case Pipelines::OITResultPipeline:
			vertShaderCode = readFile("./Shaders/quadVS.spv");
			fragShaderCode = readFile("./Shaders/OITResult.spv");
			depthWrite = VK_FALSE;

			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

			cullingFlag = VK_CULL_MODE_NONE;
			break;
		case Pipelines::DemoOITColorAccumPipeline:
			vertShaderCode = readFile("./Shaders/DemoOITVS.spv");
			fragShaderCode = readFile("./Shaders/DemoOITColorPS.spv");

			depthWrite = VK_FALSE;
			pipelineColorAttachmentFormat = VK_FORMAT_R16G16B16A16_SFLOAT;
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		case Pipelines::DemoOITColorRevealPipeline:
			vertShaderCode = readFile("./Shaders/DemoOITVS.spv");
			fragShaderCode = readFile("./Shaders/DemoOITRevealPS.spv");

			depthWrite = VK_FALSE;
			pipelineColorAttachmentFormat = VK_FORMAT_R16_SFLOAT;
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		case Pipelines::DemoOITResultPipeline:
			vertShaderCode = readFile("./Shaders/quadVS.spv");
			fragShaderCode = readFile("./Shaders/DemoOITResult.spv");

			cullingFlag = VK_CULL_MODE_NONE;
			break;
		case Pipelines::SkyboxPipeline:
			vertShaderCode = readFile("./Shaders/skyboxVS.spv");
			fragShaderCode = readFile("./Shaders/skyboxPS.spv");

			colorBlendAttachment.blendEnable = VK_FALSE;
			cullingFlag = VK_CULL_MODE_FRONT_BIT;
			break;
		case Pipelines::LuminancePipeline:
			vertShaderCode = readFile("./Shaders/LuminanceVS.spv");
			fragShaderCode = readFile("./Shaders/LuminancePS.spv");

			cullingFlag = VK_CULL_MODE_NONE;
			break;
		case Pipelines::BlurPipeline:
			vertShaderCode = readFile("./Shaders/BlurVS.spv");
			fragShaderCode = readFile("./Shaders/BlurPS.spv");

			cullingFlag = VK_CULL_MODE_NONE;
			break;
		case Pipelines::WaterPipeline:
			vertShaderCode = readFile("./Shaders/waterVS.spv");
			fragShaderCode = readFile("./Shaders/waterPS.spv");

			cullingFlag = VK_CULL_MODE_NONE;
			break;
		case Pipelines::FirePipeline:
			vertShaderCode = readFile("./Shaders/waterVS.spv");
			fragShaderCode = readFile("./Shaders/fireballPS.spv");

			cullingFlag = VK_CULL_MODE_NONE;
			break;
		case Pipelines::ComputeParticlePipeline:
			vertShaderCode = readFile("./Shaders/computeParticleVS.spv");
			fragShaderCode = readFile("./Shaders/computeParticlePS.spv");

			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			cullingFlag = VK_CULL_MODE_NONE;
			break;
		case Pipelines::EnumCount:
			break;
		default:
			break;
		}

		// Build shader modules to link to Graphics Pipeline
		// Create Shader Modules
		VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
		VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

		// -- Shader Stage Creation Information
		// Vertex stage creation information
		VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";
		vertShaderStageInfo.pSpecializationInfo = nullptr;

		// Fragment stage creation information
		VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";
		fragShaderStageInfo.pSpecializationInfo = nullptr;

		// Put shader stage creation info in to array
		// Graphics pipeline createion info requires array of shader stage creates
		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		// How the data for a single vertex(including info such as position, color, texture coords, normals) is as a whole
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		auto bindingDescription = GLTFStaticModel::Vertex::getBindingDescription();
		auto attributeDescriptions = GLTFStaticModel::Vertex::getAttributeDescriptions();

		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		// Create a input assembly
		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		if (pipelineName == Pipelines::ComputeParticlePipeline)
		{
			inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		}

		if (pipelineName == Pipelines::OffscreenPipeline2)
		{
			inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		}

		// Create a viewport
		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.scissorCount = 1;

		// Create a rasterizer
		VkPipelineRasterizationStateCreateInfo rasterizer{};

		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = polygonMode;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = cullingFlag;

		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp = 0.0f;
		rasterizer.depthBiasSlopeFactor = 0.0f;

		// Create a multisampling
		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling.minSampleShading = 1.0f;
		multisampling.pSampleMask = nullptr;
		multisampling.alphaToCoverageEnable = VK_FALSE;
		multisampling.alphaToOneEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		// Create a depth and stencil
		VkPipelineDepthStencilStateCreateInfo depthStencil{};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = depthTest;
		depthStencil.depthWriteEnable = depthWrite;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.minDepthBounds = 0.0f;
		depthStencil.maxDepthBounds = 1.0f;
		depthStencil.stencilTestEnable = VK_FALSE;
		depthStencil.front = {};
		depthStencil.back = {};

		// Blend attachment state (how blending is handle)

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		// Create a dynamic states
		std::vector<VkDynamicState> dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		VkPipelineDynamicStateCreateInfo dynamicState{};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicState.pDynamicStates = dynamicStates.data();

		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(PushConstants);

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};

		if (pipelineName == Pipelines::OffscreenPipeline)
		{
			std::array<VkDescriptorSetLayout, 1> descriptorSetLayouts = { postEffectSetLayout };

			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
			pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();

			pipelineLayoutInfo.pushConstantRangeCount = 1;
			pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

			VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayouts[static_cast<int>(pipelineName)]));
		}
		else if (pipelineName == Pipelines::LuminancePipeline ||
			pipelineName == Pipelines::BlurPipeline)
		{
			// Pipeline layout
			std::array<VkDescriptorSetLayout, 1> descriptorSetLayouts = { dynamicTextureSamplerSetLayout };

			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
			pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();

			pipelineLayoutInfo.pushConstantRangeCount = 1;
			pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

			VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayouts[static_cast<int>(pipelineName)]));
		}
		else if (pipelineName == Pipelines::OITResultPipeline ||
			pipelineName == Pipelines::DemoOITResultPipeline)
		{
			// Pipeline layout
			std::array<VkDescriptorSetLayout, 3> descriptorSetLayouts = { descriptorSetLayout, samplerSetLayout, OITDescriptorSetLayout };

			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
			pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();

			pipelineLayoutInfo.pushConstantRangeCount = 1;
			pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

			// Create a pipeline layout
			VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayouts[static_cast<int>(pipelineName)]));
		}
		else if (pipelineName == Pipelines::SkyboxPipeline)
		{
			// Pipeline layout
			std::array<VkDescriptorSetLayout, 2> descriptorSetLayouts = { descriptorSetLayout, samplerSetLayout };

			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
			pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();

			pipelineLayoutInfo.pushConstantRangeCount = 1;
			pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

			// Create a pipeline layout
			VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayouts[static_cast<int>(pipelineName)]));
		}
		else if (pipelineName == Pipelines::ComputeParticlePipeline)
		{
			VkVertexInputBindingDescription particleBindingDescription{};
			particleBindingDescription.binding = 0;
			particleBindingDescription.stride = 32;
			particleBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			std::array<VkVertexInputAttributeDescription, 2> particleAttributeDescriptions{};
			particleAttributeDescriptions[0].binding = 0;
			particleAttributeDescriptions[0].location = 0;
			particleAttributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			particleAttributeDescriptions[0].offset = 0;

			particleAttributeDescriptions[1].binding = 0;
			particleAttributeDescriptions[1].location = 1;
			particleAttributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
			particleAttributeDescriptions[1].offset = 8;

			vertexInputInfo.vertexBindingDescriptionCount = 1;
			vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(particleAttributeDescriptions.size());
			vertexInputInfo.pVertexBindingDescriptions = &particleBindingDescription;
			vertexInputInfo.pVertexAttributeDescriptions = particleAttributeDescriptions.data();

			// Pipeline layout
			std::array<VkDescriptorSetLayout, 1> descriptorSetLayouts = { computeDescriptorSetLayout };

			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
			pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();

			// Create a pipeline layout
			VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayouts[static_cast<int>(pipelineName)]));
		}
		else
		{
			// Pipeline layout
			std::array<VkDescriptorSetLayout, 3> descriptorSetLayouts = { descriptorSetLayout, samplerSetLayout, dynamicTextureSamplerSetLayout };

			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
			pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();

			pipelineLayoutInfo.pushConstantRangeCount = 1;
			pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

			// Create a pipeline layout
			VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayouts[static_cast<int>(pipelineName)]));
		}

		// Create a graphics pipeline
		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;

		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicState;

		pipelineInfo.layout = pipelineLayouts[static_cast<int>(pipelineName)];

		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.basePipelineIndex = -1;

		VkPipelineRenderingCreateInfoKHR pipelineRenderingCreateInfo{};
		pipelineRenderingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
		pipelineRenderingCreateInfo.colorAttachmentCount = 1;

		pipelineRenderingCreateInfo.pColorAttachmentFormats = &pipelineColorAttachmentFormat;
		depthFormat = findDepthFormat();
		pipelineRenderingCreateInfo.depthAttachmentFormat = depthFormat;
		// Chain into the pipeline creat einfo
		pipelineInfo.pNext = &pipelineRenderingCreateInfo;

		VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipelines[static_cast<int>(pipelineName)]));

		// Destroy Shder Modules, no longer	needed after Pipeline created
		vkDestroyShaderModule(device, fragShaderModule, nullptr);
		vkDestroyShaderModule(device, vertShaderModule, nullptr);
	}
}

void Graphics::createComputePipeline()
{
	auto computeShaderCode = readFile("./Shaders/computeParticleCS.spv");

	VkShaderModule computeShaderModule = createShaderModule(computeShaderCode);

	VkPipelineShaderStageCreateInfo computeShaderStageInfo{};
	computeShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	computeShaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
	computeShaderStageInfo.module = computeShaderModule;
	computeShaderStageInfo.pName = "main";

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &computeDescriptorSetLayout;

	VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &computePipelineLayout));

	VkComputePipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	pipelineInfo.layout = computePipelineLayout;
	pipelineInfo.stage = computeShaderStageInfo;

	VK_CHECK(vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &computePipeline));

	vkDestroyShaderModule(device, computeShaderModule, nullptr);
}

VkShaderModule Graphics::createShaderModule(const std::vector<char>& code)
{
	// Shader Module creation information
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	VK_CHECK(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule));

	return shaderModule;
}

void Graphics::createCommandPool()
{
	// Get indices of queue families from device
	QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsAndComputeFamily.value();

	// Create a Graphics queue family command pool
	VK_CHECK(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool));
}

void Graphics::createaDepthResources()
{
	VkSamplerCreateInfo samplerInfo = {};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_NEAREST;
	samplerInfo.minFilter = VK_FILTER_NEAREST;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.anisotropyEnable = VK_FALSE;
	samplerInfo.maxAnisotropy = 1.0;
	samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0;
	samplerInfo.minLod = 0.0;
	samplerInfo.maxLod = 1.0;

	VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &depthSampler));

	// Create Depth buffer image
	createImage(physicalDevice, device,
		swapChainExtent.width, swapChainExtent.height,
		depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		depthImage, depthImageMemory);

	// Create Depth buffer image view
	depthImageView = createImageView(device, depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

	transitionImageLayout(device, commandPool, graphicsQueue, depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1);
}

void Graphics::createShaderStorageBuffers()
{
	std::srand(static_cast<unsigned>(std::time(0)));
	float rndDist = static_cast<float>(std::rand()) / RAND_MAX;

	// Initial particle positions on a circle
	std::vector<Particle> particles(PARTICLE_COUNT);
	for (auto& particle : particles) {
		float rndDist = static_cast<float>(std::rand()) / RAND_MAX;
		float r = 0.25f * sqrt(rndDist);
		float theta = rndDist * 2.0f * 3.14159265358979323846f;
		float x = r * cos(theta) * HEIGHT / WIDTH;
		float y = r * sin(theta);
		particle.SetPosition(glm::vec2(x, y));
		particle.SetVelocity(glm::normalize(glm::vec2(x, y)) * 0.00025f);
		particle.SetColor(glm::vec4(rndDist, rndDist, rndDist, 1.0f));
	}

	VkDeviceSize bufferSize = sizeof(Particle) * PARTICLE_COUNT;

	// Create a staging buffer used to upload data to the gpu
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(physicalDevice, device,
		bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, particles.data(), (size_t)bufferSize);
	vkUnmapMemory(device, stagingBufferMemory);

	shaderStorageBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	shaderStorageBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);

	// Copy initial particle data to all storage buffers
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		createBuffer(physicalDevice, device,
			bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, shaderStorageBuffers[i], shaderStorageBuffersMemory[i]);
		copyBuffer(device, commandPool, graphicsQueue, stagingBuffer, shaderStorageBuffers[i], bufferSize);
	}

	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void Graphics::createUniformBuffers()
{
	// View projection buffer size
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

	// Create Uniform Buffers
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		createBuffer(physicalDevice, device,
			bufferSize,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			uniformBuffers[i], uniformBuffersMemory[i]);

		vkMapMemory(device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
	}
}

void Graphics::createDescriptorPool()
{
	// Create uniform descriptor pool
	// Type of descriptors and how many Descriptors
	std::array<VkDescriptorPoolSize, 5> poolSizes{};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	poolSizes[2].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[2].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	poolSizes[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[3].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	poolSizes[4].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[4].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	// Data to create Descriptor pool
	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	// Create Descriptor Pool
	VK_CHECK(vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool));

	// Create sampler descriptor pool
	// Texture sampler pool
	VkDescriptorPoolSize samplerPoolSize = {};
	samplerPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerPoolSize.descriptorCount = MAX_OBJECTS * 7;

	VkDescriptorPoolCreateInfo samplerPoolCreateInfo = {};
	samplerPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	samplerPoolCreateInfo.maxSets = MAX_OBJECTS * 7;
	samplerPoolCreateInfo.poolSizeCount = 1;
	samplerPoolCreateInfo.pPoolSizes = &samplerPoolSize;

	VK_CHECK(vkCreateDescriptorPool(device, &samplerPoolCreateInfo, nullptr, &samplerDescriptorPool));

	// Create dynamicc texture sampler descriptor pool
	// Dynamic Texture sampler pool
	VkDescriptorPoolSize dynamicTextureSamplerPoolSize = {};
	dynamicTextureSamplerPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	dynamicTextureSamplerPoolSize.descriptorCount = MAX_OBJECTS;

	VkDescriptorPoolCreateInfo dynamicTexturePoolCreateInfo = {};
	dynamicTexturePoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	dynamicTexturePoolCreateInfo.maxSets = MAX_OBJECTS;
	dynamicTexturePoolCreateInfo.poolSizeCount = 1;
	dynamicTexturePoolCreateInfo.pPoolSizes = &dynamicTextureSamplerPoolSize;

	VK_CHECK(vkCreateDescriptorPool(device, &dynamicTexturePoolCreateInfo, nullptr, &dynamicTextureSamplerDescriptorPool));

	VkDescriptorPoolSize OITPoolSize = {};
	OITPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	OITPoolSize.descriptorCount = MAX_OBJECTS;

	VkDescriptorPoolCreateInfo OITSamplerPoolCreateInfo = {};
	OITSamplerPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	OITSamplerPoolCreateInfo.maxSets = MAX_OBJECTS;
	OITSamplerPoolCreateInfo.poolSizeCount = 1;
	OITSamplerPoolCreateInfo.pPoolSizes = &OITPoolSize;

	VK_CHECK(vkCreateDescriptorPool(device, &OITSamplerPoolCreateInfo, nullptr, &OITDescriptorPool));

	// Create sampler descriptor pool
	// Texture sampler pool
	VkDescriptorPoolSize postEffectPoolSize = {};
	postEffectPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	postEffectPoolSize.descriptorCount = 20;

	VkDescriptorPoolCreateInfo postEffectPoolCreateInfo = {};
	postEffectPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	postEffectPoolCreateInfo.maxSets = 20;
	postEffectPoolCreateInfo.poolSizeCount = 1;
	postEffectPoolCreateInfo.pPoolSizes = &postEffectPoolSize;

	VK_CHECK(vkCreateDescriptorPool(device, &postEffectPoolCreateInfo, nullptr, &postEffectPool));

	std::array<VkDescriptorPoolSize, 2> computePoolSizes{};
	computePoolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	computePoolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	computePoolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	computePoolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT) * 2;

	VkDescriptorPoolCreateInfo computePoolInfo{};
	computePoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	computePoolInfo.poolSizeCount = 2;
	computePoolInfo.pPoolSizes = poolSizes.data();
	computePoolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	VK_CHECK(vkCreateDescriptorPool(device, &computePoolInfo, nullptr, &computeDescriptorPool));
}

void Graphics::createComputeDescriptorSets()
{
	std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, computeDescriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = computeDescriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	allocInfo.pSetLayouts = layouts.data();

	computeDescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
	VK_CHECK(vkAllocateDescriptorSets(device, &allocInfo, computeDescriptorSets.data()));

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		VkDescriptorBufferInfo uniformBufferInfo{};
		uniformBufferInfo.buffer = uniformBuffers[i];
		uniformBufferInfo.offset = 0;
		uniformBufferInfo.range = sizeof(UniformBufferObject);

		std::array<VkWriteDescriptorSet, 3> descriptorWrites{};
		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = computeDescriptorSets[i];
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &uniformBufferInfo;

		VkDescriptorBufferInfo storageBufferInfoLastFrame{};
		storageBufferInfoLastFrame.buffer = shaderStorageBuffers[(i - 1) % MAX_FRAMES_IN_FLIGHT];
		storageBufferInfoLastFrame.offset = 0;
		storageBufferInfoLastFrame.range = sizeof(Particle) * PARTICLE_COUNT;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = computeDescriptorSets[i];
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pBufferInfo = &storageBufferInfoLastFrame;

		VkDescriptorBufferInfo storageBufferInfoCurrentFrame{};
		storageBufferInfoCurrentFrame.buffer = shaderStorageBuffers[i];
		storageBufferInfoCurrentFrame.offset = 0;
		storageBufferInfoCurrentFrame.range = sizeof(Particle) * PARTICLE_COUNT;

		descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[2].dstSet = computeDescriptorSets[i];
		descriptorWrites[2].dstBinding = 2;
		descriptorWrites[2].dstArrayElement = 0;
		descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		descriptorWrites[2].descriptorCount = 1;
		descriptorWrites[2].pBufferInfo = &storageBufferInfoCurrentFrame;

		vkUpdateDescriptorSets(device, 3, descriptorWrites.data(), 0, nullptr);
	}
}

void Graphics::createDescriptorSets()
{
	// Resize Descriptor set list so one for every buffer
	std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);

	// Descriptor set allocation info
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	allocInfo.pSetLayouts = layouts.data();

	descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);

	// Allocate descriptor sets
	VK_CHECK(vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()));

	// Update all of descriptor sets buffer bindings
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		// List of descriptor set writes
		std::array<VkWriteDescriptorSet, 5> descriptorWrites{};
		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = descriptorSets[i];
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;
		descriptorWrites[0].pImageInfo = nullptr;
		descriptorWrites[0].pTexelBufferView = nullptr;

		VkDescriptorImageInfo imageInfo = {};
		imageInfo.sampler = depthSampler;
		imageInfo.imageView = depthImageView;
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = descriptorSets[i];
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pImageInfo = &imageInfo;

		VkDescriptorImageInfo skyImageInfo = {};
		skyImageInfo.sampler = skybox.cubeMap.sampler;
		skyImageInfo.imageView = skybox.cubeMap.view;
		skyImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[2].dstSet = descriptorSets[i];
		descriptorWrites[2].dstBinding = 2;
		descriptorWrites[2].dstArrayElement = 0;
		descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[2].descriptorCount = 1;
		descriptorWrites[2].pImageInfo = &skyImageInfo;

		VkDescriptorImageInfo skyImageIrrInfo = {};
		skyImageIrrInfo.sampler = skyboxIrr.cubeMap.sampler;
		skyImageIrrInfo.imageView = skyboxIrr.cubeMap.view;
		skyImageIrrInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		descriptorWrites[3].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[3].dstSet = descriptorSets[i];
		descriptorWrites[3].dstBinding = 3;
		descriptorWrites[3].dstArrayElement = 0;
		descriptorWrites[3].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[3].descriptorCount = 1;
		descriptorWrites[3].pImageInfo = &skyImageIrrInfo;

		VkDescriptorImageInfo skyImageLUT = {};
		skyImageLUT.sampler = getTexturesVector()[static_cast<int>(TextureType::LUT)].sampler;
		skyImageLUT.imageView = getTexturesVector()[static_cast<int>(TextureType::LUT)].view;
		skyImageLUT.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		descriptorWrites[4].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[4].dstSet = descriptorSets[i];
		descriptorWrites[4].dstBinding = 4;
		descriptorWrites[4].dstArrayElement = 0;
		descriptorWrites[4].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[4].descriptorCount = 1;
		descriptorWrites[4].pImageInfo = &skyImageLUT;

		// Update the descriptor sets with new buffer / binding info
		vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}
}

void Graphics::createCommandBuffers()
{
	// Resize command buffer count to have one for each framebuffer
	commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

	// Allocate command buffers and place handles in array of buffers
	VK_CHECK(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()));
}

void Graphics::createComputeCommandBuffers()
{
	computeCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)computeCommandBuffers.size();

	VK_CHECK(vkAllocateCommandBuffers(device, &allocInfo, computeCommandBuffers.data()));
}

void Graphics::createSyncObjects()
{
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	computeFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
	computeInFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	// Semaphore creation information
	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	// Fence creation information
	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		VK_CHECK(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]));
		VK_CHECK(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]));
		VK_CHECK(vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]));

		VK_CHECK(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &computeFinishedSemaphores[i]));
		VK_CHECK(vkCreateFence(device, &fenceInfo, nullptr, &computeInFlightFences[i]));
	}
}

void Graphics::recreateSwapChain()
{
	// Recreating swapchain for new resolution
	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	while (width == 0 || height == 0)
	{
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(device);

	cleanupSwapChain();

	createSwapChain();
	createImageViews();
	createaDepthResources();
	prepareOITColorAccum();
	prepareOITColorReveal();
	prepareFinalTexture();
	prepareOITResult();
	prepareLuminance();
	prepareBlur();
	prepareOffscreen();
}

void Graphics::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, HighResolutionTimer timer)
{
	// Information about how to begin each command buffer
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0;
	beginInfo.pInheritanceInfo = nullptr;

	// Start recording commands to command buffer
	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to begin recording command buffer");
	}

	//\\\\\\\\\\

	/////////////////////////////////////////////////////////////

	//Synchronisation for images
	const VkImageMemoryBarrier image_memory_barrier_prepass_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.image = offscreen.offscreenColorAttachment.image,
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	const VkImageMemoryBarrier image_memory_barrier_depth_prepass_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		.image = depthImage,
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	// Pipeline barrier for color
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		0, 0, nullptr, 0, nullptr, 1, &image_memory_barrier_prepass_start);

	// Pipeline barrier for depth
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
		VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
		0, 0, nullptr, 0, nullptr, 1, &image_memory_barrier_depth_prepass_start);

	//// New structures are used to define the attachments used in dynamic rendering

	VkRenderingAttachmentInfoKHR colorAttachment{};
	colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachment.imageView = offscreen.offscreenColorAttachment.view;
	colorAttachment.imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.clearValue.color = { 0.0f,0.0f,0.0f,0.0f };

	VkRenderingAttachmentInfoKHR depthStencilAttachment{};
	depthStencilAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	depthStencilAttachment.imageView = depthImageView;
	depthStencilAttachment.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	depthStencilAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthStencilAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	depthStencilAttachment.clearValue.depthStencil = { 1.0f,  0 };

	VkRenderingInfoKHR renderingInfo{};
	renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
	renderingInfo.renderArea = { 0, 0, swapChainExtent.width, swapChainExtent.height };
	renderingInfo.layerCount = 1;
	renderingInfo.colorAttachmentCount = 1;
	renderingInfo.pColorAttachments = &colorAttachment;
	renderingInfo.pDepthAttachment = &depthStencilAttachment;
	renderingInfo.pStencilAttachment = nullptr;

	// - Begin rendering
	vkCmdBeginRendering(commandBuffer, &renderingInfo);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	{
		// -- Model Pipeline: Phong Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::ShadowMapPipeline)]);

		// Bind camera descriptor
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts[static_cast<int>(Pipelines::ShadowMapPipeline)],
			0, 1, &descriptorSets[currentFrame], 0, nullptr);

		// -- Model Pipeline: Shadow Shader
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::ShadowMapPipeline)], static_cast<int>(ShaderType::Flat));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::ShadowMapPipeline)], static_cast<int>(ShaderType::Phong));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::ShadowMapPipeline)], static_cast<int>(ShaderType::PBR));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::ShadowMapPipeline)], static_cast<int>(ShaderType::PBRIBL));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::ShadowMapPipeline)], static_cast<int>(ShaderType::Water));
	}

	// --

	// - End of rendering
	vkCmdEndRendering(commandBuffer);

	/////////////////////////
	const VkImageMemoryBarrier image_memory_barrier_prepass_OITColorAccum_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.image = OITColorAccum.offscreenColorAttachment.image,
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	// Pipeline barrier for color
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		0, 0, nullptr, 0, nullptr, 1, &image_memory_barrier_prepass_OITColorAccum_start);

	//VkRenderingAttachmentInfoKHR colorAttachment{};
	colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachment.imageView = OITColorAccum.offscreenColorAttachment.view;
	colorAttachment.imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.clearValue.color = { 0.0f,0.0f,0.0f,0.0f };

	//VkRenderingInfoKHR renderingInfo{};
	renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
	renderingInfo.renderArea = { 0, 0, swapChainExtent.width, swapChainExtent.height };
	renderingInfo.layerCount = 1;
	renderingInfo.colorAttachmentCount = 1;
	renderingInfo.pColorAttachments = &colorAttachment;
	renderingInfo.pDepthAttachment = nullptr;
	renderingInfo.pStencilAttachment = nullptr;

	// - Begin rendering
	vkCmdBeginRendering(commandBuffer, &renderingInfo);

	//VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	//VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	{
		// -- Model Pipeline: Phong Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::OITColorAccumPipeline)]);

		// Bind camera descriptor
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts[static_cast<int>(Pipelines::OITColorAccumPipeline)],
			0, 1, &descriptorSets[currentFrame], 0, nullptr);

		// -- Model Pipeline: Shadow Shader
		ActorManager::Instance().renderTransparent(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::OITColorAccumPipeline)], static_cast<int>(ShaderType::OITColorAccum));
	}

	// - End of rendering
	vkCmdEndRendering(commandBuffer);

	/////////////////////////
	const VkImageMemoryBarrier image_memory_barrier_prepass_OITColorReveal_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.image = OITColorReveal.offscreenColorAttachment.image,
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	// Pipeline barrier for color
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		0, 0, nullptr, 0, nullptr, 1, &image_memory_barrier_prepass_OITColorReveal_start);

	//VkRenderingAttachmentInfoKHR colorAttachment{};
	colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachment.imageView = OITColorReveal.offscreenColorAttachment.view;
	colorAttachment.imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.clearValue.color = { 1.0f,0.0f,0.0f,0.0f };

	//VkRenderingInfoKHR renderingInfo{};
	renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
	renderingInfo.renderArea = { 0, 0, swapChainExtent.width, swapChainExtent.height };
	renderingInfo.layerCount = 1;
	renderingInfo.colorAttachmentCount = 1;
	renderingInfo.pColorAttachments = &colorAttachment;
	renderingInfo.pDepthAttachment = nullptr;
	renderingInfo.pStencilAttachment = nullptr;

	// - Begin rendering
	vkCmdBeginRendering(commandBuffer, &renderingInfo);

	//VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	//VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	{
		// -- Model Pipeline: Phong Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::OITColorRevealPipeline)]);

		// Bind camera descriptor
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts[static_cast<int>(Pipelines::OITColorRevealPipeline)],
			0, 1, &descriptorSets[currentFrame], 0, nullptr);

		// -- Model Pipeline: Shadow Shader
		ActorManager::Instance().renderTransparent(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::OITColorRevealPipeline)], static_cast<int>(ShaderType::OITColorAccum));
	}

	// - End of rendering
	vkCmdEndRendering(commandBuffer);

	////////////////////////

		//Synchronisation for images
	const VkImageMemoryBarrier image_memory_barrier_skybox_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.image = FinalTexture.offscreenColorAttachment.image,
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	const VkImageMemoryBarrier image_memory_barrier_depth_skybox_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		.image = FinalTexture.offscreenDepthAttachment.image,
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	// Pipeline barrier for color
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		0, 0, nullptr, 0, nullptr, 1, &image_memory_barrier_skybox_start);

	// Pipeline barrier for depth
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
		VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
		0, 0, nullptr, 0, nullptr, 1, &image_memory_barrier_depth_skybox_start);

	//// New structures are used to define the attachments used in dynamic rendering

	VkRenderingAttachmentInfoKHR colorAttachment_skybox{};
	colorAttachment_skybox.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachment_skybox.imageView = FinalTexture.offscreenColorAttachment.view;
	colorAttachment_skybox.imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR;
	colorAttachment_skybox.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment_skybox.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment_skybox.clearValue.color = { 0.0f,0.0f,0.0f,0.0f };

	VkRenderingAttachmentInfoKHR depthStencilAttachment_depth_skybox{};
	depthStencilAttachment_depth_skybox.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	depthStencilAttachment_depth_skybox.imageView = FinalTexture.offscreenDepthAttachment.view;
	depthStencilAttachment_depth_skybox.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	depthStencilAttachment_depth_skybox.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthStencilAttachment_depth_skybox.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	depthStencilAttachment_depth_skybox.clearValue.depthStencil = { 1.0f,  0 };

	VkRenderingInfoKHR renderingInfo_skybox{};
	renderingInfo_skybox.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
	renderingInfo_skybox.renderArea = { 0, 0, swapChainExtent.width, swapChainExtent.height };
	renderingInfo_skybox.layerCount = 1;
	renderingInfo_skybox.colorAttachmentCount = 1;
	renderingInfo_skybox.pColorAttachments = &colorAttachment_skybox;
	renderingInfo_skybox.pDepthAttachment = &depthStencilAttachment_depth_skybox;
	renderingInfo_skybox.pStencilAttachment = nullptr;

	// - Begin rendering
	vkCmdBeginRendering(commandBuffer, &renderingInfo_skybox);

	// -- Model Pipeline: Phong Shader
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::SkyboxPipeline)]);

	// Bind camera descriptor
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts[static_cast<int>(Pipelines::SkyboxPipeline)],
		0, 1, &descriptorSets[currentFrame], 0, nullptr);

	// Bind camera descriptor
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts[static_cast<int>(Pipelines::OITResultPipeline)],
		2, 1, &OITResult.descriptorSet, 0, nullptr);

	// -- Model Pipeline: Shadow Shader
	ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::SkyboxPipeline)], static_cast<int>(ShaderType::Skybox));

	static bool wireframe = false;

	if (glfwGetKey(window, GLFW_KEY_F9) == GLFW_PRESS)
	{
		wireframe = !wireframe;
	}

	if (!wireframe)
	{
		// -- Model Pipeline: Flat Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::UnlitPipeline)]);
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::UnlitPipeline)], static_cast<int>(ShaderType::Flat));

		// -- Model Pipeline: Phong Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::PhongPipeline)]);
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::PhongPipeline)], static_cast<int>(ShaderType::Phong));

		// -- Model Pipeline: PBR Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::PBRPipeline)]);
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::PBRPipeline)], static_cast<int>(ShaderType::PBR));

		// -- Model Pipeline: PBRIBL Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::PBRIBLPipeline)]);
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::PBRIBLPipeline)], static_cast<int>(ShaderType::PBRIBL));

		// -- Model Pipeline: Water Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::WaterPipeline)]);
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::WaterPipeline)], static_cast<int>(ShaderType::Water));

		// -- Model Pipeline: Water Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::FirePipeline)]);
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::FirePipeline)], static_cast<int>(ShaderType::Fireball));
	}
	else
	{
		// -- Model Pipeline: Phong Shader
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::DebugDrawingPipeline)]);

		// -- Model Pipeline: PBR Shader
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::DebugDrawingPipeline)], static_cast<int>(ShaderType::Phong));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::DebugDrawingPipeline)], static_cast<int>(ShaderType::PBR));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::DebugDrawingPipeline)], static_cast<int>(ShaderType::PBRIBL));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::DebugDrawingPipeline)], static_cast<int>(ShaderType::Flat));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::DebugDrawingPipeline)], static_cast<int>(ShaderType::Water));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::DebugDrawingPipeline)], static_cast<int>(ShaderType::Fireball));
		ActorManager::Instance().renderSolid(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::DebugDrawingPipeline)], static_cast<int>(ShaderType::Skybox));
	}

	if (true)
	{
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::OITResultPipeline)]);

		// -- Model Pipeline: OIT
		vkCmdDraw(commandBuffer, 3, 1, 0, 0);
	}

	// - End of rendering
	vkCmdEndRendering(commandBuffer);

	////////////////////////////////////////////////////////////

	// Synchronisation for images
	const VkImageMemoryBarrier Luminance_memory_barrier_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.image = Luminance.offscreenColorAttachment.image,
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	// Pipeline barrier for color
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		0, 0, nullptr, 0, nullptr, 1, &Luminance_memory_barrier_start);

	//VkRenderingAttachmentInfoKHR colorAttachment{};
	colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachment.imageView = Luminance.offscreenColorAttachment.view;
	colorAttachment.imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.clearValue.color = { 0.0f,0.0f,0.0f,0.0f };

	//VkRenderingInfoKHR renderingInfo{};
	renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
	renderingInfo.renderArea = { 0, 0, swapChainExtent.width, swapChainExtent.height };
	renderingInfo.layerCount = 1;
	renderingInfo.colorAttachmentCount = 1;
	renderingInfo.pColorAttachments = &colorAttachment;
	renderingInfo.pDepthAttachment = nullptr;
	renderingInfo.pStencilAttachment = nullptr;

	// - Begin rendering
	vkCmdBeginRendering(commandBuffer, &renderingInfo);

	//VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	//VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts[static_cast<int>(Pipelines::LuminancePipeline)],
		0, 1, &Luminance.descriptorSet, 0, nullptr);

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::LuminancePipeline)]);

	vkCmdDraw(commandBuffer, 3, 1, 0, 0);

	// - End of rendering
	vkCmdEndRendering(commandBuffer);

	////////////////////////////////////////////////////////////

	// Synchronisation for images
	const VkImageMemoryBarrier Blur_memory_barrier_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.image = Blur.offscreenColorAttachment.image,
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	// Pipeline barrier for color
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		0, 0, nullptr, 0, nullptr, 1, &Blur_memory_barrier_start);

	//VkRenderingAttachmentInfoKHR colorAttachment{};
	colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachment.imageView = Blur.offscreenColorAttachment.view;
	colorAttachment.imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.clearValue.color = { 0.0f,0.0f,0.0f,0.0f };

	//VkRenderingInfoKHR renderingInfo{};
	renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
	renderingInfo.renderArea = { 0, 0, swapChainExtent.width, swapChainExtent.height };
	renderingInfo.layerCount = 1;
	renderingInfo.colorAttachmentCount = 1;
	renderingInfo.pColorAttachments = &colorAttachment;
	renderingInfo.pDepthAttachment = nullptr;
	renderingInfo.pStencilAttachment = nullptr;

	// - Begin rendering
	vkCmdBeginRendering(commandBuffer, &renderingInfo);

	//VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	//VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts[static_cast<int>(Pipelines::BlurPipeline)],
		0, 1, &Blur.descriptorSet, 0, nullptr);

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::BlurPipeline)]);

	vkCmdDraw(commandBuffer, 3, 1, 0, 0);

	// - End of rendering
	vkCmdEndRendering(commandBuffer);

	//////////////////////////////////////////////////////////////////

	// Present

	const VkImageMemoryBarrier new_image_memory_barrier_start
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.image = swapChainImages[imageIndex],
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	//// Pipeline barrier for color
	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		0, 0, nullptr, 0, nullptr, 1, &new_image_memory_barrier_start);

	// New structures are used to define the attachments used in dynamic rendering

	colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachment.imageView = swapChainImageViews[imageIndex];
	colorAttachment.imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.clearValue.color = { 0.0f,0.0f,0.0f,0.0f };

	renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
	renderingInfo.renderArea = { 0, 0, swapChainExtent.width, swapChainExtent.height };
	renderingInfo.layerCount = 1;
	renderingInfo.colorAttachmentCount = 1;
	renderingInfo.pColorAttachments = &colorAttachment;
	renderingInfo.pDepthAttachment = nullptr;
	renderingInfo.pStencilAttachment = nullptr;

	// - Begin rendering
	vkCmdBeginRendering(commandBuffer, &renderingInfo);

	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	// Bind specific pipeline
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::OffscreenPipeline)]);

	PushConstants pushConstants;
	pushConstants.timer.r = timer.TimeStamp();
	vkCmdPushConstants(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::OffscreenPipeline)], VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(PushConstants), &pushConstants);

	// Bind camera descriptor
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts[static_cast<int>(Pipelines::OffscreenPipeline)],
		0, 1, &offscreen.descriptorSet, 0, nullptr);

	vkCmdDraw(commandBuffer, 3, 1, 0, 0);

	// --
	if (isParticleRender)
	{
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::ComputeParticlePipeline)]);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)swapChainExtent.width;
		viewport.height = (float)swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = swapChainExtent;
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, &shaderStorageBuffers[currentFrame], offsets);
		vkCmdDraw(commandBuffer, PARTICLE_COUNT, 1, 0, 0);
	}

	// -- UI Pipeline

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelines[static_cast<int>(Pipelines::UIPipeline)]);

	// UI rendering
	UI::Instance().render(commandBuffer, pipelineLayouts[static_cast<int>(Pipelines::UIPipeline)]);

	// --

	// - End of rendering
	vkCmdEndRendering(commandBuffer);

	// End of synchronisation for images
	const VkImageMemoryBarrier new_image_memory_barrier_end
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		.image = swapChainImages[imageIndex],
		.subresourceRange =
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};

	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
		0, 0, nullptr, 0, nullptr, 1, &new_image_memory_barrier_end);

	////\\\\\\\\\\

	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to record command buffer");
	}
}

void Graphics::recordComputeCommandBuffer(VkCommandBuffer computeCommandBuffer, HighResolutionTimer timer)
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	VK_CHECK(vkBeginCommandBuffer(computeCommandBuffer, &beginInfo));

	vkCmdBindPipeline(computeCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, computePipeline);
	vkCmdBindDescriptorSets(computeCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, computePipelineLayout, 0, 1, &computeDescriptorSets[currentFrame], 0, 0);

	vkCmdDispatch(computeCommandBuffer, PARTICLE_COUNT / 256, 1, 1);

	VK_CHECK(vkEndCommandBuffer(computeCommandBuffer));
}

void Graphics::updateUniformBuffer(HighResolutionTimer timer, float elapsedTime, uint32_t currentImage, Camera* camera)
{
	UniformBufferObject ubo{};

	float zNear = 1.0f;
	float zFar = 1000.f;

	// Model Info
	ubo.view = glm::lookAt(camera->getEye(), camera->getFocus(), glm::vec3(0.f, 1.f, 0.f));
	ubo.proj = glm::perspectiveFov(glm::radians(60.0f), (float)swapChainExtent.width, (float)swapChainExtent.height, zNear, zFar);
	ubo.proj[1][1] *= -1;
	ubo.model = glm::mat4(1.0f);

	// Light Info
	ubo.lightColor = static_cast<DirectionalLight*>(sceneLights[0].get())->GetColor();
	ubo.lightDirection = { static_cast<DirectionalLight*>(sceneLights[0].get())->GetDirection(), 1.0f };
	ubo.lightMVP = static_cast<DirectionalLight*>(sceneLights[0].get())->GetLightProjection() * static_cast<DirectionalLight*>(sceneLights[0].get())->GetLightView() * ubo.model;
	// Camera Info
	ubo.cameraPosition = glm::vec4(camera->getEye().x, camera->getEye().y, camera->getEye().z, 1.f);

	// Timer Info
	ubo.timeConstants.r = elapsedTime;
	ubo.timeConstants.g = timer.TimeStamp();

	memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

void Graphics::prepareOffscreen()
{
	offscreen.width = swapChainExtent.width;
	offscreen.height = swapChainExtent.height;

	// Find a suitable depth format
	VkFormat fbDepthFormat = findDepthFormat();

	// Color attachment
	VkImageCreateInfo image = {};
	image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = VK_FORMAT_B8G8R8A8_UNORM;
	image.extent.width = offscreen.width;
	image.extent.height = offscreen.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	VkMemoryRequirements memReqs;
	VK_CHECK(vkCreateImage(device, &image, nullptr, &offscreen.offscreenColorAttachment.image));
	vkGetImageMemoryRequirements(device, offscreen.offscreenColorAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &offscreen.offscreenColorAttachment.mem));
	vkBindImageMemory(device, offscreen.offscreenColorAttachment.image, offscreen.offscreenColorAttachment.mem, 0);

	VkImageViewCreateInfo colorImageView = {};
	colorImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = VK_FORMAT_B8G8R8A8_UNORM;
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = offscreen.offscreenColorAttachment.image;
	VK_CHECK(vkCreateImageView(device, &colorImageView, nullptr, &offscreen.offscreenColorAttachment.view));

	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo = {};
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

	VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &offscreen.sampler));

	// Depth stencil attachment
	image.format = fbDepthFormat;
	image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &offscreen.offscreenDepthAttachment.image));
	vkGetImageMemoryRequirements(device, offscreen.offscreenDepthAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &offscreen.offscreenDepthAttachment.mem));
	vkBindImageMemory(device, offscreen.offscreenDepthAttachment.image, offscreen.offscreenDepthAttachment.mem, 0);

	VkImageViewCreateInfo depthStencilView = {};
	depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depthStencilView.format = fbDepthFormat;
	depthStencilView.flags = 0;
	depthStencilView.subresourceRange = {};
	depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	if (fbDepthFormat >= VK_FORMAT_D16_UNORM_S8_UINT) {
		depthStencilView.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}
	depthStencilView.subresourceRange.baseMipLevel = 0;
	depthStencilView.subresourceRange.levelCount = 1;
	depthStencilView.subresourceRange.baseArrayLayer = 0;
	depthStencilView.subresourceRange.layerCount = 1;
	depthStencilView.image = offscreen.offscreenDepthAttachment.image;
	VK_CHECK(vkCreateImageView(device, &depthStencilView, nullptr, &offscreen.offscreenDepthAttachment.view));

	// Fill a descriptor for later use in a descriptor set
	offscreen.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	offscreen.descriptor.imageView = offscreen.offscreenColorAttachment.view;
	offscreen.descriptor.sampler = offscreen.sampler;

	VkDescriptorSet descriptorSet;

	// Descriptor set allocation info
	// TODO : Change to offscreen pull
	VkDescriptorSetAllocateInfo setAllocInfo = {};
	setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocInfo.descriptorPool = postEffectPool;
	setAllocInfo.descriptorSetCount = 1;
	setAllocInfo.pSetLayouts = &postEffectSetLayout;

	// Allocate descriptor sets
	VK_CHECK(vkAllocateDescriptorSets(device, &setAllocInfo, &descriptorSet));

	VkDescriptorImageInfo finalTexture = FinalTexture.descriptor;
	VkDescriptorImageInfo bloomTexture = Blur.descriptor;

	std::vector<VkDescriptorImageInfo> imageDescriptors = {
		finalTexture,
		bloomTexture,
	};

	std::array<VkWriteDescriptorSet, 2> writeDescriptorSets{};
	for (size_t i = 0; i < imageDescriptors.size(); i++) {
		writeDescriptorSets[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSets[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		writeDescriptorSets[i].descriptorCount = 1;
		writeDescriptorSets[i].dstSet = descriptorSet;
		writeDescriptorSets[i].dstBinding = static_cast<uint32_t>(i);
		writeDescriptorSets[i].pImageInfo = &imageDescriptors[i];
	}

	vkUpdateDescriptorSets(device, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, NULL);

	offscreen.descriptorSet = descriptorSet;
}

void Graphics::prepareFinalTexture()
{
	FinalTexture.width = swapChainExtent.width;
	FinalTexture.height = swapChainExtent.height;

	// Find a suitable depth format
	VkFormat fbDepthFormat = findDepthFormat();

	// Color attachment
	VkImageCreateInfo image = {};
	image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = VK_FORMAT_B8G8R8A8_UNORM;
	image.extent.width = FinalTexture.width;
	image.extent.height = FinalTexture.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	VkMemoryRequirements memReqs;
	VK_CHECK(vkCreateImage(device, &image, nullptr, &FinalTexture.offscreenColorAttachment.image));
	vkGetImageMemoryRequirements(device, FinalTexture.offscreenColorAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &FinalTexture.offscreenColorAttachment.mem));
	vkBindImageMemory(device, FinalTexture.offscreenColorAttachment.image, FinalTexture.offscreenColorAttachment.mem, 0);

	VkImageViewCreateInfo colorImageView = {};
	colorImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = VK_FORMAT_B8G8R8A8_UNORM;
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = FinalTexture.offscreenColorAttachment.image;
	VK_CHECK(vkCreateImageView(device, &colorImageView, nullptr, &FinalTexture.offscreenColorAttachment.view));

	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo = {};
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

	VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &FinalTexture.sampler));

	// Depth stencil attachment
	image.format = fbDepthFormat;
	image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &FinalTexture.offscreenDepthAttachment.image));
	vkGetImageMemoryRequirements(device, FinalTexture.offscreenDepthAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &FinalTexture.offscreenDepthAttachment.mem));
	vkBindImageMemory(device, FinalTexture.offscreenDepthAttachment.image, FinalTexture.offscreenDepthAttachment.mem, 0);

	VkImageViewCreateInfo depthStencilView = {};
	depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depthStencilView.format = fbDepthFormat;
	depthStencilView.flags = 0;
	depthStencilView.subresourceRange = {};
	depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	if (fbDepthFormat >= VK_FORMAT_D16_UNORM_S8_UINT) {
		depthStencilView.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}
	depthStencilView.subresourceRange.baseMipLevel = 0;
	depthStencilView.subresourceRange.levelCount = 1;
	depthStencilView.subresourceRange.baseArrayLayer = 0;
	depthStencilView.subresourceRange.layerCount = 1;
	depthStencilView.image = FinalTexture.offscreenDepthAttachment.image;
	VK_CHECK(vkCreateImageView(device, &depthStencilView, nullptr, &FinalTexture.offscreenDepthAttachment.view));

	// Fill a descriptor for later use in a descriptor set
	FinalTexture.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	FinalTexture.descriptor.imageView = FinalTexture.offscreenColorAttachment.view;
	FinalTexture.descriptor.sampler = FinalTexture.sampler;

	VkDescriptorSet descriptorSet;

	// Descriptor set allocation info
	// TODO : Change to offscreen pull
	VkDescriptorSetAllocateInfo setAllocInfo = {};
	setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocInfo.descriptorPool = dynamicTextureSamplerDescriptorPool;
	setAllocInfo.descriptorSetCount = 1;
	setAllocInfo.pSetLayouts = &dynamicTextureSamplerSetLayout;

	// Allocate descriptor sets
	VK_CHECK(vkAllocateDescriptorSets(device, &setAllocInfo, &descriptorSet));

	// Texture image info
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;							// Image layout when image in use
	imageInfo.imageView = FinalTexture.descriptor.imageView;															// Image to bind to set
	imageInfo.sampler = FinalTexture.descriptor.sampler;															// Sampler to use for set

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
	vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);

	FinalTexture.descriptorSet = descriptorSet;
}

void Graphics::prepareOITColorAccum()
{
	OITColorAccum.width = swapChainExtent.width;
	OITColorAccum.height = swapChainExtent.height;

	// Color attachment
	VkImageCreateInfo image = {};
	image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = VK_FORMAT_R16G16B16A16_SFLOAT;
	image.extent.width = OITColorAccum.width;
	image.extent.height = OITColorAccum.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	VkMemoryRequirements memReqs;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &OITColorAccum.offscreenColorAttachment.image));
	vkGetImageMemoryRequirements(device, OITColorAccum.offscreenColorAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &OITColorAccum.offscreenColorAttachment.mem));
	vkBindImageMemory(device, OITColorAccum.offscreenColorAttachment.image, OITColorAccum.offscreenColorAttachment.mem, 0);

	VkImageViewCreateInfo colorImageView = {};
	colorImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = VK_FORMAT_R16G16B16A16_SFLOAT;
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = OITColorAccum.offscreenColorAttachment.image;
	VK_CHECK(vkCreateImageView(device, &colorImageView, nullptr, &OITColorAccum.offscreenColorAttachment.view));

	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo = {};
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

	VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &OITColorAccum.sampler));

	// Fill a descriptor for later use in a descriptor set
	OITColorAccum.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	OITColorAccum.descriptor.imageView = OITColorAccum.offscreenColorAttachment.view;
	OITColorAccum.descriptor.sampler = OITColorAccum.sampler;

	VkDescriptorSet descriptorSet;

	// Descriptor set allocation info
	// TODO : Change to offscreen pull
	VkDescriptorSetAllocateInfo setAllocInfo = {};
	setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocInfo.descriptorPool = dynamicTextureSamplerDescriptorPool;
	setAllocInfo.descriptorSetCount = 1;
	setAllocInfo.pSetLayouts = &dynamicTextureSamplerSetLayout;

	// Allocate descriptor sets
	VK_CHECK(vkAllocateDescriptorSets(device, &setAllocInfo, &descriptorSet));

	// Texture image info
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;							// Image layout when image in use
	imageInfo.imageView = OITColorAccum.descriptor.imageView;															// Image to bind to set
	imageInfo.sampler = OITColorAccum.descriptor.sampler;															// Sampler to use for set

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
	vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);

	OITColorAccum.descriptorSet = descriptorSet;
}

void Graphics::prepareOITColorReveal()
{
	OITColorReveal.width = swapChainExtent.width;
	OITColorReveal.height = swapChainExtent.height;

	// Color attachment
	VkImageCreateInfo image = {};
	image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = VK_FORMAT_R16_SFLOAT;
	image.extent.width = OITColorReveal.width;
	image.extent.height = OITColorReveal.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	VkMemoryRequirements memReqs;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &OITColorReveal.offscreenColorAttachment.image));
	vkGetImageMemoryRequirements(device, OITColorReveal.offscreenColorAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &OITColorReveal.offscreenColorAttachment.mem));
	vkBindImageMemory(device, OITColorReveal.offscreenColorAttachment.image, OITColorReveal.offscreenColorAttachment.mem, 0);

	VkImageViewCreateInfo colorImageView = {};
	colorImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = VK_FORMAT_R16_SFLOAT;
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = OITColorReveal.offscreenColorAttachment.image;
	VK_CHECK(vkCreateImageView(device, &colorImageView, nullptr, &OITColorReveal.offscreenColorAttachment.view));

	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo = {};
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

	VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &OITColorReveal.sampler));

	// Fill a descriptor for later use in a descriptor set
	OITColorReveal.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	OITColorReveal.descriptor.imageView = OITColorReveal.offscreenColorAttachment.view;
	OITColorReveal.descriptor.sampler = OITColorReveal.sampler;

	VkDescriptorSet descriptorSet;

	// Descriptor set allocation info
	// TODO : Change to offscreen pull
	VkDescriptorSetAllocateInfo setAllocInfo = {};
	setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocInfo.descriptorPool = dynamicTextureSamplerDescriptorPool;
	setAllocInfo.descriptorSetCount = 1;
	setAllocInfo.pSetLayouts = &dynamicTextureSamplerSetLayout;

	// Allocate descriptor sets
	VK_CHECK(vkAllocateDescriptorSets(device, &setAllocInfo, &descriptorSet));

	// Texture image info
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;							// Image layout when image in use
	imageInfo.imageView = OITColorReveal.descriptor.imageView;															// Image to bind to set
	imageInfo.sampler = OITColorReveal.descriptor.sampler;															// Sampler to use for set

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
	vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);

	OITColorReveal.descriptorSet = descriptorSet;
}

void Graphics::prepareOITResult()
{
	OITResult.width = swapChainExtent.width;
	OITResult.height = swapChainExtent.height;

	// Find a suitable depth format
	VkFormat fbDepthFormat = findDepthFormat();

	// Color attachment
	VkImageCreateInfo image = {};
	image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = VK_FORMAT_B8G8R8A8_UNORM;
	image.extent.width = OITResult.width;
	image.extent.height = OITResult.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	VkMemoryRequirements memReqs;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &OITResult.offscreenColorAttachment.image));
	vkGetImageMemoryRequirements(device, OITResult.offscreenColorAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &OITResult.offscreenColorAttachment.mem));
	vkBindImageMemory(device, OITResult.offscreenColorAttachment.image, OITResult.offscreenColorAttachment.mem, 0);

	VkImageViewCreateInfo colorImageView = {};
	colorImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = VK_FORMAT_B8G8R8A8_UNORM;
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = OITResult.offscreenColorAttachment.image;
	VK_CHECK(vkCreateImageView(device, &colorImageView, nullptr, &OITResult.offscreenColorAttachment.view));

	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo = {};
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

	VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &OITResult.sampler));

	// Depth stencil attachment
	image.format = fbDepthFormat;
	image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &OITResult.offscreenDepthAttachment.image));
	vkGetImageMemoryRequirements(device, OITResult.offscreenDepthAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &OITResult.offscreenDepthAttachment.mem));
	vkBindImageMemory(device, OITResult.offscreenDepthAttachment.image, OITResult.offscreenDepthAttachment.mem, 0);

	VkImageViewCreateInfo depthStencilView = {};
	depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depthStencilView.format = fbDepthFormat;
	depthStencilView.flags = 0;
	depthStencilView.subresourceRange = {};
	depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	if (fbDepthFormat >= VK_FORMAT_D16_UNORM_S8_UINT) {
		depthStencilView.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}
	depthStencilView.subresourceRange.baseMipLevel = 0;
	depthStencilView.subresourceRange.levelCount = 1;
	depthStencilView.subresourceRange.baseArrayLayer = 0;
	depthStencilView.subresourceRange.layerCount = 1;
	depthStencilView.image = OITResult.offscreenDepthAttachment.image;
	VK_CHECK(vkCreateImageView(device, &depthStencilView, nullptr, &OITResult.offscreenDepthAttachment.view));

	// Fill a descriptor for later use in a descriptor set
	OITResult.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	OITResult.descriptor.imageView = OITResult.offscreenColorAttachment.view;
	OITResult.descriptor.sampler = OITResult.sampler;

	VkDescriptorSet descriptorSet;

	// Descriptor set allocation info
	// TODO : Change to offscreen pull
	VkDescriptorSetAllocateInfo setAllocInfo = {};
	setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocInfo.descriptorPool = OITDescriptorPool;
	setAllocInfo.descriptorSetCount = 1;
	setAllocInfo.pSetLayouts = &OITDescriptorSetLayout;

	// Allocate descriptor sets
	VK_CHECK(vkAllocateDescriptorSets(device, &setAllocInfo, &descriptorSet));

	VkDescriptorImageInfo colorAccum = OITColorAccum.descriptor;
	VkDescriptorImageInfo colorReveal = OITColorReveal.descriptor;
	VkDescriptorImageInfo finalTexture = FinalTexture.descriptor;

	std::vector<VkDescriptorImageInfo> imageDescriptors = {
		colorAccum,
		colorReveal,
		finalTexture,
	};

	std::array<VkWriteDescriptorSet, 3> writeDescriptorSets{};
	for (size_t i = 0; i < imageDescriptors.size(); i++) {
		writeDescriptorSets[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSets[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		writeDescriptorSets[i].descriptorCount = 1;
		writeDescriptorSets[i].dstSet = descriptorSet;
		writeDescriptorSets[i].dstBinding = static_cast<uint32_t>(i);
		writeDescriptorSets[i].pImageInfo = &imageDescriptors[i];
	}

	vkUpdateDescriptorSets(device, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, NULL);

	OITResult.descriptorSet = descriptorSet;
}

void Graphics::prepareLuminance()
{
	Luminance.width = swapChainExtent.width;
	Luminance.height = swapChainExtent.height;

	// Find a suitable depth format
	VkFormat fbDepthFormat = findDepthFormat();

	// Color attachment
	VkImageCreateInfo image = {};
	image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = VK_FORMAT_B8G8R8A8_UNORM;
	image.extent.width = Luminance.width;
	image.extent.height = Luminance.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	VkMemoryRequirements memReqs;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &Luminance.offscreenColorAttachment.image));
	vkGetImageMemoryRequirements(device, Luminance.offscreenColorAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &Luminance.offscreenColorAttachment.mem));
	vkBindImageMemory(device, Luminance.offscreenColorAttachment.image, Luminance.offscreenColorAttachment.mem, 0);

	VkImageViewCreateInfo colorImageView = {};
	colorImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = VK_FORMAT_B8G8R8A8_UNORM;
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = Luminance.offscreenColorAttachment.image;
	VK_CHECK(vkCreateImageView(device, &colorImageView, nullptr, &Luminance.offscreenColorAttachment.view));

	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo = {};
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

	VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &Luminance.sampler));

	// Depth stencil attachment
	image.format = fbDepthFormat;
	image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &Luminance.offscreenDepthAttachment.image));
	vkGetImageMemoryRequirements(device, Luminance.offscreenDepthAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &Luminance.offscreenDepthAttachment.mem));
	vkBindImageMemory(device, Luminance.offscreenDepthAttachment.image, Luminance.offscreenDepthAttachment.mem, 0);

	VkImageViewCreateInfo depthStencilView = {};
	depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depthStencilView.format = fbDepthFormat;
	depthStencilView.flags = 0;
	depthStencilView.subresourceRange = {};
	depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	if (fbDepthFormat >= VK_FORMAT_D16_UNORM_S8_UINT) {
		depthStencilView.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}
	depthStencilView.subresourceRange.baseMipLevel = 0;
	depthStencilView.subresourceRange.levelCount = 1;
	depthStencilView.subresourceRange.baseArrayLayer = 0;
	depthStencilView.subresourceRange.layerCount = 1;
	depthStencilView.image = Luminance.offscreenDepthAttachment.image;
	VK_CHECK(vkCreateImageView(device, &depthStencilView, nullptr, &Luminance.offscreenDepthAttachment.view));

	// Fill a descriptor for later use in a descriptor set
	Luminance.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	Luminance.descriptor.imageView = Luminance.offscreenColorAttachment.view;
	Luminance.descriptor.sampler = Luminance.sampler;

	VkDescriptorSet descriptorSet;

	// Descriptor set allocation info
	VkDescriptorSetAllocateInfo setAllocInfo = {};
	setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocInfo.descriptorPool = dynamicTextureSamplerDescriptorPool;
	setAllocInfo.descriptorSetCount = 1;
	setAllocInfo.pSetLayouts = &dynamicTextureSamplerSetLayout;

	// Allocate descriptor sets
	VK_CHECK(vkAllocateDescriptorSets(device, &setAllocInfo, &descriptorSet));

	// Texture image info
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;							// Image layout when image in use
	imageInfo.imageView = FinalTexture.descriptor.imageView;															// Image to bind to set
	imageInfo.sampler = FinalTexture.descriptor.sampler;															// Sampler to use for set

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
	vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);

	Luminance.descriptorSet = descriptorSet;
}

void Graphics::prepareBlur()
{
	Blur.width = swapChainExtent.width;
	Blur.height = swapChainExtent.height;

	// Find a suitable depth format
	VkFormat fbDepthFormat = findDepthFormat();

	// Color attachment
	VkImageCreateInfo image = {};
	image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = VK_FORMAT_B8G8R8A8_UNORM;
	image.extent.width = Blur.width;
	image.extent.height = Blur.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	VkMemoryRequirements memReqs;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &Blur.offscreenColorAttachment.image));
	vkGetImageMemoryRequirements(device, Blur.offscreenColorAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &Blur.offscreenColorAttachment.mem));
	vkBindImageMemory(device, Blur.offscreenColorAttachment.image, Blur.offscreenColorAttachment.mem, 0);

	VkImageViewCreateInfo colorImageView = {};
	colorImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = VK_FORMAT_B8G8R8A8_UNORM;
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = Blur.offscreenColorAttachment.image;
	VK_CHECK(vkCreateImageView(device, &colorImageView, nullptr, &Blur.offscreenColorAttachment.view));

	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo = {};
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

	VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &Blur.sampler));

	// Depth stencil attachment
	image.format = fbDepthFormat;
	image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VK_CHECK(vkCreateImage(device, &image, nullptr, &Blur.offscreenDepthAttachment.image));
	vkGetImageMemoryRequirements(device, Blur.offscreenDepthAttachment.image, &memReqs);
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK(vkAllocateMemory(device, &memAlloc, nullptr, &Blur.offscreenDepthAttachment.mem));
	vkBindImageMemory(device, Blur.offscreenDepthAttachment.image, Blur.offscreenDepthAttachment.mem, 0);

	VkImageViewCreateInfo depthStencilView = {};
	depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depthStencilView.format = fbDepthFormat;
	depthStencilView.flags = 0;
	depthStencilView.subresourceRange = {};
	depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	if (fbDepthFormat >= VK_FORMAT_D16_UNORM_S8_UINT) {
		depthStencilView.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}
	depthStencilView.subresourceRange.baseMipLevel = 0;
	depthStencilView.subresourceRange.levelCount = 1;
	depthStencilView.subresourceRange.baseArrayLayer = 0;
	depthStencilView.subresourceRange.layerCount = 1;
	depthStencilView.image = Blur.offscreenDepthAttachment.image;
	VK_CHECK(vkCreateImageView(device, &depthStencilView, nullptr, &Blur.offscreenDepthAttachment.view));

	// Fill a descriptor for later use in a descriptor set
	Blur.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	Blur.descriptor.imageView = Blur.offscreenColorAttachment.view;
	Blur.descriptor.sampler = Blur.sampler;

	VkDescriptorSet descriptorSet;

	// Descriptor set allocation info
	VkDescriptorSetAllocateInfo setAllocInfo = {};
	setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocInfo.descriptorPool = dynamicTextureSamplerDescriptorPool;
	setAllocInfo.descriptorSetCount = 1;
	setAllocInfo.pSetLayouts = &dynamicTextureSamplerSetLayout;

	// Allocate descriptor sets
	VK_CHECK(vkAllocateDescriptorSets(device, &setAllocInfo, &descriptorSet));

	// Texture image info
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;							// Image layout when image in use
	imageInfo.imageView = Luminance.descriptor.imageView;															// Image to bind to set
	imageInfo.sampler = Luminance.descriptor.sampler;															// Sampler to use for set

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
	vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);

	Blur.descriptorSet = descriptorSet;
}

void Graphics::cleanupSwapChain()
{
	{
		vkDestroyImageView(device, FinalTexture.offscreenColorAttachment.view, nullptr);
		vkDestroyImage(device, FinalTexture.offscreenColorAttachment.image, nullptr);
		vkFreeMemory(device, FinalTexture.offscreenColorAttachment.mem, nullptr);

		vkDestroyImageView(device, FinalTexture.offscreenDepthAttachment.view, nullptr);
		vkDestroyImage(device, FinalTexture.offscreenDepthAttachment.image, nullptr);
		vkFreeMemory(device, FinalTexture.offscreenDepthAttachment.mem, nullptr);

		vkDestroyImageView(device, Luminance.offscreenColorAttachment.view, nullptr);
		vkDestroyImage(device, Luminance.offscreenColorAttachment.image, nullptr);
		vkFreeMemory(device, Luminance.offscreenColorAttachment.mem, nullptr);

		vkDestroyImageView(device, Luminance.offscreenDepthAttachment.view, nullptr);
		vkDestroyImage(device, Luminance.offscreenDepthAttachment.image, nullptr);
		vkFreeMemory(device, Luminance.offscreenDepthAttachment.mem, nullptr);

		vkDestroyImageView(device, Blur.offscreenColorAttachment.view, nullptr);
		vkDestroyImage(device, Blur.offscreenColorAttachment.image, nullptr);
		vkFreeMemory(device, Blur.offscreenColorAttachment.mem, nullptr);

		vkDestroyImageView(device, Blur.offscreenDepthAttachment.view, nullptr);
		vkDestroyImage(device, Blur.offscreenDepthAttachment.image, nullptr);
		vkFreeMemory(device, Blur.offscreenDepthAttachment.mem, nullptr);

		vkDestroyImageView(device, OITResult.offscreenColorAttachment.view, nullptr);
		vkDestroyImage(device, OITResult.offscreenColorAttachment.image, nullptr);
		vkFreeMemory(device, OITResult.offscreenColorAttachment.mem, nullptr);

		vkDestroyImageView(device, OITResult.offscreenDepthAttachment.view, nullptr);
		vkDestroyImage(device, OITResult.offscreenDepthAttachment.image, nullptr);
		vkFreeMemory(device, OITResult.offscreenDepthAttachment.mem, nullptr);

		vkDestroyImageView(device, OITColorReveal.offscreenColorAttachment.view, nullptr);
		vkDestroyImage(device, OITColorReveal.offscreenColorAttachment.image, nullptr);
		vkFreeMemory(device, OITColorReveal.offscreenColorAttachment.mem, nullptr);

		vkDestroyImageView(device, OITColorAccum.offscreenColorAttachment.view, nullptr);
		vkDestroyImage(device, OITColorAccum.offscreenColorAttachment.image, nullptr);
		vkFreeMemory(device, OITColorAccum.offscreenColorAttachment.mem, nullptr);

		vkDestroyImageView(device, offscreen.offscreenColorAttachment.view, nullptr);
		vkDestroyImage(device, offscreen.offscreenColorAttachment.image, nullptr);
		vkFreeMemory(device, offscreen.offscreenColorAttachment.mem, nullptr);

		vkDestroyImageView(device, offscreen.offscreenDepthAttachment.view, nullptr);
		vkDestroyImage(device, offscreen.offscreenDepthAttachment.image, nullptr);
		vkFreeMemory(device, offscreen.offscreenDepthAttachment.mem, nullptr);
	}

	for (size_t i = 0; i < swapChainImageViews.size(); i++)
	{
		vkDestroyImageView(device, swapChainImageViews[i], nullptr);
	}

	vkDestroySwapchainKHR(device, swapChain, nullptr);
}

void Graphics::checkAvailableExtensions()
{
	uint32_t extensionsCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionsCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

	if (enableValidationLayers)
	{
		std::cout << "Available extensions:\n";
		for (const auto& extension : extensions)
		{
			std::cout << '\t' << extension.extensionName << '\n';
		}
	}
}

bool Graphics::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}

	return true;
}

bool Graphics::checkDeviceExtensionsSupport(VkPhysicalDevice device)
{
	uint32_t extensionsCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionsCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

std::vector<const char*> Graphics::getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

	dynamicRenderingFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES_KHR;
	dynamicRenderingFeaturesKHR.dynamicRendering = VK_TRUE;

	return extensions;
}

void Graphics::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		throw std::runtime_error("Failed to find GPUs with Vulkan support");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (isDeviceSuitable(device))
		{
			physicalDevice = device;
			msaaSamples = getMaxUsableSampleCount();

			vkGetPhysicalDeviceProperties(device, &deviceProperties);
			vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE)
	{
		physicalDevice = devices[0];
	}

	if (physicalDevice == VK_NULL_HANDLE)
	{
		throw std::runtime_error("Failed to find a suitable");
	}
}

bool Graphics::isDeviceSuitable(VkPhysicalDevice device)
{
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	QueueFamilyIndices indices = findQueueFamilies(device);

	if (true)
	{
		std::cout << "API version : " << deviceProperties.apiVersion << '\n'
			<< "Device ID : " << deviceProperties.deviceID << '\n'
			<< "Device name : " << deviceProperties.deviceName << '\n'
			<< "Device Type : " << deviceProperties.deviceType << '\n'
			<< "Driver Version : " << deviceProperties.driverVersion << '\n'
			<< "Max PushConstantSize : " << deviceProperties.limits.maxPushConstantsSize << '\n';
	}

	bool extensionsSupported = checkDeviceExtensionsSupport(device);

	bool swapChainAdequate = false;
	if (extensionsSupported)
	{
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

#ifdef DISCRETE
	return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) && indices.isComplete() && extensionsSupported && swapChainAdequate && deviceFeatures.samplerAnisotropy;
#else
	return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) && indices.isComplete() && extensionsSupported && swapChainAdequate && deviceFeatures.samplerAnisotropy;
#endif // DISCRETE
}

QueueFamilyIndices Graphics::findQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT))
		{
			indices.graphicsAndComputeFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

		if (presentSupport)
		{
			indices.presentFamily = i;
		}

		if (indices.isComplete())
		{
			break;
		}

		++i;
	}

	return indices;
}

VkFormat Graphics::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	for (VkFormat format : candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
		{
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
		{
			return format;
		}
	}

	throw std::runtime_error("failed to find supported format!");
}

VkFormat Graphics::findDepthFormat()
{
	return findSupportedFormat(
		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

SwapChainSupportDetails Graphics::querySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

VkSampleCountFlagBits Graphics::getMaxUsableSampleCount()
{
	VkPhysicalDeviceProperties physicalDeviceProperties;
	vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

	VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
	if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
	if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
	if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
	if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
	if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
	if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

	return VK_SAMPLE_COUNT_1_BIT;
}

std::vector<char> Graphics::readFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

VkSurfaceFormatKHR Graphics::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for (const auto& availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR Graphics::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes)
	{
		//	VK_PRESENT_MODE_IMMEDIATE_KHR = 0,
		//	VK_PRESENT_MODE_MAILBOX_KHR = 1,
		//	VK_PRESENT_MODE_FIFO_KHR = 2,
		//	VK_PRESENT_MODE_FIFO_RELAXED_KHR = 3,

		if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
		{
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Graphics::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != (std::numeric_limits<uint32_t>::max)())
	{
		return capabilities.currentExtent;
	}
	else
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}

void Graphics::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData = nullptr;
}

void Graphics::setupDebugMessenger()
{
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	populateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to set up debug messenger");
	}
}

VkResult Graphics::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void Graphics::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr)
	{
		func(instance, debugMessenger, pAllocator);
	}
}