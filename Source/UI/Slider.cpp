#include "Slider.h"

#include "UI.h"

Slider::Slider(std::vector<std::string> controlNames, float minValue, float maxValue)
{
	auto sprites = UI::Instance().getSprites();

	for (auto it : sprites)
	{
		if (it->fileName == controlNames[0])
		{
			background = it;
		}
		if (it->fileName == controlNames[1])
		{
			knob = it;
		}
	}

	this->minValue = minValue;
	this->maxValue = maxValue;
}

void Slider::setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a)
{
	background->setSpriteValues(positionX, positionY, positionZ, width, height, angle, r, g, b, a);
	knob->setSpriteValues(positionX, positionY, positionZ, width, height, angle, r, g, b, a);
}

void Slider::updateSpriteValues()
{
}

void Slider::updateValues(float timer, int value)
{
}

void Slider::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	background->draw(commandBuffer, pipelineLayout);
	knob->draw(commandBuffer, pipelineLayout);
}

void Slider::update(float elapsedTime, GLFWwindow* window)
{
}