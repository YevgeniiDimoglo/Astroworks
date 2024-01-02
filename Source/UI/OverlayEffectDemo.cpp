#include "OverlayEffectDemo.h"

#include "UI.h"
#include "../Player/Player.h"

void OverlayEffectDemo::initialize(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Background images
	std::shared_ptr<Widget> minimapArea = std::make_shared<Image>("window_transparent");
	minimapArea->setImageValues(-0.55f, 0.8f, 0.f, 0.45f, 0.1f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["minimapArea"] = minimapArea;

	std::shared_ptr<Widget> background = std::make_shared<Image>("window_transparent");
	background->setImageValues(-0.76f, -0.2f, 0.f, 0.25f, 0.9f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backendWidgets["background"] = background;

	// Shape selector
	std::vector<std::string> torusButtonNames = {
	"Torus",
	"TorusPressed",
	"TorusPressed",
	"TorusPressed"
	};

	std::shared_ptr<Widget> buttonTorus = std::make_shared<Button>(torusButtonNames);
	buttonTorus->setImageValues(-0.9f, -0.85f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> cicleInButtonNames = {
	"CircleIn",
	"CircleInPressed",
	"CircleInPressed",
	"CircleInPressed"
	};

	std::shared_ptr<Widget> buttonCircleIn = std::make_shared<Button>(cicleInButtonNames);
	buttonCircleIn->setImageValues(-0.8f, -0.85f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> circleButtonNames = {
	"Circle",
	"CirclePressed",
	"CirclePressed",
	"CirclePressed"
	};

	std::shared_ptr<Widget> buttonCircle = std::make_shared<Button>(circleButtonNames);
	buttonCircle->setImageValues(-0.7f, -0.85f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> hyperButtonNames = {
	"Hyper",
	"HyperPressed",
	"HyperPressed",
	"HyperPressed"
	};

	std::shared_ptr<Widget> buttonHyper = std::make_shared<Button>(hyperButtonNames);
	buttonHyper->setImageValues(-0.6f, -0.85f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::shared_ptr<Widget>> shapeButtons = { buttonTorus, buttonCircleIn, buttonCircle, buttonHyper };

	std::shared_ptr<Widget> radioButtonShape = std::make_shared<RadioButton>(shapeButtons);
	radioButtonShape->registerObserver(&UI::Instance());
	radioButtonShape->registerObserver(&UI::Instance());
	frontendWidgets["radioButtonShape"] = radioButtonShape;

	// Texture selector
	std::vector<std::string> textureOneButtonNames = {
	"Texture1",
	"Texture1Pressed",
	"Texture1Pressed",
	"Texture1Pressed"
	};

	std::shared_ptr<Widget> textureOneButton = std::make_shared<Button>(textureOneButtonNames);
	textureOneButton->setImageValues(-0.9f, -0.65f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> textureTwoButtonNames = {
	"Texture2",
	"Texture2Pressed",
	"Texture2Pressed",
	"Texture2Pressed"
	};

	std::shared_ptr<Widget> textureTwoButton = std::make_shared<Button>(textureTwoButtonNames);
	textureTwoButton->setImageValues(-0.75f, -0.65f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::string> textureThreeButtonNames = {
	"Texture3",
	"Texture3Pressed",
	"Texture3Pressed",
	"Texture3Pressed"
	};

	std::shared_ptr<Widget> textureThreeButton = std::make_shared<Button>(textureThreeButtonNames);
	textureThreeButton->setImageValues(-0.6f, -0.65f, 0.f, 0.05f, 0.085f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);

	std::vector<std::shared_ptr<Widget>> textureButtons = { textureOneButton, textureTwoButton, textureThreeButton };

	std::shared_ptr<Widget> radioButtonTexture = std::make_shared<RadioButton>(textureButtons);
	radioButtonTexture->registerObserver(&UI::Instance());
	radioButtonTexture->registerObserver(&UI::Instance());
	frontendWidgets["radioButtonTexture"] = radioButtonTexture;

	// Timer
	std::shared_ptr<Widget> inGameTimer = std::make_shared<Timer>("inGameTimer");
	inGameTimer->setImageValues(-0.28f, 0.81f, 0.f, 0.08f, 0.08f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontendWidgets["inGameTimer"] = inGameTimer;
}

void OverlayEffectDemo::finalize()
{
}

void OverlayEffectDemo::update(float elapsedTime, GLFWwindow* window)
{
	for (auto it : backendWidgets)
	{
		it.second->update(elapsedTime, window);
	}

	for (auto it : frontendWidgets)
	{
		it.second->update(elapsedTime, window);

		if (it.first == "inGameTimer")
		{
			it.second->updateValues(Player::Instance().getInGameTimer().TimeStamp(), 0);
		}
	}
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