#include "../Framework/ResourceManager.h"

#include "../Player/Player.h"

#include "Actor.h"
#include "ActorTypes.h"

#include "Building.h"

#include "Components/Transform.h"
#include "Components/Movement.h"

void Actor::start()
{
	for (std::shared_ptr<Component>& component : components)
	{
		component->start();
	}
}

void Actor::update(float elapsedTime)
{
	for (std::shared_ptr<Component>& component : components)
	{
		component->update(elapsedTime);
	}
}

void Actor::updateTransform()
{
	// Transform matrix
	glm::mat4x4 translate = glm::translate(glm::mat4x4(1.0f), this->position);

	this->rotation = glm::quat(euler);
	glm::mat4x4 rotate = glm::mat4_cast(this->rotation);

	glm::mat4x4 scale = glm::scale(glm::mat4x4(1.0f), this->scale);

	glm::mat4x4 transform = translate * rotate * scale;
	model->setSceneValues(transform);
	model->setTimer(timer);
}

void Actor::updateMaterials(GLTFStaticModel::Material newMaterial)
{
	std::vector<GLTFStaticModel::Material> materials = model->getMaterials();
	for (auto it : materials)
	{
		it.additionalTexture = newMaterial.additionalTexture;
		model->updateDescriptors(it);
		model->setBaseColor(newMaterial.baseColorFactor);
	}
}

void Actor::loadModel(std::string filename)
{
	// TODO: merge loading model and loading file
	model = std::make_shared<GLTFStaticModel>(filename);
	modelPath = filename;
}

void Actor::loadFile(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout)
{
	// TODO: merge loading model and loading file
	model = ResourceManager::Instance().LoadModel(newPhysicalDevice, newLogicalDevice, transferQueue, transferCommandPool, samplerDescriptorPool, samplerSetLayout, model);
	loadedModel = true;
}

void Actor::destroy(VkDevice newLogicalDevice)
{
	// Cleanup model resources
	if (model.use_count() == 1)
	{
		model->cleanupResourses(newLogicalDevice);
	}
}

std::shared_ptr<Actor> ActorManager::create()
{
	// Create start actors
	std::shared_ptr<Actor> actor = std::make_shared<Actor>();
	{
		static int id = 0;
		std::string name = "Actor" + id;
		actor->setName(name);
	}
	startActors.emplace_back(actor);

	return actor;
}

void ActorManager::deserializeActor()
{
	for (auto it : ResourceManager::Instance().getActorsOnScreen(currentLevelName))
	{
		std::shared_ptr<Actor> actor = ActorManager::Instance().create();
		actor->loadModel(it.filePath);
		actor->setName(it.name);
		actor->setPosition(it.position);
		actor->setEuler(it.euler);
		actor->setScale(it.scale);
		actor->setType(it.type);
		actor->setTypeName(it.typeName);
		actor->setDomain(it.domain);
		actor->setShader(it.shader);
		actor->setControllerName(it.controller);

		actor->addComponent<Transform>();

		if (it.type == "Unit")
		{
			actor->addComponent<Unit>();
			actor->addComponent<Movement>();

			if (it.typeName == "Worker")
			{
				actor->addComponent<Worker>();
			}

			if (it.typeName == "Alien")
			{
				actor->addComponent<Alien>();
			}
		}

		if (it.type == "Building")
		{
			actor->addComponent<Building>();
			actor->getComponent<Building>()->setCurrentBuildingTime(1000.f);
		}

		if (actor->getControllerName() == "Player")
		{
			Player::Instance().emplaceActor(actor);
		}

		{
			if (actor->getShader() == "Flat")
			{
				actor->setShaderType(ShaderType::Flat);
			}

			if (actor->getShader() == "Phong")
			{
				actor->setShaderType(ShaderType::Phong);
			}

			if (actor->getShader() == "PBR")
			{
				actor->setShaderType(ShaderType::PBR);
			}

			if (actor->getShader() == "PBRIBL")
			{
				actor->setShaderType(ShaderType::PBRIBL);
			}

			if (actor->getShader() == "Water")
			{
				actor->setShaderType(ShaderType::Water);
			}

			if (actor->getShader() == "Fireball")
			{
				actor->setShaderType(ShaderType::Fireball);
			}

			if (actor->getShader() == "Transparent")
			{
				actor->setShaderType(ShaderType::OITColorAccum);
				actor->setTransparent(true);
			}

			if (actor->getShader() == "Skybox")
			{
				actor->setShaderType(ShaderType::Skybox);
			}
		}
	}
}

