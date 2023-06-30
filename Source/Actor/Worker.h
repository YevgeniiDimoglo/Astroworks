#pragma once

#include "Unit.h"
#include "Movement.h"

// Worker type of Unit

class Worker : public Unit
{
public:
	Worker();
	Worker(std::string name);
	~Worker() override;

	std::string getName() const override { return "Worker"; }

	void setPointOfInterest(glm::vec3 position, bool isMineral) {
		pointOfInterest = position;
		mineral = isMineral;
	}

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
		Attack,
		Death,
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

	void TransitionAttackState();
	void UpdateAttackState(float elapsedTime);

	void TransitionDeathState();
	void UpdateDeathState(float elapsedTime);

	void workerControl(float elapsedTime);

private:
	std::shared_ptr<Movement> movement;

	float movementTimer = 3.0f;

	State state = State::Idle;

	float gatherTime = 2.0f;
	bool needMovement = true;

	glm::vec3 pointOfInterest;
	bool mineral = false;
};