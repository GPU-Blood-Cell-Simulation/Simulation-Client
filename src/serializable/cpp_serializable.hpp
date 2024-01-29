#pragma once

namespace serializable
{
	/// <summary>
	/// An interface for generating C++ headers for the server from config
	/// </summary>
	class ICppSerializable
	{
	public:
		virtual ~ICppSerializable() {}

		/// <summary>
		/// Transform config data into a C++ header and save it to a .hpp file
		/// </summary>
		virtual void serializeToCpp() const = 0;
	};
}