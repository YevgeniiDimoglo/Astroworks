#pragma once

// Enemy information

#include "../Graphics/Utilities.h"

class Enemy : public IObserver
{
private:

	Enemy() {}
	virtual ~Enemy() {}

public:
	static Enemy& Instance()
	{
		static Enemy instance;
		return instance;
	}

	void notify(std::string widgetName, int widgetAction) override;

	void spawn();

	void update();

private:

	glm::vec3 position = { 0.f, 0.f, 25.f };

	bool lockspawn = false;
};