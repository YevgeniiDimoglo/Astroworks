#pragma once

#include "Camera.h"

// FPV camera

class FreeCameraController
{
public:
	void SyncCameraToController(Camera* camera);
	void SyncControllerToCamera(Camera* camera);

	void Update(GLFWwindow* window, float deltaTime);

private:
	glm::vec3 eye;
	glm::vec3 focus;
	glm::vec3 up;
	glm::vec3 right;

	float distance;
	float angleX = 3.14f;
	float angleY = 0.0f;

	bool cameraEnable = true;
};