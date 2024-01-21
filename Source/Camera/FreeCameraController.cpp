#include "FreeCameraController.h"

#include "../Input/Input.h"

#define CAMERA_SPEED 10.0f;

static float MOUSESPEED = 0.05f;

void FreeCameraController::SyncCameraToController(Camera* camera)
{
	eye = camera->getEye();
	focus = camera->getFocus();
	up = camera->getUp();
	right = camera->getRight();
}

void FreeCameraController::SyncControllerToCamera(Camera* camera)
{
	glm::vec3 front = glm::cross(up, right);
	front = glm::normalize(front);
	camera->setLookAt(eye, eye + front, up);
}

void FreeCameraController::Update(GLFWwindow* window, float deltaTime)
{
	if (Input::IsKeyDown(window, KeyCode::Escape))
	{
		cameraEnable = !cameraEnable;

		if (cameraEnable)
		{
			Input::SetCursorMode(window, CursorMode::Hidden);
		}
		else
		{
			Input::SetCursorMode(window, CursorMode::Normal);
		}
	}

	if (cameraEnable)
	{
		glm::vec2 mousePosition = Input::GetMousePosition(window);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPos(window, width * 0.5, height * 0.5);

		angleX += MOUSESPEED * deltaTime * float(width * 0.5 - mousePosition.x);
		angleY += MOUSESPEED * deltaTime * float(height * 0.5 - mousePosition.y - 0.5);

		if (glm::degrees(angleY) >= 89.5) angleY = glm::radians(89.5);
		if (glm::degrees(angleY) <= -89.5) angleY = glm::radians(-89.5);

		glm::vec3 front = glm::vec3(
			cosf(angleY) * sin(angleX),
			sinf(angleY),
			cosf(angleY) * cos(angleX)
		);

		glm::vec3 right = glm::vec3(
			sinf(angleX - 3.14f / 2.0f),
			0,
			cosf(angleX - 3.14f / 2.0f)
		);

		glm::vec3 up = glm::normalize(glm::cross(right, front));

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			glm::vec3 forwardCamera = front;
			glm::normalize(forwardCamera);
			eye += forwardCamera * 0.05f * CAMERA_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			glm::vec3 forwardCamera = front;
			glm::normalize(forwardCamera);
			eye -= forwardCamera * 0.05f * CAMERA_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			glm::vec3 forwardCamera = front;
			glm::normalize(forwardCamera);
			glm::vec3 leftCamera = glm::cross(up, forwardCamera);
			glm::normalize(leftCamera);
			eye += leftCamera * 0.05f * CAMERA_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			glm::vec3 forwardCamera = front;
			glm::normalize(forwardCamera);
			glm::vec3 rightCamera = glm::cross(forwardCamera, up);
			glm::normalize(rightCamera);
			eye += rightCamera * 0.05f * CAMERA_SPEED;
		}

		this->right = right;
		this->up = up;
	}
}