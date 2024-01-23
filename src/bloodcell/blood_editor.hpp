#pragma once

#include "../serializable/blood_cell_json_conversion/blood_cells_definition.hpp"
#include "../serializable/config_data.hpp"

namespace gui
{
	class GUIController;

	/// <summary>
	/// Main editor for blood cell types
	/// </summary>
	class BloodEditor
	{
		float diameter;
	public:
		int editorIndex;
		
		BloodEditor(int editorIndex);
		void recalculateBloodTypeDiameter(serializable::BloodCellType& type);
		void renderGUISprings(gui::GUIController& guiController, serializable::ConfigData& config);
		void renderGUIVertices(gui::GUIController& guiController, serializable::ConfigData& config);
	};
}