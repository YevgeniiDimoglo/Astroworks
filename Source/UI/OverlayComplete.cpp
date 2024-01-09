#include "OverlayComplete.h"

#include "UI.h"
#include "../Player/Player.h"

void OverlayComplete::initialize(GLFWwindow* window)
{
	std::shared_ptr<Widget> imageBackScreen = std::make_shared<Image>("titlebg");
	imageBackScreen->setImageValues(0.f, 0.f, 1.f, 1.f, 1.f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backWidgets["titlebg"] = imageBackScreen;

	std::shared_ptr<Widget> rank = std::make_shared<Image>("rank");
	rank->setImageValues(-.5f, -0.0f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["rank"] = rank;

	std::shared_ptr<Widget> stamp = std::make_shared<Image>("stampsealrankS");
	stamp->setImageValues(.5f, -0.0f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["stamp"] = stamp;

	std::shared_ptr<Widget> score = std::make_shared<Image>("result");
	score->setImageValues(-.5f, -0.7f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["score"] = score;

	std::shared_ptr<Widget> scoreCounter = std::make_shared<Counter>("scoreCounter");
	scoreCounter->setImageValues(0.65f, -0.7f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["scoreCounter"] = scoreCounter;

	std::vector<std::string> buttonNames = {
	"exit",
	"exith",
	"exit",
	"exit"
	};

	std::shared_ptr<Widget> buttonExit = std::make_shared<Button>(buttonNames);
	buttonExit->setImageValues(0.0f, 0.4f, 0.f, 0.3f, 0.15f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	buttonExit->registerObserver(&UI::Instance());
	buttonExit->registerObserver(&Player::Instance());
	frontWidgets["buttonExit"] = buttonExit;
}

void OverlayComplete::finalize()
{
}

void OverlayComplete::update(float elapsedTime, GLFWwindow* window)
{
	if (Player::Instance().calculateScore() <= 100)
	{
		std::shared_ptr<Widget> stamp = std::make_shared<Image>("stampsealrankE");
		stamp->setImageValues(.5f, -0.0f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		frontWidgets["stamp"] = stamp;
	}
	else if (Player::Instance().calculateScore() <= 100 && Player::Instance().calculateScore() <= 200)
	{
		std::shared_ptr<Widget> stamp = std::make_shared<Image>("stampsealrankD");
		stamp->setImageValues(.5f, -0.0f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		frontWidgets["stamp"] = stamp;
	}
	else if (Player::Instance().calculateScore() <= 200 && Player::Instance().calculateScore() <= 300)
	{
		std::shared_ptr<Widget> stamp = std::make_shared<Image>("stampsealrankC");
		stamp->setImageValues(.5f, -0.0f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		frontWidgets["stamp"] = stamp;
	}
	else if (Player::Instance().calculateScore() <= 300 && Player::Instance().calculateScore() <= 500)
	{
		std::shared_ptr<Widget> stamp = std::make_shared<Image>("stampsealrankB");
		stamp->setImageValues(.5f, -0.0f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		frontWidgets["stamp"] = stamp;
	}
	else if (Player::Instance().calculateScore() <= 500 && Player::Instance().calculateScore() <= 700)
	{
		std::shared_ptr<Widget> stamp = std::make_shared<Image>("stampsealrankA");
		stamp->setImageValues(.5f, -0.0f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		frontWidgets["stamp"] = stamp;
	}
	else
	{
		std::shared_ptr<Widget> stamp = std::make_shared<Image>("stampsealrankS");
		stamp->setImageValues(.5f, -0.0f, 0.f, 0.2f, 0.2f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
		frontWidgets["stamp"] = stamp;
	}

	for (auto it : backWidgets)
	{
		it.second->update(elapsedTime, window);
	}

	for (auto it : frontWidgets)
	{
		if (it.first == "scoreCounter")
		{
			it.second->updateValues(0, Player::Instance().calculateScore());
		}

		it.second->update(elapsedTime, window);
	}
}

void OverlayComplete::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
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