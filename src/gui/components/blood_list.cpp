#include "../gui_controller.hpp"

#include "../extensions.hpp"
#include "../../bloodcell/blood_editor.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

#ifndef _cellTypes
#define _cellTypes config.bloodCellsDefinition.bloodCellTypes
#endif

namespace gui
{
	using json = nlohmann::json;

	void GUIController::renderBloodList(serializable::ConfigData& config)
	{
		if (editors.size() == 0)
			ImGui::Text("No blood cells defined yet");
		else
			ImGui::Text("Defined blood cell models:");
		ImGui::NewLine();
		for(auto& editor : editors)
		{
			serializable::BloodCellType& modelData = _cellTypes.at(editor.editorIndex);
			if (ImGui::Button(modelData.name.c_str())) {
				selectedEditor = &editor;
				editor.recalculateBloodTypeDiameter(_cellTypes.at(editor.editorIndex));
				ImGui::OpenPopup("BloodListPopup");
			}
			ImGui::SameLine();

			ImGui::PushItemWidth(100);
			std::string inputName = "quantity##" + modelData.name;
			ImGui::InputInt(inputName.c_str(), &modelData.quantity);
		}
		if (ImGui::BeginPopup("BloodListPopup"))
		{
			if (ImGui::Button("Edit springs"))
				setMode(Mode::configureBloodCellSprings);
			else if (ImGui::Button("Edit vertices"))
				setMode(Mode::configureBloodCellVertices);			
			ImGui::EndPopup();
		}

		static char newCellName[255] = "";
		static int newCellVerticesCount = 1;

		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::Text("Add custom blood cell definition: ");
		ImGui::Text("\tName:");
		ImGui::SameLine();
		ImGui::PushItemWidth(130);
		ImGui::InputText("##cellname", newCellName, IM_ARRAYSIZE(newCellName));
		ImGui::Text("\tVertices count:");
		ImGui::SameLine();
		ImGui::InputInt("##verticecount", &newCellVerticesCount);
		if (newCellVerticesCount < 1)
			newCellVerticesCount = 1;
		if (ImGui::Button(" Add "))
		{
			std::string newName(newCellName);
			if(!newName.empty() && std::all_of(newName.begin(), newName.end(), [](auto ch) { return !std::isspace(ch);}) && 
				(std::find_if(_cellTypes.begin(), _cellTypes.end(), [&newName](auto& conf) {return conf.name == newName;}) == _cellTypes.end()))
					addTypeAndEditor(newName, newCellVerticesCount);
		}
		ImGui::NewLine();

		if (ext::CenteredButton("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}