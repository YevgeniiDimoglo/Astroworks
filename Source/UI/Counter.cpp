#include "Counter.h"

#include "UI.h"

Counter::Counter(std::string name)
{
	widgetUniqueName = name;
}

void Counter::setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a)
{
	this->positionX = positionX;
	this->positionY = positionY;
	this->positionZ = positionZ;
	this->width = width;
	this->height = height;
	this->angle = angle;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Counter::updateSpriteValues()
{
}

void Counter::changeValue(float& value)
{
}

void Counter::updateValues(float timer, int value)
{
	this->timer = timer;
	this->value = value;
}

void Counter::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	// TODO: remove update from draw
	for (auto it : images)
	{
		it->draw(commandBuffer, pipelineLayout);
	}
}

void Counter::update(float elapsedTime, GLFWwindow* window)
{
	images.clear();
	int digits = 0;

	auto sprites = UI::Instance().getSprites();

	if (value == 0)
	{
		std::shared_ptr<Image> tempImage = std::make_shared<Image>("0d");
		tempImage->setImageValues(positionX - 0.1f * digits, positionY, positionZ, width, height, angle, r, g, b, a);
		images.insert(images.begin(), tempImage);
	}

	while (value > 0)
	{
		int temp = value % 10;
		std::shared_ptr<Image> tempImage = std::make_shared<Image>(std::to_string(temp) + "d");
		tempImage->setImageValues(positionX - 0.1f * digits, positionY, positionZ, width, height, angle, r, g, b, a);
		images.insert(images.begin(), tempImage);

		digits++;
		value /= 10;
	}

	for (auto it : images)
	{
		it->update(elapsedTime, window);
	}
}