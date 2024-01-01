#include "../gui_controller.hpp"

#include "../themes/themes.hpp"

#include <imgui_file_dialog/ImGuiFileDialog.h>

namespace gui
{
	void GUIController::renderMenuBar()
	{
        static IoOperation selectedOperation = IoOperation::none;

        static auto selectOpenFileDialog = [&](IoOperation type)
            {
                selectedOperation = type;
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose file", ".json",
                    ".", 1, nullptr, ImGuiFileDialogFlags_Modal);
            };

        static auto selectSaveFileDialog = [&](IoOperation type)
            {
                selectedOperation = type;
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Save as", ".json",
                    ".", 1, nullptr, ImGuiFileDialogFlags_Modal);
            };

        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Load"))
            {
                if (ImGui::MenuItem("General configuration"))
                    selectOpenFileDialog(IoOperation::generalLoad);
                if (ImGui::MenuItem("Blood cells"))
                    selectOpenFileDialog(IoOperation::bloodCellLoad);
                if (ImGui::MenuItem("Vein"))
                    selectOpenFileDialog(IoOperation::veinLoad);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Save"))
            {
                if (ImGui::MenuItem("General configuration"))
                    selectSaveFileDialog(IoOperation::generalSave);
                if (ImGui::MenuItem("Blood cells"))
                    selectSaveFileDialog(IoOperation::bloodCellSave);
                if (ImGui::MenuItem("Vein"))
                    selectSaveFileDialog(IoOperation::veinSave);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Themes"))
            {
                static int selectedTheme = 0;
                if (ImGui::MenuItem("Default dark", nullptr, selectedTheme == 0))
                {
                    selectedTheme = 0;
                    styles::dark::setTheme();
                }
                if (ImGui::MenuItem("Default light", nullptr, selectedTheme == 1))
                {
                    selectedTheme = 1;
                    styles::light::setTheme();
                }
                if (ImGui::MenuItem("Cinder", nullptr, selectedTheme == 2))
                {
                    selectedTheme = 2;
                    styles::cinder::setTheme();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
 
        renderDialogWindow(selectedOperation);

	}
}