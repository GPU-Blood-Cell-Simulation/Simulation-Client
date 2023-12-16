#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderSimulation()
	{
		ImGui::Text("Simulation in progress");
		streamReceiver.handleEvents();
		streamReceiver.renderFrame();

		if (ImGui::Button("Done") || streamReceiver.streamEnded())
		{
			streamReceiver.pause();

			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}