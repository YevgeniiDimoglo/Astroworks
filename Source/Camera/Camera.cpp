#include "Camera.h"

void Camera::setLookAt(const glm::vec3& neye, const glm::vec3& nfocus, const glm::vec3& nup)
{
	view = glm::lookAt(neye, nfocus, nup);
	view = glm::inverse(view);

	right = glm::vec3(view[0][0], view[1][0], view[2][0]);
	up = glm::vec3(view[0][1], view[1][1], view[2][1]);
	front = glm::vec3(view[0][2], view[1][2], view[2][2]);

	this->eye = neye;
	this->focus = nfocus;
}

void Camera::setPerspectiveFov(float fovY, float width, float height, float nearZ, float farZ)
{
	projection = glm::perspectiveFov(fovY, width, height, nearZ, farZ);
}