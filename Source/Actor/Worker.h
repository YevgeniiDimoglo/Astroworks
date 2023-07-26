#pragma once

#include "Unit.h"

#include "Movement.h"

// Worker type of Unit

class Worker : public Unit
{
public:
	Worker();
	~Worker() override;

	void setPointOfInterest(glm::vec3 position, bool isMineral) {
		pointOfInterest = position;
		mineral = isMineral;
	}

	void setBuildingType(std::string type) { this->buildingType = type; }

	void execute();

	void setState(int number);

	void start() override;

	void update(float elapsedTime) override;

private:

	enum class State
	{
		Wander,
		Idle,
		Search,
		Gather,
		Return,
		Building,
		BuildingProgress,
		Attack,
		Death,

		EnumCount
	};

	void TransitionWanderState();
	void UpdateWanderState(float elapsedTime);

	void TransitionIdleState();
	void UpdateIdleState(float elapsedTime);

	void TransitionSearchState();
	void UpdateSearchState(float elapsedTime);

	void TransitionGatherState();
	void UpdateGatherState(float elapsedTime);

	void TransitionReturnState();
	void UpdateReturnState(float elapsedTime);

	void TransitionBuildingState();
	void UpdateBuildingState(float elapsedTime);

	void TransitionBuildingProgressState();
	void UpdateTransitionBuildingProgressState(float elapsedTime);

	void TransitionAttackState();
	void UpdateAttackState(float elapsedTime);

	void TransitionDeathState();
	void UpdateDeathState(float elapsedTime);

	void workerControl(float elapsedTime);

private:

	State state = State::Idle;

	float gatherTime = 2.0f;
	bool needMovement = true;

	glm::vec3 pointOfInterest;
	bool mineral = false;

	std::string buildingType;
};