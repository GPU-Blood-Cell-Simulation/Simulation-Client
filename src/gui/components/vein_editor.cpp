#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderVeinEditor()
	{
		vein::Node::renderAll(*this, configManager.getData().veinRootNode.get());

		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}