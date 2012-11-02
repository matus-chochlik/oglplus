/**
 *  @file oglplus/imports/blend_file/struct_block_data.hpp
 *  @brief Convenience class for easy manipulation of block data
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMPORTS_BLEND_FILE_STRUCT_BLOCK_DATA_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_STRUCT_BLOCK_DATA_1107121519_HPP

#include <type_traits>

namespace oglplus {
namespace imports {

/// Helper class for direct access to a field's data from a specific block
template <typename T>
class BlendFileFlatStructTypedFieldData
{
private:
	BlendFileFlattenedStructField _flat_field;
	const BlendFileBlockData* _block_data_ref;

	friend class BlendFileFlatStructBlockData;

	BlendFileFlatStructTypedFieldData(
		BlendFileFlattenedStructField&& flat_field,
		const BlendFileBlockData& block_data_ref
	): _flat_field(std::move(flat_field))
	 , _block_data_ref(&block_data_ref)
	{ }

	static const BlendFileFlatStructTypedFieldData& _that(void);

	BlendFilePointer _do_get(
		BlendFilePointer*,
		std::size_t be,
		std::size_t fe
	) const
	{
		return _block_data_ref->GetPointer(_flat_field, be, fe);
	}

	BlendFilePointer _do_get(
		void**,
		std::size_t be,
		std::size_t fe
	) const
	{
		return _block_data_ref->GetPointer(_flat_field, be, fe);
	}

	std::string _do_get(
		std::string*,
		std::size_t be,
		std::size_t fe
	) const
	{
		return _block_data_ref->GetString(_flat_field, be, fe);
	}

	char _do_get(char*, std::size_t be, std::size_t fe) const
	{
		return _block_data_ref->GetInt<char>(_flat_field, be, fe);
	}

	float _do_get(float*, std::size_t be, std::size_t fe) const
	{
		return _block_data_ref->GetFloat<float>(_flat_field, be, fe);
	}

	double _do_get(double*, std::size_t be, std::size_t fe) const
	{
		return _block_data_ref->GetFloat<double>(_flat_field, be, fe);
	}

	template <typename Int>
	typename std::enable_if<
		std::is_integral<Int>::value,
		Int
	>::type _do_get(Int*, std::size_t be, std::size_t fe) const
	{
		return _block_data_ref->GetInt<Int>(_flat_field, be, fe);
	}
public:
	typedef decltype(_that()._do_get((T*)nullptr, 0, 0)) ValueType;

	BlendFileFlatStructTypedFieldData(BlendFileFlatStructTypedFieldData&& tmp)
	 : _flat_field(std::move(tmp._flat_field))
	 , _block_data_ref(tmp._block_data_ref)
	{ }

	/// Get the value of the field from the block
	ValueType Get(
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		return _do_get((T*)nullptr, block_element, field_element);
	}

	/// Get the value of the field from the block
	operator ValueType (void) const
	{
		return Get(0, 0);
	}
};

/// Convenience class combining functionality of FlattenedStruct, Block and BlockData
class BlendFileFlatStructBlockData
{
private:
	BlendFileFlattenedStruct _flat_struct;
	BlendFileBlock _block;
	BlendFileBlockData _data;

	friend class BlendFile;

	BlendFileFlatStructBlockData(
		BlendFileFlattenedStruct&& flat_struct,
		BlendFileBlock&& block,
		BlendFileBlockData&& data
	): _flat_struct(std::move(flat_struct))
	 , _block(std::move(block))
	 , _data(std::move(data))
	{ }

	template <typename T>
	static T _adjust_value(T* ptr)
	{
		assert(ptr);
		return *ptr;
	}

	static BlendFilePointer _adjust_value(void**)
	{
		return BlendFilePointer();
	}

	template <typename T>
	struct _adjust_type
	{
		typedef decltype(_adjust_value((T*)0)) type;
	};
public:
	BlendFileFlatStructBlockData(BlendFileFlatStructBlockData&& tmp)
	 : _flat_struct(std::move(tmp._flat_struct))
	 , _block(std::move(tmp._block))
	 , _data(std::move(tmp._data))
	{ }

	/// Returns the data structure
	const BlendFileFlattenedStruct& Structure(void) const
	{
		return _flat_struct;
	}

	/// The name of the block's structure type
	const std::string& StructureName(void) const
	{
		return Structure().Name();
	}

	/// The size of instance of the structure in bytes
	std::size_t StructureSize(void) const
	{
		return Structure().Size();
	}

	/// Returns a range of fields of the block's flattened structure
	BlendFileFlattenedStructFieldRange StructureFields(void) const
	{
		return Structure().Fields();
	}

	/// Returns a block's structure's field by its full name
	BlendFileFlattenedStructField StructureFieldByName(
		const std::string& field_name
	) const
	{
		return Structure().FieldByName(field_name);
	}

	/// Alias for StructureFieldByName
	BlendFileFlattenedStructField operator / (
		const std::string& field_name
	) const
	{
		return Structure().FieldByName(field_name);
	}

	/// Returns the block
	const BlendFileBlock& Block(void) const
	{
		return _block;
	}

	/// Returns the code of the block
	std::string BlockCode(void) const
	{
		return _block.Code();
	}

	/// Returns the size of the block in bytes
	uint32_t BlockSize(void) const
	{
		return _block.Size();
	}

	/// Returns the number of elements in the block
	uint32_t BlockElementCount(void) const
	{
		return _block.ElementCount();
	}

	/// Returns the 'old' pointer value of the block as loaded from input
	BlendFilePointer BlockPointer(void) const
	{
		return _block.Pointer();
	}

	/// Returns the the position of the block data in the input file
	std::streampos BlockDataPosition(void) const
	{
		return _block.DataPosition();
	}

	/// Returns the block data object
	const BlendFileBlockData& BlockData(void) const
	{
		return _data;
	}

	/// Visit the value of the specified field by a visitor
	template <class Visitor>
	void BlockDataValueVisit(
		Visitor visitor,
		const BlendFileFlattenedStructField& flat_field,
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		BlockData().ValueVisit(
			visitor,
			flat_field,
			block_element,
			field_element
		);
	}

	/// Returns a getter object that allows to obtain the value of a field
	template <typename T>
	BlendFileFlatStructTypedFieldData<T> TypedFieldValue(
		const std::string& field_name
	) const
	{
		return BlendFileFlatStructTypedFieldData<T>(
			Structure().FieldByName(field_name),
			BlockData()
		);
	}

	/// Alias for TypedFieldValue
	template <typename T>
	BlendFileFlatStructTypedFieldData<T> Field(
		const std::string& field_name
	) const
	{
		return BlendFileFlatStructTypedFieldData<T>(
			Structure().FieldByName(field_name),
			BlockData()
		);
	}

	template <typename T>
	typename _adjust_type<T>::type TryGet(
		const std::string& field_name,
		T default_value,
		std::size_t block_element = 0,
		std::size_t field_element = 0
	) const
	{
		try
		{
			return Field<T>(field_name).Get(
				block_element,
				field_element
			);
		}
		catch(...) { }
		return _adjust_value(&default_value);
	}
};

} // imports
} // oglplus

#endif // include guard
