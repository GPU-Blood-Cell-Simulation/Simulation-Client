#include "extensions.hpp"

#include "imgui/imgui/imgui.h"

namespace gui
{
	namespace ext
	{
		bool CenteredButton(const char* text, float textWidth)
		{
			auto windowWidth = ImGui::GetWindowSize().x;
			if (textWidth < 0)
			{
				textWidth = ImGui::CalcTextSize(text).x;
			}

			textWidth += 40;
			ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
			return ImGui::Button(text, ImVec2(textWidth, 30.0f));
		}

		bool InputPositiveFloat(const char* label, float* v, float minValue)
		{
			bool ret = ImGui::InputFloat(label, v);
			if (*v < minValue)
				*v = minValue;

			return ret;
		}

		bool InputPositiveInt(const char* label, int* v, int minValue)
		{
			bool ret = ImGui::InputInt(label, v);
			if (*v < minValue)
				*v = minValue;

			return ret;
		}
	}
}