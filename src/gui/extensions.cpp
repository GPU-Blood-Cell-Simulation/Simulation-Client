#include "extensions.hpp"

#include "imgui/imgui/imgui.h"

namespace gui
{
	namespace ext
	{
		static void setCursorToCenterText(const char *text, float textWidth, float offset)
		{
			float windowWidth = ImGui::GetWindowSize().x;
			if (textWidth < 0)
			{
				textWidth = ImGui::CalcTextSize(text).x;
			}

			textWidth += offset;
			ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		}

        void CenteredText(const char *text, float textWidth)
        {
			setCursorToCenterText(text, textWidth, 40.0f);
			ImGui::Text("%s", text);
        }

        bool CenteredButton(const char *text, float textWidth)
        {
			setCursorToCenterText(text, textWidth, 40.0f);
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