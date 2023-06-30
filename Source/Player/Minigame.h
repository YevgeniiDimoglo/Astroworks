#pragma once

// Only required for minigame

#include "../Graphics/Utilities.h"
#include "../Camera/Camera.h"

class Minigame
{
public:
	Minigame();
	~Minigame() {};

	void update(GLFWwindow* window, float elapsedTime);

	int health = 3;

	bool invincible = false;
	float invincibleTimer = 3.f;

	float movementSpeed = 1.5f;

	float timerRound = 5.f;
	int bullCount = 0;
};