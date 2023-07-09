#pragma once

// Player information

#include "../Graphics/Utilities.h"

#include "../Camera/Camera.h"

class Player
{
public:
	Player();
	~Player() {};

	std::string calculateScreenToWorldCoords(GLFWwindow* window, Camera& camera);

	void input();

	void update();

	std::string selectedActorName;
	std::string selectedTargetName;

	glm::vec3 movementPoint = { 0.f, 0.f, 0.f };

	static int value;
	static int selectedActorIndex;
};