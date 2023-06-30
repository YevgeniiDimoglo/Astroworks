#include "Player.h"
#include "../Actor/Worker.h"

int Player::value = 0;

Player::Player()
{
}

std::string Player::calculateScreenToWorldCoords(GLFWwindow* window, Camera& camera)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	ypos = height - ypos;

	glm::mat4x4 projection = camera.getProjection();
	glm::mat4x4 view = glm::lookAt(camera.getEye(), camera.getFocus(), glm::vec3(0.f, 1.f, 0.f));

	glm::vec3 dirStart = glm::unProject(
		glm::vec3(xpos, ypos, 0.f),
		view,
		projection,
		glm::vec4(0, 0, width, height));

	glm::vec3 dirEnd = glm::unProject(
		glm::vec3(xpos, ypos, 1.f),
		view,
		projection,
		glm::vec4(0, 0, width, height));

	glm::vec3 rayDirection = glm::normalize(dirEnd - dirStart);

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	for (auto it : actors)
	{
		if (it->getType() == "Building" || it->getType() == "Unit")
		{
			glm::vec3 rayToSphere = it->getPosition() - dirStart;
			float rayDotSphere = glm::dot(rayToSphere, rayDirection);
			if (rayDotSphere < 0.0) continue;

			float distanceToCenterSq = glm::dot(rayToSphere, rayToSphere) - rayDotSphere * rayDotSphere;
			float sphereRadiusSq = it.get()->getComponent<Unit>()->getCollisionRadius() * it.get()->getComponent<Unit>()->getCollisionRadius();
			if (distanceToCenterSq > sphereRadiusSq) continue;

			float distanceAlongRay = sqrt(sphereRadiusSq - distanceToCenterSq);

			return it->getName();
		}
		else
		{
			float denominator = glm::dot(glm::vec3(0.f, 0.f, 0.f), -glm::vec3(0.f, 1.f, 0.f));

			float t = -(denominator + glm::dot(dirStart, glm::vec3(0.f, 1.f, 0.f))) / glm::dot(rayDirection, glm::vec3(0.f, 1.f, 0.f));
			glm::vec3 intersectionPoint = dirStart + (rayDirection * t);

			movementPoint = intersectionPoint;
		}
		return "";
	}
}

void Player::update()
{
	if (selectedActorName.empty()) return;

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	for (auto it : actors)
	{
		if (it->getName() == selectedActorName)
		{
			if (it->getTypeName() == "Mineral")
			{
				selectedActorName.clear();
				selectedTargetName.clear();

				return;
			}

			if (movementPoint != glm::vec3(0.f, 0.f, 0.f))
			{
				it->getComponent<Worker>()->setPointOfInterest(movementPoint, false);
				it->getComponent<Worker>()->setState(1);

				selectedActorName.clear();
				selectedTargetName.clear();
				movementPoint = { 0.f, 0.f, 0.f };

				return;
			}

			for (auto jt : actors)
			{
				if (jt->getName() == selectedTargetName)
				{
					it->getComponent<Worker>()->setPointOfInterest(jt->getPosition(), true);
					it->getComponent<Worker>()->setState(1);

					selectedActorName.clear();
					selectedTargetName.clear();

					return;
				}
			}
		}
	}
}