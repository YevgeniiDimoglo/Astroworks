#include "ResourceManager.h"

#include "../Actor/Actor.h"

std::shared_ptr<GLTFStaticModel> ResourceManager::LoadModel(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout, std::shared_ptr<GLTFStaticModel> model)
{
	// Loading same model only once
	ModelMap::iterator it = models.find(model.get()->filePath);

	if (it != models.end())
	{
		if (!it->second.expired())
		{
			return it->second.lock();
		}
	}

	model->loadglTFFile(newPhysicalDevice, newLogicalDevice, transferQueue, transferCommandPool, samplerDescriptorPool, samplerSetLayout);

	models[model.get()->filePath] = model;

	LOG("Loading model: " + model.get()->filePath + "\n");

	return model;
}

void ResourceManager::loadFile(std::string filepath)
{
	toml::table tbl;
	try
	{
		tbl = toml::parse_file(filepath);
	}
	catch (const toml::parse_error& err)
	{
		std::cout
			<< "Error parsing file '" << *err.source().path
			<< "':\n" << err.description()
			<< "\n  (" << err.source().begin << ")\n";
	}

	auto actors = tbl["ActorsOnScreen"];

	for (size_t i = 0; i < actors.as_array()->size(); i++)
	{
		auto position = actors[i]["position"];
		auto rotation = actors[i]["rotation"];
		auto euler = actors[i]["euler"];
		auto scale = actors[i]["scale"];

		ActorOnScreen tempActor =
		{
			actors[i]["name"].value<std::string>().value(),
			{position[0].value<float>().value(), position[1].value<float>().value(), position[2].value<float>().value()},
			{rotation[0].value<float>().value(), rotation[1].value<float>().value(), rotation[2].value<float>().value(), rotation[3].value<float>().value()},
			{glm::radians(euler[0].value<float>().value()), glm::radians(euler[1].value<float>().value()), glm::radians(euler[2].value<float>().value())},
			{scale[0].value<float>().value(), scale[1].value<float>().value(), scale[2].value<float>().value()},
			actors[i]["path"].value<std::string>().value(),
			actors[i]["type"].value<std::string>().value(),
			actors[i]["typeName"].value<std::string>().value(),
			actors[i]["domain"].value<std::string>().value(),
			actors[i]["shader"].value<std::string>().value(),
			actors[i]["controller"].value<std::string>().value()
		};

		actorsOnScreen.push_back(tempActor);
	}

	actorsOnLevel["TEMP"] = actorsOnScreen;
}

void ResourceManager::loadFiles(std::string filepath)
{
	std::vector<std::string> newFilePathes = loadFilePathes(filepath);

	for (auto it : newFilePathes)
	{
		actorsOnScreen.clear();

		std::filesystem::path filePath(it);
		std::string fileName = filePath.stem().string();

		// Parsing actor values
		toml::table tbl;
		try
		{
			tbl = toml::parse_file(it);
		}
		catch (const toml::parse_error& err)
		{
			std::cout
				<< "Error parsing file '" << *err.source().path
				<< "':\n" << err.description()
				<< "\n  (" << err.source().begin << ")\n";
		}

		auto actors = tbl["ActorsOnScreen"];

		if (actors.as_array() == nullptr)
		{
			return;
		}

		for (size_t i = 0; i < actors.as_array()->size(); i++)
		{
			auto position = actors[i]["position"];
			auto rotation = actors[i]["rotation"];
			auto euler = actors[i]["euler"];
			auto scale = actors[i]["scale"];

			ActorOnScreen tempActor =
			{
				actors[i]["name"].value<std::string>().value(),
				{position[0].value<float>().value(), position[1].value<float>().value(), position[2].value<float>().value()},
				{rotation[0].value<float>().value(), rotation[1].value<float>().value(), rotation[2].value<float>().value(), rotation[3].value<float>().value()},
				{glm::radians(euler[0].value<float>().value()), glm::radians(euler[1].value<float>().value()), glm::radians(euler[2].value<float>().value())},
				{scale[0].value<float>().value(), scale[1].value<float>().value(), scale[2].value<float>().value()},
				actors[i]["path"].value<std::string>().value(),
				actors[i]["type"].value<std::string>().value(),
				actors[i]["typeName"].value<std::string>().value(),
				actors[i]["domain"].value<std::string>().value(),
				actors[i]["shader"].value<std::string>().value(),
				actors[i]["controller"].value<std::string>().value()
			};

			actorsOnScreen.push_back(tempActor);
		}

		actorsOnLevel[fileName] = actorsOnScreen;
	}
}

void ResourceManager::saveFile(std::string filepath)
{
	// Writing all actors information into file
	std::ofstream MyFile(filepath);

	std::vector<std::shared_ptr<Actor>> updateActors = ActorManager::Instance().getUpdateActors();

	for (auto it : updateActors)
	{
		MyFile << "[[ActorsOnScreen]]" << std::endl;

		MyFile << "name = " << "\"" << it.get()->getName() << "\"" << std::endl;

		MyFile << std::fixed << std::setprecision(1) << "position = " << "[" << it.get()->getPosition().x << "," << it.get()->getPosition().y << "," << it.get()->getPosition().z << "]" << std::endl;
		MyFile << std::fixed << std::setprecision(1) << "rotation = " << "[" << it.get()->getRotation().w << "," << it.get()->getRotation().x << "," << it.get()->getRotation().y << "," << it.get()->getRotation().z << "]" << std::endl;
		MyFile << std::fixed << std::setprecision(1) << "euler = " << "[" << it.get()->getEuler().x << "," << it.get()->getEuler().y << "," << it.get()->getEuler().z << "]" << std::endl;
		MyFile << std::fixed << std::setprecision(1) << "scale = " << "[" << it.get()->getScale().x << "," << it.get()->getScale().y << "," << it.get()->getScale().z << "]" << std::endl;

		MyFile << "path = " << "\"" << it.get()->getFilePath() << "\"" << std::endl;

		MyFile << "type = " << "\"" << it.get()->getType() << "\"" << std::endl;
		MyFile << "typeName = " << "\"" << it.get()->getTypeName() << "\"" << std::endl;

		MyFile << "controller = " << "\"" << it.get()->getControllerName() << "\"" << std::endl;

		MyFile << std::endl;
	}

	MyFile.close();
}