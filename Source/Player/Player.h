#pragma once

// Player information

#include "../Graphics/Utilities.h"

#include "../Camera/Camera.h"

class Player : public IObserver
{
public:
	Player();
	~Player() {};

	std::string getSelectedActor(GLFWwindow* window, Camera& camera);
	std::string getTargetActor(GLFWwindow* window, Camera& camera);

	void notify(std::string widgetName, int widgetAction) const override;

	void input(GLFWwindow* window, Camera camera);

	void update();

	static int value;
	static int selectedActorIndex;

private:

	void calculateScreenToWorldCoords(GLFWwindow* window, Camera& camera);

	struct CameraRay
	{
		glm::vec3 rayStart;
		glm::vec3 rayEnd;
		glm::vec3 rayDirection;
	} cameraRay;

	std::string selectedActorName;
	std::string selectedTargetName;

	glm::vec3 movementPoint = { 0.f, 0.f, 0.f };

	bool inputLockLMB = false;
	bool inputLockRMB = false;
};