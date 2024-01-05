#include "inputcontroller.hpp"

#include "../defines.hpp"

namespace graphics
{
	// GLFW keyboard callback function
	void InputController::handleUserInput(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		bool keyIsPressed;

		switch (action)
		{
		case GLFW_PRESS:
			keyIsPressed = true;
			break;

		case GLFW_RELEASE:
			keyIsPressed = false;
			break;
		
		default:
			// Ignoring other events
			return;
		}

		// Get the InputController instance from a custom GLFW pointer
		InputController* controller = static_cast<InputController*>(glfwGetWindowUserPointer(window));

		switch (key)
		{
		// Movement
		case GLFW_KEY_W:
			controller->pressedKeys.W = keyIsPressed;
			break;

		case GLFW_KEY_S:
			controller->pressedKeys.S = keyIsPressed;
			break;

		case GLFW_KEY_A:
			controller->pressedKeys.A = keyIsPressed;
			break;

		case GLFW_KEY_D:
			controller->pressedKeys.D = keyIsPressed;
			break;

		case GLFW_KEY_SPACE:
			controller->pressedKeys.SPACE = keyIsPressed;
			break;

		case GLFW_KEY_LEFT_SHIFT:
			controller->pressedKeys.SHIFT = keyIsPressed;
			break;

		// Rotation
		case GLFW_KEY_UP:
			controller->pressedKeys.UP = keyIsPressed;
			break;

		case GLFW_KEY_DOWN:
			controller->pressedKeys.DOWN = keyIsPressed;
			break;

		case GLFW_KEY_LEFT:
			controller->pressedKeys.LEFT = keyIsPressed;;
			break;

		case GLFW_KEY_RIGHT:
			controller->pressedKeys.RIGHT = keyIsPressed;
			break;

		// Change view mode
		case GLFW_KEY_V:
			if (action == GLFW_PRESS)
				glPolygonMode(GL_FRONT_AND_BACK, (VEIN_POLYGON_MODE = (VEIN_POLYGON_MODE == GL_LINE ? GL_FILL : GL_LINE)));
			break;
		}
	}

	// Check pressed keys every frame
	void InputController::adjustParametersUsingInput(Camera& camera)
	{
		if (pressedKeys.W)
			camera.moveForward();
		if (pressedKeys.S)
			camera.moveBack();
		if (pressedKeys.A)
			camera.moveLeft();
		if (pressedKeys.D)
			camera.moveRight();
		if (pressedKeys.SPACE)
			camera.ascend();
		if (pressedKeys.SHIFT)
			camera.descend();
		if (pressedKeys.UP)
			camera.rotateUp();
		if (pressedKeys.DOWN)
			camera.rotateDown();
		if (pressedKeys.LEFT)
			camera.rotateLeft();
		if (pressedKeys.RIGHT)
			camera.rotateRight();
	}
}
