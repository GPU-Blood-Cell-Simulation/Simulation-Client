#include "../gui_controller.hpp"

#include "../extensions.hpp"
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
			std::string inputName = "quantity##" + editor.GetModelName();
			if (ImGui::InputInt(inputName.c_str(), &editor.modelQuantity))
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
		ImGui::Text("Add custom blood cell definition with name ");
		ImGui::SameLine();
		ImGui::PushItemWidth(200);
		ImGui::InputText("##cellname", newCellName, 512);
		ImGui::SameLine();
		ImGui::Text(" vertices count ");
		ImGui::SameLine();
		ImGui::InputInt("##verticecount", &newCellVerticesCount);
		ImGui::SameLine();
		if (newCellVerticesCount < 0)
			newCellVerticesCount = 0;
		if (ImGui::Button("+"))
		{
			serializable::BloodCellType newCell = { 0, std::string(newCellName), 0, {1,1,1}};
			editors.push_back(newCell);
			memset(newCellName, 0, 512 * sizeof(char));
			newCellVerticesCount = 0;
		}
		ImGui::NewLine();

		if (ext::CenteredButton("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}