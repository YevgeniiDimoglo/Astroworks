#include "Tank.h"

#include "../Player/Player.h"

Tank::Tank()
{
	TransitionIdleState();
}

Tank::~Tank()
{
}

void Tank::start()
{
	movement = getActor()->getComponent<Movement>();

	GLTFStaticModel* model = getActor()->getModel();

	HP = 150;
}

void Tank::setState(int number)
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

void Tank::update(float elapsedTime)
{
	switch (state)
	{
	case Tank::State::Wander:
		UpdateWanderState(elapsedTime);
		break;
	case Tank::State::Idle:
		UpdateIdleState(elapsedTime);
		break;
	case Tank::State::Pursuit:
		UpdatePursuitState(elapsedTime);
		break;
	case Tank::State::Attack:
		UpdateAttackState(elapsedTime);
		break;
	case Tank::State::Damage:
		UpdateDamageState(elapsedTime);
		break;
	case Tank::State::Death:
		UpdateDeathState(elapsedTime);
		break;
	default:
		break;
	}

	collisionPosition = getActor()->getPosition();

	if (needMovement) movement->MoveToTarget(elapsedTime, 0.2f);
	if (this->getActor()->getComponent<Unit>()->HP <= 0) TransitionDeathState();
}

void Tank::TransitionWanderState()
{
	state = State::Wander;

	needMovement = true;
}

void Tank::UpdateWanderState(float elapsedTime)
{
	glm::vec3 position = getActor()->getPosition();
	if (glm::length(position - pointOfInterest) <= collisionRadius)
	{
		TransitionIdleState();
	}

	movement->SetTargetPosition(pointOfInterest);
}

void Tank::TransitionIdleState()
{
	state = State::Idle;

	needMovement = false;

	stateTimer = 1.5f;
}

void Tank::UpdateIdleState(float elapsedTime)
{
}

void Tank::TransitionPursuitState()
{
	state = State::Pursuit;

	needMovement = true;

	stateTimer = 1.0f;
}

void Tank::UpdatePursuitState(float elapsedTime)
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

void Tank::TransitionAttackState()
{
	state = State::Attack;

	needMovement = false;

	stateTimer = 3.5f;
}

void Tank::UpdateAttackState(float elapsedTime)
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

void Tank::TransitionDamageState()
{
}

void Tank::UpdateDamageState(float elapsedTime)
{
}

void Tank::TransitionDeathState()
{
	state = State::Death;
}

void Tank::UpdateDeathState(float elapsedTime)
{
	ActorManager::Instance().remove(this->getActor());
}