#pragma once

namespace gui
{
	namespace ext
	{
		bool CenteredButton(const char* text, float textWidth = -1);

		bool InputPositiveFloat(const char* label, float* v, float minValue = 0);

		bool InputPositiveInt(const char* label, int* v, int minValue = 1);
	}
}