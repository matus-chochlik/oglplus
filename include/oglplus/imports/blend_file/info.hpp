/**
 *  @file oglplus/imports/blend_file/info.hpp
 *  @brief Helper class providing basic information about a loaded .blend file
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMPORTS_BLEND_FILE_INFO_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_INFO_1107121519_HPP

namespace oglplus {
namespace imports {

/// Provides basic information about a .blend file
class BlendFileInfo
 : public BlendFileReaderClient
{
private:
	const bool _header_ok;
	bool _read_header(BlendFileReader& bfr)
	{
		return _expect(
			bfr,
			"BLENDER", 7,
			"Failed to read header"
		);
	}

	const std::size_t _pointer_size;
	std::size_t _read_pointer_size(BlendFileReader& bfr)
	{
		char c = _expect_one_of(
			bfr,
			"_-", 2,
			"Failed to read pointer size"
		);
		if(c == '_') return 4;
		if(c == '-') return 8;
		assert(!"Logic error");
		return 0;
	}

	const Endian _byte_order;
	Endian _read_endianness(BlendFileReader& bfr)
	{
		char c = _expect_one_of(
			bfr,
			"vV", 2,
			"Failed to read endianness"
		);
		if(c == 'v') return Endian::Little;
		if(c == 'V') return Endian::Big;
		assert(!"Logic error!");
		return Endian();
	}

	const int _version;
	int _read_version(BlendFileReader& bfr)
	{
		char buffer[4];
		_read(bfr, buffer, 3, "Failed to read version");
		return	(buffer[0]-'0')*100 +
			(buffer[1]-'0')*10 +
			(buffer[2]-'0')*1;
	}
public:
	BlendFileInfo(BlendFileReader& bfr)
	 : _header_ok(_read_header(bfr))
	 , _pointer_size(_read_pointer_size(bfr))
	 , _byte_order(_read_endianness(bfr))
	 , _version(_read_version(bfr))
	{ }

	/// The byte order used by the file
	Endian ByteOrder(void) const
	{
		return _byte_order;
	}

	/// The pointer size in bytes used by the file
	std::size_t PointerSize(void) const
	{
		return _pointer_size;
	}

	/// The major version number
	int VersionMajor(void) const
	{
		return _version / 100;
	}

	/// The minor version number
	int VersionMinor(void) const
	{
		return _version % 100;
	}
};

} // imports
} // oglplus

#endif // include guard
