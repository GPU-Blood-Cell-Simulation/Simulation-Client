#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderMainScreen()
	{
        // TODO: change save/load into a top bar menu
        if (ImGui::Button("Load blood cell configuration"))
        {
            configManager.loadBloodCellConfig();
            loadEditors();
        }
        if (ImGui::Button("Save blood cell configuration"))
        {
            configManager.saveBloodCellConfig();
        }
        if (ImGui::Button("Load vein configuration"))
        {
            configManager.loadVeinConfig();
        }
        if (ImGui::Button("Save vein configuration"))
        {
            configManager.saveVeinConfig();
        }
        if (ImGui::Button("Load general configuration"))
        {
            
        }
        if (ImGui::Button("Save general configuration"))
        {
            
        }
        ImGui::NewLine();

        if (ImGui::Button("Edit general configuration"))
        {
            setMode(Mode::generalEdit);
        }
        if (ImGui::Button("Edit blood cell definitions"))
        {
            setMode(Mode::bloodEdit);
        }
        if (ImGui::Button("Edit vein mesh"))
        {
            setMode(Mode::veinEdit);
            glController.setMode(graphics::Mode::VeinEdit);
        }

        if (ImGui::Button("Compile and run"))
        {
            // Write data to C++ files
            configManager.serializeAllToCpp();

            // Send data to server
            //      TODO

            // Navigate to simulation screen
            setMode(Mode::simulation);
            glController.beginSimulation();
        }
	}
}