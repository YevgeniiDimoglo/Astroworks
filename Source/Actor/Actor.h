#pragma once

#include "../Graphics/Utilities.h"
#include "../Graphics/GLTFStaticModel.h"

class Component;

class Actor : public std::enable_shared_from_this<Actor>
{
public:
	Actor() {}
	virtual ~Actor() {};

	virtual void start();

	virtual void update(float elapsedTime);

	virtual void updateTransform();

	void setName(std::string name) { this->name = name; }
	const std::string getName() const { return name; }

	const std::string getFilePath() const { return modelPath; }

	void setPosition(const glm::vec3& position) { this->position = position; }
	const glm::vec3& getPosition() const {
		return position;
	}

	void setRotation(const glm::quat& rotation) { this->rotation = rotation; }
	const glm::quat& getRotation() const {
		return rotation;
	}

	void setScale(const glm::vec3& scale) { this->scale = scale; }
	const glm::vec3& getScale() const {
		return scale;
	}

	void setEuler(const glm::vec3& euler) { this->euler = euler; }
	const glm::vec3& getEuler() const {
		return euler;
	}

	void setType(const std::string type) { this->type = type; }
	const std::string getType() const {
		return type;
	}

	void setTypeName(const std::string typeName) { this->typeName = typeName; }
	const std::string getTypeName() const {
		return typeName;
	}

	const glm::mat4x4 getTransform() const {
		return transform;
	}

	void loadModel(std::string filename);

	void loadFile(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout);

	GLTFStaticModel* getModel() const {
		return model.get();
	}

	void destroy(VkDevice newLogicalDevice);

	template<class T, class... Args>
	std::shared_ptr<T> addComponent(Args... args)
	{
		std::shared_ptr<T> component = std::make_shared<T>(args...);
		component->setActor(shared_from_this());
		components.emplace_back(component);
		return component;
	}

	template<class T>
	std::shared_ptr<T> getComponent()
	{
		for (std::shared_ptr<Component>& component : components)
		{
			std::shared_ptr<T> p = std::dynamic_pointer_cast<T>(component);
			if (p == nullptr) continue;
			return p;
		}
		return nullptr;
	}

private:

	std::string name;
	glm::vec3 position = { 0, 0, 0 };
	glm::quat rotation = { 1, 0, 0, 0 };
	glm::vec3 euler = { 0, 0, 0 };
	glm::vec3 scale = { 1, 1, 1 };
	glm::mat4x4 transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

	std::shared_ptr<GLTFStaticModel> model;
	std::string modelPath;

	std::string type;
	std::string typeName;

	std::vector<std::shared_ptr<Component>> components;
};

class ActorManager
{
private:
	ActorManager() {}
	~ActorManager() {};

public:

	static ActorManager& Instance()
	{
		static ActorManager instance;
		return instance;
	}

	std::vector<std::shared_ptr<Actor>> getUpdateActors() const { return updateActors; }

	std::shared_ptr<Actor> create();

	void deserializeActor();

	void loadFiles(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout);

	void remove(std::shared_ptr<Actor> actor);

	void update(float elapsedTime);

	void updateTransform();

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

	void cleanup(VkDevice newLogicalDevice);

private:

	std::vector<std::shared_ptr<Actor>> startActors;
	std::vector<std::shared_ptr<Actor>> updateActors;
	std::set<std::shared_ptr<Actor>>	selectionActors;
	std::set<std::shared_ptr<Actor>>	removeActors;

	bool hiddenLister = false;
	bool hiddenDetail = false;
};