#pragma once

#include <imgui/imgui/imgui.h>

namespace gui
{
	namespace themes
	{
		namespace spectrum
		{
            inline constexpr unsigned int Color(unsigned int c)
            {
                // add alpha.
                // also swap red and blue channel for some reason.
                // todo: figure out why, and fix it.
                const short a = 0xFF;
                const short r = (c >> 16) & 0xFF;
                const short g = (c >> 8) & 0xFF;
                const short b = (c >> 0) & 0xFF;
                return(a << 24)
                    | (r << 0)
                    | (g << 8)
                    | (b << 16);
            }

            inline constexpr unsigned int colorAlpha(unsigned int alpha, unsigned int c)
            {
                return ((alpha & 0xFF) << 24) | (c & 0x00FFFFFF);
            }

			struct base
			{
                static constexpr unsigned int NONE = 0x00000000; // transparent
                static constexpr unsigned int WHITE = Color(0xFFFFFF);
                static constexpr unsigned int BLACK = Color(0x000000);
                static constexpr unsigned int GRAY200 = Color(0xF4F4F4);
                static constexpr unsigned int GRAY300 = Color(0xEAEAEA);
                static constexpr unsigned int GRAY400 = Color(0xD3D3D3);
                static constexpr unsigned int GRAY500 = Color(0xBCBCBC);
                static constexpr unsigned int GRAY600 = Color(0x959595);
                static constexpr unsigned int GRAY700 = Color(0x767676);
                static constexpr unsigned int GRAY800 = Color(0x505050);
                static constexpr unsigned int GRAY900 = Color(0x323232);
                static constexpr unsigned int BLUE400 = Color(0x378EF0);
                static constexpr unsigned int BLUE500 = Color(0x2680EB);
                static constexpr unsigned int BLUE600 = Color(0x1473E6);
                static constexpr unsigned int BLUE700 = Color(0x0D66D0);
                static constexpr unsigned int RED400 = Color(0xEC5B62);
                static constexpr unsigned int RED500 = Color(0xE34850);
                static constexpr unsigned int RED600 = Color(0xD7373F);
                static constexpr unsigned int RED700 = Color(0xC9252D);
                static constexpr unsigned int ORANGE400 = Color(0xF29423);
                static constexpr unsigned int ORANGE500 = Color(0xE68619);
                static constexpr unsigned int ORANGE600 = Color(0xDA7B11);
                static constexpr unsigned int ORANGE700 = Color(0xCB6F10);
                static constexpr unsigned int GREEN400 = Color(0x33AB84);
                static constexpr unsigned int GREEN500 = Color(0x2D9D78);
                static constexpr unsigned int GREEN600 = Color(0x268E6C);
                static constexpr unsigned int GREEN700 = Color(0x12805C);

