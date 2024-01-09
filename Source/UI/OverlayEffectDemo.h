#pragma once

#include "../Graphics/Utilities.h"

#include "UIUtilities.h"

class OverlayEffectDemo : public Overlay
{
public:
	OverlayEffectDemo() {}
	~OverlayEffectDemo() override {}

	void initialize(GLFWwindow* window) override;

	void finalize() override;

	void update(float elapsedTime, GLFWwindow* window) override;

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;
};