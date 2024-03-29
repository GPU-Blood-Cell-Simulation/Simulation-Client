#include "../gui_controller.hpp"

#include "../extensions.hpp"

namespace gui
{
    void GUIController::renderSimulationTypeSelect()
    {
        static const float textWidth = ImGui::CalcTextSize("Run on Eden cluster").x;

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ext::CenteredText("Select how to run server");
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

#ifdef _WIN32
        ImGui::BeginDisabled(true);
#endif
        if (ext::CenteredButton("Run locally", textWidth))
        {
            setMode(Mode::localRuntime);
        }
#ifdef _WIN32
        ImGui::EndDisabled();
        ext::CenteredText("Option only avaibale on Linux");
#endif
        ImGui::NewLine();

        ImGui::BeginDisabled(true);
		ext::CenteredButton("Run on Eden cluster", textWidth);
		ImGui::EndDisabled();
        ImGui::NewLine();


        if (ext::CenteredButton("Manual run", textWidth))
        {
            setMode(Mode::manualRuntime);
        }
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        if(ext::CenteredButton("Back to main menu", textWidth))
        {
            setMode(Mode::mainScreen);
        }
    }
}


