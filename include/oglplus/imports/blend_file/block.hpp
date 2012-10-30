/**
 *  @file oglplus/imports/blend_file/block.hpp
 *  @brief Helper class providing information about a .blend file block
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMPORTS_BLEND_FILE_BLOCK_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_BLOCK_1107121519_HPP

#include <oglplus/imports/blend_file/range.hpp>

namespace oglplus {
namespace imports {

class BlendFile;

/// Type wrapping a pointer inside of a .blend file
class BlendFilePointer
{
public:
	typedef uint64_t ValueType;

	operator bool (void) const
	{
		return _value != 0;
	}

	bool operator !(void) const
	{
		return _value == 0;
	}

	friend bool operator == (BlendFilePointer a, BlendFilePointer b)
	{
		return a._value == b._value;
	}

	friend bool operator != (BlendFilePointer a, BlendFilePointer b)
	{
		return a._value != b._value;
	}

	ValueType Value(void) const
	{
		return _value;
	}
private:
	uint64_t _value;

	friend class BlendFileBlock;
	friend class BlendFileBlockData;

	BlendFilePointer(ValueType value)
	 : _value(value)
	{ }
};

/// Class for access to a single .blend file block
class BlendFileBlock
 : public BlendFileReaderClient
{
private:
	std::array<char, 4> _code;

	uint32_t _size;
	uint32_t _read_size(BlendFileReader& bfr, const BlendFileInfo& bfi)
	{
		return _read_int<uint32_t>(
			bfr,
			bfi.ByteOrder(),
			"Failed to read file block size"
		);
	}

	BlendFilePointer _old_ptr;
	uint64_t _read_old_ptr(BlendFileReader& bfr, const BlendFileInfo& bfi)
	{
		if(bfi.PointerSize() == 4)
			return _read_int<uint32_t>(
				bfr,
				bfi.ByteOrder(),
				"Failed to read file block old pointer"
			);
		else if(bfi.PointerSize() == 8)
			return _read_int<uint64_t>(
				bfr,
				bfi.ByteOrder(),
				"Failed to read file block old pointer"
			);
		else assert(!"Logic error!");
		return 0;
	}

	uint32_t _sdna_index;
	uint32_t _read_index(BlendFileReader& bfr, const BlendFileInfo& bfi)
	{
		return _read_int<uint32_t>(
			bfr,
			bfi.ByteOrder(),
			"Failed to read file block SDNA index"
		);
	}

	uint32_t _count;
	uint32_t _read_count(BlendFileReader& bfr, const BlendFileInfo& bfi)
	{
		return _read_int<uint32_t>(
			bfr,
			bfi.ByteOrder(),
			"Failed to read file block object count"
		);
	}

	std::streampos _data_pos;

	friend class BlendFile;
public:
	BlendFileBlock(
		BlendFileReader& bfr,
		const BlendFileInfo& bfi,
		std::array<char, 4>&& code,
		bool do_skip
	): _code(std::move(code))
	 , _size(_read_size(bfr, bfi))
	 , _old_ptr(_read_old_ptr(bfr, bfi))
	 , _sdna_index(_read_index(bfr, bfi))
	 , _count(_read_count(bfr, bfi))
	 , _data_pos(_position(bfr))
	{
		if(do_skip) _skip(bfr, _size, "Error skipping file block data");
	}

	/// Returns the code of the block
	std::string Code(void) const
	{
		return std::string(_code.data(), _code.size());
	}

	/// Returns the size of the block in bytes
	uint32_t Size(void) const
	{
		return _size;
	}

	/// Returns the number of elements in the block
	uint32_t ElementCount(void) const
	{
		return _count;
	}

	/// Returns the 'old' pointer value of the block as loaded from input
	BlendFilePointer Pointer(void) const
	{
		return _old_ptr;
	}

	/// Returns the the position of the block data in the input file
	std::streampos DataPosition(void) const
	{
		return _data_pos;
	}
};

/// Class allowing the traversal of a range of blend file blocks
class BlendFileBlockRange
 : public BlendFileRangeTpl<BlendFileBlockRange, const BlendFileBlock&>
{
private:
	const std::vector<BlendFileBlock>& _blocks;

	typedef BlendFileRangeTpl<BlendFileBlockRange, const BlendFileBlock&> Base;

	BlendFileBlockRange(const std::vector<BlendFileBlock>& blocks)
	 : Base(blocks.size())
	 , _blocks(blocks)
	{ }

	friend class BlendFile;
public:
	const BlendFileBlock& Get(std::size_t index) const
	{
		return _blocks[index];
	}
};

} // imports
} // oglplus

#endif // include guard
