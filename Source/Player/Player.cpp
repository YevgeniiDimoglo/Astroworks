#include "Player.h"
#include "../Actor/Worker.h"

int Player::value = 0;
int Player::selectedActorIndex = 0;

Player::Player()
{
}

std::string Player::getSelectedActor(GLFWwindow* window, Camera& camera)
{
	calculateScreenToWorldCoords(window, camera);

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	for (auto it : actors)
	{
		if (it->getType() == "Building" || it->getType() == "Unit")
		{
			glm::vec3 rayToSphere = it->getPosition() - cameraRay.rayStart;
			float rayDotSphere = glm::dot(rayToSphere, cameraRay.rayDirection);
			if (rayDotSphere < 0.0) continue;

			float distanceToCenterSq = glm::dot(rayToSphere, rayToSphere) - rayDotSphere * rayDotSphere;
			float sphereRadiusSq = it.get()->getComponent<Unit>()->getCollisionRadius() * it.get()->getComponent<Unit>()->getCollisionRadius();
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

			return it->getName();
		}
		else
		{
			selectedActorIndex = 0;
			return "";
		}
	}
}

std::string Player::getTargetActor(GLFWwindow* window, Camera& camera)
{
	std::string targetActorName = "";

	calculateScreenToWorldCoords(window, camera);

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	for (auto it : actors)
	{
		if (it->getType() == "Building" || it->getType() == "Unit")
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
	}

	if (targetActorName != "") return targetActorName;

	float denominator = glm::dot(glm::vec3(0.f, 0.f, 0.f), -glm::vec3(0.f, 1.f, 0.f));

	float t = -(denominator + glm::dot(cameraRay.rayStart, glm::vec3(0.f, 1.f, 0.f))) / glm::dot(cameraRay.rayDirection, glm::vec3(0.f, 1.f, 0.f));
	glm::vec3 intersectionPoint = cameraRay.rayStart + (cameraRay.rayDirection * t);

	movementPoint = intersectionPoint;
	return "terrain";
}

void Player::notify(std::string widgetName, int widgetAction) const
{
}

void Player::input(GLFWwindow* window, Camera camera)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (!inputLockLMB)
		{
			selectedActorName = getSelectedActor(window, camera);
			inputLockLMB = true;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		inputLockLMB = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (!inputLockRMB)
		{
			selectedTargetName = getTargetActor(window, camera);
			inputLockRMB = true;
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
	}
}

void Player::update()
{
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