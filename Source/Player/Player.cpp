#include "Player.h"

#include "../Actor/Worker.h"
#include "../Actor/Building.h"

std::string Player::getSelectedActor(GLFWwindow* window, Camera& camera)
{
	selectedActors.clear();

	for (auto it : controlledActors)
	{
		if (it->getType() == "Building" || it->getType() == "Unit")
		{
			glm::vec3 rayToSphere = it->getPosition() - cameraRay.rayStart;
			float rayDotSphere = glm::dot(rayToSphere, cameraRay.rayDirection);
			if (rayDotSphere < 0.0) continue;

			float distanceToCenterSq = glm::dot(rayToSphere, rayToSphere) - rayDotSphere * rayDotSphere;

			float sphereRadiusSq = 0.f;

			if (it->getType() == "Unit")
			{
				sphereRadiusSq = it.get()->getComponent<Unit>()->getCollisionRadius() * it.get()->getComponent<Unit>()->getCollisionRadius();
			}
			else if (it->getType() == "Building")
			{
				sphereRadiusSq = it.get()->getComponent<Building>()->getCollisionRadius() * it.get()->getComponent<Building>()->getCollisionRadius();
			}

			if (distanceToCenterSq > sphereRadiusSq) continue;

			float distanceAlongRay = sqrt(sphereRadiusSq - distanceToCenterSq);

			if (it->getTypeName() == "Worker")
			{
				selectedActorIndex = 1;
			}
			else if (it->getTypeName() == "Mineral")
			{
				selectedActorIndex = 2;
			}
			else if (it->getTypeName() == "Base")
			{
				selectedActorIndex = 3;
			}
			else if (it->getTypeName() == "Hangar")
			{
				selectedActorIndex = 4;
			}
			else if (it->getTypeName() == "Turret")
			{
				selectedActorIndex = 5;
			}

			selectedActors.push_back(it);
			return it->getName();
		}
	}

	selectedActorIndex = 0;
	selectedActors.clear();
	return "";
}

std::string Player::getTargetActor(GLFWwindow* window, Camera& camera)
{
	std::string targetActorName = "";

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	for (auto it : actors)
	{
		if (it->getType() == "Unit")
		{
			glm::vec3 rayToSphere = it->getPosition() - cameraRay.rayStart;
			float rayDotSphere = glm::dot(rayToSphere, cameraRay.rayDirection);
			if (rayDotSphere < 0.0) continue;

			float distanceToCenterSq = glm::dot(rayToSphere, rayToSphere) - rayDotSphere * rayDotSphere;
			float sphereRadiusSq = it.get()->getComponent<Unit>()->getCollisionRadius() * it.get()->getComponent<Unit>()->getCollisionRadius();
			if (distanceToCenterSq > sphereRadiusSq) continue;

			float distanceAlongRay = sqrt(sphereRadiusSq - distanceToCenterSq);

			targetActorName = it->getName();
			break;
		}

		if (it->getType() == "Building")
		{
			glm::vec3 rayToSphere = it->getPosition() - cameraRay.rayStart;
			float rayDotSphere = glm::dot(rayToSphere, cameraRay.rayDirection);
			if (rayDotSphere < 0.0) continue;

			float distanceToCenterSq = glm::dot(rayToSphere, rayToSphere) - rayDotSphere * rayDotSphere;
			float sphereRadiusSq = it.get()->getComponent<Building>()->getCollisionRadius() * it.get()->getComponent<Building>()->getCollisionRadius();
			if (distanceToCenterSq > sphereRadiusSq) continue;

			float distanceAlongRay = sqrt(sphereRadiusSq - distanceToCenterSq);

			targetActorName = it->getName();
			break;
		}
	}

	if (targetActorName != "") return targetActorName;

	float denominator = glm::dot(glm::vec3(0.f, 0.f, 0.f), -glm::vec3(0.f, 1.f, 0.f));

	float t = -(denominator + glm::dot(cameraRay.rayStart, glm::vec3(0.f, 1.f, 0.f))) / glm::dot(cameraRay.rayDirection, glm::vec3(0.f, 1.f, 0.f));
	glm::vec3 intersectionPoint = cameraRay.rayStart + (cameraRay.rayDirection * t);

	movementPoint = intersectionPoint;
	return "terrain";
}

