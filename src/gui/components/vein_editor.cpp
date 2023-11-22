#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderVeinEditor()
	{
		vein::Node::renderAll(*this, rootNode);

		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}