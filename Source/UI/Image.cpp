#include "Image.h"

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

void Image::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	image->draw(commandBuffer, pipelineLayout);
}