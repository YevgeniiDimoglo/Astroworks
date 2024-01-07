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
	radioButtonShape->registerObserver(&Player::Instance());
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
	radioButtonTexture->registerObserver(&Player::Instance());
	frontendWidgets["radioButtonTexture"] = radioButtonTexture;

	std::shared_ptr<Widget> redChannel = std::make_shared<Counter>("redChannel");
	redChannel->setImageValues(-0.65f, -0.5f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontendWidgets["redChannel"] = redChannel;

	std::shared_ptr<Widget> blueChannel = std::make_shared<Counter>("blueChannel");
	blueChannel->setImageValues(-0.65f, -0.4f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontendWidgets["blueChannel"] = blueChannel;

	std::shared_ptr<Widget> greenChannel = std::make_shared<Counter>("greenChannel");
	greenChannel->setImageValues(-0.65f, -0.3f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontendWidgets["greenChannel"] = greenChannel;

	std::shared_ptr<Widget> alphaChannel = std::make_shared<Counter>("alphaChannel");
	alphaChannel->setImageValues(-0.65f, -0.2f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontendWidgets["alphaChannel"] = alphaChannel;

	// Slider

	std::vector<std::string> sliderButtonNames = {
		"progress_bar_background",
		"joystick",
	};

	std::shared_ptr<Widget> sliderBloom = std::make_shared<Slider>(sliderButtonNames, 0.f, 10.f);
	sliderBloom->setImageValues(-0.0f, -0.0f, 0.f, 0.005f, 0.005f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontendWidgets["sliderBloom"] = sliderBloom;

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

		if (it.first == "redChannel")
		{
			it.second->updateValues(0, Player::currentColor.r * 255);
		}
		if (it.first == "blueChannel")
		{
			it.second->updateValues(0, Player::currentColor.g * 255);
		}
		if (it.first == "greenChannel")
		{
			it.second->updateValues(0, Player::currentColor.b * 255);
		}
		if (it.first == "alphaChannel")
		{
			it.second->updateValues(0, Player::currentColor.a * 255);
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