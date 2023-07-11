#pragma once

#include "Component.h"

// Basic ingame building component

class Building : public Component
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

	void buildingControl(float elapsedTime);

protected:

	glm::vec3 pointOfInterest = { 0, 0, 0 };

	glm::vec3 collisionPosition;
	float collisionRadius = 10.f;
};