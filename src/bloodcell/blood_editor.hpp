#pragma once

#include "../serializable/blood_cell_json_conversion/blood_cells_definition.hpp"

namespace gui
{
	class GUIController;

	class BloodEditor
	{
		serializable::BloodCellType& modelData;
		int selectedSpringIndex = -1;
		float vertexScaleFactor = 1.0f;
		int from = 0, to = 0;

	public:
		int modelQuantity;
		BloodEditor(serializable::BloodCellType& data);

		void updateQuantity() { modelData.quantity = modelQuantity; }
		std::string GetModelName() const { return modelData.name; }
		
		void renderGUISprings(gui::GUIController& guiController);
		void renderGUIVertices(gui::GUIController& guiController);
	};
}