#pragma once

#include "../Graphics/Utilities.h"

#include "UIUtilities.h"

class OverlayComplete : public Overlay
{
public:
	OverlayComplete() {}
	~OverlayComplete() override {}

	void initialize(GLFWwindow* window) override;

	void finalize() override;

	void update(float elapsedTime, GLFWwindow* window) override;

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;
};