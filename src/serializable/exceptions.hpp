#pragma once

#include <exception>

namespace serializable
{
	class FileOpenException : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Error while opening file";
		}
	};

	class FileWriteException : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Error while writing to file";
		}
	};

	class FileReadException : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Error while reading file";
		}
	};
}