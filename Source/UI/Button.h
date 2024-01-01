#pragma once

#include "../Graphics/Sprite.h"

#include "UIUtilities.h"

class Button : public Widget
{
public:
	Button() {}
	Button(std::vector<std::string> buttonNames);

	void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a) override;

	void setState(int newState) {
		switch (newState)
		{
		case 0:
			previousState = State::Normal;
			break;
		case 1:
			previousState = State::Hovered;
			break;
		case 2:
			previousState = State::Clicked;
			break;
		case 3:
			previousState = State::Disabled;
			break;
		default:
			break;
		}
	}

	std::vector<float> getPostionValues() const {
		std::vector<float> positions = {
			buttonNormal->getPositionX() - buttonNormal->getWidth(),
			buttonNormal->getPositionY() - buttonNormal->getHeight(),
			buttonNormal->getPositionX() + buttonNormal->getWidth(),
			buttonNormal->getPositionY() + buttonNormal->getHeight()
		};
		return positions;
	}

	void updateSpriteValues() override;

	void updateValues(float timer, int value) override;

	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

	void update(float elapsedTime, GLFWwindow* window) override;

private:

	enum class State
	{
		Normal,
		Hovered,
		Clicked,
		Disabled,

		EnumCount,
	};

	State state = State::Normal;
	State previousState = State::Normal;

	std::shared_ptr<Sprite> buttonNormal;
	std::shared_ptr<Sprite> buttonHover;
	std::shared_ptr<Sprite> buttonClicked;
	std::shared_ptr<Sprite> buttonDisabled;

	int overlayUUID;

	bool inputLock = false;
};