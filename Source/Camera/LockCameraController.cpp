#include "LockCameraController.h"
#include "../Actor/Actor.h"
#include "../Actor/Worker.h"

static const float CAMERAMOVEMENTSPEED = 2.f;
static const int WINDOWSCROLLBORDER = 25;

void LockCameraController::SyncCameraToController(Camera* camera)
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

void LockCameraController::SyncControllerToCamera(Camera* camera)
{
	camera->setLookAt(eye, target, glm::vec3(0.f, 1.f, 0.f));
}

void LockCameraController::Update(GLFWwindow* window, float elapsedTime)
{
	if (!cameraEnable) return;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (target.z <= -20)
		{
			target.z = -20;
		}
		else
		{
			target.z -= CAMERAMOVEMENTSPEED * elapsedTime * 10;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (target.z >= 20)
		{
			target.z = 20;
		}
		else
		{
			target.z += CAMERAMOVEMENTSPEED * elapsedTime * 10;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (target.x <= -20)
		{
			target.x = -20;
		}
		else
		{
			target.x -= CAMERAMOVEMENTSPEED * elapsedTime * 10;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (target.x >= 20)
		{
			target.x = 20;
		}
		else
		{
			target.x += CAMERAMOVEMENTSPEED * elapsedTime * 10;
		}
	}

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	if (xpos >= width - WINDOWSCROLLBORDER)
	{
		target.x += CAMERAMOVEMENTSPEED * elapsedTime;
	}
	if (xpos <= WINDOWSCROLLBORDER)
	{
		target.x -= CAMERAMOVEMENTSPEED * elapsedTime;
	}
	if (ypos >= height - WINDOWSCROLLBORDER)
	{
		target.z += CAMERAMOVEMENTSPEED * elapsedTime;
	}
	if (ypos <= WINDOWSCROLLBORDER)
	{
		target.z -= CAMERAMOVEMENTSPEED * elapsedTime;
	}

	float cp = cosf(angle.x);
	float sp = sinf(angle.x);

	float cy = cosf(angle.y);
	float sy = sinf(angle.y);

	float cr = cosf(angle.z);
	float sr = sinf(angle.z);

	glm::mat4x4 transform;
	transform[0][0] = cr * cy + sr * sp * sy;
	transform[0][1] = sr * cp;
	transform[0][2] = sr * sp * cy - cr * sy;
	transform[0][3] = 0.0f;

	transform[1][0] = cr * sp * sy - sr * cy;
	transform[1][1] = cr * cp;
	transform[1][2] = sr * sy + cr * sp * cy;
	transform[1][3] = 0.0f;

	transform[2][0] = cp * sy;
	transform[2][1] = -sp;
	transform[2][2] = cp * cy;
	transform[2][3] = 0.0f;

	transform[3][0] = 0.0f;
	transform[3][1] = 0.0f;
	transform[3][2] = 0.0f;
	transform[3][3] = 1.0f;

	transform = transform * distance;

	glm::vec3 front(transform[1][0], transform[1][1], transform[1][2]);

	eye.x = front.x + target.x;
	eye.y = front.y + target.y;
	eye.z = front.z + target.z;
}