#pragma once

#include "../Graphics/Utilities.h"

#include "UIUtilities.h"

class OverlayGame : public Overlay
{
public:
	OverlayGame() {}
	~OverlayGame() override {}

	void initialize() override;

	void finalize() override;

	void update(float elapsedTime, GLFWwindow* window) override;

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

private:
	std::map<std::string, std::shared_ptr<Widget>> widgets;
};