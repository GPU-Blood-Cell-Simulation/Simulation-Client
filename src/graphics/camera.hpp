#pragma once

#include "../defines.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>


namespace graphics
{
	/// <summary>
	/// Corresponds to the position of the user in the OpenGL world. Responsible for transforming the View matrix
	/// </summary>
	class Camera
	{
	public:
		Camera();

		void moveLeft();
		void moveRight();
		void moveForward();
		void moveBack();
		void ascend();
		void descend();

		void rotateLeft();
		void rotateRight();
		void rotateUp();
		void rotateDown();

		/// <summary>
		/// Returns the view matrix associated with current camera position and rotation
		/// </summary>
		/// <returns>The view matrix</returns>
		glm::mat4 getView() const;

		/// <summary>
		/// Current camera position
		/// </summary>
		/// <returns>The camera's position</returns>
		glm::vec3 getPosition() const;

	private:
		glm::mat4 view;

		glm::vec3 position = glm::vec3(0, 0, depth * 3);
		glm::vec3 front = glm::vec3(0, 0, -1);
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = glm::cross(front, up);

		/// <summary>
		/// Recalculates the View matrix when position or rotation changes
		/// </summary>
		void calculateView();
	};
}
