#pragma once

#include "../Graphics/Utilities.h"

class Widget
{
public:
	Widget() = default;
	Widget(std::string name) { widgetUniqueName = name; };

	void registerObserver(IObserver* observer) {
		observers.push_back(observer);
	}
	void unregisterObserver(IObserver* observer) {
		observers.remove(observer);
	}
	void notifyObservers(std::string widgetName, int widgetAction) const {
		for (auto it : observers) { it->notify(widgetName, widgetAction); }
	}

	virtual void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a) = 0;

	virtual void updateSpriteValues() = 0;

	// Change to pointer function
	virtual void updateValues(float timer, int value) = 0;

	virtual void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) = 0;

	virtual void update(float elapsedTime, GLFWwindow* window) = 0;

	std::string widgetUniqueName;

protected:
	std::list<IObserver*> observers;
};