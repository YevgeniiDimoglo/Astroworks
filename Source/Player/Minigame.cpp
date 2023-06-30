#include "Minigame.h"

#include "../Graphics/Utilities.h"
#include "../Actor/MinigameBull.h"

Minigame::Minigame()
{
}

void Minigame::update(GLFWwindow* window, float elapsedTime)
{
	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	for (auto it : actors)
	{
		if (it->getName() == "Player1")
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				it->setPosition(glm::vec3(it->getPosition().x, it->getPosition().y, it->getPosition().z - movementSpeed * elapsedTime));
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				it->setPosition(glm::vec3(it->getPosition().x, it->getPosition().y, it->getPosition().z + movementSpeed * elapsedTime));
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				it->setPosition(glm::vec3(it->getPosition().x - movementSpeed * elapsedTime, it->getPosition().y, it->getPosition().z));
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				it->setPosition(glm::vec3(it->getPosition().x + movementSpeed * elapsedTime, it->getPosition().y, it->getPosition().z));
			}

			for (auto jt : actors)
			{
				if (jt->getTypeName() == "Bull")
				{
					if (!invincible)
					{
						float distance = glm::length(it->getPosition() - jt.get()->getComponent<Unit>()->getCollisionPosition());

						if (distance <= it.get()->getComponent<Unit>()->getCollisionRadius() + jt.get()->getComponent<Unit>()->getCollisionRadius())
						{
							health--;
							invincible = true;
							std::cout << health << std::endl;
						}
					}
				}
			}
		}
	}

	if (timerRound <= 0)
	{
		std::shared_ptr<Actor> actor = ActorManager::Instance().create();
		actor->loadModel("./Data/SpaceKit/craft_racer.glb");
		actor->setName("it.name" + std::to_string(bullCount));
		actor->setScale(glm::vec3(0.75f, 0.75f, 0.75f));
		actor->setType("Unit");
		actor->setTypeName("Bull");
		actor->addComponent<Movement>();
		actor->addComponent<MinigameBull>();

		timerRound = 5.0f;
	}

	timerRound -= elapsedTime;

	if (invincible = true)
	{
		invincibleTimer -= elapsedTime;
	}

	if (invincibleTimer <= 0)
	{
		invincible = false;
		invincibleTimer = 3.0f;
	}

	if (health == 0)
	{
		std::cout << "GAME OVER" << std::endl;
	}
}