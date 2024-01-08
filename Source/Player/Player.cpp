#include "Player.h"

#include "../Actor/Worker.h"
#include "../Actor/Marine.h"
#include "../Actor/Tank.h"

#include "../Actor/Building.h"

GLTFStaticModel::Material Player::currentMaterial;
GLTFStaticModel::Image Player::currentTexture;
glm::vec2 BloomValues = { 0.5f, 2.0f };
glm::vec4 Player::currentColor = { 1.0f, 1.0f, 1.0f, 1.0f };

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

	// Change widget name to unique widget name

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

	if (widgetName == "astronautA" && widgetAction == 0)
	{
		for (auto it : selectedActors)
		{
			it.get()->getComponent<Building>()->execute();
			it.get()->getComponent<Building>()->produceUnitNumber = 1;
		}
	}

	if (widgetName == "astronautB" && widgetAction == 0)
	{
		for (auto it : selectedActors)
		{
			it.get()->getComponent<Building>()->execute();
			it.get()->getComponent<Building>()->produceUnitNumber = 1;
		}
	}

	if (widgetName == "craft_miner" && widgetAction == 0)
	{
		for (auto it : selectedActors)
		{
			it.get()->getComponent<Building>()->execute();
			it.get()->getComponent<Building>()->produceUnitNumber = 2;
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
				if (Player::Instance().getMineralValue() <= 400)
				{
					newActor->setBaseColor({ 1.f, 0.f, 0.f, 0.5f });
				}
				else
				{
					newActor->setBaseColor({ 0.f, 1.f, 0.f, 0.5f });
				}
				newActor->getComponent<Building>()->setCurrentBuildingTime(1000.f);

				prebuildActor = newActor;

				it.get()->getComponent<Worker>()->execute();

				buildingBlock = true;
				buildingMode = true;
			}
		}

		if (widgetName == "machine_barrelLarge" && widgetAction == 0)
		{
			ActorManager::Instance().remove(prebuildActor);
			prebuildActor.reset();

			for (auto it : selectedActors)
			{
				std::shared_ptr<Actor> newActor = ActorManager::Instance().create();
				newActor->loadModel("./Data/SpaceKit/machine_barrelLarge.glb");
				newActor->setName("TempBuilding" + std::to_string(ActorManager::Instance().getUpdateActors().size()));
				newActor->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
				newActor->setPosition({ 0.f, 0.f , 0.f });
				newActor->setType("Building");
				newActor->setTypeName("Supply");
				newActor->addComponent<Building>();
				newActor->setShaderType(ShaderType::Phong);
				newActor->setShaderSubType(ShaderType::PhongTransparency);
				if (Player::Instance().getMineralValue() <= 100)
				{
					newActor->setBaseColor({ 1.f, 0.f, 0.f, 0.5f });
				}
				else
				{
					newActor->setBaseColor({ 0.f, 1.f, 0.f, 0.5f });
				}
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
				if (Player::Instance().getMineralValue() <= 150)
				{
					newActor->setBaseColor({ 1.f, 0.f, 0.f, 0.5f });
				}
				else
				{
					newActor->setBaseColor({ 0.f, 1.f, 0.f, 0.5f });
				}
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
				if (Player::Instance().getMineralValue() <= 75)
				{
					newActor->setBaseColor({ 1.f, 0.f, 0.f, 0.5f });
				}
				else
				{
					newActor->setBaseColor({ 0.f, 1.f, 0.f, 0.5f });
				}
				newActor->getComponent<Building>()->setCurrentBuildingTime(1000.f);

				prebuildActor = newActor;

				it.get()->getComponent<Worker>()->execute();

				buildingBlock = true;
				buildingMode = true;
			}
		}
	}
	if (widgetName == "Torus" && widgetAction == 0)
	{
		selectedActorName = actors[0]->getName();
	}
	if (widgetName == "CircleIn" && widgetAction == 0)
	{
		selectedActorName = actors[1]->getName();
	}
	if (widgetName == "Circle" && widgetAction == 0)
	{
		selectedActorName = actors[2]->getName();
	}
	if (widgetName == "Hyper" && widgetAction == 0)
	{
		selectedActorName = actors[3]->getName();
	}

	if (widgetName == "Texture1" && widgetAction == 0)
	{
		currentMaterial.index = 9999;
		currentMaterial.baseColorFactor = currentColor * (1 / 255.f);;

		currentTexture = {
		getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].image,
			getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].imageLayout,
			getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].deviceMemory,
			getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].view,
			getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].width, getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].height,
			getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].descriptor,
			getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].sampler,
			getGlobalVector()[static_cast<int>(TextureType::GlobalTexture1)].descriptorSet,
		};

		currentMaterial.additionalTexture = &currentTexture;
	}

	if (widgetName == "Texture2" && widgetAction == 0)
	{
		currentMaterial.index = 9999;
		currentMaterial.baseColorFactor = currentColor * (1 / 255.f);;

		currentTexture = {
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].image,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].imageLayout,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].deviceMemory,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].view,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].width, getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].height,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].descriptor,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].sampler,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture1)].descriptorSet,
		};

		currentMaterial.additionalTexture = &currentTexture;
	}

	if (widgetName == "Texture3" && widgetAction == 0)
	{
		currentMaterial.index = 9999;
		currentMaterial.baseColorFactor = currentColor * (1 / 255.f);;

		currentTexture = {
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].image,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].imageLayout,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].deviceMemory,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].view,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].width, getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].height,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].descriptor,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].sampler,
		getGlobalVector()[static_cast<int>(TextureType::NoiseTexture2)].descriptorSet,
		};

		currentMaterial.additionalTexture = &currentTexture;
	}

	if (widgetName == "sliderRedChannel" || widgetName == "sliderGreenChannel" || widgetName == "sliderBlueChannel" ||
		widgetName == "sliderAlphaChannel"
		&& widgetAction == 0)
	{
		currentMaterial.baseColorFactor = currentColor * (1 / 255.f);
	}
}

