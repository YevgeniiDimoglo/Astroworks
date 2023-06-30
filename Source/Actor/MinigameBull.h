#pragma once

// Only required for minigame

#include "Unit.h"
#include "Movement.h"

class MinigameBull : public Unit
{
public:
	MinigameBull();
	~MinigameBull() override;

	std::string getName() const override { return "MinigameBull"; }

	void setState(int number);

	void start() override;

	void update(float elapsedTime) override;

private:

	enum class State
	{
		Idle,
		Wander,
		Death,
	};

	void TransitionWanderState();
	void UpdateWanderState(float elapsedTime);

	void TransitionIdleState();
	void UpdateIdleState(float elapsedTime);

	void TransitionDeathState();
	void UpdateDeathState(float elapsedTime);

	void MinigameBullControl(float elapsedTime);

private:
	std::shared_ptr<Movement> movement;

	State state = State::Idle;

	glm::vec3 pointOfInterest;

	float timerToLive = 10.f;

	std::vector< std::pair<glm::vec3, int>> spawnPositionDirection
	{
		// Right
		{ { 3.0f, 1.0f, 2.0f}, 0 },
		{ { 3.0f, 1.0f,  1.0f}, 0 },
		{ { 3.0f, 1.0f,  0.0f}, 0 },
		{ { 3.0f, 1.0f, -1.0f}, 0 },
		{ { 3.0f, 1.0f, -2.0f}, 0 },

			// Up
		{ {-2.0f, 1.0f, -3.0f}, 1 },
		{ {-1.0f, 1.0f, -3.0f}, 1 },
		{ { 0.0f, 1.0f, -3.0f}, 1 },
		{ { 1.0f, 1.0f, -3.0f}, 1 },
		{ { 2.0f, 1.0f, -3.0f}, 1 },

			// Left
		{ {-3.0f, 1.0f, -2.0f}, 2 },
		{ {-3.0f, 1.0f, -1.0f}, 2 },
		{ {-3.0f, 1.0f,  0.0f}, 2 },
		{ {-3.0f, 1.0f,  1.0f}, 2 },
		{ {-3.0f, 1.0f,  2.0f}, 2 },

			// Down
		{ { 2.0f, 1.0f,  3.0f}, 3 },
		{ { 1.0f, 1.0f,  3.0f}, 3 },
		{ { 0.0f, 1.0f,  3.0f}, 3 },
		{ {-1.0f, 1.0f,  3.0f}, 3 },
		{ {-2.0f, 1.0f,  3.0f}, 3 },
	};
};