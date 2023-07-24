#include "Building.h"

#include "../Player/Player.h"

#include "../Actor/Actor.h"
#include "../Actor/Unit.h"
#include "../Actor/Worker.h"

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

	// Produce worker
	if (getActor()->getTypeName() == "Base")
	{
		if (timerToProduce <= 0)
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
			recruteStart = false;
		}
	}

	getActor()->setTimer({ currentBuildingTime / buildingTime, 0.f, 0.f, 0.f });
}

void Building::execute()
{
	recruteStart = true;
}

void Building::buildingControl(float elapsedTime)
{
	if (recruteStart)
	{
		timerToProduce -= elapsedTime;
	}

	if (buildingStart)
	{
		currentBuildingTime += elapsedTime;
	}

	if (currentBuildingTime >= buildingTime)
	{
		finished = true;
	}

	if (!finished)
	{
		getActor()->setShaderType(ShaderType::PhongDissolve);
	}
	else
	{
		getActor()->setShaderType(ShaderType::Phong);
	}

	if (HP <= 0)
	{
		ActorManager::Instance().remove(this->getActor());
	}
}