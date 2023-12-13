#include "blood_editor.hpp"
#include "../objects/bloodcellmodel.hpp"
#include "../gui/gui_controller.hpp"
#include <utility>
#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>.

void gui::bloodEditor::renderGUISprings(gui::GUIController& guiController)
{
	ImGui::Text(std::format("Vertices are numbered [0..{}]\n\tAdd new spring: ", modelData->vertices.size() - 1).c_str());
	int from = 0, to = 0;

	ImGui::PushItemWidth(50);
	ImGui::InputInt(" -> ", &from);
	ImGui::SameLine();
	ImGui::PushItemWidth(50);
	ImGui::InputInt(" ", &to);

	if (ImGui::Button("Add"))
	{
		modelData->springs.push_back(std::make_pair(from, to));
	}
	ImGui::NewLine();
	int counter = 1;
	for (auto spring : modelData->springs)
	{
		if (ImGui::Button(std::format("Spr. {} -> {}", spring.first, spring.second).c_str()))
		{
			selectedSpringIndex = counter - 1;
			ImGui::OpenPopup(springPopupName.c_str());
		}

		if (counter++ % 5)
			ImGui::SameLine();
		else
			ImGui::NewLine();
	}

	if (ImGui::BeginPopup(springPopupName.c_str()))
	{
		if (ImGui::Button("Delete"))
		{
			modelData->springs.erase(modelData->springs.begin() + selectedSpringIndex);
			selectedSpringIndex = -1;
		}
		ImGui::EndPopup();
	}

	ImGui::NewLine();
	if (ImGui::Button("Confirm"))
	{
		guiController.setMode(gui::Mode::bloodEdit);
		guiController.releaseEditor();
	}
}

void gui::bloodEditor::renderGUIVertices(gui::GUIController& guiController)
{
	ImGui::Text(std::format("Vertices are numbered [0..{}]", modelData->vertices.size() - 1).c_str());
	ImGui::NewLine();
	int counter = 0;
	for (glm::vec3 vertex : modelData->vertices)
	{
		std::string name = "Vertex ";
		name.append((const char*)counter++);
		float* vecPtr = glm::value_ptr(vertex);
		ImGui::InputFloat3(name.c_str(), vecPtr);
	}
	if (ImGui::Button("Confirm"))
	{
		guiController.setMode(gui::Mode::bloodEdit);
		guiController.releaseEditor();
	}
}

gui::bloodEditor::bloodEditor(bloodcell::bloodCellModel_data* dataReference)
{
	modelData = dataReference;
	modelQuantity = modelData->quantity;
}
