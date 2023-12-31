#pragma once

#include "../Graphics/Sprite.h"

#include "UIUtilities.h"

class Button;

class RadioButton : public Widget
{
public:
	RadioButton() {}
	RadioButton(std::vector<std::shared_ptr<Widget>> buttonNames);

	void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a) override;

	int getSelectedButtonIndex() const { return selectedButtonIndex; }

	void updateSpriteValues() override;

	void updateValues(float timer, int value) override;

	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

	void update(float elapsedTime, GLFWwindow* window) override;

private:

	enum class State
	{
		Normal,

		EnumCount,
	};

	State state = State::Normal;

	std::vector<std::shared_ptr<Widget>> buttons;
	int selectedButtonIndex = -1;

	int overlayUUID;

	bool inputLock = false;
};