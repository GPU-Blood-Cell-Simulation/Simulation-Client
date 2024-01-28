#pragma once

#include <GLFW/glfw3.h>

#include "../communication/client_endpoint.hpp"


class SimulationInputController {
public:
    /// <summary>
    /// Setup callback, which sends events to server during streaming in response to clicking keys
    /// </summary>
    /// <param name="window">Pointer to GLFW window with stream output</param>
    /// <param name="controller">Message controller connected to server</param>
    static void setInputCallback(GLFWwindow* window, ClientCommunicationEndpoint* controller);

private:
    static void handleUserInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};
