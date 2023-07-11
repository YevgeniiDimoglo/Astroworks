#include "OverlayGame.h"

#include "../Player/Player.h"

void OverlayGame::initialize()
{
	std::shared_ptr<Widget> rock = std::make_shared<Image>("rock_crystalsLargeB");
	rock->setImageValues(0.8f, -0.9f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets["0rock"] = rock;

	std::shared_ptr<Widget> supply = std::make_shared<Image>("barrel");
	supply->setImageValues(0.6f, -0.9f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets["0supply"] = supply;

	std::shared_ptr<Widget> minimapArea = std::make_shared<Image>("window_transparent");
	minimapArea->setImageValues(-0.8f, 0.7f, 0.f, 0.2f, 0.3f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets["0minimapArea"] = minimapArea;

	std::shared_ptr<Widget> mainViewArea = std::make_shared<Image>("window_transparent");
	mainViewArea->setImageValues(0.0f, 0.7f, 0.f, 0.5f, 0.3f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets["0mainViewArea"] = mainViewArea;

	std::shared_ptr<Widget> commandArea = std::make_shared<Image>("window_transparent");
	commandArea->setImageValues(.8f, 0.7f, 0.f, 0.2f, 0.3f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets["0commandArea"] = commandArea;

	/*std::shared_ptr<Widget> space = std::make_shared<Image>("Space");
	space->setImageValues(0.0f, 0.0f, 0.999, 1.0f, 1.0f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets["space"] = space;*/
}

void OverlayGame::finalize()
{
}

void OverlayGame::update(float elapsedTime, GLFWwindow* window)
{
	std::shared_ptr<Widget> selectedUnit;

	switch (Player::Instance().getSelectedActorIndex())
	{
	case 0:
		selectedUnit = std::make_shared<Image>("Dummy");
		selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 0.f);
		widgets["1selectedUnit"] = selectedUnit;
		break;
	case 1:
		if (widgets.count("1selectedUnit") != 0)
		{
			widgets.erase("1selectedUnit");
			selectedUnit = std::make_shared<Image>("astronautA");
			selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
			widgets["1selectedUnit"] = selectedUnit;
		}
		break;
	case 2:
		if (widgets.count("1selectedUnit") != 0)
		{
			widgets.erase("1selectedUnit");
			selectedUnit = std::make_shared<Image>("rock_crystalsLargeA");
			selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
			widgets["1selectedUnit"] = selectedUnit;
		}
		break;
	case 3:
		if (widgets.count("1selectedUnit") != 0)
		{
			widgets.erase("1selectedUnit");
			selectedUnit = std::make_shared<Image>("hangar_roundGlass");
			selectedUnit->setImageValues(0.0f, 0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
			widgets["1selectedUnit"] = selectedUnit;
		}
		break;
	default:

		break;
	}

	for (auto it : widgets)
	{
		it.second->update(elapsedTime, window);
	}
}

void OverlayGame::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	for (auto it : widgets)
	{
		it.second->draw(commandBuffer, pipelineLayout);
	}
}