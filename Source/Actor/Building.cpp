#include "Building.h"

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
	}

	if (getActor()->getTypeName() == "Hangar")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 1.f;
	}

	if (getActor()->getTypeName() == "Turret")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.5f;
	}

	if (getActor()->getTypeName() == "Mineral")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.5f;
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
			newActor->addComponent<Worker>(newActor->getName());

			timerToProduce = 5.f;
			recruteStart = false;
		}
	}
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
}