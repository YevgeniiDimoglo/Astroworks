#include "Player.h"

#include "../UI/UI.h"

GLTFStaticModel::Material Player::currentMaterial;
GLTFStaticModel::Image Player::currentTexture;
glm::vec2 BloomValues = { 0.5f, 2.0f };
glm::vec4 Player::currentColor = { 1.0f, 1.0f, 1.0f, 1.0f };
std::vector<int> Player::textureIndex(4, 0);

std::string Player::getSelectedActor(GLFWwindow* window, Camera* camera)
{
	return "";
}

std::string Player::getTargetActor(GLFWwindow* window, Camera* camera)
{
	return "";
}

void Player::notify(std::string widgetName, int widgetAction)
{
	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

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

	auto widgets = UI::Instance().getCurrentOverlay().getWidgets();

	if (widgetName == "Torus" && widgetAction == 0)
	{
		selectedActorName = actors[0]->getName();
		currentMaterial = objectMaterials[0];
		currentMaterial.index = 0;
		currentTextureIndex = textureIndex[0];
		if (objectMaterials[0].additionalTexture != nullptr)
		{
			currentTexture = *objectMaterials[0].additionalTexture;
		}

		currentColor = currentMaterial.baseColorFactor;

		widgets["sliderRedChannel"].get()->updateValues(0, currentColor.r * 255);
		widgets["sliderGreenChannel"].get()->updateValues(0, currentColor.g * 255);
		widgets["sliderBlueChannel"].get()->updateValues(0, currentColor.b * 255);
		widgets["sliderAlphaChannel"].get()->updateValues(0, currentColor.a * 255);
		widgets["radioButtonTexture"].get()->updateValues(0, currentTextureIndex);
	}
	if (widgetName == "CircleIn" && widgetAction == 0)
	{
		selectedActorName = actors[1]->getName();
		currentMaterial = objectMaterials[1];
		currentMaterial.index = 1;
		currentTextureIndex = textureIndex[1];
		if (objectMaterials[1].additionalTexture != nullptr)
		{
			currentTexture = *objectMaterials[1].additionalTexture;
		}

		currentColor = currentMaterial.baseColorFactor;

		widgets["sliderRedChannel"].get()->updateValues(0, currentColor.r * 255);
		widgets["sliderGreenChannel"].get()->updateValues(0, currentColor.g * 255);
		widgets["sliderBlueChannel"].get()->updateValues(0, currentColor.b * 255);
		widgets["sliderAlphaChannel"].get()->updateValues(0, currentColor.a * 255);
		widgets["radioButtonTexture"].get()->updateValues(0, currentTextureIndex);
	}
	if (widgetName == "Circle" && widgetAction == 0)
	{
		selectedActorName = actors[2]->getName();
		currentMaterial = objectMaterials[2];
		currentMaterial.index = 2;
		currentTextureIndex = textureIndex[2];
		if (objectMaterials[2].additionalTexture != nullptr)
		{
			currentTexture = *objectMaterials[2].additionalTexture;
		}

		currentColor = currentMaterial.baseColorFactor;

		widgets["sliderRedChannel"].get()->updateValues(0, currentColor.r * 255);
		widgets["sliderGreenChannel"].get()->updateValues(0, currentColor.g * 255);
		widgets["sliderBlueChannel"].get()->updateValues(0, currentColor.b * 255);
		widgets["sliderAlphaChannel"].get()->updateValues(0, currentColor.a * 255);
		widgets["radioButtonTexture"].get()->updateValues(0, currentTextureIndex);
	}
	if (widgetName == "Hyper" && widgetAction == 0)
	{
		selectedActorName = actors[3]->getName();
		currentMaterial = objectMaterials[3];
		currentMaterial.index = 3;
		currentTextureIndex = textureIndex[3];
		if (objectMaterials[3].additionalTexture != nullptr)
		{
			currentTexture = *objectMaterials[3].additionalTexture;
		}

		currentColor = currentMaterial.baseColorFactor;

		widgets["sliderRedChannel"].get()->updateValues(0, currentColor.r * 255);
		widgets["sliderGreenChannel"].get()->updateValues(0, currentColor.g * 255);
		widgets["sliderBlueChannel"].get()->updateValues(0, currentColor.b * 255);
		widgets["sliderAlphaChannel"].get()->updateValues(0, currentColor.a * 255);
		widgets["radioButtonTexture"].get()->updateValues(0, currentTextureIndex);
	}

	if (widgetName == "Texture1" && widgetAction == 0)
	{
		currentTextureIndex = 0;

		currentMaterial.baseColorFactor = currentColor * (1 / 255.f);

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
		currentTextureIndex = 1;

		currentMaterial.baseColorFactor = currentColor * (1 / 255.f);

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
		currentTextureIndex = 2;

		currentMaterial.baseColorFactor = currentColor * (1 / 255.f);

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
	std::vector<std::shared_ptr<Actor>> actors = ActorManager::Instance().getUpdateActors();

	calculateScreenToWorldCoords(window, camera);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int width, height;
		glfwGetWindowSize(window, &width, &height);
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

	if (currentMaterial.index != -1)
	{
		objectMaterials[currentMaterial.index] = currentMaterial;
		if (currentTexture.image == nullptr)
		{
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
		}
		else
		{
			textureIndex[currentMaterial.index] = currentTextureIndex;
		}
	}
}

int Player::calculateScore()
{
	int totalScore = 0;

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