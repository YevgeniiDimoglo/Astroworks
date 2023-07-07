#pragma once

#include "UI.h"
#include "../Graphics/Sprite.h"

class Image : public Widget
{
public:
	Image() {}
	Image(std::string name);
	//~Image() {}

	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

private:
	std::shared_ptr<Sprite> image;
};