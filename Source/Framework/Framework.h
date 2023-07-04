#pragma once

#include "../Misc/HighResolutionTimer.h"
#include "../Graphics/Graphics.h"

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
};
