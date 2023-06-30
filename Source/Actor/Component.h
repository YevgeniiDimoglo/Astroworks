#pragma once

#include "Actor.h"

class Component
{
public:
	Component() {}
	virtual ~Component() {}

	virtual std::string getName() const = 0;

	virtual void start() {}

	virtual void update(float elapsedTIme) {}

	void setActor(std::shared_ptr<Actor> actor) { this->actor = actor; }
	std::shared_ptr<Actor> getActor() { return actor.lock(); }

private:
	std::weak_ptr<Actor>	actor;
};