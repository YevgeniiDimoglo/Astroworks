#pragma once

#include "Unit.h"

#include "Movement.h"

// Worker type of Unit

class Tank : public Unit
{
public:
	Tank();
	~Tank() override;

	void setPointOfInterest(glm::vec3 position) {
		pointOfInterest = position;
	}

	void setState(int number);

	void start() override;

	void update(float elapsedTime) override;

	std::string targetName;

private:

	enum class State
	{
		Wander,
		Idle,
		Pursuit,
		Attack,
		IdleBattle,
		Damage,
		Death,

		EnumCount
	};

	void TransitionWanderState();
	void UpdateWanderState(float elapsedTime);

	void TransitionIdleState();
	void UpdateIdleState(float elapsedTime);

	void TransitionPursuitState();
	void UpdatePursuitState(float elapsedTime);

	void TransitionAttackState();
	void UpdateAttackState(float elapsedTime);

	void TransitionDamageState();
	void UpdateDamageState(float elapsedTime);

	void TransitionDeathState();
	void UpdateDeathState(float elapsedTime);

private:

	State state = State::Wander;

	bool needMovement = true;
	float moveSpeed = 0.5f;

	float searchRange = 5.0f;
	float attackRange = 5.0f;
	float stateTimer = 3.5f;

	glm::vec3 pointOfInterest;
};