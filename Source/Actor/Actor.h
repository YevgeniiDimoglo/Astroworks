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

	virtual void updateMaterials(GLTFStaticModel::Material newMaterial);

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

	void setDomain(const std::string domain) { this->domain = domain; }
	const std::string getDomain() const {
		return domain;
	}

	void setShader(const std::string shader) { this->shader = shader; }
	const std::string getShader() const {
		return shader;
	}

	void setControllerName(const std::string controllerName) { this->controller = controllerName; }
	const std::string getControllerName() const {
		return controller;
	}

	void setBaseColor(const glm::vec4 baseColor) { this->baseColor = baseColor; }

	void setShaderType(const ShaderType shaderType) { this->shaderType = shaderType; }
	const ShaderType getShaderType() const {
		return shaderType;
	}

	void setTransparent(const bool isTransparent) { this->transparent = isTransparent; }
	const bool getTransparent() const {
		return transparent;
	}

	void setTimer(const glm::vec4& timer) { this->timer = timer; }
	const glm::vec3& getTimer() const {
		return timer;
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

	bool loadedModel = false;

private:

	std::string name;
	glm::vec3 position = { 0, 0, 0 };
	glm::quat rotation = { 1, 0, 0, 0 };
	glm::vec3 euler = { 0, 0, 0 };
	glm::vec3 scale = { 1, 1, 1 };
	glm::mat4x4 transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

	glm::vec4 baseColor = { 1.f, 1.f, 1.f, 1.f };
	glm::vec4 timer;

	std::shared_ptr<GLTFStaticModel> model;
	std::string modelPath;

	std::string type;
	std::string typeName;

	std::string domain;
	std::string shader;

	std::string controller;

	std::vector<std::shared_ptr<Component>> components;

	ShaderType shaderType;

	bool transparent = false;
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

	std::string getCurrentLevelName() const { return currentLevelName; }
	void setCurrentLevelName(std::string newCurrentLevelName) { this->currentLevelName = newCurrentLevelName; }

	std::shared_ptr<Actor> create();

	void deserializeActor();

	void loadFiles(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout);

	void remove(std::shared_ptr<Actor> actor);

	void update(float elapsedTime);

	void switchLevel(std::string newLevelName);

	void updateTransform();

	void renderSolid(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int pipelineNumber);
	void renderTransparent(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int pipelineNumber);

	void cleanup(VkDevice newLogicalDevice);

private:

	std::string currentLevelName = "TEMP";

	std::vector<std::shared_ptr<Actor>> startActors;
	std::vector<std::shared_ptr<Actor>> updateActors;
	std::set<std::shared_ptr<Actor>>	selectionActors;
	std::set<std::shared_ptr<Actor>>	removeActors;
	std::set<std::shared_ptr<Actor>>	deletedActors;

	bool hiddenLister = false;
	bool hiddenDetail = false;
};