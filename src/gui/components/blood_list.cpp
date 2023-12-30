#include "../gui_controller.hpp"
#include "../../bloodcell/blood_editor.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

namespace gui
{
	using json = nlohmann::json;

	void GUIController::renderBloodList()
	{
		if (editors.size() == 0)
			ImGui::Text("No blood cells defined yet");
		else
			ImGui::Text("Defined blood cell models:");
		ImGui::NewLine();
		for(auto& editor : editors)
		{
			if (ImGui::Button(editor.GetModelName().c_str())) {
				selectedEditor = &editor;
				ImGui::OpenPopup("BloodListPopup");
			}
			ImGui::SameLine();

			ImGui::PushItemWidth(100);
			if (ImGui::InputInt("quantity", &editor.modelQuantity))
			{
				editor.updateQuantity();
			}
		}
		if (ImGui::BeginPopup("BloodListPopup"))
		{
			if (ImGui::Button("Edit springs"))
				setMode(Mode::configureBloodCellSprings);
			else if (ImGui::Button("Edit vertices"))
				setMode(Mode::configureBloodCellVertices);			
			ImGui::EndPopup();
		}
		ImGui::NewLine();
		ImGui::NewLine();

		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}