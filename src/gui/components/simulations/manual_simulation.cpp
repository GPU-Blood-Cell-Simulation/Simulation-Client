#include "../../gui_controller.hpp"

#include "../../extensions.hpp"


namespace gui
{
    void GUIController::renderManualSimulation()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ext::CenteredText("Config successfully generated");
        ImGui::Dummy(ImVec2(0.0f, 40.0f));
        ext::CenteredText("Run server manually and start watching stream");
        ImGui::NewLine();
        if (ext::CenteredButton("Watch stream", 200.0))
        {
            setMode(Mode::streamWatching);
        }
        ImGui::NewLine();
        if (ext::CenteredButton("Back to main menu", 200.0))
        {
            setMode(Mode::mainScreen);
        }
    }
}
