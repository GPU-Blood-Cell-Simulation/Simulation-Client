#include "../gui_controller.hpp"
#include <string>

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