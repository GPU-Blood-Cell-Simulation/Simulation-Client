#pragma once

#include "spectrum_light.hpp"
#include "spectrum_dark.hpp"

#include <imgui/imgui/imgui.h>

namespace gui
{
	namespace themes
	{
		namespace imguiDark
		{
			inline void setTheme()
			{
				ImGui::StyleColorsDark();
			}
		}

		namespace imguiLight
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

		namespace enemymouse
		{
			void setTheme();
		}
	}
}