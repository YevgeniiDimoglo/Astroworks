#include "Unit.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::start()
{
	movement = getActor()->getComponent<Movement>();

	GLTFStaticModel* model = getActor()->getModel();

	// Setup collisions
	if (getActor()->getTypeName() == "Base")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 1.f;
	}

	if (getActor()->getTypeName() == "Mineral")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.5f;
	}

	if (getActor()->getTypeName() == "Worker")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.3f;
	}

	if (getActor()->getTypeName() == "Player")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 1.f;
	}
}

void Unit::update(float elapsedTime)
{
	unitControl(elapsedTime);
}

void Unit::unitControl(float elapsedTime)
{
}