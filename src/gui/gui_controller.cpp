#include "gui_controller.hpp"

#include "extensions.hpp"
#include "themes/themes.hpp"
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

	GUIController::GUIController(GLFWwindow* window, serializable::ConfigManager& configManager, streaming::StreamManager& streamManager, graphics::GLController& glController):
        io(createImguiContext()), configManager(configManager), streamManager(streamManager), glController(glController)
	{
        // Setup Dear ImGui context
        io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowMinSize = ImVec2(500, 500);

        themes::cinder::setTheme();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
	}

	void GUIController::renderUI()
	{
        // Delete child nodes that were marked "to be deleted" in the previous frame
        configManager.getData().veinRootNode->deleteMarkedChildren();

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
        
        ImGuiWindowFlags windowFlags = 0;
        windowFlags |= ImGuiWindowFlags_MenuBar;

        ImGui::Begin("Configuration window", nullptr, windowFlags); // Create a window and append into it.        

        // Render error if occurred
        if (ImGui::BeginPopupModal("Error"))
        {
            ImGui::Text("%s", error.c_str());
            if (ext::CenteredButton("OK"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }

        renderMenuBar();

        switch (mode)
        {
        case Mode::mainScreen:
            renderMainScreen();
            break;
        case Mode::generalEdit:
            renderGeneralEditor();
            break;
        case Mode::bloodEdit:
            renderBloodList(configManager.getData());
            break;
        case Mode::veinEdit:
            renderVeinEditor();
            break;
        case Mode::addVein:
            renderAddVein();
            break;
        case Mode::streamWatching:
            renderStream();
            break;
        case Mode::selectingRuntimeType:
            renderSimulationTypeSelect();
            break;
        case Mode::manualRuntime:
            renderManualSimulation();
            break;
        case Mode::localRuntime:
            renderLocalSimulation();
            break;
        case Mode::configureBloodCellSprings:
            renderBloodCellSpringsDetails(configManager.getData());
            break;
        case Mode::configureBloodCellVertices:
            renderBloodCellVerticesDetails(configManager.getData());
            break;
        case Mode::configureBloodCellColor:
            renderBloodCellColorDetails(configManager.getData());
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
        for (size_t i = 0; i < configManager.getData().bloodCellsDefinition.bloodCellTypes.size(); ++i)
        {
            editors.push_back(BloodEditor(i));
        }

        releaseEditor();
    }

    void GUIController::addTypeAndEditor(std::string typeName, int typeSize)
    {
		serializable::BloodCellType newBloodCell = {typeSize, typeName, 0,  {1,1,1} };
		newBloodCell.vertices.resize(typeSize, {0,0,0});
		newBloodCell.normals.resize(typeSize, {0,0,0});
		for(int i = 0; i < typeSize; ++i)
        {
            newBloodCell.indices.push_back(i);
            newBloodCell.indices.push_back((i + 1)%typeSize);
            newBloodCell.indices.push_back((i + 2)%typeSize);
        }
        configManager.getData().bloodCellsDefinition.bloodCellTypes.push_back(newBloodCell);
        editors.push_back(configManager.getData().bloodCellsDefinition.bloodCellTypes.size() - 1);
    }

    void GUIController::setError(const std::string& msg)
    {
        ImGui::OpenPopup("Error");
        error = msg;
    }
}


