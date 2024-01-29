#include "extensions.hpp"

#include "imgui/imgui/imgui_internal.h"


namespace gui
{
	namespace ext
	{

        void CenteredText(const char *text, float textWidth)
        {
			auto windowWidth = ImGui::GetWindowSize().x;
			if (textWidth < 0)
			{
				textWidth = ImGui::CalcTextSize(text).x;
			}

			ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
			ImGui::Text("%s", text);
        }


        bool CenteredButton(const char *text, float textWidth)
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


        bool Spinner(const char *label, float radius, int thickness, const ImU32 &color)
        {
			auto windowWidth = ImGui::GetWindowSize().x;
			ImGui::SetCursorPosX((windowWidth - 2 * radius) * 0.5f);

            ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems)
				return false;
			
			ImGuiContext& g = *GImGui;
			const ImGuiStyle& style = g.Style;
			const ImGuiID id = window->GetID(label);
			
			ImVec2 pos = window->DC.CursorPos;
			ImVec2 size((radius )*2, (radius + style.FramePadding.y)*2);
			
			const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
			ImGui::ItemSize(bb, style.FramePadding.y);
			if (!ImGui::ItemAdd(bb, id))
				return false;
			
			// Render
			window->DrawList->PathClear();
			
			int num_segments = 30;
			
			const float a_min = IM_PI*2.0f * ((float)num_segments-10) / (float)num_segments;
			const float a_max = IM_PI*2.0f * ((float)num_segments-3) / (float)num_segments;

			const ImVec2 centre = ImVec2(pos.x+radius, pos.y+radius+style.FramePadding.y);
			
			for (int i = 0; i < num_segments; i++) {
				const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
				window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a+g.Time*8) * radius,
													centre.y + ImSin(a+g.Time*8) * radius));
			}

			window->DrawList->PathStroke(color, false, thickness);

			return true;
        }
    }
}