#include "FreeCameraController.h"
#include "../Graphics/Graphics.h"

static float MOUSESPEED = 0.05f;

void FreeCameraController::SyncCameraToController(Camera* camera)
{
	eye = camera->getEye();
	focus = camera->getFocus();
	up = camera->getUp();
	right = camera->getRight();

	glm::vec3 vector = focus - eye;
	distance = glm::length(vector);

	glm::vec3 front = camera->getFront();
	angleX = ::asinf(-front.y);

	if (up.y < 0)
	{
		if (front.y > 0)
		{
			angleX = -glm::pi<float>() - angleX;
		}
		else
		{
			angleX = glm::pi<float>() - angleX;
		}
		angleY = ::atan2f(front.x, front.z);
	}
	else
	{
		angleY = ::atan2f(-front.x, -front.z);
	}
}

void FreeCameraController::SyncControllerToCamera(Camera* camera)
{
	glm::vec3 front = glm::cross(up, right);
	front = glm::normalize(front);
	camera->setLookAt(eye, eye + front, up);
}

void FreeCameraController::Update(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		cameraEnable = !cameraEnable;

		if (cameraEnable)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	if (cameraEnable)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPos(window, width * 0.5, height * 0.5);

		angleX += MOUSESPEED * deltaTime * float(width * 0.5 - xpos);
		angleY += MOUSESPEED * deltaTime * float(height * 0.5 - ypos - 0.5);

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
			eye += forwardCamera * 0.05f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			glm::vec3 forwardCamera = front;
			glm::normalize(forwardCamera);
			eye -= forwardCamera * 0.05f;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			glm::vec3 forwardCamera = front;
			glm::normalize(forwardCamera);
			glm::vec3 leftCamera = glm::cross(up, forwardCamera);
			glm::normalize(leftCamera);
			eye += leftCamera * 0.05f;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			glm::vec3 forwardCamera = front;
			glm::normalize(forwardCamera);
			glm::vec3 rightCamera = glm::cross(forwardCamera, up);
			glm::normalize(rightCamera);
			eye += rightCamera * 0.05f;
		}

		this->right = right;
		this->up = up;
	}
}