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

	bool getReadyStatus() {
		if (state == State::Finished || state == State::Production) return true;
		return false;
	}

	void setCurrentBuildingTime(float currentBuildingTime) { this->currentBuildingTime = currentBuildingTime; }

	void setBuildingStart(bool buildingStart) { this->buildingStart = buildingStart; }

	void update(float elapsedTime) override;

	void setState(int number);

	void execute();

	void applyDamage(int damage);

	int HP = 10;

protected:

	void buildingControl(float elapsedTime);

private:

	enum class State
	{
		Construction,
		Finished,
		Production,
		Destroyed,

		EnumCount
	};

	State state = State::Finished;

	void TransitionConstructionState();
	void UpdateConstructionState(float elapsedTime);

	void TransitionFinishedState();
	void UpdateFinishedState(float elapsedTime);

	void TransitionProductionState();
	void UpdateProductionState(float elapsedTime);

	void TransitionDestroyedState();
	void UpdateDestroyedState(float elapsedTime);

	glm::vec3 pointOfInterest = { 0, 0, 0 };

	glm::vec3 collisionPosition;
	float collisionRadius = 10.f;

	float timerToProduce = 5.f;

	bool finished = false;
	bool buildingStart = false;
	float buildingTime;
	float currentBuildingTime = 0.f;
};