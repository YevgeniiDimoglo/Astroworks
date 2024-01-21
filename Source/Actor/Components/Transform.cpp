#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::updateTransform()
{
	// Transform matrix
	/*glm::mat4x4 translate = glm::translate(glm::mat4x4(1.0f), this->position);

	this->rotation = glm::quat(euler);
	glm::mat4x4 rotate = glm::mat4_cast(this->rotation);

	glm::mat4x4 scale = glm::scale(glm::mat4x4(1.0f), this->scale);

	glm::mat4x4 transform = translate * rotate * scale;*/
}