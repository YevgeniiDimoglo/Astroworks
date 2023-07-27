#include "Enemy.h"

#include "../Actor/Unit.h"
#include "../Actor/Movement.h"
#include "../Actor/Alien.h"

#include "Player.h"

void Enemy::notify(std::string widgetName, int widgetAction)
{
}

void Enemy::spawn()
{
	switch (static_cast<int>(Player::Instance().getInGameTimer().TimeStamp()))
	{
	case 120:
		if (!lockspawn)
		{
			for (size_t i = 0; i < 10; i++)
			{
				glm::vec3 currentPosition = position;

				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/alien.glb");
				newActor->setName("NewAlien" + std::to_string(ActorManager::Instance().getUpdateActors().size()) + std::to_string(rand()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ currentPosition.x + rand() % 15 * 2.f, currentPosition.y, currentPosition.z + rand() % 15 * 2.f });
				newActor->setType("Unit");
				newActor->setTypeName("Alien");
				newActor->addComponent<Movement>();
				newActor->addComponent<Unit>();
				newActor->addComponent<Alien>();
				newActor->setShaderType(ShaderType::Phong);
			}
		};
		lockspawn = true;
		break;
	case 300:
		if (!lockspawn)
		{
			for (size_t i = 0; i < 30; i++)
			{
				glm::vec3 currentPosition = position;

				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/alien.glb");
				newActor->setName("NewAlien" + std::to_string(ActorManager::Instance().getUpdateActors().size()) + std::to_string(rand()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ currentPosition.x + rand() % 15 * 2.f, currentPosition.y, currentPosition.z + rand() % 15 * 2.f });
				newActor->setType("Unit");
				newActor->setTypeName("Alien");
				newActor->addComponent<Movement>();
				newActor->addComponent<Unit>();
				newActor->addComponent<Alien>();
				newActor->setShaderType(ShaderType::Phong);
			}
		};
		lockspawn = true;
		break;
	case 500:
		if (!lockspawn)
		{
			for (size_t i = 0; i < 50; i++)
			{
				glm::vec3 currentPosition = position;

				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/alien.glb");
				newActor->setName("NewAlien" + std::to_string(ActorManager::Instance().getUpdateActors().size()) + std::to_string(rand()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ currentPosition.x + rand() % 15 * 2.f, currentPosition.y, currentPosition.z + rand() % 15 * 2.f });
				newActor->setType("Unit");
				newActor->setTypeName("Alien");
				newActor->addComponent<Movement>();
				newActor->addComponent<Unit>();
				newActor->addComponent<Alien>();
				newActor->setShaderType(ShaderType::Phong);
			}
		};
		lockspawn = true;
		break;
	default:
		lockspawn = false;
		break;
	}
}

void Enemy::update()
{
	spawn();
}