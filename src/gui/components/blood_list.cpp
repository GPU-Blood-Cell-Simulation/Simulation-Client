#include "../gui_controller.hpp"
#include "../../objects/bloodcellmodel.hpp"
#include "../../bloodcell/blood_editor.hpp"

namespace gui
{
	void GUIController::renderBloodList()
	{
		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}

		for(auto editor : editors)
		{
			if (ImGui::Button(editor->GetModelName().c_str())) {
				selectedEditor = editor;
				ImGui::OpenPopup("BloodListPopup");
			}
			ImGui::SameLine();
			ImGui::InputInt("quantity", &editor->modelQuantity);
		}
		if (ImGui::BeginPopup("BloodListPopup"))
		{
			if (ImGui::Button("Edit springs"))
				setMode(Mode::configureBloodCellSprings);
			else if (ImGui::Button("Edit vertices"))
				setMode(Mode::configureBloodCellVertices);
			ImGui::EndPopup();
		}
	}
}