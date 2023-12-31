#pragma once

#include <GLFW/glfw3.h>

#include "../communication/server_communication_controller.hpp"


class SimulationInputController {
public:
    static void setInputCallback(GLFWwindow* window, ServerCommunicationController* controller);

private:
    static void handleUserInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};
