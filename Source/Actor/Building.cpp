#include "Building.h"

void Building::start()
{
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
}

void Building::update(float elapsedTime)
{
	buildingControl(elapsedTime);
}

void Building::buildingControl(float elapsedTime)
{
}