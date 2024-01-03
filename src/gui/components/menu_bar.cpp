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
                static int selectedTheme = 2;
                if (ImGui::MenuItem("ImGui dark", nullptr, selectedTheme == 0))
                {
                    selectedTheme = 0;
                    themes::imguiDark::setTheme();
                }
                if (ImGui::MenuItem("ImGu light", nullptr, selectedTheme == 1))
                {
                    selectedTheme = 1;
                    themes::imguiLight::setTheme();
                }
                if (ImGui::MenuItem("Cinder", nullptr, selectedTheme == 2))
                {
                    selectedTheme = 2;
                    themes::cinder::setTheme();
                }
                if (ImGui::MenuItem("Spectrum dark", nullptr, selectedTheme == 3))
                {
                    selectedTheme = 3;
                    themes::spectrum::dark::setTheme();
                }
                if (ImGui::MenuItem("Spectrum light", nullptr, selectedTheme == 4))
                {
                    selectedTheme = 4;
                    themes::spectrum::light::setTheme();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
 
        renderDialogWindow(selectedOperation);

	}
}