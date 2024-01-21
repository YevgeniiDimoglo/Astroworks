#pragma once

// Moving component

#include "../../Graphics/Utilities.h"
#include "Component.h"

class Movement : public Component
{
public:
	Movement();
	virtual ~Movement();

	void SetRandomTargetPosition();
	void SetTargetPosition(glm::vec3 pointOfInterest);

	void MoveToTarget(float elapsedTime, float speedRate);
	void MoveLocal(float vx, float vz, float speed, float elapsedTime);
	void Turn(float elapsedTime, float vx, float vz, float speed);

private:
	glm::vec3 currentPosition = { 0.f, 0.f, 0.f };
	glm::vec3 targetPosition = { 0.f, 0.f, 0.f };

	glm::vec3 territoryOrigin = { 10.f, 0.f, 10.f };
	float territoryRange = 10.f;

	float moveSpeed = 3.f;
	float turnSpeed = 5.f;
};