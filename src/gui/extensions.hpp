#pragma once

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
	}
}