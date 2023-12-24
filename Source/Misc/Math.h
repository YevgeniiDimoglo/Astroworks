#pragma once

#include <cstdlib>

static float Lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}

static float RandomRange(float min, float max)
{
	return min + (max - min) * (rand() / static_cast<float>(RAND_MAX));
}
