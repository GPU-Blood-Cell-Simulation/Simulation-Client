#pragma once

namespace serializable
{
	class ICppSerializable
	{
	public:
		virtual ~ICppSerializable() {}

		virtual void serializeToCpp() const = 0;
	};
}