#pragma once

#include "../Graphics/Sprite.h"

#include "UIUtilities.h"

class Image;

class Slider : public Widget
{
public:
	Slider() {}
	Slider(std::vector<std::string> controlNames, std::string widgetName, float minValue, float maxValue, float defaultValue = 0);

	void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a) override;

	void updateSpriteValues() override;

	void changeValue(float& value) override;

	void updateValues(float timer, int value) override;

	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

	void update(float elapsedTime, GLFWwindow* window) override;

	float GetCurrentValue() { return currentValue; }

private:

	float minValue;
	float maxValue;
	float currentValue;
	float defaultValue;

	float minPosition;
	float maxPosition;
	float currentPosition;

	float pLeftUpX;
	float pLeftUpY;
	float pRightBottomX;
	float pRightBottomY;

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