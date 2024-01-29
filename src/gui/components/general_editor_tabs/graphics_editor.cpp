#include "../../gui_controller.hpp"

#include "../../extensions.hpp"

#include <imgui_stdlib/imgui_stdlib.h>

namespace gui
{
	void GUIController::renderGraphicsEditor()
	{
		auto& data = configManager.getData().generalConfig.graphics;

		ImGui::Checkbox("Use lighting", &data.useLighting);
		ImGui::NewLine();

		ext::InputPositiveFloat("Camera movement speed", &data.cameraMovementSpeedCoefficient, 0.001f);
		ext::InputPositiveFloat("Camera rotation speed", &data.cameraRotationSpeed, 0.001f);
		ImGui::NewLine();

		ext::InputPositiveInt("Video width", &data.videoWidth);
		ext::InputPositiveInt("Video height", &data.videoHeight);
		ImGui::NewLine();

		ImGui::Checkbox("Save video to file", &data.saveVideoToFile);
		ImGui::BeginDisabled(!data.saveVideoToFile);
		ImGui::Text("\tVideo file path:");
		ImGui::SameLine();
		ImGui::InputText("##videoFileName", data.videoFileName, IM_ARRAYSIZE(data.videoFileName));
		ImGui::EndDisabled();
	}
}