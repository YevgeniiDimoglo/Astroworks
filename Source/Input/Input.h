#pragma once

#include "../Graphics/Utilities.h"

class Input
{
public:
	static bool IsKeyDown(GLFWwindow* window, KeyCode keycode);

	static bool IsMouseButtonDown(GLFWwindow* window, MouseButton button);

	static glm::vec2 GetMousePosition(GLFWwindow* window);

	static glm::vec2 GetWindowsSize(GLFWwindow* window);

	static void SetCursorMode(GLFWwindow* window, CursorMode mode);
};