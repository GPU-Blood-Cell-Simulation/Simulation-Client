#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderGeneralEditor()
	{
		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}