#pragma once

#include "Unit.h"

#include "Components/Movement.h"

// Worker type of Unit

class Alien : public Unit
{
public:
	Alien();
	~Alien() override;

	void setPointOfInterest(glm::vec3 position) {
		pointOfInterest = position;
	}

	void setState(int number);

	void setTerritory(const glm::vec3 origin, float range);

	void start() override;

	void update(float elapsedTime) override;

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

	bool searchEnemy();

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
	float moveSpeed = 2.5f;

	float searchRange = 100.0f;
	float attackRange = 0.3f;
	float stateTimer = 3.5f;

	glm::vec3 territoryOrigin = { 0, 0, 0 };
	float territoryRange = 5.0f;

	glm::vec3 pointOfInterest;
};