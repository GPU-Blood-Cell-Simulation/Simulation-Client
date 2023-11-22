#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderMainScreen()
	{
        if (ImGui::Button("Load configuration"))
        {
            configManager.loadConfiguration("Config/config.json");
        }
        if (ImGui::Button("Save configuration"))
        {
            configManager.saveConfiguration("Config/config.json");
        }

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
            setMode(Mode::simulation);
            glController.setMode(graphics::Mode::Simulation);
        }
	}
}