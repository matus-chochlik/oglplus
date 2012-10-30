/**
 *  @file oglplus/imports/blend_file/block_data.hpp
 *  @brief Helper class providing access to .blend file block data
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMPORTS_BLEND_FILE_BLOCK_DATA_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_BLOCK_DATA_1107121519_HPP

namespace oglplus {
namespace imports {

class BlendFileBlockData
{
private:
	std::vector<char> _block_data;
	Endian _byte_order;
	std::size_t _ptr_size;

	friend class BlendFile;

	BlendFileBlockData(
		std::vector<char>&& block_data,
		Endian byte_order,
		std::size_t ptr_size
	): _block_data(block_data)
	 , _byte_order(byte_order)
	 , _ptr_size(ptr_size)
	{ }
public:
	template <typename Int>
	Int GetInt(const BlendFileFlattenedStructField& field) const
	{
		assert(sizeof(Int) == field.Field().BaseType().Size());
		const char* pos = _block_data.data() + field.Offset();
		return ReorderToNative(
			_byte_order,
			*reinterpret_cast<const Int*>(pos)
		);
	}

	uint64_t GetPointer(const BlendFileFlattenedStructField& field) const
	{
		const char* pos = _block_data.data() + field.Offset();
		if(_ptr_size == 4)
			return ReorderToNative(
				_byte_order,
				*reinterpret_cast<const uint32_t*>(pos)
			);
		if(_ptr_size == 8)
			return ReorderToNative(
				_byte_order,
				*reinterpret_cast<const uint64_t*>(pos)
			);
		assert(!"Invalid pointer size!");
		return 0;
	}

	template <typename Float>
	Float GetFloat(const BlendFileFlattenedStructField& field) const
	{
		assert(sizeof(Float) == field.Field().BaseType().Size());
		const char* pos = _block_data.data() + field.Offset();
		return *reinterpret_cast<const Float*>(pos);
	}

	std::string GetString(const BlendFileFlattenedStructField& field) const
	{
		const char* pos = _block_data.data() + field.Offset();
		return std::string(pos, field.Size());
	}
};


} // imports
} // oglplus

#endif // include guard
