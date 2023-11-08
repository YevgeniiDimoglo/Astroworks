#pragma once

#include "../Graphics/Utilities.h"

class Overlay
{
public:
	Overlay() {}
	virtual ~Overlay() {}

	virtual void initialize(GLFWwindow* window) = 0;

	virtual void finalize() = 0;

	virtual void update(float elapsedTime, GLFWwindow* window) = 0;

	virtual void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) = 0;

	bool isReady() const { return ready; }

	void setReady() { ready = true; }

private:
	bool ready = true;
};