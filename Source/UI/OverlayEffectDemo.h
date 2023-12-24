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

private:
	std::map<std::string, std::shared_ptr<Widget>> backendWidgets;
	std::map<std::string, std::shared_ptr<Widget>> frontendWidgets;
};