void ActorManager::loadFiles(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout)
{
	for (std::shared_ptr<Actor>& actor : startActors)
	{
		actor->loadFile(newPhysicalDevice, newLogicalDevice, transferQueue, transferCommandPool, samplerDescriptorPool, samplerSetLayout);
	}
}

void ActorManager::remove(std::shared_ptr<Actor> actor)
{
	removeActors.insert(actor);
}

void ActorManager::update(float elapsedTime)
{
	for (std::shared_ptr<Actor>& actor : startActors)
	{
		actor->start();
		if (actor->loadedModel)
		{
			updateActors.emplace_back(actor);
		}
	}

	startActors.erase(
		std::remove_if(
			startActors.begin(),
			startActors.end(),
			[](std::shared_ptr<Actor>& actor) { return actor->loadedModel == true; }
		),
		startActors.end()
	);

	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		actor->update(elapsedTime);
	}

	for (const std::shared_ptr<Actor>& actor : removeActors)
	{
		std::vector<std::shared_ptr<Actor>>::iterator itStart = std::find(startActors.begin(), startActors.end(), actor);
		if (itStart != startActors.end())
		{
			startActors.erase(itStart);
		}

		std::vector<std::shared_ptr<Actor>>::iterator itUpdate = std::find(updateActors.begin(), updateActors.end(), actor);
		if (itUpdate != updateActors.end())
		{
			updateActors.erase(itUpdate);
		}

		std::set<std::shared_ptr<Actor>>::iterator itSelection = selectionActors.find(actor);
		if (itSelection != selectionActors.end())
		{
			selectionActors.erase(itSelection);
		}
	}
	removeActors.clear();
}

void ActorManager::switchLevel(std::string newLevelName)
{
	currentLevelName = newLevelName;

	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		deletedActors.insert(actor);
	}

	updateActors.clear();

	deserializeActor();
}

void ActorManager::updateTransform()
{
}

void ActorManager::renderSolid(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int pipelineNumber)
{
	// TODO: Move updateTransform to update function
	// Render actor models
	static int localTimer = 0;
	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		if (actor->getTransparent() == true) continue;

		if (static_cast<int>(actor->getShaderType()) == pipelineNumber)
		{
			GLTFStaticModel* model = actor->getModel();
			if (model != nullptr)
			{
				actor->updateTransform();

				model->draw(commandBuffer, pipelineLayout);
			}
		}
	}
}

void ActorManager::renderTransparent(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int pipelineNumber)
{
	// TODO: Move updateTransform to update function
	// Render actor models
	static int localTimer = 0;
	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		if (actor->getTransparent() == false) continue;

		if (static_cast<int>(actor->getShaderType()) == pipelineNumber)
		{
			GLTFStaticModel* model = actor->getModel();
			if (model != nullptr)
			{
				actor->updateTransform();

				model->draw(commandBuffer, pipelineLayout);
			}
		}
	}
}

void ActorManager::cleanup(VkDevice newLogicalDevice)
{
	// Cleanup up all remaining actors
	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		actor->destroy(newLogicalDevice);
		actor.reset();
	}

	for (auto it : deletedActors)
	{
		it->destroy(newLogicalDevice);
		it.reset();
	}

	removeActors.clear();
}