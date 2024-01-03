#include "themes.hpp"

namespace gui
{
	namespace themes
	{
		namespace spectrum
		{
			void dark::setTheme()
			{
				base::setTheme<dark>();
			}

			void light::setTheme()
			{
				base::setTheme<light>();
			}
		}
	}
}