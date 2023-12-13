#include "../gui_controller.hpp"
#include <string>
#include <format>

namespace gui
{
	void GUIController::renderBloodCellSpringsDetails()
	{
		selectedEditor->renderGUISprings(*this);
	}

	void GUIController::renderBloodCellVerticesDetails()
	{
		selectedEditor->renderGUIVertices(*this);
	}
}