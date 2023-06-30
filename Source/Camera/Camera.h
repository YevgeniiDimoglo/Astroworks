#pragma once

#include "../Graphics/Utilities.h"

class Camera
{
public:

	void setLookAt(const glm::vec3& eye, const glm::vec3& focus, const glm::vec3& up);
	void setPerspectiveFov(float fovY, float widht, float height, float nearZ, float farZ);

	glm::mat4x4 getView() const { return view; }
	glm::mat4x4 getProjection() const { return projection; }

	glm::vec3 getEye() const { return eye; }
	glm::vec3 getFocus() const { return focus; }

	glm::vec3 getUp() const { return up; }
	glm::vec3 getFront() const { return front; }
	glm::vec3 getRight() const { return right; }

private:
	glm::mat4x4 view;
	glm::mat4x4 projection;

	glm::vec3 eye;
	glm::vec3 focus;

	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 right;
};