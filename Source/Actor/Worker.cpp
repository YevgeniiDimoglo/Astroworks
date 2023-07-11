#include "Worker.h"
#include "../Player/Player.h"

Worker::Worker(std::string name)
{
	TransitionIdleState();
}

Worker::~Worker()
{
}

void Worker::setState(int number)
{
	switch (number)
	{
	case 0:
		TransitionIdleState();
		break;

	case 1:
		TransitionWanderState();
		break;
	}
}

void Worker::start()
{
	movement = getActor()->getComponent<Movement>();

	GLTFStaticModel* model = getActor()->getModel();
}

void Worker::update(float elapsedTime)
{
	workerControl(elapsedTime);

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	collisionPosition = getActor()->getPosition();
	collisionRadius = 0.3f;
}

void Worker::workerControl(float elapsedTime)
{
	switch (state)
	{
	case Worker::State::Wander:
		UpdateWanderState(elapsedTime);
		break;
	case Worker::State::Idle:
		UpdateIdleState(elapsedTime);
		break;
	case Worker::State::Search:
		UpdateSearchState(elapsedTime);
		break;
	case Worker::State::Gather:
		UpdateGatherState(elapsedTime);
		break;
	case Worker::State::Return:
		UpdateReturnState(elapsedTime);
		break;
	case Worker::State::Attack:
		UpdateAttackState(elapsedTime);
		break;
	case Worker::State::Death:
		UpdateDeathState(elapsedTime);
		break;
	default:
		break;
	}

	if (needMovement) movement->MoveToTarget(elapsedTime, 1.f);
}

void Worker::TransitionWanderState()
{
	state = State::Wander;
	needMovement = true;
}

void Worker::UpdateWanderState(float elapsedTime)
{
	glm::vec3 position = getActor()->getPosition();
	if (glm::length(position - pointOfInterest) <= 0.1f)
	{
		if (mineral)
		{
			TransitionSearchState();
		}
		else
		{
			TransitionIdleState();
		}
	}

	movement->SetTargetPosition(pointOfInterest);
}

void Worker::TransitionIdleState()
{
	state = State::Idle;
	needMovement = false;
}

void Worker::UpdateIdleState(float elapsedTime)
{
}

void Worker::TransitionSearchState()
{
	state = State::Search;
	needMovement = true;
}

void Worker::UpdateSearchState(float elapsedTime)
{
	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	std::string clothestMineralName;

	float distance = 999.f;

	for (auto it : actors)
	{
		if (it->getTypeName() == "Mineral")
		{
			float newDisatance = sqrtf(pow(this->getActor()->getPosition().x - it->getPosition().x, 2) + pow(this->getActor()->getPosition().z - it->getPosition().z, 2));
			if (newDisatance < distance)
			{
				if (newDisatance < 0.5f)
				{
					TransitionGatherState();
				}
				distance = newDisatance;
				pointOfInterest = it->getPosition();
			}
		}
	}

	movement->SetTargetPosition(pointOfInterest);
}

void Worker::TransitionGatherState()
{
	state = State::Gather;

	needMovement = false;
}

void Worker::UpdateGatherState(float elapsedTime)
{
	if (gatherTime <= 0)
	{
		gatherTime = 2.f;
		TransitionReturnState();
	}

	gatherTime -= elapsedTime;
}

void Worker::TransitionReturnState()
{
	state = State::Return;

	needMovement = true;
}

void Worker::UpdateReturnState(float elapsedTime)
{
	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	std::string clothestMineralName;

	float distance = 999.f;

	for (auto it : actors)
	{
		if (it->getTypeName() == "Base")
		{
			float newDisatance = sqrtf(pow(this->getActor()->getPosition().x - it->getPosition().x, 2) + pow(this->getActor()->getPosition().z - it->getPosition().z, 2));
			if (newDisatance < distance)
			{
				if (newDisatance < 1.5f)
				{
					TransitionSearchState();
					Player::Instance().setMineralValue(Player::Instance().getMineralValue() + 20);
				}
				distance = newDisatance;
				pointOfInterest = it->getPosition();
			}
		}
	}

	movement->SetTargetPosition(pointOfInterest);
}

void Worker::TransitionAttackState()
{
	state = State::Attack;
}

void Worker::UpdateAttackState(float elapsedTime)
{
}

void Worker::TransitionDeathState()
{
	state = State::Death;
}

void Worker::UpdateDeathState(float elapsedTime)
{
}