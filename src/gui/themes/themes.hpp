#pragma once

#include <imgui/imgui/imgui.h>

namespace gui
{
	namespace styles
	{
		namespace dark
		{
			inline void setTheme()
			{
				ImGui::StyleColorsDark();
			}
		}

		namespace light
		{
			inline void setTheme()
			{
				ImGui::StyleColorsLight();
			}
		}

		namespace cinder
		{
			void setTheme();
		}
	}
}