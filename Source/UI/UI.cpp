#include "UI.h"

void UI::remove(std::shared_ptr<Sprite> sprite)
{
}

void UI::add(std::string name, VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout,
	float positionX, float positionY, float positionZ, float scaleW, float scaleH, float angle, float r, float g, float b, float a)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>("./Data/UI/" + name + ".png");
	// TODO: fix rotation
	sprite->setSpriteValues(positionX, positionY, positionZ, scaleW, scaleH, angle, r, g, b, a);
	sprites.emplace_back(sprite);
	sprite->loadFile(newPhysicalDevice, newLogicalDevice, transferQueue, transferCommandPool, samplerDescriptorPool, samplerSetLayout);
}

void UI::update(float elapsedTime)
{
	for (auto it : sprites)
	{
		it->updateTransform();
	}
}

void UI::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	for (auto it : sprites)
	{
		it->draw(commandBuffer, pipelineLayout);
	}
}

void UI::cleanup(VkDevice newLogicalDevice)
{
	for (auto it : sprites)
	{
		it->cleanupResourses(newLogicalDevice);
	}
}