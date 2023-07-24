#pragma once

#include "Component.h"
#include "Movement.h"

// Basic ingame unit component

class Unit : public Component
{
public:

	void start() override;

	const glm::vec3& getCollisionPosition() const {
		return collisionPosition;
	}

	const float& getCollisionRadius() const {
		return collisionRadius;
	}

	void update(float elapsedTime) override;

protected:

	void unitControl(float elapsedTime);

protected:

	int HP;

	glm::vec3 pointOfInterest = { 0, 0, 0 };

	glm::vec3 collisionPosition;
	float collisionRadius = 0.1f;

	std::shared_ptr<Movement> movement;
	float movementTimer = 3.0f;
};