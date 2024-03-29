#pragma once

#include "camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace graphics
{
	/// <summary>
	/// Handles keyboard input and passes it to the camera
	/// </summary>
	class InputController
	{
	public:
		/// <summary>
		/// Sets handleUserInput method as keyboard event handler for specific window
		/// </summary>
		/// <param name="window">Window, which keyboard events should be handled</param>
		void setInputCallback(GLFWwindow* window);

		/// <summary>
		/// The callback that handles the input from user keyboard after GLFW polls events
		/// </summary>
		static void handleUserInput(GLFWwindow* window, int key, int scancode, int action, int mods);

		/// <summary>
		/// Moves or rotates the camera based on user keyboard input
		/// </summary>
		/// <param name="camera">The camera to move or rotate</param>
		void adjustParametersUsingInput(Camera& camera);
	private:
		struct PressedKeys
		{
			bool W = false;
			bool S = false;
			bool A = false;
			bool D = false;
			bool SPACE = false;
			bool SHIFT = false;

			bool UP = false;
			bool DOWN = false;
			bool LEFT = false;
			bool RIGHT = false;
		} pressedKeys;
	};
}