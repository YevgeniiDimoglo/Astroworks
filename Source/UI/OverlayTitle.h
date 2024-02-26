#pragma once

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
};