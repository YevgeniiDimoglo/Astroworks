#include "Timer.h"

#include "UI.h"

Timer::Timer(std::string name)
{
}

void Timer::setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a)
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

void Timer::updateSpriteValues()
{
}

void Timer::updateValues(float timer, int value)
{
	this->timer = timer;
	this->value = value;
}

void Timer::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	// TODO: remove update from draw
	for (auto it : images)
	{
		it->draw(commandBuffer, pipelineLayout);
	}
}

void Timer::update(float elapsedTime, GLFWwindow* window)
{
	images.clear();
	int digits = 0;

	auto sprites = UI::Instance().getSprites();

	int minutes = static_cast<int>(timer) / 60;
	int seconds = static_cast<int>(timer) - minutes * 60;

	if (minutes == 0)
	{
		std::shared_ptr<Image> tempImage = std::make_shared<Image>("0d");
		tempImage->setImageValues(positionX - 0.42f, positionY, positionZ, width, height, angle, r, g, b, a);
		images.insert(images.begin(), tempImage);
	}

	while (minutes > 0)
	{
		int temp = minutes % 10;
		std::shared_ptr<Image> tempImage = std::make_shared<Image>(std::to_string(temp) + "d");
		tempImage->setImageValues(positionX - 0.42f, positionY, positionZ, width, height, angle, r, g, b, a);
		images.insert(images.begin(), tempImage);

		digits++;
		minutes /= 10;
	}

	digits = 0;

	if (seconds == 0)
	{
		std::shared_ptr<Image> tempImage = std::make_shared<Image>("0d");
		tempImage->setImageValues(positionX - 0.17f * digits, positionY, positionZ, width, height, angle, r, g, b, a);
		images.insert(images.begin(), tempImage);
	}

	while (seconds > 0)
	{
		int temp = seconds % 10;
		std::shared_ptr<Image> tempImage = std::make_shared<Image>(std::to_string(temp) + "d");
		tempImage->setImageValues(positionX - 0.17f * digits, positionY, positionZ, width, height, angle, r, g, b, a);
		images.insert(images.begin(), tempImage);

		digits++;
		seconds /= 10;
	}

	for (auto it : images)
	{
		it->update(elapsedTime, window);
	}
}