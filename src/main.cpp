#include <glad/glad.h>

#include "defines.hpp"
#include "graphics/glcontroller.hpp"
#include "gui/GUIController.hpp"
#include "serializable/config_manager.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui/backend/imgui_impl_glfw.h>
#include <imgui/backend/imgui_impl_opengl3.h>
#include <sstream>


//#pragma float_control( except, on )
// NVIDIA GPU selector for devices with multiple GPUs (e.g. laptops)
extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

void programLoop(GLFWwindow* window);

int main()
{
    // OpenGL setup
#pragma region OpenGLsetup
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(windowWidth, windowHeight, "Blood Cell Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load GL and set the viewport to match window size
    gladLoadGL();
    glViewport(0, 0, windowWidth, windowHeight);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //VEIN_POLYGON_MODE = GL_FILL;

    // debug
    glEnable(GL_DEBUG_OUTPUT);

#pragma endregion

    // Main simulation loop

    programLoop(window);

    // Cleanup

    glfwTerminate();

    return 0;
}

// Main simulation loop - upon returning from this function all memory-freeing destructors are called
void programLoop(GLFWwindow* window)
{
    double lastTime = glfwGetTime();
    int frameCount = 0;

    // Create a configuration manager
    serializable::ConfigManager configManager;

    // Create the vein root
    std::unique_ptr<vein::Node> veinRoot = std::make_unique<vein::BifurcationNode>();

    // Create a graphics controller
    graphics::GLController glController(window, veinRoot.get());

    // Create a GUI controller
    gui::GUIController guiController(window, glController, configManager);

    // MAIN LOOP HERE - dictated by glfw

    while (!glfwWindowShouldClose(window))
    {
        // Clear 
        glClearColor(1.00f, 0.75f, 0.80f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Receive positions from the server
            // TODO

        // OpenGL render
        #pragma region rendering

        // simulation / vein editor rendering
        glController.draw();

        // gui rendering
        guiController.renderUI();

        glfwSwapBuffers(window);

        // Show FPS in the title bar
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;
        if (delta >= 1.0)
        {
            double fps = double(frameCount) / delta;
            std::stringstream ss;
            ss << "Blood Cell Simulation" << " " << " [" << fps << " FPS]";

            glfwSetWindowTitle(window, ss.str().c_str());
            lastTime = currentTime;
            frameCount = 0;
        }
        else
        {
            frameCount++;
        }
        #pragma endregion

        // Handle user input
        glfwPollEvents();
        glController.handleInput();
    }
}