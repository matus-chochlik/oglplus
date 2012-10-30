/**
 *  @file oglplus/imports/blend_file/structure.hpp
 *  @brief Class providing information about a structure defined in a .blend file
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMPORTS_BLEND_FILE_STRUCTURE_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_STRUCTURE_1107121519_HPP

namespace oglplus {
namespace imports {

class BlendFileFlattenedStruct;

/// Provides information about a field of a blender structure
class BlendFileStructField
{
private:
	std::shared_ptr<BlendFileSDNA> _sdna;
	std::size_t _struct_index;
	std::size_t _field_index;

	friend class BlendFileStructFieldRange;
	friend class BlendFileFlattenedStructField;

	BlendFileStructField(
		const std::shared_ptr<BlendFileSDNA>& _sdna,
		std::size_t struct_index,
		std::size_t field_index
	): _sdna(_sdna)
	 , _struct_index(struct_index)
	 , _field_index(field_index)
	{
		assert(_sdna);
	}
public:
	/// Returns the base type of the field
	/**
	 *  @note The actual type may be a pointer to the base
	 *  type or an array of multiple elements of the base type.
	 *
	 *  @see IsPointer
	 *  @see IsPointerToFunc
	 *  @see IsArray
	 *  @see ElementCount
 	 */
	BlendFileType BaseType(void) const
	{
		return BlendFileType(
			_sdna,
			_sdna->_structs[_struct_index].
				_field_type_indices[_field_index],
			_struct_index
		);
	}

	/// Returns the defintion string of the structure field
	const std::string& Definition(void) const
	{
		return _sdna->_names[
			_sdna->_structs[_struct_index].
			_field_name_indices[_field_index]
		];
	}

	/// Returns the name of the structure field
	std::string Name(void) const
	{
		return _sdna->_field_name_from_def(Definition());
	}

	/// Returns true if the field is a regular pointer
	bool IsPointer(void) const
	{
		return	_sdna->_structs[_struct_index].
			_field_ptr_flags[_field_index];
	}

	/// Returns true if the field is a pointer to a function
	bool IsPointerToFunc(void) const
	{
		return	_sdna->_structs[_struct_index].
			_field_fn_ptr_flags[_field_index];
	}

	/// Returns true if the field is an array
	bool IsArray(void) const
	{
		return	_sdna->_structs[_struct_index].
			_field_array_flags[_field_index];
	}

	/// Returns the number of elements in case of an array, 1 otherwise
	std::size_t ElementCount(void) const
	{
		return	_sdna->_structs[_struct_index].
			_field_elem_counts[_field_index];
	}

	/// Returns the size of the field in bytes
	std::size_t Size(void) const
	{
		bool is_ptr = IsPointer() || IsPointerToFunc();

		if(IsArray())
		{
			std::size_t ec = ElementCount();
			if(is_ptr) return _sdna->_ptr_size * ec;
			else return BaseType().Size() * ec;
		}
		if(is_ptr) return _sdna->_ptr_size;
		return BaseType().Size();
	}
};

/// Class allowing the traversal of structure's fields
class BlendFileStructFieldRange
 : public BlendFileRangeTpl<BlendFileStructFieldRange, BlendFileStructField>
{
private:
	std::shared_ptr<BlendFileSDNA> _sdna;
	std::size_t _struct_index;

	typedef BlendFileRangeTpl<BlendFileStructFieldRange, BlendFileStructField> Base;

	friend class BlendFileStruct;

	BlendFileStructFieldRange(
		const std::shared_ptr<BlendFileSDNA>& sdna,
		std::size_t struct_index
	): Base(sdna->_structs[struct_index]._field_count())
	 , _sdna(sdna)
	 , _struct_index(struct_index)
	{ }
public:
	BlendFileStructField Get(std::size_t index) const
	{
		return BlendFileStructField(
			_sdna,
			_struct_index,
			index
		);
	}
};

/// Wrapper around Blender structure meta-data
class BlendFileStruct
 : public BlendFileType
{
private:

	friend class BlendFile;
	friend class BlendFileStructRange;
	friend class BlendFileStructField;
	friend class BlendFileFlattenedStructField;

	BlendFileStruct(
		const std::shared_ptr<BlendFileSDNA>& _sdna,
		std::size_t struct_index
	): BlendFileType(
		_sdna,
		_sdna->_structs[struct_index]._type_index,
		struct_index
	)
	{ }

public:
	BlendFileStruct(const BlendFileType& type)
	 : BlendFileType(type)
	{ }

	/// Returns a range of fields of structure
	BlendFileStructFieldRange Fields(void) const
	{
		return BlendFileStructFieldRange(
			_sdna,
			_struct_index
		);
	}

	inline BlendFileFlattenedStruct Flattened(void) const;
};

BlendFileStruct BlendFileType::AsStructure(void) const
{
	return BlendFileStruct(*this);
}

/// Allows the traversal of a range of Blender structures
class BlendFileStructRange
 : public BlendFileRangeTpl<BlendFileStructRange, BlendFileStruct>
{
private:
	std::shared_ptr<BlendFileSDNA> _sdna;

	typedef BlendFileRangeTpl<BlendFileStructRange, BlendFileStruct> Base;

	friend class BlendFile;

	BlendFileStructRange(const std::shared_ptr<BlendFileSDNA>& sdna)
	 : Base(sdna->_structs.size())
	 , _sdna(sdna)
	{ }
public:
	BlendFileStruct Get(std::size_t index) const
	{
		return BlendFileStruct(_sdna, index);
	}
};

} // imports
} // oglplus

#endif // include guard
