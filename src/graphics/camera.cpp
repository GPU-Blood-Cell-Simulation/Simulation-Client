#include "camera.hpp"

#include "../defines.hpp"

#include <glm/ext/matrix_transform.hpp>

namespace graphics
{
	inline constexpr float cameraMovementSpeed = width * cameraMovementSpeedCoefficient;

	Camera::Camera()
	{
		calculateView();
	}

	void Camera::moveLeft()
	{
		position -= right * cameraMovementSpeed;
		calculateView();
	}

	void Camera::moveRight()
	{
		position += right * cameraMovementSpeed;
		calculateView();
	}

	void Camera::moveForward()
	{
		position += front * cameraMovementSpeed;
		calculateView();
	}

	void Camera::moveBack()
	{
		position -= front * cameraMovementSpeed;
		calculateView();
	}

	void Camera::ascend()
	{
		position += up * cameraMovementSpeed;
		calculateView();
	}

	void Camera::descend()
	{
		position -= up * cameraMovementSpeed;
		calculateView();
	}

	void Camera::rotateLeft()
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), cameraRotationSpeed, up);
		front = rotation * glm::vec4(front, 1.0f);
		right = rotation * glm::vec4(right, 1.0f);
		calculateView();
	}

	void Camera::rotateRight()
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -cameraRotationSpeed, up);
		front = rotation * glm::vec4(front, 1.0f);
		right = rotation * glm::vec4(right, 1.0f);
		calculateView();
	}

	void Camera::rotateUp()
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), cameraRotationSpeed, right);
		front = rotation * glm::vec4(front, 1.0f);
		up = rotation * glm::vec4(up, 1.0f);
		calculateView();
	}

	void Camera::rotateDown()
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -cameraRotationSpeed, right);
		front = rotation * glm::vec4(front, 1.0f);
		up = rotation * glm::vec4(up, 1.0f);
		calculateView();
	}

	glm::mat4 graphics::Camera::getView() const
	{
		return view;
	}

	glm::vec3 graphics::Camera::getPosition() const
	{
		return position;
	}

	void graphics::Camera::calculateView()
	{
		view = glm::lookAt(position, position + front, up);
	}
}
