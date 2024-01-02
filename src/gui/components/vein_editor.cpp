#include "../gui_controller.hpp"

#include "../extensions.hpp"

namespace gui
{
	void GUIController::renderVeinEditor()
	{
		vein::Node::renderAll(*this, configManager.getData().veinRootNode.get());

		ImGui::NewLine();
		if (ext::CenteredButton("Done"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}