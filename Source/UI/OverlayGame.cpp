#include "OverlayGame.h"

void OverlayGame::initialize()
{
	std::shared_ptr<Widget> rock = std::make_shared<Image>("rock_crystalsLargeB");
	rock->setImageValues(0.8f, -0.9f, 0.001f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets.emplace_back(rock);
}

void OverlayGame::finalize()
{
}

void OverlayGame::update(float elapsedTime, GLFWwindow* window)
{
	for (auto it : widgets)
	{
		it->update(elapsedTime, window);
	}
}

void OverlayGame::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	for (auto it : widgets)
	{
		it->draw(commandBuffer, pipelineLayout);
	}
}