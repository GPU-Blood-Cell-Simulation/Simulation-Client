#include "../gui_controller.hpp"
#include "../../serializable/blood_cells_definition.hpp"
#include "../../objects/bloodcellmodel.hpp"
#include "../../bloodcell/blood_editor.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

namespace gui
{
	using json = nlohmann::json;

	void GUIController::renderBloodList()
	{
		ImGui::Text("Defined blood cell models:");
		ImGui::PushItemWidth(100);
		ImGui::InputInt("Decimal precision", &decimalPrecision);
		if (decimalPrecision < 1)
			decimalPrecision = 1;
		if (decimalPrecision > 7)
			decimalPrecision = 7;

		ImGui::NewLine();
		for(auto editor : editors)
		{
			if (ImGui::Button(editor->GetModelName().c_str())) {
				selectedEditor = editor;
				ImGui::OpenPopup("BloodListPopup");
			}
			ImGui::SameLine();

			ImGui::PushItemWidth(100);
			if (ImGui::InputInt("quantity", &editor->modelQuantity))
			{
				editor->updateQuantity();
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
		if (ImGui::Button("Generate headers"))
		{
			bloodcell::bloodCellModel::createHeaderFromData(decimalPrecision);
		}
		if (ImGui::Button("Save config"))
		{
			json jout;
			serializable::to_json(jout);
			std::ofstream outjson("Config\\bloodCellConfig.json");
			outjson << std::setw(3) << jout << std::endl;
		}
		if (ImGui::Button("Read config"))
		{
			std::ifstream injson("Config\\bloodCellConfig.json");
			json jin = json::parse(injson);
			serializable::from_json(jin);
		}
		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}