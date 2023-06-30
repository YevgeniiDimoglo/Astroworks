#pragma once

#include "Component.h"
#include "Movement.h"

// Basic ingame unit component

class Unit : public Component
{
public:
	Unit();
	~Unit() override;

	std::string getName() const override { return "Player"; }

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

	glm::vec3 pointOfInterest = { 0, 0, 0 };

	glm::vec3 collisionPosition;
	float collisionRadius = 10.f;

private:
	std::shared_ptr<Movement> movement;

	float movementTimer = 3.0f;
};