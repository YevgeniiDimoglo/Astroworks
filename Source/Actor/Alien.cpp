#include "Alien.h"

Alien::Alien()
{
	TransitionWanderState();
}

Alien::~Alien()
{
}

void Alien::setTerritory(const glm::vec3 origin, float range)
{
	territoryOrigin = origin;
	territoryRange = range;
}

void Alien::start()
{
}

void Alien::update(float elapsedTime)
{
	switch (state)
	{
	case Alien::State::Wander:
		UpdateWanderState(elapsedTime);
		break;
	case Alien::State::Idle:
		UpdateIdleState(elapsedTime);
		break;
	case Alien::State::Pursuit:
		UpdatePursuitState(elapsedTime);
		break;
	case Alien::State::Attack:
		UpdateAttackState(elapsedTime);
		break;
	case Alien::State::IdleBattle:
		UpdateIdleBattleStance(elapsedTime);
		break;
	case Alien::State::Damage:
		UpdateDamageState(elapsedTime);
		break;
	case Alien::State::Death:
		UpdateDeathState(elapsedTime);
		break;
	default:
		break;
	}

	if (needMovement) movement->MoveToTarget(elapsedTime, 0.8f);
	if (HP <= 0) TransitionDeathState();
}

void Alien::TransitionWanderState()
{
	state = State::Wander;

	movement->SetRandomTargetPosition();
}

void Alien::UpdateWanderState(float elapsedTime)
{
}

void Alien::TransitionIdleState()
{
}

void Alien::UpdateIdleState(float elapsedTime)
{
}

void Alien::TransitionPursuitState()
{
}

void Alien::UpdatePursuitState(float elapsedTime)
{
}

void Alien::TransitionAttackState()
{
}

void Alien::UpdateAttackState(float elapsedTime)
{
}

void Alien::TransitionIdleBattleState()
{
}

void Alien::UpdateIdleBattleStance(float elapsedTime)
{
}

void Alien::TransitionDamageState()
{
}

void Alien::UpdateDamageState(float elapsedTime)
{
}

void Alien::TransitionDeathState()
{
}

void Alien::UpdateDeathState(float elapsedTime)
{
}