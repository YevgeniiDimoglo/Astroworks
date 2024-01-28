#include "OverlayScene.h"

#include "../UI/UI.h"
#include "../Player/Player.h"

void OverlayScene::initialize(GLFWwindow* window)
{
	//std::shared_ptr<Widget> minimapArea = std::make_shared<Image>("window_transparent");
	//minimapArea->setImageValues(-0.55f, 0.8f, 0.f, 0.45f, 0.1f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	//backWidgets["minimapArea"] = minimapArea;

	//std::shared_ptr<Widget> inGameTimer = std::make_shared<Timer>("inGameTimer");
	//inGameTimer->setImageValues(-0.28f, 0.81f, 0.f, 0.08f, 0.08f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	//frontWidgets["inGameTimer"] = inGameTimer;

	std::vector<std::string> LevelScene = {
	"1d",
	"1h",
	"1h",
	"1h"
	};

	std::shared_ptr<Widget> buttonLevelScene = std::make_shared<Button>(LevelScene);
	buttonLevelScene->setImageValues(0.9f, -0.85f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> LevelPBR = {
	"2d",
	"2h",
	"2h",
	"2h"
	};

	std::shared_ptr<Widget> buttonLevelPBR = std::make_shared<Button>(LevelPBR);
	buttonLevelPBR->setImageValues(0.9f, -0.65f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> LevelOIT = {
	"3d",
	"3h",
	"3h",
	"3h"
	};

	std::shared_ptr<Widget> buttonLevelOIT = std::make_shared<Button>(LevelOIT);
	buttonLevelOIT->setImageValues(0.9f, -0.45f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> LevelTextures = {
	"4d",
	"4h",
	"4h",
	"4h"
	};

	std::shared_ptr<Widget> buttonLevelTextures = std::make_shared<Button>(LevelTextures);
	buttonLevelTextures->setImageValues(0.9f, -0.25f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> LevelMisc = {
	"5d",
	"5h",
	"5h",
	"5h"
	};

	std::shared_ptr<Widget> buttonLevelMisc = std::make_shared<Button>(LevelMisc);
	buttonLevelMisc->setImageValues(0.9f, -0.05f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> LevelBig = {
	"6d",
	"6h",
	"6h",
	"6h"
	};

	std::shared_ptr<Widget> buttonLevelBig = std::make_shared<Button>(LevelBig);
	buttonLevelBig->setImageValues(0.9f, 0.15f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> LevelSkybox = {
	"7d",
	"7h",
	"7h",
	"7h"
	};

	std::shared_ptr<Widget> buttonLevelSkybox = std::make_shared<Button>(LevelSkybox);
	buttonLevelSkybox->setImageValues(0.9f, 0.35f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::shared_ptr<Widget>> sceneButtons = { buttonLevelScene, buttonLevelPBR, buttonLevelOIT, buttonLevelTextures, buttonLevelMisc, buttonLevelBig, buttonLevelSkybox };

	std::shared_ptr<Widget> radioButtonScene = std::make_shared<RadioButton>(sceneButtons);
	radioButtonScene->registerObserver(&UI::Instance());
	radioButtonScene->registerObserver(&Player::Instance());
	frontWidgets["radioButtonScene"] = radioButtonScene;
}

void OverlayScene::finalize()
{
}

void OverlayScene::update(float elapsedTime, GLFWwindow* window)
{
	for (auto it : backWidgets)
	{
		it.second->update(elapsedTime, window);
	}

	for (auto it : frontWidgets)
	{
		it.second->update(elapsedTime, window);
	}
}

void OverlayScene::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	for (auto it : backWidgets)
	{
		it.second->draw(commandBuffer, pipelineLayout);
	}

	for (auto it : frontWidgets)
	{
		it.second->draw(commandBuffer, pipelineLayout);
	}
}