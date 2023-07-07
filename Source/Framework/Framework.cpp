#include "Framework.h"

Framework::Framework()
{
	thisApp = Graphics();

	ResourceManager recourceManager = ResourceManager::Instance();
	//recourceManager.loadFile("./Data/Level/Level.toml");
	recourceManager.loadFile("./Data/Level/MinigameLevel.toml");

	for (auto it : recourceManager.getActorsOnScreen())
	{
		std::shared_ptr<Actor> actor = ActorManager::Instance().create();
		actor->loadModel(it.filePath);
		actor->setName(it.name);
		actor->setPosition(it.position);
		actor->setEuler(it.euler);
		actor->setScale(it.scale);
		actor->setType(it.type);
		actor->setTypeName(it.typeName);

		if (it.type == "Unit")
		{
			actor->addComponent<Movement>();

			if (it.typeName == "Worker")
			{
				actor->addComponent<Worker>(it.name);
			}
			else
			{
				actor->addComponent<Unit>();
			}
		}

		if (it.type == "Building")
		{
			actor->addComponent<Unit>();
		}
	}

	UI::Instance().setFileNames(recourceManager.loadFilePathes("./Data/UI/"));
	UI::Instance().changeOverlay(std::make_unique<OverlayTitle>());

	thisApp.init();

	camera.setPerspectiveFov(
		glm::radians(60.f),
		thisApp.getExtent().width, thisApp.getExtent().height,
		0.1f,
		1000.0f);
}

Framework::~Framework()
{
	thisApp.finalize();
}

void Framework::update(HighResolutionTimer timer, float elapsedTime)
{
	ActorManager::Instance().update(elapsedTime);

	UI::Instance().update(timer, elapsedTime);

	lockCameraController.Update(thisApp.getWindow(), elapsedTime);
	lockCameraController.SyncControllerToCamera(camera);

	thisApp.update(timer, elapsedTime, camera);

	if (glfwGetKey(thisApp.getWindow(), GLFW_KEY_F11) == GLFW_PRESS)
	{
		ResourceManager::Instance().saveFile("./Data/Level/NewLevel.toml");
	}
}

void Framework::render(HighResolutionTimer timer, float elapsedTime)
{
	thisApp.draw(timer, elapsedTime);
}

void Framework::run()
{
	while (!glfwWindowShouldClose(thisApp.getWindow()))
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

	// Compute averages over one second period.
	if ((timer.TimeStamp() - time_tlapsed) >= 1.0f)
	{
		float fps = static_cast<float>(frames);
		float mspf = 1000.0f / fps;
		std::ostringstream outs;
		outs.precision(6);
		outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
		glfwSetWindowTitle(thisApp.getWindow(), outs.str().c_str());

		// Reset for next average.
		frames = 0;
		time_tlapsed += 1.0f;
	}
}