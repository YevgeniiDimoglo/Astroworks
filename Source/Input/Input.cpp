#include "Input.h"

bool Input::IsKeyDown(GLFWwindow* window, KeyCode keycode)
{
	int resultkeycode = -1;

	switch (static_cast<int>(keycode))
	{
	case 0:
		resultkeycode = 256;
		break;
	default:
		resultkeycode = 257;
		break;
	}
	int state = glfwGetKey(window, resultkeycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonDown(GLFWwindow* window, MouseButton button)
{
	int state = glfwGetMouseButton(window, (int)button);
	return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	return { (float)x, (float)y };
}

void Input::SetCursorMode(GLFWwindow* window, CursorMode mode)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
}

glm::vec2 Input::GetWindowsSize(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return glm::vec2(width, height);
}