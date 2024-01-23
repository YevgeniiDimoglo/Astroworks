#include "Player.h"

#include "../Input/Input.h"

#include "../Actor/ActorTypes.h"

#include "../UI/UI.h"

glm::vec2 BloomValues = { 1.0f, 0.0f };

std::string Player::getSelectedActor(GLFWwindow* window, Camera* camera)
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
				buildingReady = it->getComponent<Building>()->getReadyStatus();
				selectedActorIndex = 3;
			}
			else if (it->getTypeName() == "Hangar")
			{
				buildingReady = it->getComponent<Building>()->getReadyStatus();
				selectedActorIndex = 4;
			}
			else if (it->getTypeName() == "Turret")
			{
				buildingReady = it->getComponent<Building>()->getReadyStatus();
				selectedActorIndex = 5;
			}
			else if (it->getTypeName() == "Supply")
			{
				buildingReady = it->getComponent<Building>()->getReadyStatus();
				selectedActorIndex = 6;
			}
			else if (it->getTypeName() == "Marine")
			{
				selectedActorIndex = 7;
			}
			else if (it->getTypeName() == "Tank")
			{
				selectedActorIndex = 8;
			}

			selectedActors.push_back(it);
			return it->getName();
		}
	}

	selectedActorIndex = 0;
	selectedActors.clear();
	return "";
}

std::string Player::getTargetActor(GLFWwindow* window, Camera* camera)
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
	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();
	auto widgets = UI::Instance().getCurrentOverlay().getWidgets();

	if (widgetName == "start" && widgetAction == 0)
	{
		isPaused = false;
		inGameTimer.Start();
		selectedActorIndex = 0;
	}

	if (widgetName == "exit" && widgetAction == 0)
	{
		closeApp = true;
	}
}

void Player::input(GLFWwindow* window, Camera* camera)
{
	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	calculateScreenToWorldCoords(window, camera);

	if (closeApp)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Player::update()
{
	if (isPaused)
	{
		inGameTimer.Stop();
		return;
	}
	else
	{
		inGameTimer.Start();
	}

	inGameTimer.Tick();

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();
}

int Player::calculateScore()
{
	int totalScore = 0;

	for (auto it : controlledActors)
	{
		if (it->getTypeName() == "Base")
		{
			totalScore += 100;
		}
		if (it->getTypeName() == "Supply")
		{
			totalScore += 20;
		}
		if (it->getTypeName() == "Hangar")
		{
			totalScore += 50;
		}
		if (it->getTypeName() == "Turret")
		{
			totalScore += 10;
		}
		if (it->getTypeName() == "Worker")
		{
			totalScore += 1;
		}
		if (it->getTypeName() == "Marine")
		{
			totalScore += 2;
		}
		if (it->getTypeName() == "Tank")
		{
			totalScore += 5;
		}
	}

	return totalScore;
}

void Player::calculateScreenToWorldCoords(GLFWwindow* window, Camera* camera)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	ypos = height - ypos;

	glm::mat4x4 projection = camera->getProjection();
	glm::mat4x4 view = glm::lookAt(camera->getEye(), camera->getFocus(), glm::vec3(0.f, 1.f, 0.f));

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

bool Player::checkSupplyAvailability(int additionalValue)
{
	if (currentSupplyValue + additionalValue > overallSupplyValue) return false;
	return true;
}

bool Player::checkResourceAvailability(int additionalValue)
{
	if (mineralValue - additionalValue < 0) return false;
	mineralValue -= additionalValue;
	return true;
}