#pragma once

enum class LightType
{
	Directional,
	Point,
	Spot,
	Area,
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
		float xPos, float yPos, float zPos,
		float FOV, float distance, float angleX, float angleY)
	{
		color.r = red;
		color.b = blue;
		color.g = green;
		ambientIntensity = aIntensity;
		diffuseIntensity = dIntensity;

		lightDist = distance;
		lightAngle = FOV;
		lightXAngle = angleX;
		lightYAngle = angleY;

		const glm::mat4 rotY = glm::rotate(glm::mat4(1.f), lightYAngle, glm::vec3(0, 1, 0));
		const glm::mat4 rotX = glm::rotate(rotY, lightXAngle, glm::vec3(1, 0, 0));

		//lightPosition = glm::vec3(rotX * glm::vec4(0, 0, lightDist, 1.0f));
		lightPosition = glm::vec3(xPos, yPos, zPos);

		lightProjection = glm::perspective(glm::radians(lightAngle), 1.0f, lightNear, lightFar);

		lightView = glm::lookAt(glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z), glm::vec3(0), glm::vec3(0, 1, 0));

		direction = -glm::normalize(glm::vec3(lightView[2]));
	};

	glm::vec3 GetLightPosition() { return lightPosition; }
	glm::mat4 GetLightProjection() { return lightProjection; }
	glm::mat4 GetLightView() { return lightView; }
	glm::vec3 GetDirection() { return direction; }

private:
	glm::vec3 direction;

	float lightAngle = 120.0f;
	float lightNear = 1.0f;
	float lightFar = 1000.0f;

	float lightDist = 10.0f;
	float lightXAngle = 0.0f;
	float lightYAngle = 0.5f;

	glm::vec3 lightPosition = glm::vec3(0);

	glm::mat4 lightProjection = glm::mat4(1);
	glm::mat4 lightView = glm::mat4(1);
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