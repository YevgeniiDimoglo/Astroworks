#pragma once

#include "../Graphics/Sprite.h"

#include "UIUtilities.h"

class Image;

class Timer : public Widget
{
public:
	Timer() {}
	Timer(std::string name);

	void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a) override;

	void updateSpriteValues() override;

	void updateValues(float timer, int value) override;

	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

	void update(float elapsedTime, GLFWwindow* window) override;

private:

	float timer = 0;
	int value = 0;

	float positionX;
	float positionY;
	float positionZ;
	float width;
	float height;
	float angle;
	float r;
	float g;
	float b;
	float a;

	std::vector<std::shared_ptr<Image>> images;
};