#pragma once

#include "../Graphics/Utilities.h"

#include "UIUtilities.h"

class OverlayTitle : public Overlay
{
public:
	OverlayTitle() {}
	~OverlayTitle() override {}

	void initialize(GLFWwindow* window) override;

	void finalize() override;

	void update(float elapsedTime, GLFWwindow* window) override;

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

private:
	std::vector<std::shared_ptr<Widget>> widgets;
};