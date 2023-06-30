#include "MinigameBull.h"

#include "../Player/Player.h"

MinigameBull::MinigameBull()
{
	TransitionWanderState();
}

MinigameBull::~MinigameBull()
{
}

void MinigameBull::setState(int number)
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

void MinigameBull::start()
{
	movement = getActor()->getComponent<Movement>();

	GLTFStaticModel* model = getActor()->getModel();

	int i = (rand() % spawnPositionDirection.size()) + 1;

	getActor()->setPosition(spawnPositionDirection[i].first);
	if (spawnPositionDirection[i].second == 0)
	{
		getActor()->setEuler(glm::vec3(0.f, glm::radians(90.f), 0.f));
		pointOfInterest = glm::vec3(getActor()->getPosition().x - 20.f, getActor()->getPosition().y, getActor()->getPosition().z);
	}

	if (spawnPositionDirection[i].second == 1)
	{
		getActor()->setEuler(glm::vec3(0.f, glm::radians(180.f), 0.f));
		pointOfInterest = glm::vec3(getActor()->getPosition().x, getActor()->getPosition().y, getActor()->getPosition().z + 20.f);
	}

	if (spawnPositionDirection[i].second == 2)
	{
		getActor()->setEuler(glm::vec3(0.f, glm::radians(-90.f), 0.f));
		pointOfInterest = glm::vec3(getActor()->getPosition().x + 20.f, getActor()->getPosition().y, getActor()->getPosition().z);
	}

	if (spawnPositionDirection[i].second == 3)
	{
		getActor()->setEuler(glm::vec3(0.f, glm::radians(0.f), 0.f));
		pointOfInterest = glm::vec3(getActor()->getPosition().x, getActor()->getPosition().y, getActor()->getPosition().z - 20.f);
	}
}

void MinigameBull::update(float elapsedTime)
{
	MinigameBullControl(elapsedTime);

	collisionPosition = getActor()->getPosition();
	collisionRadius = 0.3f;
}

void MinigameBull::MinigameBullControl(float elapsedTime)
{
	switch (state)
	{
	case MinigameBull::State::Idle:
		UpdateIdleState(elapsedTime);
		break;
	case MinigameBull::State::Wander:
		UpdateWanderState(elapsedTime);
		break;
	case MinigameBull::State::Death:
		UpdateDeathState(elapsedTime);
		break;
	default:
		break;
	}

	if (state != MinigameBull::State::Idle)
	{
		movement->MoveToTarget(elapsedTime, 1.1f);
	}
}

void MinigameBull::TransitionWanderState()
{
	state = State::Wander;
}

void MinigameBull::UpdateWanderState(float elapsedTime)
{
	if (timerToLive <= 0)
	{
		TransitionDeathState();
	}

	timerToLive -= elapsedTime;

	movement->SetTargetPosition(pointOfInterest);
}

void MinigameBull::TransitionIdleState()
{
	state = State::Idle;
}

void MinigameBull::UpdateIdleState(float elapsedTime)
{
}

void MinigameBull::TransitionDeathState()
{
	state = State::Death;
}

void MinigameBull::UpdateDeathState(float elapsedTime)
{
	ActorManager::Instance().remove(getActor());
}