void Player::notify(std::string widgetName, int widgetAction)
{
	// Change widget name to unique widget name

	if (widgetName == "start" && widgetAction == 0)
	{
		isPaused = false;
		selectedActorIndex = 0;
	}

	if (widgetName == "astronautA" && widgetAction == 0)
	{
		for (auto it : selectedActors)
		{
			it.get()->getComponent<Building>()->execute();
		}
	}

	if (!buildingBlock)
	{
		if (widgetName == "hangar_roundGlass" && widgetAction == 0)
		{
			ActorManager::Instance().remove(prebuildActor);
			prebuildActor.reset();

			for (auto it : selectedActors)
			{
				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/hangar_roundGlass.glb");
				newActor->setName("TempBuilding" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ 0.f, 0.f , 0.f });
				newActor->setType("Building");
				newActor->setTypeName("Base");
				newActor->addComponent<Building>();
				newActor->setShaderType(ShaderType::Phong);
				newActor->setShaderSubType(ShaderType::PhongTransparency);
				newActor->getComponent<Building>()->setCurrentBuildingTime(1000.f);

				prebuildActor = newActor;

				it.get()->getComponent<Worker>()->execute();

				buildingBlock = true;
				buildingMode = true;
			}
		}

		if (widgetName == "hangar_smallB" && widgetAction == 0)
		{
			ActorManager::Instance().remove(prebuildActor);
			prebuildActor.reset();

			for (auto it : selectedActors)
			{
				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/hangar_smallB.glb");
				newActor->setName("TempBuilding" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ 0.f, 0.f , 0.f });
				newActor->setType("Building");
				newActor->setTypeName("Hangar");
				newActor->addComponent<Building>();
				newActor->setShaderType(ShaderType::Phong);
				newActor->setShaderSubType(ShaderType::PhongTransparency);
				newActor->getComponent<Building>()->setCurrentBuildingTime(1000.f);

				prebuildActor = newActor;

				it.get()->getComponent<Worker>()->execute();

				buildingBlock = true;
				buildingMode = true;
			}
		}

		if (widgetName == "turret_double" && widgetAction == 0)
		{
			ActorManager::Instance().remove(prebuildActor);
			prebuildActor.reset();

			for (auto it : selectedActors)
			{
				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/turret_double.glb");
				newActor->setName("TempBuilding" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ 0.f, 0.f , 0.f });
				newActor->setType("Building");
				newActor->setTypeName("Turret");
				newActor->addComponent<Building>();
				newActor->setShaderType(ShaderType::Phong);
				newActor->setShaderSubType(ShaderType::PhongTransparency);
				newActor->getComponent<Building>()->setCurrentBuildingTime(1000.f);

				prebuildActor = newActor;

				it.get()->getComponent<Worker>()->execute();

				buildingBlock = true;
				buildingMode = true;
			}
		}
	}
}

void Player::input(GLFWwindow* window, Camera camera)
{
	calculateScreenToWorldCoords(window, camera);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		if (ypos / height >= 0.7f)
		{
		}
		else
		{
			if (!inputLockLMB)
			{
				if (buildingMode)
				{
					for (auto it : selectedActors)
					{
						it.get()->getComponent<Worker>()->setState(5);
						it.get()->getComponent<Worker>()->setPointOfInterest(prebuildActor->getPosition(), false);
						it.get()->getComponent<Worker>()->setBuildingType(prebuildActor->getTypeName());
					}

					inputLockLMB = true;
					buildingMode = false;
					ActorManager::Instance().remove(prebuildActor);
					prebuildActor.reset();
				}
				else
				{
					selectedActorName = getSelectedActor(window, camera);
					inputLockLMB = true;
				}
			}
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		inputLockLMB = false;
		buildingBlock = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		if (ypos / height >= 0.7f)
		{
		}
		else
		{
			if (!inputLockRMB)
			{
				selectedTargetName = getTargetActor(window, camera);
				inputLockRMB = true;
			}
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		inputLockRMB = false;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		selectedActorName.clear();
		selectedTargetName.clear();
		selectedActorIndex = 0;

		ActorManager::Instance().remove(prebuildActor);
		prebuildActor.reset();
		buildingMode = false;
	}
}

void Player::update()
{
	if (isPaused) return;

	if (prebuildActor != nullptr)
	{
		float denominator = glm::dot(glm::vec3(0.f, 0.f, 0.f), -glm::vec3(0.f, 1.f, 0.f));
		float t = -(denominator + glm::dot(cameraRay.rayStart, glm::vec3(0.f, 1.f, 0.f))) / glm::dot(cameraRay.rayDirection, glm::vec3(0.f, 1.f, 0.f));
		glm::vec3 intersectionPoint = cameraRay.rayStart + (cameraRay.rayDirection * t);
		prebuildActor->setPosition(intersectionPoint);
	}

	if (selectedActorName.empty() || selectedTargetName.empty()) return;

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	for (auto it : actors)
	{
		if (it->getName() == selectedActorName)
		{
			if (it->getTypeName() == "Worker")
			{
				if (selectedTargetName == "terrain")
				{
					it->getComponent<Worker>()->setPointOfInterest(movementPoint, false);
					it->getComponent<Worker>()->setState(1);

					selectedTargetName.clear();

					return;
				}
				else
				{
					for (auto jt : actors)
					{
						if (jt->getName() == selectedTargetName)
						{
							it->getComponent<Worker>()->setPointOfInterest(jt->getPosition(), true);
							it->getComponent<Worker>()->setState(1);

							selectedTargetName.clear();

							return;
						}
					}
				}
			}
		}
	}
}

void Player::calculateScreenToWorldCoords(GLFWwindow* window, Camera& camera)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	ypos = height - ypos;

	glm::mat4x4 projection = camera.getProjection();
	glm::mat4x4 view = glm::lookAt(camera.getEye(), camera.getFocus(), glm::vec3(0.f, 1.f, 0.f));

	cameraRay.rayStart = glm::unProject(
		glm::vec3(xpos, ypos, 0.f),
		view,
		projection,
		glm::vec4(0, 0, width, height));

	cameraRay.rayEnd = glm::unProject(
		glm::vec3(xpos, ypos, 1.f),
		view,
		projection,
		glm::vec4(0, 0, width, height));

	cameraRay.rayDirection = glm::normalize(cameraRay.rayEnd - cameraRay.rayStart);
}