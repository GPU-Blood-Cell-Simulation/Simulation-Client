#include "../gui_controller.hpp"
#include "../../bloodcell/blood_editor.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

namespace gui
{
	using json = nlohmann::json;

	void GUIController::renderBloodList()
	{
		static int decimalPrecision = 7;
		ImGui::Text("Defined blood cell models:");
		ImGui::PushItemWidth(100);
		ImGui::InputInt("Decimal precision", &decimalPrecision);
		if (decimalPrecision < 1)
			decimalPrecision = 1;
		if (decimalPrecision > 7)
			decimalPrecision = 7;

		// TODO: save decimalPrecision to config data (do we really need it?)

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