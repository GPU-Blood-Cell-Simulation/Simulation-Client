#include "stream_input_controller.hpp"


void SimulationInputController::setInputCallback(GLFWwindow *window, ClientCommunicationEndpoint *controller)
{
    glfwSetWindowUserPointer(window, controller);
	glfwSetKeyCallback(window, SimulationInputController::handleUserInput);
}


void SimulationInputController::handleUserInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    EventType eventToSend;

    // Get the ClientCommunicationEndpoint instance from a custom GLFW pointer
    auto controller = static_cast<ClientCommunicationEndpoint*>(glfwGetWindowUserPointer(window));

    // Single events
    switch (key)
    {
    case GLFW_KEY_V:
        if (action == GLFW_PRESS)
            controller->sendSingleEvent(EventType::togglePolygonMode);
        return;

    case GLFW_KEY_B:
        if (action == GLFW_PRESS)
            controller->sendSingleEvent(EventType::toggleSpringsRendering);
        return;
    
    default:
        break;
    }

    // Events with duration
    switch (key)
    {
    // Movement
    case GLFW_KEY_W:
        eventToSend = EventType::cameraForward;
        break;

    case GLFW_KEY_S:
        eventToSend = EventType::cameraBack;
        break;

    case GLFW_KEY_A:
        eventToSend = EventType::cameraLeft;
        break;

    case GLFW_KEY_D:
        eventToSend = EventType::cameraRight;
        break;

    case GLFW_KEY_SPACE:
        eventToSend = EventType::cameraAscend;
        break;

    case GLFW_KEY_LEFT_SHIFT:
        eventToSend = EventType::cameraDescend;
        break;

    // Rotation
    case GLFW_KEY_UP:
        eventToSend = EventType::cameraRotateUp;
        break;

    case GLFW_KEY_DOWN:
        eventToSend = EventType::cameraRotateDown;
        break;

    case GLFW_KEY_LEFT:
        eventToSend = EventType::cameraRotateLeft;
        break;

    case GLFW_KEY_RIGHT:
        eventToSend = EventType::cameraRotateRight;
        break;

    default:
        return;
    }

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
