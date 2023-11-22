#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\euler_angles.hpp>

class Camera
{
public:

	void setLookAt(const glm::vec3& eye, const glm::vec3& focus, const glm::vec3& up);
	void setPerspectiveFov(float fovY, float widht, float height, float nearZ, float farZ);

	void setAspect(float width, float height) { this->aspect = width / height; }

	glm::mat4x4 getView() const { return view; }
	glm::mat4x4 getProjection() const { return projection; }

	glm::vec3 getEye() const { return eye; }
	glm::vec3 getFocus() const { return focus; }

	glm::vec3 getUp() const { return up; }
	glm::vec3 getFront() const { return front; }
	glm::vec3 getRight() const { return right; }

	float getFov() const { return fov; }
	float getAspect() const { return aspect; }
	float getNearPlane() const { return nearPlane; }
	float getFarPlane() const { return farPlane; }

private:
	glm::mat4x4 view;
	glm::mat4x4 projection;

	glm::vec3 eye;
	glm::vec3 focus;

	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 right;

	float fov = glm::radians(60.0f);
	float aspect = 1.7;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
};