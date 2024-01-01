#include "../gui_controller.hpp"

#include <imgui/imgui/imgui.h>
#include <imgui_file_dialog/ImGuiFileDialog.h>
#include <iostream>

namespace gui
{

	void GUIController::renderDialogWindow(IoOperation& operation)
	{
		// display
		if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
		{
			// action if OK
			if (ImGuiFileDialog::Instance()->IsOk())
			{
				std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
				try
				{
					switch (operation)
					{
					case IoOperation::generalLoad:
						configManager.loadGeneralConfig(filePath);
						break;
					case IoOperation::bloodCellLoad:
						configManager.loadBloodCellConfig(filePath);
						loadEditors();
						break;
					case IoOperation::veinLoad:
						configManager.loadVeinConfig(filePath);
						break;
					case IoOperation::generalSave:
						configManager.saveGeneralConfig(filePath);
						break;
					case IoOperation::bloodCellSave:
						configManager.saveBloodCellConfig(filePath);
						break;
					case IoOperation::veinSave:
						configManager.saveVeinConfig(filePath);
						break;
					}
				}
				catch (...)
				{	
					setError("An unknown error occured");
				}

				operation = IoOperation::none;
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}
	}
}