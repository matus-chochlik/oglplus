/**
 *  @file oglplus/imports/blend_file/reader.hpp
 *  @brief Helper class for .blend file import basic input operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMPORTS_BLEND_FILE_READER_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_READER_1107121519_HPP

#include <cassert>
#include <stdexcept>
#include <istream>
#include <sstream>
#include <cstddef>
#include <string>
#include <vector>

namespace oglplus {
namespace imports {

// Internal helper class used for .blend file read operations
// Wraps around an istream and implements operations used by
// the loader
// NOTE: implementation detail, do not use
class BlendFileReader
 : public BlendFileUtils
{
private:
	std::istream& _input;

	// peek at the next byte and return true if we are at EOF
	bool _eof(void)
	{
		_input.peek();
		return _input.eof();
	}

	// composes error message and throws an exception
	template <typename String>
	void _error(String&& message)
	{
		std::stringstream ss;
		ss << "Blend file read error at byte ";
		ss << _input.tellg();
		ss << ": ";
		ss << message;
		throw std::runtime_error(ss.str());
	}

	// reads a single char throws on error
	char _read_char(const char* error_message)
	{
		char c = '\0';
		if(_input.get(c).fail()) _error(error_message);
		return c;
	}

	// reads the specified number of bytes throws on error
	void _raw_read(
		char* buffer,
		std::size_t size,
		const char* error_message
	)
	{
		assert(size != 0);
		if(_input.read(buffer, size).fail())
			_error(error_message);
	}

	// reads a string of the specified lenght,
	// terminates by zero
	// throws on error
	void _read(
		char* buffer,
		std::size_t max,
		const char* error_message
	)
	{
		assert(max != 0);
		if(_input.read(buffer, max).fail())
			_error(error_message);
		else buffer[max] = '\0';
	}

	// reads until a delimiter is found,
	// throws on error
	void _read_until(
		std::streambuf& sb,
		char delimiter,
		const char* error_message
	)
	{
		if(_input.get(sb, delimiter).fail())
			_error(error_message);
		_input.ignore();
	}

	// skips the specified number of bytes
	// throws on error
	void _skip(
		std::size_t size,
		const char* error_message
	)
	{
		if(_input.ignore(size).fail())
			_error(error_message);
	}

	// aligns the input to the specified size
	// throws on error
	void _align(
		const std::size_t size,
		const char* error_message
	)
	{
		std::streampos input_pos = _input.tellg();
		const std::size_t mod = _align_diff(input_pos, size);
		if(mod != 0)
		{
			_skip(size - mod, error_message);
			assert(_input.tellg() % size == 0);
		}
	}

	friend class BlendFileReaderClient;
public:
	BlendFileReader(std::istream& input)
	 : BlendFileUtils(4)
	 , _input(input)
	{ }
};

} // imports
} // oglplus

#endif // include guard
