#pragma once

#include "../Graphics/Utilities.h"

#include "UIUtilities.h"

class OverlayGame : public Overlay
{
public:
	OverlayGame() {}
	~OverlayGame() override {}

	void initialize(GLFWwindow* window) override;

	void finalize() override;

	void update(float elapsedTime, GLFWwindow* window) override;

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;
};