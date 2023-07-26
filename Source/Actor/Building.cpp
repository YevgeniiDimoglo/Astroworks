#include "Building.h"

#include "../Player/Player.h"

#include "../Actor/Actor.h"

#include "../Actor/Unit.h"
#include "../Actor/Worker.h"
#include "../Actor//Marine.h"
#include "../Actor/Tank.h"

#include "../Actor/Movement.h"

void Building::start()
{
	GLTFStaticModel* model = getActor()->getModel();

	// Setup collisions
	if (getActor()->getTypeName() == "Base")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 1.f;
		buildingTime = 75.6f;
		HP = 1500;
	}

	if (getActor()->getTypeName() == "Supply")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 1.f;
		buildingTime = 25.4f;
		HP = 500;
	}

	if (getActor()->getTypeName() == "Hangar")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 1.f;
		buildingTime = 50.4f;
		HP = 1000;
	}

	if (getActor()->getTypeName() == "Turret")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.5f;
		buildingTime = 18.9f;
		HP = 200;
	}

	if (getActor()->getTypeName() == "Mineral")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.5f;
		buildingTime = 999.f;
		HP = 9999;
	}
}

void Building::update(float elapsedTime)
{
	buildingControl(elapsedTime);

	switch (state)
	{
	case Building::State::Construction:
		UpdateConstructionState(elapsedTime);
		break;
	case Building::State::Finished:
		UpdateFinishedState(elapsedTime);
		break;
	case Building::State::Production:
		UpdateProductionState(elapsedTime);
		break;
	case Building::State::Destroyed:
		UpdateDestroyedState(elapsedTime);
		break;
	default:
		break;
	}

	if (this->getActor()->getComponent<Building>()->HP <= 0) TransitionDestroyedState();
}

void Building::setState(int number)
{
	switch (number)
	{
	case 0:
		TransitionConstructionState();
		break;
	case 1:
		TransitionFinishedState();
		break;
	case 2:
		TransitionProductionState();
		break;
	case 3:
		TransitionDestroyedState();
		break;
	}
}

void Building::execute()
{
	TransitionProductionState();
}

void Building::applyDamage(int damage)
{
	HP -= damage;
}

void Building::buildingControl(float elapsedTime)
{
}

void Building::TransitionConstructionState()
{
	state = State::Construction;

	getActor()->setShaderType(ShaderType::PhongDissolve);
}

void Building::UpdateConstructionState(float elapsedTime)
{
	currentBuildingTime += elapsedTime;

	getActor()->setTimer({ currentBuildingTime / buildingTime, 0.f, 0.f, 0.f });

	if (currentBuildingTime >= buildingTime) TransitionFinishedState();
}

void Building::TransitionFinishedState()
{
	state = State::Finished;

	getActor()->setShaderType(ShaderType::Phong);
}

void Building::UpdateFinishedState(float elapsedTime)
{
}

void Building::TransitionProductionState()
{
	state = State::Production;
}

void Building::UpdateProductionState(float elapsedTime)
{
	timerToProduce -= elapsedTime;

	if (getActor()->getTypeName() == "Base")
	{
		if (timerToProduce <= 0)
		{
			if (produceUnitNumber == 1)
			{
				std::shared_ptr<Actor> thisActor = getActor();
				glm::vec3 currentPosition = thisActor->getPosition();

				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/astronautA.glb");
				newActor->setName("NewWorker" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ currentPosition.x + 2.f, currentPosition.y, currentPosition.z + 2.f });
				newActor->setType("Unit");
				newActor->setTypeName("Worker");
				newActor->addComponent<Movement>();
				newActor->addComponent<Unit>();
				newActor->addComponent<Worker>();
				newActor->setShaderType(ShaderType::Phong);
				newActor->setControllerName("Player");

				Player::Instance().emplaceActor(newActor);

				timerToProduce = 5.f;

				TransitionFinishedState();
			}
		}
	}

	if (getActor()->getTypeName() == "Hangar")
	{
		if (timerToProduce <= 0)
		{
			if (produceUnitNumber == 1)
			{
				std::shared_ptr<Actor> thisActor = getActor();
				glm::vec3 currentPosition = thisActor->getPosition();

				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/astronautB.glb");
				newActor->setName("NewMarine" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ currentPosition.x + 2.f, currentPosition.y, currentPosition.z + 2.f });
				newActor->setType("Unit");
				newActor->setTypeName("Marine");
				newActor->addComponent<Movement>();
				newActor->addComponent<Unit>();
				newActor->addComponent<Marine>();
				newActor->setShaderType(ShaderType::Phong);
				newActor->setControllerName("Player");

				Player::Instance().emplaceActor(newActor);

				timerToProduce = 13.f;

				TransitionFinishedState();
			}

			if (produceUnitNumber == 2)
			{
				std::shared_ptr<Actor> thisActor = getActor();
				glm::vec3 currentPosition = thisActor->getPosition();

				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/craft_miner.glb");
				newActor->setName("NewTank" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
				newActor->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
				newActor->setPosition({ currentPosition.x + 2.f, currentPosition.y, currentPosition.z + 2.f });
				newActor->setType("Unit");
				newActor->setTypeName("Tank");
				newActor->addComponent<Movement>();
				newActor->addComponent<Unit>();
				newActor->addComponent<Tank>();
				newActor->setShaderType(ShaderType::Phong);
				newActor->setControllerName("Player");

				Player::Instance().emplaceActor(newActor);

				timerToProduce = 32.f;

				TransitionFinishedState();
			}

			produceUnitNumber = 0;
		}
	}
}

void Building::TransitionDestroyedState()
{
	state = State::Destroyed;
}

void Building::UpdateDestroyedState(float elapsedTime)
{
	Player::Instance().removeActor(this->getActor());
	ActorManager::Instance().remove(this->getActor());
}