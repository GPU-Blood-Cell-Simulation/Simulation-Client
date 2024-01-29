#pragma once

#include "imgui/imgui/imgui.h"


namespace gui
{
	/// <summary>
	/// Contains ImGui extensions
	/// </summary>
	namespace ext
	{
		/// <summary>
		/// A wrapper creating an ImGui::Text that is centered horizontally on the screen
		/// </summary>
		/// <param name="text">Text to display</param>
		/// <param name="textWidth">The width of the button's text. If negative, it will be calculated automatically</param>
		void CenteredText(const char *text, float textWidth= -1.0f);

		/// <summary>
		/// A wrapper creating an ImGui::Button that is centered horizontally on the screen
		/// </summary>
		/// <param name="text">Text to display</param>
		/// <param name="textWidth">The width of the button's text. If negative, it will be calculated automatically</param>
		/// <returns>The ImGui::Button result</returns>
		bool CenteredButton(const char* text, float textWidth = -1.0f);

		/// <summary>
		/// A wrapper for ImGui::InputFloat that accepts only values above a threshold
		/// </summary>
		/// <param name="label">Label to display</param>
		/// <param name="v">The value pointer</param>
		/// <param name="minValue">The minium value to clamp to</param>
		/// <returns>The ImGui::InputFloat result</returns>
		bool InputPositiveFloat(const char* label, float* v, float minValue = 0);

		/// <summary>
		/// A wrapper for ImGui::InputInt that accepts only values above a threshold
		/// </summary>
		/// <param name="label">Label to display</param>
		/// <param name="v">The value pointer</param>
		/// <param name="minValue">The minium value to clamp to</param>
		/// <returns>The ImGui::InputInt result</returns>
		bool InputPositiveInt(const char* label, int* v, int minValue = 1);

		/// <summary>
		/// Spinning progress indicator. Inspired by https://github.com/ocornut/imgui/issues/1901
		/// </summary>
		/// <param name="id">ImGUI widget ID</param>
		/// <param name="radius">Radius of a spinner</param>
		/// <param name="thickness">Thickness of a spinning line</param>
		/// <param name="color">Color of a spinning line</param>
		bool Spinner(const char* id, float radius, int thickness, const ImU32& color);
	}
}