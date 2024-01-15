#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

class Camera
{
public:

	void setLookAt(const glm::vec3& eye, const glm::vec3& focus, const glm::vec3& up);
	void setPerspectiveFov(float fovY, float widht, float height, float nearZ, float farZ);

	void setAspect(float width, float height) { this->aspect = width / height; }
	void setFront(glm::vec3 front) { this->front = front; }
	void setPosition(glm::vec3 position) { this->eye = position; }

	glm::mat4x4 getView() const { return view; }
	glm::mat4x4 getViewMatrix()
	{
		glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.f), eye);
		glm::mat4 cameraRotation = getRotationMatrix();
		return glm::inverse(cameraTranslation * cameraRotation);
	}

	glm::mat4x4 getRotationMatrix()
	{
		glm::vec3 norm_up = glm::normalize(up);
		glm::vec3 norm_front = glm::normalize(front);
		glm::vec3 norm_right = glm::normalize(right);

		float pitch = std::atan2(norm_front.y, norm_up.y);
		float yaw = std::atan2(norm_right.x, norm_front.x);

		glm::quat pitchRotation = glm::angleAxis(pitch, glm::vec3{ 1.f, 0.f, 0.f });
		glm::quat yawRotation = glm::angleAxis(yaw, glm::vec3{ 0.f, -1.f, 0.f });

		return glm::mat4_cast(yawRotation) * glm::mat4_cast(pitchRotation);
	}

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
	float aspect = 1.7f;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
};