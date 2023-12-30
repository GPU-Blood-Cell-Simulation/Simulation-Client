#include "blood_editor.hpp"

#include "../gui/gui_controller.hpp"
#include "../serializable/blood_cell_json_conversion/spring.hpp"

#include <cstdio>
#include <utility>
#include <glm/gtc/type_ptr.hpp>

namespace gui
{
	void BloodEditor::renderGUISprings(gui::GUIController &guiController)
	{
		ImGui::Text("Vertices are numbered [0..%lu]\n\tAdd new spring: ", modelData.vertices.size() - 1);

		ImGui::PushItemWidth(100);
		ImGui::InputInt(" -> ", &from);
		ImGui::SameLine();
		ImGui::PushItemWidth(100);
		ImGui::InputInt(" ", &to);
		if (from < 0)
			from = 0;
		if (to < 0)
			to = 0;
		if (from >= modelData.vertices.size())
			from = modelData.vertices.size() - 1;
		if (to >= modelData.vertices.size())
			to = modelData.vertices.size() - 1;

		if (ImGui::Button("Add"))
		{
			serializable::Spring pair {from, to};
			serializable::Spring revPair {to, from};

			if (std::find(modelData.springs.begin(), modelData.springs.end(), pair) == modelData.springs.end() &&
				std::find(modelData.springs.begin(), modelData.springs.end(), revPair) == modelData.springs.end())
				modelData.springs.push_back(pair);
		}
		ImGui::NewLine();
		int counter = 1;
		for (auto&& spring : modelData.springs)
		{
			std::string buttonText = "Spr." + std::to_string(spring.from) + " -> " +  std::to_string(spring.to);
			if (ImGui::Button(buttonText.c_str()))
			{
				selectedSpringIndex = counter - 1;
				ImGui::OpenPopup("springEditorPopup");
			}

			if (counter++ % 5)
				ImGui::SameLine();
			else
				ImGui::NewLine();
		}

		if (ImGui::BeginPopup("springEditorPopup"))
		{
			if (ImGui::Button("Delete"))
			{
				modelData.springs.erase(modelData.springs.begin() + selectedSpringIndex);
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

	void BloodEditor::renderGUIVertices(gui::GUIController &guiController)
	{
		ImGui::Text("Vertices are numbered [0..%lu]\n ", modelData.vertices.size() - 1);

		ImGui::NewLine();
		int counter = 0;
		if (ImGui::Button("Center vertices"))
		{
			glm::vec3 center{0, 0, 0};
			for (glm::vec3 vertex : modelData.vertices)
			{
				center += vertex;
			}
			center /= modelData.vertices.size();
			for (glm::vec3 &vertex : modelData.vertices)
			{
				vertex -= center;
			}
		}
		ImGui::PushItemWidth(100);
		ImGui::InputFloat(" scale by factor ", &vertexScaleFactor, 0.05f, 0.1f);
		ImGui::SameLine();
		if (ImGui::Button("Go"))
		{
			for (glm::vec3 &vertex : modelData.vertices)
			{
				vertex /= vertexScaleFactor;
			}
			vertexScaleFactor = 1.0f;
		}
		ImGui::NewLine();
		ImGui::PushItemWidth(200);
		for (glm::vec3 &vertex : modelData.vertices)
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

	BloodEditor::BloodEditor(serializable::BloodCellType &data) : modelData(data), modelQuantity(data.quantity) {}
}