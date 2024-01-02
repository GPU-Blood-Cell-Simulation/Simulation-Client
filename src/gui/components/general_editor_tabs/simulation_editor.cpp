#include "../../gui_controller.hpp"

#include "../../extensions.hpp"

namespace gui
{
	void GUIController::renderSimulationEditor()
	{
		auto& data = configManager.getData().generalConfig.simulation;

		ext::InputPositiveFloat("Delta time (dt)", &data.dt, 0.01f);
		ext::InputPositiveInt("Grid cell width", &data.cellWidth);
		ext::InputPositiveInt("Grid cell height)", &data.cellHeight);
		ext::InputPositiveInt("Grid cell depth", &data.cellDepth);
	}
}