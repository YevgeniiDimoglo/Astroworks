#include "OverlayEffectDemo.h"

#include "UI.h"
#include "../Player/Player.h"

void OverlayEffectDemo::initialize(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Background images
	std::shared_ptr<Widget> minimapArea = std::make_shared<Image>("window_transparent");
	minimapArea->setImageValues(-0.55f, 0.8f, 0.f, 0.45f, 0.1f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backWidgets["minimapArea"] = minimapArea;

	std::shared_ptr<Widget> background = std::make_shared<Image>("window_transparent");
	background->setImageValues(-0.76f, -0.2f, 0.f, 0.27f, 0.95f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	backWidgets["background"] = background;

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
	frontWidgets["radioButtonShape"] = radioButtonShape;

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
	frontWidgets["radioButtonTexture"] = radioButtonTexture;

	std::shared_ptr<Widget> redChannel = std::make_shared<Counter>("redChannel");
	redChannel->setImageValues(-0.65f, -0.45f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["redChannel"] = redChannel;

	std::shared_ptr<Widget> blueChannel = std::make_shared<Counter>("blueChannel");
	blueChannel->setImageValues(-0.65f, -0.25f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["blueChannel"] = blueChannel;

	std::shared_ptr<Widget> greenChannel = std::make_shared<Counter>("greenChannel");
	greenChannel->setImageValues(-0.65f, -0.05f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["greenChannel"] = greenChannel;

	std::shared_ptr<Widget> alphaChannel = std::make_shared<Counter>("alphaChannel");
	alphaChannel->setImageValues(-0.65f, 0.15f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["alphaChannel"] = alphaChannel;

	std::shared_ptr<Widget> bloom = std::make_shared<Counter>("bloom");
	bloom->setImageValues(-0.65f, 0.35f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["bloom"] = bloom;

	std::shared_ptr<Widget> bloom2 = std::make_shared<Counter>("bloom2");
	bloom2->setImageValues(-0.65f, 0.5f, 0.f, 0.05f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["bloom2"] = bloom2;

	// Sliders

	std::vector<std::string> sliderButtonNames = {
		"progress_bar_background",
		"knob",
	};

	// Counters

	std::shared_ptr<Widget> sliderRedChannel = std::make_shared<Slider>(sliderButtonNames, "sliderRedChannel", 0.f, 255.f, 255.f);
	sliderRedChannel->setImageValues(-0.75f, -0.4f, 0.f, 0.2f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	sliderRedChannel->registerObserver(&UI::Instance());
	sliderRedChannel->registerObserver(&Player::Instance());
	frontWidgets["sliderRedChannel"] = sliderRedChannel;

	std::shared_ptr<Widget> sliderGreenChannel = std::make_shared<Slider>(sliderButtonNames, "sliderGreenChannel", 0.f, 255.f, 255.f);
	sliderGreenChannel->setImageValues(-0.75f, -0.2f, 0.f, 0.2f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	sliderGreenChannel->registerObserver(&UI::Instance());
	sliderGreenChannel->registerObserver(&Player::Instance());
	frontWidgets["sliderGreenChannel"] = sliderGreenChannel;

	std::shared_ptr<Widget> sliderBlueChannel = std::make_shared<Slider>(sliderButtonNames, "sliderBlueChannel", 0.f, 255.f, 255.f);
	sliderBlueChannel->setImageValues(-0.75f, 0.0f, 0.f, 0.2f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	sliderBlueChannel->registerObserver(&UI::Instance());
	sliderBlueChannel->registerObserver(&Player::Instance());
	frontWidgets["sliderBlueChannel"] = sliderBlueChannel;

	std::shared_ptr<Widget> sliderAlphaChannel = std::make_shared<Slider>(sliderButtonNames, "sliderAlphaChannel", 0.f, 255.f, 255.f);
	sliderAlphaChannel->setImageValues(-0.75f, 0.2f, 0.f, 0.2f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	sliderAlphaChannel->registerObserver(&UI::Instance());
	sliderAlphaChannel->registerObserver(&Player::Instance());
	frontWidgets["sliderAlphaChannel"] = sliderAlphaChannel;

	std::shared_ptr<Widget> sliderBloom = std::make_shared<Slider>(sliderButtonNames, "sliderBloom", 0.f, 2.f);
	sliderBloom->setImageValues(-0.75f, 0.4f, 0.f, 0.2f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	sliderBloom->registerObserver(&UI::Instance());
	sliderBloom->registerObserver(&Player::Instance());
	frontWidgets["sliderBloom"] = sliderBloom;

	std::shared_ptr<Widget> sliderBloom2 = std::make_shared<Slider>(sliderButtonNames, "sliderBloom2", 0.f, 10.f);
	sliderBloom2->setImageValues(-0.75f, 0.55f, 0.f, 0.2f, 0.05f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	sliderBloom2->registerObserver(&UI::Instance());
	sliderBloom2->registerObserver(&Player::Instance());
	frontWidgets["sliderBloom2"] = sliderBloom2;

	// Timer
	std::shared_ptr<Widget> inGameTimer = std::make_shared<Timer>("inGameTimer");
	inGameTimer->setImageValues(-0.28f, 0.81f, 0.f, 0.08f, 0.08f, glm::radians(0.f), 1.f, 1.f, 1.f, 1.f);
	frontWidgets["inGameTimer"] = inGameTimer;
}

void OverlayEffectDemo::finalize()
{
}

void OverlayEffectDemo::update(float elapsedTime, GLFWwindow* window)
{
	for (auto it : backWidgets)
	{
		it.second->update(elapsedTime, window);
	}

	for (auto it : frontWidgets)
	{
		it.second->update(elapsedTime, window);

		if (it.first == "inGameTimer")
		{
			it.second->updateValues(Player::Instance().getInGameTimer().TimeStamp(), 0);
		}

		if (it.first == "redChannel")
		{
			it.second->updateValues(0, Player::currentColor.r);
		}
		if (it.first == "blueChannel")
		{
			it.second->updateValues(0, Player::currentColor.g);
		}
		if (it.first == "greenChannel")
		{
			it.second->updateValues(0, Player::currentColor.b);
		}
		if (it.first == "alphaChannel")
		{
			it.second->updateValues(0, Player::currentColor.a);
		}
		if (it.first == "bloom")
		{
			it.second->updateValues(0, BloomValues.x);
		}
		if (it.first == "bloom2")
		{
			it.second->updateValues(0, BloomValues.y);
		}

		if (it.first == "sliderRedChannel")
		{
			it.second->changeValue(Player::currentColor.r);
		}

		if (it.first == "sliderGreenChannel")
		{
			it.second->changeValue(Player::currentColor.g);
		}

		if (it.first == "sliderBlueChannel")
		{
			it.second->changeValue(Player::currentColor.b);
		}

		if (it.first == "sliderAlphaChannel")
		{
			it.second->changeValue(Player::currentColor.a);
		}

		if (it.first == "sliderBloom")
		{
			it.second->changeValue(BloomValues.x);
		}

		if (it.first == "sliderBloom2")
		{
			it.second->changeValue(BloomValues.y);
		}
	}
}

void OverlayEffectDemo::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
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