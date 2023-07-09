#include "Image.h"

#include "UI.h"

Image::Image(std::string name)
{
	auto sprites = UI::Instance().getSprites();
	for (auto it : sprites)
	{
		if (it->fileName == name)
		{
			image = it;
		}
	}
}

void Image::setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a)
{
	image->setSpriteValues(positionX, positionY, positionZ, width, height, angle, r, g, b, a);
}

void Image::setOverlayUUID(int uuid)
{
}

void Image::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	image->draw(commandBuffer, pipelineLayout);
}

void Image::update(float elapsedTime, GLFWwindow* window)
{
	image->updateTransform();
}