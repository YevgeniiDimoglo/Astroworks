#pragma once

#include "Utilities.h"

enum class LightType
{
	Directional,
	Point,
	Spot,
	Areal,
};

class Light
{
public:
	Light(LightType lightType = LightType::Directional);

	void DrawDebugPrimitive();

	LightType GetLightType() { return lightType; }

	glm::vec3 GetPosition() { return position; }
	void SetPosition(glm::vec3 position) { this->position = position; }

	glm::vec3 GetDirection() { return direction; }
	void SetDirection(glm::vec3 direction) { this->direction = direction; }

	glm::vec4 GetColor() { return color; }
	void SetColor(glm::vec4) { this->color = color; }

	void SetRange(float range) { this->range = range; }

	float GetInnerCorner() { return innerCorner; }
	void SetInnerCorner(float innerCorner) { this->innerCorner = innerCorner; }

	float GetOuterCorner() { return outerCorner; }
	void SetOuterCorner(float outerCorner) { this->outerCorner = outerCorner; }

private:
	LightType	lightType = LightType::Directional;
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 direction = glm::vec3(0, -1, -1);
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	float range = 20.0f;
	float innerCorner = 0.99f;
	float outerCorner = 0.9f;
};

class LightManager
{
	LightManager() {};
	~LightManager();

public:
	static LightManager& Instance()
	{
		static LightManager lightManager;
		return lightManager;
	}

	void Register(Light* light);

	void Remove(Light* light);

	void Clear();

	void DrawDebugPrimitive();

	glm::vec4 GetAmbientColor() { return ambientColor; }
	void SetAmbientColor(glm::vec4 ambientColor) { this->ambientColor = ambientColor; }

	int GetLightCount() const { return static_cast<int>(lights.size()); }
	Light* GetLight(int index) const { return lights.at(index); }

private:
	std::vector<Light*> lights;
	glm::vec4 ambientColor = { 0.2f, 0.2f, 0.2f, 1.0f };
};