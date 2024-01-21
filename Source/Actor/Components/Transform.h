#pragma once

// Transform component

#include "../../Graphics/Utilities.h"
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	void updateTransform();

private:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4x4 transform;
};