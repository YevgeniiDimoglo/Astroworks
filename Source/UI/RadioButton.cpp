#include "RadioButton.h"

#include "UI.h"

RadioButton::RadioButton(std::vector<std::shared_ptr<Widget>> buttonNames)
{
	buttons = buttonNames;
}

void RadioButton::setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a)
{
}

void RadioButton::updateSpriteValues()
{
}

void RadioButton::updateValues(float timer, int value)
{
}

void RadioButton::draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	for (auto it : buttons)
	{
		it->draw(commandBuffer, pipelineLayout);
	}
}

void RadioButton::update(float elapsedTime, GLFWwindow* window)
{
	double xpos, ypos;
	int width, height;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetWindowSize(window, &width, &height);

	float x_norm = xpos / (width / 2) - 1;
	float y_norm = ypos / (height / 2) - 1;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (!inputLock)
		{
			int index = 0;
			for (auto it : buttons)
			{
				float pLeftUpX = static_cast<Button*>(it.get())->getPostionValues()[0];
				float pLeftUpY = static_cast<Button*>(it.get())->getPostionValues()[1];
				float pRightBottomX = static_cast<Button*>(it.get())->getPostionValues()[2];
				float pRightBottomY = static_cast<Button*>(it.get())->getPostionValues()[3];

				if ((x_norm > pLeftUpX && x_norm < pRightBottomX) && (y_norm > pLeftUpY && y_norm < pRightBottomY))
				{
					selectedButtonIndex = index;
					static_cast<Button*>(buttons[selectedButtonIndex].get())->setState(2);
					break;
				}

				index++;
			}
			//notifyObservers(, 0);
			inputLock = true;
		}
	}

	for (auto it : buttons)
	{
		it->update(elapsedTime, window);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		inputLock = false;
	}
}