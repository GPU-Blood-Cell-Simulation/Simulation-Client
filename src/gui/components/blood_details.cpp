#include "../gui_controller.hpp"
#include "../../serializable/config_data.hpp"
#include <string>

namespace gui
{
	void GUIController::renderBloodCellSpringsDetails(serializable::ConfigData& config)
	{
		selectedEditor->renderGUISprings(*this, config);
	}

	void GUIController::renderBloodCellVerticesDetails(serializable::ConfigData& config)
	{
		selectedEditor->renderGUIVertices(*this, config);
	}

	void GUIController::renderBloodCellColorDetails(serializable::ConfigData& config)
	{
		selectedEditor->renderGUIColors(*this, config);
	}
}