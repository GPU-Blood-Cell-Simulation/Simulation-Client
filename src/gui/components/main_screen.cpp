
#include "../gui_controller.hpp"

#include "../extensions.hpp"

namespace gui
{
	void GUIController::renderMainScreen()
	{
        static const float textWidth = ImGui::CalcTextSize("Edit blood cell definitions").x;

        if (ext::CenteredButton("Edit general configuration", textWidth))
        {
            setMode(Mode::generalEdit);
        }
        ImGui::NewLine();

        if (ext::CenteredButton("Edit blood cell definitions", textWidth))
        {
            setMode(Mode::bloodEdit);
        }
        ImGui::NewLine();

        if (ext::CenteredButton("Edit vein mesh", textWidth))
        {
            setMode(Mode::veinEdit);
            glController.setMode(graphics::Mode::VeinEdit);
        }
        ImGui::NewLine();
        ImGui::Dummy(ImVec2(0.0f, 30.0f));

        if (ext::CenteredButton("Compile and run", textWidth))
        {
            // Write data to C++ files
            try
            {
                configManager.serializeAllToCpp();
            }
            catch (const std::exception& e)
            {
                setError("Error while creating config C++ headers for the server: \n" + std::string(e.what()));
                return;
            }

            // Send data to server
            //      TODO

            // Navigate to simulation screen
            setMode(Mode::simulation);
            glController.setMode(graphics::Mode::Simulation);
        }
	}
}