void Player::input(GLFWwindow* window, Camera* camera)
{
	if (Player::currentMaterial.index == -1)
	{
		currentMaterial.index = -1;
	}

	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

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

	if (prebuildActor != nullptr)
	{
		float denominator = glm::dot(glm::vec3(0.f, 0.f, 0.f), -glm::vec3(0.f, 1.f, 0.f));
		float t = -(denominator + glm::dot(cameraRay.rayStart, glm::vec3(0.f, 1.f, 0.f))) / glm::dot(cameraRay.rayDirection, glm::vec3(0.f, 1.f, 0.f));
		glm::vec3 intersectionPoint = cameraRay.rayStart + (cameraRay.rayDirection * t);
		prebuildActor->setPosition(intersectionPoint);
	}

	currentSupplyValue = 0;
	overallSupplyValue = 0;

	for (auto it : controlledActors)
	{
		if (it->getTypeName() == "Supply" && it->getComponent<Building>()->getReadyStatus()) overallSupplyValue += 8;
		if (it->getTypeName() == "Base" && it->getComponent<Building>()->getReadyStatus()) overallSupplyValue += 10;
	}

	for (auto it : controlledActors)
	{
		if (it->getTypeName() == "Worker") currentSupplyValue += 1;
		if (it->getTypeName() == "Marine") currentSupplyValue += 1;
		if (it->getTypeName() == "Tank") currentSupplyValue += 2;
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
							if (jt->getTypeName() == "Worker")
							{
								return;
							}

							it->getComponent<Worker>()->setPointOfInterest(jt->getPosition(), true);
							it->getComponent<Worker>()->setState(1);

							selectedTargetName.clear();

							return;
						}
					}
				}
			}
			else if (it->getTypeName() == "Marine")
			{
				if (selectedTargetName == "terrain")
				{
					it->getComponent<Marine>()->setPointOfInterest(movementPoint);
					it->getComponent<Marine>()->setState(1);
					it->getComponent<Marine>()->targetName = "";

					selectedTargetName.clear();

					return;
				}
				else
				{
					for (auto jt : actors)
					{
						if (jt->getName() == selectedTargetName || it->getControllerName() == "Enemy")
						{
							if (jt->getTypeName() == "Marine")
							{
								return;
							}

							it->getComponent<Marine>()->setPointOfInterest(jt->getPosition());
							it->getComponent<Marine>()->setState(2);
							it->getComponent<Marine>()->targetName = selectedTargetName;

							selectedTargetName.clear();

							return;
						}
					}
				}
			}
			else if (it->getTypeName() == "Tank")
			{
				if (selectedTargetName == "terrain")
				{
					it->getComponent<Tank>()->setPointOfInterest(movementPoint);
					it->getComponent<Tank>()->setState(1);
					it->getComponent<Tank>()->targetName = "";

					selectedTargetName.clear();

					return;
				}
				else
				{
					for (auto jt : actors)
					{
						if (jt->getName() == selectedTargetName || it->getControllerName() == "Enemy")
						{
							if (jt->getTypeName() == "Tank")
							{
								return;
							}

							it->getComponent<Tank>()->setPointOfInterest(jt->getPosition());
							it->getComponent<Tank>()->setState(2);
							it->getComponent<Tank>()->targetName = selectedTargetName;

							selectedTargetName.clear();

							return;
						}
					}
				}
			}
		}
	}
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