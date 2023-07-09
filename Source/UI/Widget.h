#pragma once

#include "../Graphics/Utilities.h"

class Widget
{
public:
	Widget() = default;
	Widget(std::string name) {};

	void registerObserver(IObserver* observer) {
		this->observer = observer;
	}
	void unregisterObserver(IObserver* observer) {
		this->observer = nullptr;
	}
	void notifyObservers(std::string widgetName, int widgetAction) const {
		observer->notify(widgetName, widgetAction);
	}

	virtual void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a) = 0;

	virtual void setOverlayUUID(int uuid) = 0;

	virtual void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) = 0;

	virtual void update(float elapsedTime, GLFWwindow* window) = 0;

protected:
	IObserver* observer;
};