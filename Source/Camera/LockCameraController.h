#pragma once

#include "Camera.h"

// TPV camera

class LockCameraController
{
public:
	LockCameraController() {}
	~LockCameraController() {}

	void SyncCameraToController(Camera* camera);
	void SyncControllerToCamera(Camera* camera);

	void Update(GLFWwindow* window, float elapsedTime);

	void SetTarget(const glm::vec3 target) { this->target = target; }

private:
	glm::vec3 target = { 0, 0, 0 };
	glm::vec3 angle = { glm::radians(40.f), glm::radians(0.f) , 0 };

	glm::vec3 eye;
	glm::vec3 focus;
	glm::vec3 up;
	glm::vec3 right;

	float distance = 10.f;
	float angleX = 3.14f;
	float angleY = 0.0f;

	bool cameraEnable = true;
};