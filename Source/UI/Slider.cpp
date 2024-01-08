#include "Slider.h"

#include "UI.h"

Slider::Slider(std::vector<std::string> controlNames, std::string widgetName, float minValue, float maxValue, float defaultValue)
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
	this->defaultValue = defaultValue;

	widgetUniqueName = widgetName;
}

void Slider::setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a)
{
	minPosition = positionX - width;
	maxPosition = positionX + width;

	if (defaultValue != 0)
	{
		float ratio = (defaultValue - minValue) / (maxValue - minValue);
		currentPosition = ratio * (maxPosition - minPosition) + minPosition;
	}
	else
	{
		currentPosition = positionX - width;
	}

	this->positionX = positionX;
	this->positionY = positionY;
	this->positionZ = positionZ;
	this->height = height;
	this->width = width;
	this->angle = angle;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;

	pLeftUpX = positionX - width;
	pLeftUpY = positionY - height;
	pRightBottomX = positionX + width;
	pRightBottomY = positionY + height;
}

void Slider::updateSpriteValues()
{
	background->setSpriteValues(positionX, positionY, positionZ, width, height, angle, r, g, b, a);
	knob->setSpriteValues(currentPosition, positionY, positionZ, height * 0.4f, height * 0.4f, angle, r, g, b, a);
}

void Slider::changeValue(float& value)
{
	float ratio = (currentPosition - minPosition) / (maxPosition - minPosition);
	value = minValue + ratio * (maxValue - minValue);
}

void Slider::updateValues(float timer, int value)
{
}

void Slider::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	updateSpriteValues();
	knob->updateTransform();
	background->updateTransform();

	background->draw(commandBuffer, pipelineLayout);
	knob->draw(commandBuffer, pipelineLayout);
}

void Slider::update(float elapsedTime, GLFWwindow* window)
{
	double xpos, ypos;
	int width, height;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetWindowSize(window, &width, &height);

	float x_norm = xpos / (width / 2) - 1;
	float y_norm = ypos / (height / 2) - 1;

	if ((x_norm > pLeftUpX && x_norm < pRightBottomX) && (y_norm > pLeftUpY && y_norm < pRightBottomY))
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			currentPosition = x_norm;
			knob->setSpriteValues(currentPosition, this->positionY, this->positionZ, this->height * 0.4f, this->height * 0.4f, this->angle, this->r, this->g, this->b, this->a);
			notifyObservers(widgetUniqueName, 0);
		}
	}
}