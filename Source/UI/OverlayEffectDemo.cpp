#include "OverlayEffectDemo.h"

#include "UI.h"
#include "../Player/Player.h"

void OverlayEffectDemo::initialize(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	std::shared_ptr<Widget> minimapArea = std::make_shared<Image>("window_transparent");
	minimapArea->setImageValues(-0.55f, 0.8f, 0.f, 0.45f, 0.1f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["minimapArea"] = minimapArea;

	std::vector<std::string> buttonNames = {
	"Circle",
	"CirclePressed",
	"CirclePressed",
	"CirclePressed"
	};

	std::shared_ptr<Widget> buttonCircle = std::make_shared<Button>(buttonNames);
	buttonCircle->setImageValues(0.0f, 0.4f, 0.f, 0.3f, 0.15f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	buttonCircle->registerObserver(&UI::Instance());
	buttonCircle->registerObserver(&Player::Instance());
	frontendWidgets["buttonCircle"] = buttonCircle;

	std::shared_ptr<Widget> inGameTimer = std::make_shared<Timer>("inGameTimer");
	inGameTimer->setImageValues(-0.28f, 0.81f, 0.f, 0.08f, 0.08f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontendWidgets["inGameTimer"] = inGameTimer;
}

void OverlayEffectDemo::finalize()
{
}

void OverlayEffectDemo::update(float elapsedTime, GLFWwindow* window)
{
}

void OverlayEffectDemo::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
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