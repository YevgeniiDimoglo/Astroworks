#include "Unit.h"

void Unit::start()
{
	movement = getActor()->getComponent<Movement>();

	GLTFStaticModel* model = getActor()->getModel();

	// Setup collisions
	if (getActor()->getTypeName() == "Worker")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.3f;
	}

	if (getActor()->getTypeName() == "Alien")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.3f;
	}

	if (getActor()->getTypeName() == "Marine")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.3f;
	}

	if (getActor()->getTypeName() == "Tank")
	{
		collisionPosition = getCollisionPosition();
		collisionRadius = 0.5f;
	}
}

void Unit::update(float elapsedTime)
{
	unitControl(elapsedTime);
}

void Unit::unitControl(float elapsedTime)
{
}

void Unit::applyDamage(int damage)
{
	HP -= damage;
}