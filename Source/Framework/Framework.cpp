#include "Framework.h"

#include "ResourceManager.h"

#include "../Actor/Actor.h"

#include "../UI/UI.h"
#include "../UI/OverlayGame.h"
#include "../UI/OverlayTitle.h"
#include "../UI/OverlayEffectDemo.h"

#include "../Player/Player.h"
#include "../Player/Enemy.h"
#include "../Input/Input.h"

#include "../Camera/Camera.h"
#include "../Camera/FreeCameraController.h"
#include "../Camera/LockCameraController.h"

Framework::Framework()
{
	std::srand(std::time(0));

	thisApp = std::make_unique<Graphics>();

	ActorManager::Instance().setCurrentLevelName("LevelDEFAULT");

	ResourceManager::Instance().loadFiles("./Data/Level/");

	ActorManager::Instance().deserializeActor();

	UI::Instance().setFileNames(ResourceManager::Instance().loadFilePathes("./Data/UI/"));
	UI::Instance().changeOverlay(std::make_unique<OverlayTitle>());

	thisApp->init();

	camera = new Camera();
	camera->setPerspectiveFov(
		glm::radians(60.f),
		thisApp->getExtent().width, thisApp->getExtent().height,
		0.1f,
		1000.0f);

	camera->setAspect(thisApp->getExtent().width, thisApp->getExtent().height);
	camera->setPosition({ 10.0f, 9.0f, 18.0f });

	freeCameraController = new FreeCameraController();
	lockCameraController = new LockCameraController();

	freeCameraController->SyncCameraToController(camera);
	lockCameraController->SyncCameraToController(camera);
}

Framework::~Framework()
{
	delete freeCameraController;
	delete lockCameraController;
	delete camera;

	thisApp->finalize();
}

void Framework::update(HighResolutionTimer timer, float elapsedTime)
{
	Player::Instance().input(thisApp->getWindow(), camera);

	Player::Instance().update();

	Enemy::Instance().update();

	ActorManager::Instance().update(elapsedTime);

	UI::Instance().update(timer, elapsedTime, thisApp->getWindow());

	if (!Player::Instance().getIsPaused())
	{
		if (isFreeCameraController)
		{
			freeCameraController->Update(thisApp->getWindow(), elapsedTime);
			freeCameraController->SyncControllerToCamera(camera);
		}
		else
		{
			lockCameraController->Update(thisApp->getWindow(), elapsedTime);
			lockCameraController->SyncControllerToCamera(camera);
		}
	}

	if (glfwGetKey(thisApp->getWindow(), GLFW_KEY_F9) == GLFW_PRESS)
	{
		thisApp->wireframe = !thisApp->wireframe;
	}

	if (glfwGetKey(thisApp->getWindow(), GLFW_KEY_F10) == GLFW_PRESS)
	{
		thisApp->drawUI = !thisApp->drawUI;
	}

	thisApp->update(timer, elapsedTime, camera);
}

void Framework::render(HighResolutionTimer timer, float elapsedTime)
{
	thisApp->draw(timer, elapsedTime);
}

void Framework::run()
{
	while (!glfwWindowShouldClose(thisApp->getWindow()))
	{
		glfwPollEvents();

		float elapsedTime;

		timer.Tick();
		calculateFrameStats();

		elapsedTime = syncInterval == 0
			? timer.TimeInterval()
			: syncInterval / 60.0f;

		update(timer, elapsedTime);
		render(timer, elapsedTime);
	}
}

void Framework::calculateFrameStats()
{
	static int frames = 0;
	static float time_tlapsed = 0.0f;

	frames++;

	if ((timer.TimeStamp() - time_tlapsed) >= 1.0f)
	{
		float fps = static_cast<float>(frames);
		float mspf = 1000.0f / fps;
		std::ostringstream outs;
		outs.precision(6);
		outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
		glfwSetWindowTitle(thisApp->getWindow(), outs.str().c_str());

		frames = 0;
		time_tlapsed += 1.0f;
	}
}