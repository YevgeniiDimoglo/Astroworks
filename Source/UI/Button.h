#pragma once

#include "../Graphics/Sprite.h"

#include "UIUtilities.h"

class Button : public Widget
{
public:
	Button() {}
	Button(std::vector<std::string> buttonNames);
	~Button() {}

	void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a);

	void setOverlayUUID(int uuid) { overlayUUID = uuid; }

	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

	void update(float elapsedTime, GLFWwindow* window);

private:

	enum class State
	{
		Normal,
		Hovered,
		Clicked,
		Disabled,
	};

	State state = State::Normal;

	std::shared_ptr<Sprite> buttonNormal;
	std::shared_ptr<Sprite> buttonHover;
	std::shared_ptr<Sprite> buttonClicked;
	std::shared_ptr<Sprite> buttonDisabled;

	int overlayUUID;
};