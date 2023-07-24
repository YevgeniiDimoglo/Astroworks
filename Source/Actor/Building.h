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

	void setCurrentBuildingTime(float currentBuildingTime) { this->currentBuildingTime = currentBuildingTime; }

	void setBuildingStart(bool buildingStart) { this->buildingStart = buildingStart; }

	void update(float elapsedTime) override;

	void execute();

protected:

	void buildingControl(float elapsedTime);

protected:

	int HP = 0;

	glm::vec3 pointOfInterest = { 0, 0, 0 };

	glm::vec3 collisionPosition;
	float collisionRadius = 10.f;

	float timerToProduce = 5.f;
	bool recruteStart = false;

	bool finished = false;
	bool buildingStart = false;
	float buildingTime;
	float currentBuildingTime = 0.f;
};