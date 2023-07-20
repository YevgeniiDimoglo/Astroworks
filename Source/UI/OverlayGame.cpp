#include "OverlayGame.h"

#include "../UI/UI.h"
#include "../Player/Player.h"

void OverlayGame::initialize()
{
	std::shared_ptr<Widget> rock = std::make_shared<Image>("rock_crystalsLargeB");
	rock->setImageValues(0.8f, -0.9f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["rock"] = rock;

	std::shared_ptr<Widget> supply = std::make_shared<Image>("barrel");
	supply->setImageValues(0.6f, -0.9f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["supply"] = supply;

	std::shared_ptr<Widget> minimapArea = std::make_shared<Image>("window_transparent");
	minimapArea->setImageValues(-0.8f, 0.7f, 0.f, 0.2f, 0.3f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["minimapArea"] = minimapArea;

	std::shared_ptr<Widget> mainViewArea = std::make_shared<Image>("window_transparent");
	mainViewArea->setImageValues(0.0f, 0.7f, 0.f, 0.5f, 0.3f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["mainViewArea"] = mainViewArea;

	std::shared_ptr<Widget> commandArea = std::make_shared<Image>("window_transparent");
	commandArea->setImageValues(.8f, 0.7f, 0.f, 0.2f, 0.3f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["commandArea"] = commandArea;
}

void OverlayGame::finalize()
{
}

void OverlayGame::update(float elapsedTime, GLFWwindow* window)
{
	std::shared_ptr<Widget> selectedUnit;
	std::shared_ptr<Widget> workerIcon;
	frontendWidgets.erase("selectedUnit");
	frontendWidgets.erase("workerIcon");

	switch (Player::Instance().getSelectedActorIndex())
	{
	case 0:
		selectedUnit = std::make_shared<Image>("Dummy");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 0.f);
		break;
	case 1:
		selectedUnit = std::make_shared<Image>("astronautA");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		break;
	case 2:
		selectedUnit = std::make_shared<Image>("rock_crystalsLargeA");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		break;
	case 3:
		selectedUnit = std::make_shared<Image>("hangar_roundGlass");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

		std::vector<std::string> workerbuttonNames = {
		"astronautA",
		"astronautA",
		"astronautA",
		"astronautA"
		};
		workerIcon = std::make_shared<Button>(workerbuttonNames);
		workerIcon->setImageValues(0.7f, 0.5f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		workerIcon->registerObserver(&UI::Instance());
		workerIcon->registerObserver(&Player::Instance());

		frontendWidgets["workerIcon"] = workerIcon;

		break;
	}

	frontendWidgets["selectedUnit"] = selectedUnit;

	for (auto it : backendWidgets)
	{
		it.second->update(elapsedTime, window);
	}

	for (auto it : frontendWidgets)
	{
		it.second->update(elapsedTime, window);
	}
}

void OverlayGame::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	for (auto it : backendWidgets)
	{
		it.second->draw(commandBuffer, pipelineLayout);
	}

	for (auto it : frontendWidgets)
	{
		it.second->draw(commandBuffer, pipelineLayout);
	}
}