                template<class Spectrum>
                static void setTheme()
                {
                    using namespace ImGui;

                    ImGuiStyle* style = &ImGui::GetStyle();
                    style->GrabRounding = 4.0f;

                    ImVec4* colors = style->Colors;
                    colors[ImGuiCol_Text] = ColorConvertU32ToFloat4(Spectrum::GRAY800); // text on hovered controls is gray900
                    colors[ImGuiCol_TextDisabled] = ColorConvertU32ToFloat4(Spectrum::GRAY500);
                    colors[ImGuiCol_WindowBg] = ColorConvertU32ToFloat4(Spectrum::GRAY100);
                    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
                    colors[ImGuiCol_PopupBg] = ColorConvertU32ToFloat4(Spectrum::GRAY50); // not sure about this. Note: applies to tooltips too.
                    colors[ImGuiCol_Border] = ColorConvertU32ToFloat4(Spectrum::GRAY300);
                    colors[ImGuiCol_BorderShadow] = ColorConvertU32ToFloat4(Spectrum::NONE); // We don't want shadows. Ever.
                    colors[ImGuiCol_FrameBg] = ColorConvertU32ToFloat4(Spectrum::GRAY75); // this isnt right, spectrum does not do this, but it's a good fallback
                    colors[ImGuiCol_FrameBgHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY50);
                    colors[ImGuiCol_FrameBgActive] = ColorConvertU32ToFloat4(Spectrum::GRAY200);
                    colors[ImGuiCol_TitleBg] = ColorConvertU32ToFloat4(Spectrum::GRAY300); // those titlebar values are totally made up, spectrum does not have this.
                    colors[ImGuiCol_TitleBgActive] = ColorConvertU32ToFloat4(Spectrum::GRAY200);
                    colors[ImGuiCol_TitleBgCollapsed] = ColorConvertU32ToFloat4(Spectrum::GRAY400);
                    colors[ImGuiCol_MenuBarBg] = ColorConvertU32ToFloat4(Spectrum::GRAY100);
                    colors[ImGuiCol_ScrollbarBg] = ColorConvertU32ToFloat4(Spectrum::GRAY100); // same as regular background
                    colors[ImGuiCol_ScrollbarGrab] = ColorConvertU32ToFloat4(Spectrum::GRAY400);
                    colors[ImGuiCol_ScrollbarGrabHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY600);
                    colors[ImGuiCol_ScrollbarGrabActive] = ColorConvertU32ToFloat4(Spectrum::GRAY700);
                    colors[ImGuiCol_CheckMark] = ColorConvertU32ToFloat4(Spectrum::BLUE500);
                    colors[ImGuiCol_SliderGrab] = ColorConvertU32ToFloat4(Spectrum::GRAY700);
                    colors[ImGuiCol_SliderGrabActive] = ColorConvertU32ToFloat4(Spectrum::GRAY800);
                    colors[ImGuiCol_Button] = ColorConvertU32ToFloat4(Spectrum::GRAY75); // match default button to Spectrum's 'Action Button'.
                    colors[ImGuiCol_ButtonHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY50);
                    colors[ImGuiCol_ButtonActive] = ColorConvertU32ToFloat4(Spectrum::GRAY200);
                    colors[ImGuiCol_Header] = ColorConvertU32ToFloat4(Spectrum::BLUE400);
                    colors[ImGuiCol_HeaderHovered] = ColorConvertU32ToFloat4(Spectrum::BLUE500);
                    colors[ImGuiCol_HeaderActive] = ColorConvertU32ToFloat4(Spectrum::BLUE600);
                    colors[ImGuiCol_Separator] = ColorConvertU32ToFloat4(Spectrum::GRAY400);
                    colors[ImGuiCol_SeparatorHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY600);
                    colors[ImGuiCol_SeparatorActive] = ColorConvertU32ToFloat4(Spectrum::GRAY700);
                    colors[ImGuiCol_ResizeGrip] = ColorConvertU32ToFloat4(Spectrum::GRAY400);
                    colors[ImGuiCol_ResizeGripHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY600);
                    colors[ImGuiCol_ResizeGripActive] = ColorConvertU32ToFloat4(Spectrum::GRAY700);
                    colors[ImGuiCol_PlotLines] = ColorConvertU32ToFloat4(Spectrum::BLUE400);
                    colors[ImGuiCol_PlotLinesHovered] = ColorConvertU32ToFloat4(Spectrum::BLUE600);
                    colors[ImGuiCol_PlotHistogram] = ColorConvertU32ToFloat4(Spectrum::BLUE400);
                    colors[ImGuiCol_PlotHistogramHovered] = ColorConvertU32ToFloat4(Spectrum::BLUE600);
                    colors[ImGuiCol_TextSelectedBg] = ColorConvertU32ToFloat4((Spectrum::BLUE400 & 0x00FFFFFF) | 0x33000000);
                    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
                    colors[ImGuiCol_NavHighlight] = ColorConvertU32ToFloat4((Spectrum::GRAY900 & 0x00FFFFFF) | 0x0A000000);
                    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
                    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
                    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
                }
			};   
		}
	}
}