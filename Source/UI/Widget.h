#pragma once

#include "../Graphics/Utilities.h"

class Widget
{
public:
	Widget() = default;
	Widget(std::string name) {};
	//virtual ~Widget();

	virtual void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) = 0;
};