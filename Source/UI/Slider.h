#pragma once

#include "../Graphics/Sprite.h"

#include "UIUtilities.h"

class Image;

class Slider : public Widget
{
public:
	Slider() {}
	Slider(std::vector<std::string> controlNames, float minValue, float maxValue);

	void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a) override;

	void updateSpriteValues() override;

	void updateValues(float timer, int value) override;

	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

	void update(float elapsedTime, GLFWwindow* window) override;

private:

	float minValue;
	float maxValue;

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

	std::shared_ptr<Sprite> background;
	std::shared_ptr<Sprite> knob;
};