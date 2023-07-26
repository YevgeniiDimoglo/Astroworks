#include "Marine.h"

#include "../Player/Player.h"

Marine::Marine()
{
	TransitionIdleState();
}

Marine::~Marine()
{
}

void Marine::start()
{
	movement = getActor()->getComponent<Movement>();

	GLTFStaticModel* model = getActor()->getModel();

	HP = 160;
}

void Marine::setState(int number)
{
	switch (number)
	{
	case 0:
		TransitionIdleState();
		break;
	case 1:
		TransitionWanderState();
		break;
	case 2:
		TransitionPursuitState();
		break;
	case 3:
		TransitionAttackState();
		break;
	case 4:
		TransitionDeathState();
		break;
	default:
		TransitionIdleState();
		break;
	}
}

void Marine::update(float elapsedTime)
{
	switch (state)
	{
	case Marine::State::Wander:
		UpdateWanderState(elapsedTime);
		break;
	case Marine::State::Idle:
		UpdateIdleState(elapsedTime);
		break;
	case Marine::State::Pursuit:
		UpdatePursuitState(elapsedTime);
		break;
	case Marine::State::Attack:
		UpdateAttackState(elapsedTime);
		break;
	case Marine::State::Damage:
		UpdateDamageState(elapsedTime);
		break;
	case Marine::State::Death:
		UpdateDeathState(elapsedTime);
		break;
	default:
		break;
	}

	collisionPosition = getActor()->getPosition();

	if (needMovement) movement->MoveToTarget(elapsedTime, 0.8f);
	if (this->getActor()->getComponent<Unit>()->HP <= 0) TransitionDeathState();
}

void Marine::TransitionWanderState()
{
	state = State::Wander;

	needMovement = true;
}

void Marine::UpdateWanderState(float elapsedTime)
{
	glm::vec3 position = getActor()->getPosition();
	if (glm::length(position - pointOfInterest) <= collisionRadius)
	{
		TransitionIdleState();
	}

	movement->SetTargetPosition(pointOfInterest);
}

void Marine::TransitionIdleState()
{
	state = State::Idle;

	needMovement = false;

	stateTimer = 1.5f;
}

void Marine::UpdateIdleState(float elapsedTime)
{
}

void Marine::TransitionPursuitState()
{
	state = State::Pursuit;

	needMovement = true;

	stateTimer = 1.0f;
}

void Marine::UpdatePursuitState(float elapsedTime)
{
	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	float distance = 999.f;

	for (auto it : actors)
	{
		if (it->getName() == targetName)
		{
			float newDisatance = sqrtf(pow(this->getActor()->getPosition().x - it->getPosition().x, 2) + pow(this->getActor()->getPosition().z - it->getPosition().z, 2));
			if (newDisatance < distance)
			{
				distance = newDisatance;
				pointOfInterest = it->getPosition();
			}
		}
	}

	movement->SetTargetPosition(pointOfInterest);

	if (distance < attackRange)
	{
		TransitionAttackState();
	}

	if (distance > 10.0f)
	{
		TransitionIdleState();
	}
}

void Marine::TransitionAttackState()
{
	state = State::Attack;

	needMovement = false;

	stateTimer = 3.5f;
}

void Marine::UpdateAttackState(float elapsedTime)
{
	stateTimer -= elapsedTime;

	if (stateTimer < 0.0f)
	{
		std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

		float distance = 999.f;

		for (auto it : actors)
		{
			if (it->getName() == targetName)
			{
				float newDisatance = sqrtf(pow(this->getActor()->getPosition().x - it->getPosition().x, 2) + pow(this->getActor()->getPosition().z - it->getPosition().z, 2));
				if (newDisatance < distance)
				{
					distance = newDisatance;
					pointOfInterest = it->getPosition();
				}
			}
		}

		if (distance < attackRange)
		{
			for (auto it : actors)
			{
				if (it->getName() == targetName)
				{
					if (it->getType() == "Unit")
					{
						it->getComponent<Unit>()->applyDamage(10);
					}
				}
			}
			TransitionAttackState();
		}
		else
		{
			TransitionWanderState();
		}
	}
}

void Marine::TransitionDamageState()
{
}

void Marine::UpdateDamageState(float elapsedTime)
{
}

void Marine::TransitionDeathState()
{
	state = State::Death;
}

void Marine::UpdateDeathState(float elapsedTime)
{
	ActorManager::Instance().remove(this->getActor());
}