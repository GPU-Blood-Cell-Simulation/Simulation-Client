#pragma once

#include "../objects/bloodcellmodel.hpp"

namespace gui
{
	class GUIController;

	class bloodEditor
	{
		bloodcell::bloodCellModel_data* modelData;
		std::string springPopupName = "springEditorPopup";
		int selectedSpringIndex = -1;
		float vertexScaleFactor = 1.0f;
		int from = 0, to = 0;
		int modelNumber;
		static int modelsCount;

	public:

		int modelQuantity;
		bloodEditor(bloodcell::bloodCellModel_data* dataReference);

		std::string GetModelName() { return "bloodCell_" + std::to_string(modelNumber); }
		void renderGUISprings(gui::GUIController& guiController);
		void renderGUIVertices(gui::GUIController& guiController);

	};
}