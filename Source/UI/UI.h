#pragma once

#include "../Graphics/Utilities.h"
#include "../Graphics/Sprite.h"

#include "UIUtilities.h"

#include "../Misc/HighResolutionTimer.h"

class UI : public IObserver
{
private:
	UI() {}
	virtual ~UI() {}

public:
	static UI& Instance()
	{
		static UI instance;
		return instance;
	}

	void notify(std::string widgetName, int widgetAction) override;

	void setFileNames(std::vector<std::string> filePathes) { fileNames = filePathes; }

	std::vector<std::shared_ptr<Sprite>> getSprites() const { return sprites; }

	Overlay& getCurrentOverlay() const { return *this->currentOverlay; }

	void loadFiles(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout);

	void add(std::string name, VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout,
		float positionX, float positionY, float positionZ, float scaleW, float scaleH, float angle, float r, float g, float b, float a);

	void update(HighResolutionTimer timer, float elapsedTime, GLFWwindow* window);

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

	void clear();

	void cleanup(VkDevice newLogicalDevice);

	void changeOverlay(std::unique_ptr<Overlay> overlay);

private:

	enum class  OverlayUUIDs
	{
		OverlayTitle,
		OverlayGame,
		OverlayLoading,
		OverlayFinish,

		EnumCount
	};

	std::unique_ptr<Overlay> currentOverlay;
	std::unique_ptr<Overlay> nextOverlay;

	std::vector<std::string> fileNames;
	std::vector<std::shared_ptr<Sprite>> sprites;
};