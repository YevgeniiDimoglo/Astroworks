#include "OverlayTitle.h"

#include "UI.h"
#include "../Player/Player.h"

void OverlayTitle::initialize()
{
	std::shared_ptr<Widget> imageBackScreen = std::make_shared<Image>("titlebg");
	imageBackScreen->setImageValues(0.f, 0.f, 0.f, 1.f, 1.f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets.emplace_back(imageBackScreen);

	std::shared_ptr<Widget> imageFrontScreen = std::make_shared<Image>("Title");
	imageFrontScreen->setImageValues(0.f, 0.f, 0.f, 1.f, 1.f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	widgets.emplace_back(imageFrontScreen);

	std::vector<std::string> buttonNames = {
	"start",
	"starth",
	"start",
	"start"
	};

	std::shared_ptr<Widget> buttonStart = std::make_shared<Button>(buttonNames);
	buttonStart->setImageValues(0.0f, 0.4f, 0.f, 0.3f, 0.15f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	buttonStart->registerObserver(&UI::Instance());
	buttonStart->registerObserver(&Player::Instance());
	widgets.emplace_back(buttonStart);
}

void OverlayTitle::finalize()
{
}

void OverlayTitle::update(float elapsedTime, GLFWwindow* window)
{
	for (auto it : widgets)
	{
		it->update(elapsedTime, window);
	}
}

void OverlayTitle::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	for (auto it : widgets)
	{
		it->draw(commandBuffer, pipelineLayout);
	}
}