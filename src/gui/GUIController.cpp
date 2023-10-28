#include "GUIController.hpp"

#include<GLFW/glfw3.h>

#include <imgui/backend/imgui_impl_glfw.h>
#include <imgui/backend/imgui_impl_opengl3.h>


namespace gui
{
    static ImGuiIO& createImguiContext()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        return ImGui::GetIO();
    }

	GUIController::GUIController(GLFWwindow* window, graphics::GLController& glController, serializable::ConfigManager& configManager) :
        io(createImguiContext()), glController(glController), configManager(configManager)
	{
        // Setup Dear ImGui context
        io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
	}

	void GUIController::renderUI()
	{
        static int previousButtonClicked = 0;
        static int buttonClicked = 0;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Configuration window"); // Create a window and append into it.        

        if (glController.mode == graphics::Mode::Simulation)
        {
            ImGui::Text("Simulation in progress...");
        }
        else
        {
            ImGui::Text("Mode");
            ImGui::RadioButton("general config", &buttonClicked, 0); ImGui::SameLine();
            ImGui::RadioButton("Simulation", &buttonClicked, 1); ImGui::SameLine();
            ImGui::RadioButton("Vein edition", &buttonClicked, 2);
        }

        if (buttonClicked != previousButtonClicked) // button selection changed
        {
            switch (buttonClicked)
            {
            case 0:
                glController.mode = graphics::Mode::None;
                break;
            case 1:
                glController.mode = graphics::Mode::None;
                break;
            case 2:
                glController.mode = graphics::Mode::VeinEdition;
                break;
            }
            previousButtonClicked = buttonClicked;
        }

        switch (buttonClicked)
        {
        case 0:
            ImGui::Text("General configuration screen");
            if (ImGui::Button("Load configuration"))
            {
                configManager.loadConfiguration("Config/config.json");
            }
            if (ImGui::Button("Save configuration"))
            {
                configManager.saveConfiguration("Config/config.json");
            }
            break;
        case 1:
            ImGui::Text("Simulation screen");
            if (glController.mode == graphics::Mode::Simulation)
            {
                if (ImGui::Button("Cancel"))
                {
                    glController.endSimulation();
                }
            }
            else
            {
                if (ImGui::Button("Compile and run (placeholder)"))
                {
                    glController.beginSimulation(configManager.getData());
                }
            }

            break;
        case 2:
            ImGui::Text("Vein editor screen");
            break;
        }

        ImGui::End();

        ImGui::Render();
        finalDraw();
	}

    void GUIController::finalDraw()
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}


