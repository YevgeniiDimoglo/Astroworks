#pragma once

#include "../Graphics/Utilities.h"

class Widget;

class Overlay
{
public:
	Overlay() {}
	virtual ~Overlay() {}

	virtual void initialize(GLFWwindow* window) = 0;

	virtual void finalize() = 0;

	virtual void update(float elapsedTime, GLFWwindow* window) = 0;

	virtual void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) = 0;

	virtual std::map<std::string, std::shared_ptr<Widget>> getWidgets() { return frontWidgets; }

	bool isReady() const { return ready; }

	void setReady() { ready = true; }

protected:
	std::map<std::string, std::shared_ptr<Widget>> frontWidgets;
	std::map<std::string, std::shared_ptr<Widget>> backWidgets;

private:
	bool ready = true;
};