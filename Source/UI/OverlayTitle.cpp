#include "OverlayTitle.h"

void OverlayTitle::initialize()
{
	std::shared_ptr<Widget> backScreen = std::make_shared<Image>("titlebg");
	widgets.emplace_back(backScreen);
}

void OverlayTitle::finalize()
{
}

void OverlayTitle::update(float elapsedTime)
{
}

void OverlayTitle::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	for (auto it : widgets)
	{
		it->draw(commandBuffer, pipelineLayout);
	}
}