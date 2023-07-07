#pragma once

#include "../Graphics/Utilities.h"

#include "Overlay.h"
#include "Widget.h"
#include "Image.h"

class OverlayTitle : public Overlay
{
public:
	OverlayTitle() {}
	~OverlayTitle() override {}

	void initialize() override;

	void finalize() override;

	void update(float elapsedTime) override;

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

private:
	std::vector<std::shared_ptr<Widget>> widgets;
};