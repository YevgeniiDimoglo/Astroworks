#pragma once

#include "../Misc/HighResolutionTimer.h"
#include "../Graphics/Graphics.h"

#include "../Camera/Camera.h"
#include "../Camera/FreeCameraController.h"
#include "../Camera/LockCameraController.h"

#include "../Actor/Actor.h"
#include "../Actor/Unit.h"
#include "../Actor/Worker.h"
#include "../Actor/Movement.h"

#include "../UI/UI.h"
#include "../UI/OverlayTitle.h"
#include "../UI/OverlayGame.h"

#include "../Player/Player.h"

#include "ResourceManager.h"

class Framework
{
public:
	Framework();
	~Framework();

public:
	void run();

private:
	void update(HighResolutionTimer timer, float elapsedTime);
	void render(HighResolutionTimer timer, float elapsedTime);

	void calculateFrameStats();

private:

	HighResolutionTimer timer;

	Graphics thisApp;

	ResourceManager resourceManager;

	Camera camera;
	FreeCameraController freeCameraController;
	LockCameraController lockCameraController;

	Player player;
	bool inputLock = false;
};
