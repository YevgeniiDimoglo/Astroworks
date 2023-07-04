#pragma once

#include "../Graphics/Utilities.h"
#include "../Graphics/Sprite.h"

class UI
{
private:
	UI() {}
	~UI() {};

public:

	static UI& Instance()
	{
		static UI instance;
		return instance;
	}

	std::vector<std::shared_ptr<Sprite>> getSprites() const { return sprites; }

	void remove(std::shared_ptr<Sprite> sprite);

	void add(std::string name, VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout,
		float positionX, float positionY, float positionZ, float scaleW, float scaleH, float angle, float r, float g, float b, float a);

	void update(float elapsedTime);

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

	void cleanup(VkDevice newLogicalDevice);

private:

	std::vector<std::shared_ptr<Sprite>> sprites;
};