#include "../../gui_controller.hpp"

#include "../../extensions.hpp"

namespace gui
{
	void GUIController::renderGraphicsEditor()
	{
		auto& data = configManager.getData().generalConfig.graphics;

		ImGui::Checkbox("Use lighting", &data.useLighting);

		ext::InputPositiveFloat("Camera movement speed", &data.cameraMovementSpeedCoefficient, 0.001f);
		ext::InputPositiveFloat("Camera rotation speed", &data.cameraMovementSpeedCoefficient, 0.001f);
	}
}