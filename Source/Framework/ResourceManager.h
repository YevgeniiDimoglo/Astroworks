#pragma once

#include "../Graphics/Utilities.h"
#include "../Graphics/GLTFStaticModel.h"
#include "../Graphics/Sprite.h"

class ResourceManager
{
public:
	ResourceManager() {}
	~ResourceManager() {};

	static ResourceManager& Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	std::vector<std::string> getFilePathes() const { return filePathes; }
	std::vector<std::string> loadFilePathes(std::string folderPath) {
		std::vector<std::string> newFilePathes;
		for (const auto& entry : std::filesystem::directory_iterator(folderPath))
			newFilePathes.push_back(entry.path().string());
		return newFilePathes;
	}

	std::map<std::string, std::vector<ActorOnScreen>> getActorsOnLevel() const { return actorsOnLevel; }
	std::vector<ActorOnScreen> getActorsOnScreen(std::string LevelName) { return actorsOnLevel[LevelName]; }

	std::shared_ptr<GLTFStaticModel> LoadModel(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout, std::shared_ptr<GLTFStaticModel> model);

	void loadFile(std::string filepath);
	void loadFiles(std::string filepath);
	void saveFile(std::string filepath);

private:

	std::vector<std::string> filePathes;
	std::map<std::string, std::vector<ActorOnScreen>> actorsOnLevel;
	std::vector<ActorOnScreen> actorsOnScreen;

	using ModelMap = std::map<std::string, std::weak_ptr<GLTFStaticModel>>;

	ModelMap models;
};