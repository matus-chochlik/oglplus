/**
 *  @file oglplus/imports/blend_file/block_data.hpp
 *  @brief Helper class providing access to .blend file block data
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMPORTS_BLEND_FILE_BLOCK_DATA_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_BLOCK_DATA_1107121519_HPP

namespace oglplus {
namespace imports {


/// Class wrapping the data of a file block
class BlendFileBlockData
{
private:
	// TODO: some kind of caching in BlendFile or BlendFileBlock
	// and only a reference to the buffer here
	// to make this class more lightweight
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

	template <unsigned Level>
	BlendFilePointerTpl<Level> _do_make_pointer(
		const char* pos,
		std::size_t type_index
	) const
	{
		if(_ptr_size == 4)
			return BlendFilePointerTpl<Level>(aux::ReorderToNative(
				_byte_order,
				*reinterpret_cast<const uint32_t*>(pos)
			), type_index);
		if(_ptr_size == 8)
			return BlendFilePointerTpl<Level>(aux::ReorderToNative(
				_byte_order,
				*reinterpret_cast<const uint64_t*>(pos)
			), type_index);
		assert(!"Invalid pointer size!");
		return BlendFilePointerTpl<Level>();
	}

	template <unsigned Level>
	BlendFilePointerTpl<Level> _do_get_pointer(
		std::size_t type_index,
		std::size_t field_offset,
		std::size_t block_element,
		std::size_t field_element,
		std::size_t data_offset
	) const
	{
		const char* pos =
			_block_data.data() +
			data_offset +
			block_element * _struct_size +
			field_element * _ptr_size +
			field_offset;
		return _do_make_pointer<Level>(pos, type_index);
	}

	template <unsigned Level>
	BlendFilePointerTpl<Level> _get_pointer(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element,
		std::size_t field_element,
		std::size_t data_offset
	) const
	{
		return _do_get_pointer<Level>(
			flat_field._sdna->_structs[
				flat_field._flat_fields->_field_structs[
					flat_field._flat_field_index
				]
			]._field_type_indices[
				flat_field._flat_fields->_field_indices[
					flat_field._flat_field_index
				]
			],
			flat_field.Offset(),
			block_element,
			field_element,
			data_offset
		);
	}
public:
	BlendFileBlockData(BlendFileBlockData&& tmp)
	 : _block_data(tmp._block_data)
	 , _byte_order(tmp._byte_order)
	 , _ptr_size(tmp._ptr_size)
	 , _struct_size(tmp._struct_size)
	{ }

	/// Returns the raw data of the block
	const char* RawData(void) const
	{
		return _block_data.data();
	}

	/// returns the size (in bytes) of the raw data
	std::size_t DataSize(void) const
	{
		return _block_data.size();
	}

	/// Returns a pointer at the specified index
	BlendFilePointer AsPointerTo(
		const BlendFileType& type,
		std::size_t index = 0,
		std::size_t data_offset = 0
	) const
	{
		const char* pos =
			_block_data.data() +
			data_offset +
			index * _ptr_size;
		return _do_make_pointer<1>(pos, type._type_index);
	}

	/// Returns the value of the specified field as a pointer
	BlendFilePointer GetPointer(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0,
		std::size_t data_offset = 0
	) const
	{
		return _get_pointer<1>(
			flat_field,
			block_element,
			field_element,
			data_offset
		);
	}

	/// Returns the value of the specified field as a pointer to pointer
	BlendFilePointerToPointer GetPointerToPointer(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0,
		std::size_t data_offset = 0
	) const
	{
		return _get_pointer<2>(
			flat_field,
			block_element,
			field_element,
			data_offset
		);
	}

	/// Returns the value at the specified offset as an integer
	template <typename Int>
	Int GetInt(
		std::size_t field_offset,
		std::size_t block_element,
		std::size_t field_element,
		std::size_t data_offset
	) const
	{
		const char* pos =
			_block_data.data() +
			data_offset +
			block_element * _struct_size +
			field_element * sizeof(Int) +
			field_offset;
		return aux::ReorderToNative(
			_byte_order,
			*reinterpret_cast<const Int*>(pos)
		);
	}

	/// Returns the value of the specified field as an integer
	template <typename Int>
	Int GetInt(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0,
		std::size_t data_offset = 0
	) const
	{
		assert(sizeof(Int) == flat_field.Field().BaseType().Size());
		return GetInt<Int>(
			flat_field.Offset(),
			block_element,
			field_element,
			data_offset
		);
	}

	/// Returns the value at the specified offset as a floating point value
	template <typename Float>
	Float GetFloat(
		std::size_t field_offset,
		std::size_t block_element,
		std::size_t field_element,
		std::size_t data_offset
	) const
	{
		const char* pos =
			_block_data.data() +
			data_offset +
			block_element * _struct_size +
			field_element * sizeof(Float) +
			field_offset;
		return *reinterpret_cast<const Float*>(pos);
	}

	/// Returns the value of the specified field as a floating point value
	template <typename Float>
	Float GetFloat(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0,
		std::size_t data_offset = 0
	) const
	{
		assert(sizeof(Float) == flat_field.Field().BaseType().Size());
		return GetFloat<Float>(
			flat_field.Offset(),
			block_element,
			field_element,
			data_offset
		);
	}

	/// Returns the value at the specified offset as a string
	std::string GetString(
		std::size_t field_size,
		std::size_t field_offset,
		std::size_t block_element,
		std::size_t field_element,
		std::size_t data_offset
	) const
	{
		const char* pos =
			_block_data.data() +
			data_offset +
			block_element * _struct_size +
			field_element * field_size +
			field_offset;
		return std::string(pos, field_size);
	}

	/// Returns the value of the specified field as a string
	std::string GetString(
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0,
		std::size_t data_offset = 0
	) const
	{
		return GetString(
			flat_field.Size(),
			flat_field.Offset(),
			block_element,
			field_element,
			data_offset
		);
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
		std::size_t field_element = 0,
		std::size_t data_offset = 0
	) const
	{
		auto f = flat_field.Field();
		if(f.IsPointer())
		{
			visitor(GetPointer(
				flat_field,
				block_element,
				field_element,
				data_offset
			));
		}
		else if(f.IsPointerToPointer())
		{
			visitor(GetPointerToPointer(
				flat_field,
				block_element,
				field_element,
				data_offset
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
						field_element,
						data_offset
					));
				else visitor(GetInt<char>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			}
			else if(bt.IsNative<uint8_t>())
				visitor(GetInt<uint8_t>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<int8_t>())
				visitor(GetInt<int8_t>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<uint16_t>())
				visitor(GetInt<uint16_t>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<int16_t>())
				visitor(GetInt<int16_t>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<uint32_t>())
				visitor(GetInt<uint32_t>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<int32_t>())
				visitor(GetInt<int32_t>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<uint64_t>())
				visitor(GetInt<uint64_t>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<int64_t>())
				visitor(GetInt<int64_t>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<float>())
				visitor(GetFloat<float>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else if(bt.IsNative<double>())
				visitor(GetFloat<double>(
					flat_field,
					block_element,
					field_element,
					data_offset
				));
			else visitor(
				_block_data.data() +
				data_offset +
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
