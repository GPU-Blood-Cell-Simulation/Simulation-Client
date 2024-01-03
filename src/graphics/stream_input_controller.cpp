#include "stream_input_controller.hpp"


void SimulationInputController::setInputCallback(GLFWwindow *window, ServerCommunicationController *controller)
{
    glfwSetWindowUserPointer(window, controller);
	glfwSetKeyCallback(window, SimulationInputController::handleUserInput);
}


void SimulationInputController::handleUserInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Event eventToSend;

    switch (key)
    {
    // Movement
    case GLFW_KEY_W:
        eventToSend = Event::cameraForward;
        break;

    case GLFW_KEY_S:
        eventToSend = Event::cameraBack;
        break;

    case GLFW_KEY_A:
        eventToSend = Event::cameraLeft;
        break;

    case GLFW_KEY_D:
        eventToSend = Event::cameraRight;
        break;

    case GLFW_KEY_SPACE:
        eventToSend = Event::cameraAscend;
        break;

    case GLFW_KEY_LEFT_SHIFT:
        eventToSend = Event::cameraDescend;
        break;

    // Rotation
    case GLFW_KEY_UP:
        eventToSend = Event::cameraRotateUp;
        break;

    case GLFW_KEY_DOWN:
        eventToSend = Event::cameraRotateDown;
        break;

    case GLFW_KEY_LEFT:
        eventToSend = Event::cameraRotateLeft;
        break;

    case GLFW_KEY_RIGHT:
        eventToSend = Event::cameraRotateRight;
        break;

    default:
        return;
    }

    // Get the ServerCommunicationController instance from a custom GLFW pointer
    auto controller = static_cast<ServerCommunicationController*>(glfwGetWindowUserPointer(window));

    switch (action)
    {
    case GLFW_PRESS:
        controller->sendStartEvent(eventToSend);
        break;

    case GLFW_RELEASE:
        controller->sendEndEvent(eventToSend);
        break;
    
    default:
        // Ignoring other events
        return;
    }
}
