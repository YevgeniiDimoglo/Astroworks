#include "Actor.h"
#include "Component.h"
#include "../Framework/ResourceManager.h"

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
		updateActors.emplace_back(actor);
	}
	startActors.clear();

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

void ActorManager::updateTransform()
{
	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		actor->updateTransform();
	}
}

void ActorManager::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	// TODO: Move updateTransform to update function
	// Render actor models
	static int localTimer = 0;
	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		GLTFStaticModel* model = actor->getModel();
		if (model != nullptr)
		{
			actor->updateTransform();
			model->draw(commandBuffer, pipelineLayout);
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

	removeActors.clear();
}