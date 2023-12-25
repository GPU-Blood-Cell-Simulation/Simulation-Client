#include "gui_controller.hpp"

#include "../vein/nodes/node.hpp"
#include <GLFW/glfw3.h>
#include <imgui/backend/imgui_impl_glfw.h>
#include <imgui/backend/imgui_impl_opengl3.h>


namespace gui
{
    void GUIController::setMode(Mode mode)
    {
        this->mode = mode;
    }

    void GUIController::selectNode(vein::Node* node, bool selectedLeft)
    {
        selectedNode = node;
        this->selectedLeft = selectedLeft;
        firstRender = true;
    }

    static ImGuiIO& createImguiContext()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        return ImGui::GetIO();
    }

	GUIController::GUIController(GLFWwindow* window, serializable::ConfigManager& configManager, graphics::GLController& glController) :
        io(createImguiContext()), configManager(configManager), glController(glController)
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
        // Delete child nodes that were marked "to be deleted" in the previous frame
        configManager.getData().veinDefinition.rootNode->deleteMarkedChildren();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // imgui debug
        bool show = false;
        if (show)
        {
            ImGui::ShowDemoWindow(&show);
            ImGui::Render();
            finalDraw();
            return;
        }
        

        ImGui::Begin("Configuration window"); // Create a window and append into it.        

        switch (mode)
        {
        case Mode::mainScreen:
            renderMainScreen();
            break;
        case Mode::generalEdit:
            renderGeneralEditor();
            break;
        case Mode::bloodEdit:
            renderBloodList();
            break;
        case Mode::veinEdit:
            renderVeinEditor();
            break;
        case Mode::addVein:
            renderAddVein();
            break;
        case Mode::simulation:
            renderSimulation();
            break;
        case Mode::configureBloodCellSprings:
            renderBloodCellSpringsDetails();
            break;
        case Mode::configureBloodCellVertices:
            renderBloodCellVerticesDetails();
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

    void GUIController::loadEditors()
    {
        editors.clear();
        for (auto&& type : configManager.getData().bloodCellsDefinition.bloodCellTypes)
        {
            editors.push_back(BloodEditor(type));
        }

        releaseEditor();
    }
}


