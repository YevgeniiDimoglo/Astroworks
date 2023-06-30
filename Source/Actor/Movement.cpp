#include "Movement.h"

Movement::Movement()
{
}

Movement::~Movement()
{
}

void Movement::SetRandomTargetPosition()
{
	float theta = ::RandomRange(0, glm::two_pi<float>());
	float range = ::RandomRange(0, territoryRange);

	targetPosition.x = territoryOrigin.x + range * sinf(theta);
	targetPosition.y = territoryOrigin.y;
	targetPosition.z = territoryOrigin.z + range * cosf(theta);
}

void Movement::SetTargetPosition(glm::vec3 pointOfInterest)
{
	targetPosition.x = pointOfInterest.x;
	targetPosition.y = pointOfInterest.y;
	targetPosition.z = pointOfInterest.z;
}

void Movement::MoveToTarget(float elapsedTime, float speedRate)
{
	std::shared_ptr<Actor> actor = getActor();
	currentPosition = actor->getPosition();
	float vx = targetPosition.x - currentPosition.x;
	float vz = targetPosition.z - currentPosition.z;
	float dist = sqrtf(vx * vx + vz * vz);
	vx /= dist;
	vz /= dist;

	MoveLocal(vx, vz, moveSpeed * speedRate, elapsedTime);
	//Turn(elapsedTime, vx, vz, turnSpeed * speedRate);
}

void Movement::MoveLocal(float vx, float vz, float speed, float elapsedTime)
{
	std::shared_ptr<Actor> actor = getActor();

	actor->setPosition({ actor->getPosition().x + vx * elapsedTime * speed , 0.f, actor->getPosition().z + vz * elapsedTime * speed });
}

void Movement::Turn(float elapsedTime, float vx, float vz, float speed)
{
	std::shared_ptr<Actor> actor = getActor();

	speed *= elapsedTime;

	if (vx == 0 && vz == 0) return;

	float moveVecLength = sqrtf(vx * vx + vz * vz);
	float moveVecX = vx / moveVecLength;
	float moveVecZ = vz / moveVecLength;

	float frontX = sinf(actor->getEuler().y);
	float frontZ = cosf(actor->getEuler().y);

	float cross = (moveVecZ * frontX) - (moveVecX * frontZ);

	float dot = (moveVecX * frontX) + (moveVecZ * frontZ);
	float rot = 1.0f - dot;

	if (rot >= speed)
	{
		rot = speed;
	}

	if (cross < 0.0f)
	{
		actor->setEuler({ actor->getEuler().x, actor->getEuler().y + rot, actor->getEuler().z });
	}
	else
	{
		actor->setEuler({ actor->getEuler().x, actor->getEuler().y - rot, actor->getEuler().z });
	}
}