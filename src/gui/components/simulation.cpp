#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderSimulation()
	{
		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}