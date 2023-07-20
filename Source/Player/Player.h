#pragma once

// Player information

#include "../Graphics/Utilities.h"

#include "../Actor/Actor.h"
#include "../Camera/Camera.h"

class Player : public IObserver
{
private:

	Player() {}
	virtual ~Player() {}

public:
	static Player& Instance()
	{
		static Player instance;
		return instance;
	}

	void notify(std::string widgetName, int widgetAction) override;

	std::string getSelectedActor(GLFWwindow* window, Camera& camera);
	std::string getTargetActor(GLFWwindow* window, Camera& camera);

	void setSelectedActorIndex(int index) { selectedActorIndex = index; }
	int getSelectedActorIndex() const { return selectedActorIndex; }

	void setMineralValue(int mineralValue) { this->mineralValue = mineralValue; }
	int getMineralValue() const { return mineralValue; }

	void setPause(bool pause) { isPaused = pause; }
	void setUnPause(bool unpause) { isPaused = unpause; }
	bool getIsPaused() const { return isPaused; }

	void input(GLFWwindow* window, Camera camera);

	void update();

	void changePause() { isPaused = !isPaused; }

private:

	void calculateScreenToWorldCoords(GLFWwindow* window, Camera& camera);

	struct CameraRay
	{
		glm::vec3 rayStart;
		glm::vec3 rayEnd;
		glm::vec3 rayDirection;
	} cameraRay;

	std::string selectedActorName;
	std::string selectedTargetName;

	glm::vec3 movementPoint = { 0.f, 0.f, 0.f };

	bool inputLockLMB = false;
	bool inputLockRMB = false;

	// Player objects

	int mineralValue = 0;
	int selectedActorIndex = 0;

	bool isPaused = false;

	std::vector<std::shared_ptr<Actor>> controlledActors;
	std::vector<std::shared_ptr<Actor>> selectedActors;
};