#include "../gui_controller.hpp"

#include "../extensions.hpp"

namespace gui
{
	void GUIController::renderGeneralEditor()
	{
		static int selectedTab = 0;
		auto& style = ImGui::GetStyle();
		auto buttonWidth = ImGui::GetWindowSize().x / 3 - 10;

		auto pushStyle = [&](int tab)
			{
				if (tab == selectedTab)
					ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_ButtonActive]);
				else
					ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_Button]);
			};
		
		pushStyle(0);
		if (ImGui::Button("Simulation", ImVec2(buttonWidth, 40)))
		{
			selectedTab = 0;
		}
		ImGui::PopStyleColor();
		ImGui::SameLine();

		pushStyle(1);
		if (ImGui::Button("Physics", ImVec2(buttonWidth, 40)))
		{
			selectedTab = 1;
		}
		ImGui::PopStyleColor();
		ImGui::SameLine();

		pushStyle(2);
		if (ImGui::Button("Graphics", ImVec2(buttonWidth, 40)))
		{
			selectedTab = 2;
		}
		ImGui::PopStyleColor();

		ImGui::NewLine();
		switch (selectedTab)
		{
		case 0:
			renderSimulationEditor();
			break;
		case 1:
			renderPhysicsEditor();
			break;
		case 2:
			renderGraphicsEditor();
			break;
		}

		ImGui::NewLine();
		if (ext::CenteredButton("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}