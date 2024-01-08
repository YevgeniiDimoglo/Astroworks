#include "Button.h"

#include "UI.h"

Button::Button(std::vector<std::string> buttonNames)
{
	auto sprites = UI::Instance().getSprites();
	for (auto it : sprites)
	{
		if (it->fileName == buttonNames[0])
		{
			buttonNormal = it;
		}
		if (it->fileName == buttonNames[1])
		{
			buttonHover = it;
		}
		if (it->fileName == buttonNames[2])
		{
			buttonClicked = it;
		}
		if (it->fileName == buttonNames[3])
		{
			buttonDisabled = it;
		}
	}

	widgetUniqueName = buttonNames[0];
}

void Button::setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a)
{
	buttonNormal->setSpriteValues(positionX, positionY, positionZ, width, height, angle, r, g, b, a);
	buttonHover->setSpriteValues(positionX, positionY, positionZ, width, height, angle, r, g, b, a);
	buttonClicked->setSpriteValues(positionX, positionY, positionZ, width, height, angle, r, g, b, a);
	buttonDisabled->setSpriteValues(positionX, positionY, positionZ, width, height, angle, r, g, b, a);
}

void Button::updateSpriteValues()
{
}

void Button::changeValue(float& value)
{
}

void Button::updateValues(float timer, int value)
{
}

void Button::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	switch (state)
	{
	case Button::State::Normal:
		buttonNormal->draw(commandBuffer, pipelineLayout);
		break;
	case Button::State::Hovered:
		buttonHover->draw(commandBuffer, pipelineLayout);
		break;
	case Button::State::Clicked:
		buttonClicked->draw(commandBuffer, pipelineLayout);
		break;
	case Button::State::Disabled:
		buttonDisabled->draw(commandBuffer, pipelineLayout);
		break;
	default:
		break;
	}
}

void Button::update(float elapsedTime, GLFWwindow* window)
{
	double xpos, ypos;
	int width, height;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetWindowSize(window, &width, &height);

	float x_norm = xpos / (width / 2) - 1;
	float y_norm = ypos / (height / 2) - 1;

	float pLeftUpX = buttonNormal->getPositionX() - buttonNormal->getWidth();
	float pLeftUpY = buttonNormal->getPositionY() - buttonNormal->getHeight();

	float pRightBottomX = buttonNormal->getPositionX() + buttonNormal->getWidth();
	float pRightBottomY = buttonNormal->getPositionY() + buttonNormal->getHeight();

	if ((x_norm > pLeftUpX && x_norm < pRightBottomX) && (y_norm > pLeftUpY && y_norm < pRightBottomY))
	{
		state = Button::State::Hovered;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			if (!inputLock)
			{
				notifyObservers(buttonNormal->fileName, 0);
				state = Button::State::Clicked;
				inputLock = true;
			}
		}
	}
	else
	{
		state = previousState;
	}

	switch (state)
	{
	case Button::State::Normal:
		buttonNormal->updateTransform();
		break;
	case Button::State::Hovered:
		buttonHover->updateTransform();
		break;
	case Button::State::Clicked:
		buttonClicked->updateTransform();
		break;
	case Button::State::Disabled:
		buttonDisabled->updateTransform();
		break;
	default:
		break;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		inputLock = false;
	}
}