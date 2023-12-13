#include "blood_editor.hpp"
#include "../objects/bloodcellmodel.hpp"
#include "../gui/gui_controller.hpp"
#include <utility>
#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>.


int gui::bloodEditor::modelsCount = 0;

void gui::bloodEditor::renderGUISprings(gui::GUIController& guiController)
{
	modelNumber = modelsCount++;
	
	ImGui::Text(std::format("Vertices are numbered [0..{}]\n\tAdd new spring: ", modelData->vertices.size() - 1).c_str());

	ImGui::PushItemWidth(100);
	ImGui::InputInt(" -> ", &from);
	ImGui::SameLine();
	ImGui::PushItemWidth(100);
	ImGui::InputInt(" ", &to);
	if (from < 0) from = 0;
	if (to < 0) to = 0;
	if (from >= modelData->vertices.size()) from = modelData->vertices.size() - 1;
	if (to >= modelData->vertices.size()) to = modelData->vertices.size() - 1;

	if (ImGui::Button("Add"))
	{
		auto pair = std::make_pair(from, to);
		auto revPair = std::make_pair(to, from);

		if(std::find(modelData->springs.begin(), modelData->springs.end(), pair) == modelData->springs.end() &&
			std::find(modelData->springs.begin(), modelData->springs.end(), revPair) == modelData->springs.end())
			modelData->springs.push_back(pair);
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
	if (ImGui::Button("Center vertices"))
	{
		glm::vec3 center{ 0,0,0 };
		for (glm::vec3 vertex : modelData->vertices)
		{
			center += vertex;
		}
		center /= modelData->vertices.size();
		for (glm::vec3& vertex : modelData->vertices)
		{
			vertex -= center;
		}
	}
	ImGui::PushItemWidth(100);
	ImGui::InputFloat(" scale by factor ", &vertexScaleFactor, 0.05f, 0.1f);
	ImGui::SameLine();
	if (ImGui::Button("Go"))
	{
		for (glm::vec3& vertex : modelData->vertices)
		{
			vertex /= vertexScaleFactor;
		}
		vertexScaleFactor = 1.0f;
	}
	ImGui::NewLine();
	ImGui::PushItemWidth(200);
	for (glm::vec3& vertex : modelData->vertices)
	{
		std::string name = "Vertex " + std::to_string(counter);
		ImGui::InputFloat3(name.c_str(), glm::value_ptr(vertex));
		counter++;
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
