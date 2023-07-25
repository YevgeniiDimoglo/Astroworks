#include "Worker.h"
#include "../Player/Player.h"

#include "../Actor/Building.h"

Worker::Worker()
{
	TransitionIdleState();
}

Worker::~Worker()
{
}

void Worker::execute()
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
	case 2:
		TransitionSearchState();
		break;
	case 3:
		TransitionGatherState();
		break;
	case 4:
		TransitionReturnState();
		break;
	case 5:
		TransitionBuildingState();
		break;
	case 6:
		TransitionAttackState();
		break;
	case 7:
		TransitionDeathState();
		break;
	default:
		TransitionIdleState();
		break;
	}
}

void Worker::start()
{
	movement = getActor()->getComponent<Movement>();

	GLTFStaticModel* model = getActor()->getModel();

	HP = 60;
}

void Worker::update(float elapsedTime)
{
	workerControl(elapsedTime);

	collisionPosition = getActor()->getPosition();
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
	case Worker::State::Building:
		UpdateBuildingState(elapsedTime);
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
	if (this->getActor()->getComponent<Unit>()->HP <= 0) TransitionDeathState();
}

void Worker::TransitionWanderState()
{
	state = State::Wander;
	needMovement = true;
}

void Worker::UpdateWanderState(float elapsedTime)
{
	glm::vec3 position = getActor()->getPosition();
	if (glm::length(position - pointOfInterest) <= collisionRadius)
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

void Worker::TransitionBuildingState()
{
	state = State::Building;

	needMovement = true;
}

void Worker::UpdateBuildingState(float elapsedTime)
{
	float newDisatance = sqrtf(pow(this->getActor()->getPosition().x - pointOfInterest.x, 2) + pow(this->getActor()->getPosition().z - pointOfInterest.z, 2));
	if (newDisatance < 0.1f)
	{
		if (buildingType == "Base")
		{
			std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
			newActor->loadModel("./Data/SpaceKit/hangar_roundGlass.glb");
			newActor->setName("TempBuilding" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
			newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
			newActor->setPosition({ pointOfInterest.x, pointOfInterest.y , pointOfInterest.z });
			newActor->setType("Building");
			newActor->setTypeName("Base");
			newActor->addComponent<Building>();
			newActor->getComponent<Building>()->setState(0);
			Player::Instance().emplaceActor(newActor);
		}
		else if (buildingType == "Supply")
		{
			std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
			newActor->loadModel("./Data/SpaceKit/machine_barrelLarge.glb");
			newActor->setName("TempBuilding" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
			newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
			newActor->setPosition({ pointOfInterest.x, pointOfInterest.y , pointOfInterest.z });
			newActor->setType("Building");
			newActor->setTypeName("Supply");
			newActor->addComponent<Building>();
			newActor->getComponent<Building>()->setState(0);
			Player::Instance().emplaceActor(newActor);
		}
		else if (buildingType == "Hangar")
		{
			std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
			newActor->loadModel("./Data/SpaceKit/hangar_smallB.glb");
			newActor->setName("TempBuilding" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
			newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
			newActor->setPosition({ pointOfInterest.x, pointOfInterest.y , pointOfInterest.z });
			newActor->setType("Building");
			newActor->setTypeName("Hangar");
			newActor->addComponent<Building>();
			newActor->getComponent<Building>()->setState(0);
			Player::Instance().emplaceActor(newActor);
		}
		else if (buildingType == "Turret")
		{
			std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
			newActor->loadModel("./Data/SpaceKit/turret_double.glb");
			newActor->setName("TempBuilding" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
			newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
			newActor->setPosition({ pointOfInterest.x, pointOfInterest.y , pointOfInterest.z });
			newActor->setType("Building");
			newActor->setTypeName("Turret");
			newActor->addComponent<Building>();
			newActor->getComponent<Building>()->setState(0);
			Player::Instance().emplaceActor(newActor);
		}

		Player::Instance().selectedActorName.clear();
		Player::Instance().selectedTargetName.clear();
		Player::Instance().setSelectedActorIndex(0);
		Player::Instance().buildingMode = false;

		TransitionDeathState();
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
	Player::Instance().removeActor(this->getActor());
	ActorManager::Instance().remove(this->getActor());
}