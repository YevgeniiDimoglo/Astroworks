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
	commandArea->setImageValues(.75f, 0.7f, 0.f, 0.25f, 0.3f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["commandArea"] = commandArea;
}

void OverlayGame::finalize()
{
}

void OverlayGame::update(float elapsedTime, GLFWwindow* window)
{
	std::shared_ptr<Widget> selectedUnit;
	std::shared_ptr<Widget> workerIcon;
	std::shared_ptr<Widget> baseIcon;
	std::shared_ptr<Widget> hangarIcon;
	std::shared_ptr<Widget> turretIcon;

	frontendWidgets.erase("selectedUnit");
	frontendWidgets.erase("workerIcon");
	frontendWidgets.erase("baseIcon");
	frontendWidgets.erase("hangarIcon");
	frontendWidgets.erase("turretIcon");

	switch (Player::Instance().getSelectedActorIndex())
	{
	case 0:
	{
		selectedUnit = std::make_shared<Image>("Dummy");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 0.f);
		break;
	}
	case 1:
	{
		selectedUnit = std::make_shared<Image>("astronautA");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

		std::vector<std::string> baseButtonNames = {
		"hangar_roundGlass",
		"hangar_roundGlass",
		"hangar_roundGlass",
		"hangar_roundGlass"
		};
		baseIcon = std::make_shared<Button>(baseButtonNames);
		baseIcon->setImageValues(0.6f, 0.55f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		baseIcon->registerObserver(&UI::Instance());
		baseIcon->registerObserver(&Player::Instance());

		frontendWidgets["baseIcon"] = baseIcon;

		std::vector<std::string> hangarButtonNames = {
		"hangar_smallB",
		"hangar_smallB",
		"hangar_smallB",
		"hangar_smallB"
		};
		hangarIcon = std::make_shared<Button>(hangarButtonNames);
		hangarIcon->setImageValues(0.75f, 0.55f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		hangarIcon->registerObserver(&UI::Instance());
		hangarIcon->registerObserver(&Player::Instance());

		frontendWidgets["hangarIcon"] = hangarIcon;

		std::vector<std::string> turretButtonNames = {
		"turret_double",
		"turret_double",
		"turret_double",
		"turret_double"
		};
		turretIcon = std::make_shared<Button>(turretButtonNames);
		turretIcon->setImageValues(0.9f, 0.55f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		turretIcon->registerObserver(&UI::Instance());
		turretIcon->registerObserver(&Player::Instance());

		frontendWidgets["turretIcon"] = turretIcon;
		break;
	}
	case 2:
	{
		selectedUnit = std::make_shared<Image>("rock_crystalsLargeA");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		break;
	}
	case 3:
	{
		selectedUnit = std::make_shared<Image>("hangar_roundGlass");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

		std::vector<std::string> workerbuttonNames = {
		"astronautA",
		"astronautA",
		"astronautA",
		"astronautA"
		};
		workerIcon = std::make_shared<Button>(workerbuttonNames);
		workerIcon->setImageValues(0.6f, 0.55f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		workerIcon->registerObserver(&UI::Instance());
		workerIcon->registerObserver(&Player::Instance());

		frontendWidgets["workerIcon"] = workerIcon;
		break;
	}
	case 4:
	{
		selectedUnit = std::make_shared<Image>("hangar_smallB");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		break;
	}
	case 5:
	{
		selectedUnit = std::make_shared<Image>("turret_double");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		break;
	}
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