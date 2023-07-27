#include "Alien.h"

#include "../Player/Player.h"

#include "../Actor/Building.h"

Alien::Alien()
{
	TransitionIdleState();
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
	movement = getActor()->getComponent<Movement>();

	GLTFStaticModel* model = getActor()->getModel();

	HP = 160;
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
	case Alien::State::Damage:
		UpdateDamageState(elapsedTime);
		break;
	case Alien::State::Death:
		UpdateDeathState(elapsedTime);
		break;
	default:
		break;
	}

	collisionPosition = getActor()->getPosition();

	if (needMovement) movement->MoveToTarget(elapsedTime, 0.8f);
	if (this->getActor()->getComponent<Unit>()->HP <= 0) TransitionDeathState();
}

bool Alien::searchEnemy()
{
	for (auto it : Player::Instance().getControlledActors())
	{
		float vx = it->getPosition().x - this->getActor()->getPosition().x;
		float vy = it->getPosition().y - this->getActor()->getPosition().y;
		float vz = it->getPosition().z - this->getActor()->getPosition().z;
		float dist = sqrtf(vx * vx + vy * vy + vz * vz);
		if (dist < searchRange)
		{
			return true;

			//float distXZ = sqrtf(vx * vx + vz * vz);

			//vx /= distXZ;
			//vz /= distXZ;

			//float frontX = sinf(this->getActor()->getEuler().y);
			//float frontZ = cosf(this->getActor()->getEuler().y);

			//float dot = (frontX * vx) + (frontZ * vz);
			//if (dot > 0.f)
			//{
			//	return true;
			//}
		}
	}
	return false;
}

void Alien::TransitionWanderState()
{
	state = State::Wander;

	movement->SetRandomTargetPosition();

	needMovement = true;
}

void Alien::UpdateWanderState(float elapsedTime)
{
	glm::vec3 position = getActor()->getPosition();
	if (glm::length(position - pointOfInterest) <= collisionRadius)
	{
		TransitionIdleState();
	}

	if (searchEnemy())
	{
		TransitionPursuitState();
	}
}

void Alien::TransitionIdleState()
{
	state = State::Idle;

	stateTimer = 1.5f;

	needMovement = false;
}

void Alien::UpdateIdleState(float elapsedTime)
{
	stateTimer -= elapsedTime;

	if (stateTimer < 0.0f)
	{
		TransitionWanderState();
	}

	if (searchEnemy())
	{
		TransitionPursuitState();
	}
}

void Alien::TransitionPursuitState()
{
	state = State::Pursuit;

	stateTimer = 1.0f;

	needMovement = true;
}

void Alien::UpdatePursuitState(float elapsedTime)
{
	stateTimer -= elapsedTime;
	if (stateTimer < 0.0f)
	{
		TransitionIdleState();
	}

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	std::string clothestEnemyName;

	float distance = 999.f;

	for (auto it : actors)
	{
		if (it->getControllerName() == "Player")
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
}

void Alien::TransitionAttackState()
{
	state = State::Attack;

	stateTimer = 3.5f;
}

void Alien::UpdateAttackState(float elapsedTime)
{
	stateTimer -= elapsedTime;

	if (stateTimer < 0.0f)
	{
		std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

		std::string clothestEnemyName;

		float distance = 999.f;

		for (auto it : actors)
		{
			if (it->getControllerName() == "Player")
			{
				float newDisatance = sqrtf(pow(this->getActor()->getPosition().x - it->getPosition().x, 2) + pow(this->getActor()->getPosition().z - it->getPosition().z, 2));
				if (newDisatance < distance)
				{
					distance = newDisatance;
					pointOfInterest = it->getPosition();
					clothestEnemyName = it->getName();
				}
			}
		}

		if (distance < attackRange)
		{
			for (auto it : actors)
			{
				if (it->getName() == clothestEnemyName)
				{
					if (it->getType() == "Unit")
					{
						it->getComponent<Unit>()->applyDamage(10);
					}
					if (it->getType() == "Building")
					{
						it->getComponent<Building>()->applyDamage(100);
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

	needMovement = false;
}

void Alien::TransitionDamageState()
{
}

void Alien::UpdateDamageState(float elapsedTime)
{
}

void Alien::TransitionDeathState()
{
	state = State::Death;
}

void Alien::UpdateDeathState(float elapsedTime)
{
	ActorManager::Instance().remove(this->getActor());
}