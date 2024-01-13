#pragma once

enum class LightType
{
	Directional,
	Point,
	Spot,
	Area,
};

class Test
{
public:
	Test();
	virtual ~Test() = default;

private:
	int member;
};

class Light
{
public:
	Light();
	Light(LightType lightType) : lightType(lightType) {};

	virtual ~Light() = default;

	LightType GetLightType() { return lightType; }

	glm::vec3 GetPosition() { return position; }
	void SetPosition(glm::vec3 position) { this->position = position; }

	glm::vec4 GetColor() { return color; }
	void SetColor(glm::vec4) { this->color = color; }

protected:

	LightType lightType;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec4 color = glm::vec4(1, 1, 1, 1);

	float ambientIntensity;
	float diffuseIntensity;

	glm::mat4 lightProj;
};

class DirectionalLight : public Light
{
public:

	DirectionalLight() : Light(LightType::Directional) {};

	void InitLight(float red, float green, float blue,
		float aIntensity, float dIntensity,
		float xDir, float yDir, float zDir)
	{
		color.r = red;
		color.b = blue;
		color.g = green;
		ambientIntensity = aIntensity;
		diffuseIntensity = dIntensity;

		direction = { xDir, yDir, zDir };
	};

	glm::vec3 GetDirection() { return direction; }
	void SetDirection(glm::vec3 direction) { this->direction = direction; }

private:
	glm::vec3 direction;
};

class PointLight : public Light
{
public:
	PointLight() : Light(LightType::Point) {};

	void InitLight(float near, float far,
		float red, float green, float blue,
		float aIntensity, float dIntensity,
		float xPos, float yPos, float zPos,
		float con, float lin, float exp)
	{
		color.r = red;
		color.b = blue;
		color.g = green;
		ambientIntensity = aIntensity;
		diffuseIntensity = dIntensity;

		constant = con;
		linear = lin;
		exponent = exp;
	};

	void SetRange(float range) { this->range = range; }

	std::vector<glm::mat4> CalculateLightTransform();

	glm::vec3 GetPosition();
	GLfloat GetFarPlane();

private:
	float range = 20.0f;
	float constant, linear, exponent;
	float farPlane;
};

class SpotLight : public Light
{
public:

	SpotLight() : Light(LightType::Spot) {};

	void InitLight(float near, float far,
		float red, float green, float blue,
		float aIntensity, float dIntensity,
		float xPos, float yPos, float zPos,
		float xDir, float yDir, float zDir,
		float con, float lin, float exp,
		float edge)
	{
		color.r = red;
		color.b = blue;
		color.g = green;
		ambientIntensity = aIntensity;
		diffuseIntensity = dIntensity;

		constant = con;
		linear = lin;
		exponent = exp;
	};

	void SetRange(float range) { this->range = range; }

	float GetInnerCorner() { return innerCorner; }
	void SetInnerCorner(float innerCorner) { this->innerCorner = innerCorner; }

	float GetOuterCorner() { return outerCorner; }
	void SetOuterCorner(float outerCorner) { this->outerCorner = outerCorner; }

private:
	float range = 20.0f;
	float innerCorner = 0.99f;
	float outerCorner = 0.9f;
	float constant, linear, exponent;
};