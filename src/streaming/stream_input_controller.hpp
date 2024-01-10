#pragma once

#include <GLFW/glfw3.h>

#include "../communication/client_endpoint.hpp"


class SimulationInputController {
public:
    static void setInputCallback(GLFWwindow* window, ClientCommunicationEndpoint* controller);

private:
    static void handleUserInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};
