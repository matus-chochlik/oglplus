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
	std::size_t _struct_size;

	friend class BlendFile;

	BlendFileBlockData(
		std::vector<char>&& block_data,
		Endian byte_order,
		std::size_t ptr_size,
		std::size_t struct_size
	): _block_data(block_data)
	 , _byte_order(byte_order)
	 , _ptr_size(ptr_size)
	 , _struct_size(struct_size)
	{ }
public:
	/// Returns the value of the specified field as a pointer
	BlendFilePointer GetPointer(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		const char* pos =
			_block_data.data() +
			block_element * _struct_size +
			field_element * _ptr_size +
			flat_field.Offset();
		if(_ptr_size == 4)
			return BlendFilePointer(ReorderToNative(
				_byte_order,
				*reinterpret_cast<const uint32_t*>(pos)
			));
		if(_ptr_size == 8)
			return BlendFilePointer(ReorderToNative(
				_byte_order,
				*reinterpret_cast<const uint64_t*>(pos)
			));
		assert(!"Invalid pointer size!");
		return BlendFilePointer(0);
	}

	/// Returns the value of the specified field as an integer
	template <typename Int>
	Int GetInt(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		assert(sizeof(Int) == flat_field.Field().BaseType().Size());
		const char* pos =
			_block_data.data() +
			block_element * _struct_size +
			field_element * sizeof(Int) +
			flat_field.Offset();
		return ReorderToNative(
			_byte_order,
			*reinterpret_cast<const Int*>(pos)
		);
	}

	/// Returns the value of the specified field as a floating point value
	template <typename Float>
	Float GetFloat(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		assert(sizeof(Float) == flat_field.Field().BaseType().Size());
		const char* pos =
			_block_data.data() +
			block_element * _struct_size +
			field_element * sizeof(Float) +
			flat_field.Offset();
		return *reinterpret_cast<const Float*>(pos);
	}

	/// Returns the value of the specified field as a string
	std::string GetString(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		const char* pos =
			_block_data.data() +
			block_element * _struct_size +
			field_element * flat_field.Size() +
			flat_field.Offset();
		return std::string(pos, flat_field.Size());
	}

	/// Visits the value of the specified field by a visitor
	/**
	 *  The Visitor must implement the following overloads of operator():
	 *  @code
	 *  struct Visitor
	 *  {
	 *      // regular values of atomic types - chars,strings,integers,floats
	 *      template <typename T>
	 *      void operator()(T value);
	 *
	 *      // pointers
	 *      void operator()(BlendFilePointer pointer);
	 *
	 *      // raw data of unknown type
	 *      void operator()(const char* data, size_t size);
	 *  };
	 *  @endcode
	 */
	template <typename Visitor>
	void ValueVisitRef(
		Visitor& visitor,
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		auto f = flat_field.Field();
		if(f.IsPointer())
		{
			visitor(GetPointer(
				flat_field,
				block_element,
				field_element
			));
		}
		else
		{
			auto bt = f.BaseType();
			if(bt.IsNative<char>())
			{
				if(f.IsArray())
					visitor(GetString(
						flat_field,
						block_element,
						field_element
					));
				else visitor(GetInt<char>(
					flat_field,
					block_element,
					field_element
				));
			}
			else if(bt.IsNative<uint8_t>())
				visitor(GetInt<uint8_t>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<int8_t>())
				visitor(GetInt<int8_t>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<uint16_t>())
				visitor(GetInt<uint16_t>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<int16_t>())
				visitor(GetInt<int16_t>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<uint32_t>())
				visitor(GetInt<uint32_t>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<int32_t>())
				visitor(GetInt<int32_t>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<uint64_t>())
				visitor(GetInt<uint64_t>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<int64_t>())
				visitor(GetInt<int64_t>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<float>())
				visitor(GetFloat<float>(
					flat_field,
					block_element,
					field_element
				));
			else if(bt.IsNative<double>())
				visitor(GetFloat<double>(
					flat_field,
					block_element,
					field_element
				));
			else visitor(
				_block_data.data() +
				block_element * _struct_size +
				flat_field.Offset(),
				flat_field.Size()
			);
		}
	}

	template <typename Visitor>
	void ValueVisit(
		Visitor visitor,
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		ValueVisitRef(
			visitor,
			flat_field,
			block_element,
			field_element
		);
	}
};


} // imports
} // oglplus

#endif // include guard
