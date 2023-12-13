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
	public:

		int modelQuantity;
		bloodEditor(bloodcell::bloodCellModel_data* dataReference);

		std::string GetModelName() { return modelData->name; }
		void renderGUISprings(gui::GUIController& guiController);
		void renderGUIVertices(gui::GUIController& guiController);

	};
}