/**
 *  @file oglplus/imports/blend_file/flattened.hpp
 *  @brief Classes handling flattened SDNA structures
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMPORTS_BLEND_FILE_FLATTENED_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_FLATTENED_1107121519_HPP

namespace oglplus {
namespace imports {


class BlendFileFlattenedStructField
{
private:
	std::shared_ptr<BlendFileSDNA> _sdna;
	std::size_t _struct_index;
	std::size_t _flat_field_index;
	const BlendFileSDNA::_flat_struct_info& _flat_fields;

	BlendFileFlattenedStructField(
		const std::shared_ptr<BlendFileSDNA>& sdna,
		std::size_t struct_index,
		std::size_t flat_field_index,
		const BlendFileSDNA::_flat_struct_info& flat_fields
	): _sdna(sdna)
	 , _struct_index(struct_index)
	 , _flat_field_index(flat_field_index)
	 , _flat_fields(flat_fields)
	{ }

	friend class BlendFileFlattenedStruct;
	friend class BlendFileFlattenedStructFieldRange;
public:

	const std::string& Name(void) const
	{
		return _flat_fields._field_names[_flat_field_index];
	}

	BlendFileStruct Parent(void) const
	{
		return BlendFileStruct(
			_sdna,
			_flat_fields._field_structs[_flat_field_index]
		);
	}

	BlendFileStructField Field(void) const
	{
		return BlendFileStructField(
			_sdna,
			_flat_fields._field_structs[_flat_field_index],
			_flat_fields._field_indices[_flat_field_index]
		);
	}

	uint32_t Offset(void) const
	{
		return _flat_fields._field_offsets[_flat_field_index];
	}

	uint32_t Size(void) const
	{
		return Field().Size();
	}
};

class BlendFileFlattenedStructFieldRange
 : public BlendFileRangeTpl<
	BlendFileFlattenedStructFieldRange,
	BlendFileFlattenedStructField
>
{
private:
	std::shared_ptr<BlendFileSDNA> _sdna;
	std::size_t _struct_index;
	const BlendFileSDNA::_flat_struct_info& _flat_fields;

	typedef BlendFileRangeTpl<
		BlendFileFlattenedStructFieldRange,
		BlendFileFlattenedStructField
	> Base;

	BlendFileFlattenedStructFieldRange(
		const std::shared_ptr<BlendFileSDNA>& sdna,
		std::size_t struct_index,
		const BlendFileSDNA::_flat_struct_info& flat_fields
	): Base(flat_fields._field_count())
	 , _sdna(sdna)
	 , _struct_index(struct_index)
	 , _flat_fields(flat_fields)
	{ }

	friend class BlendFileFlattenedStruct;
public:
	BlendFileFlattenedStructField Get(std::size_t index) const
	{
		return BlendFileFlattenedStructField(
			_sdna,
			_struct_index,
			index,
			_flat_fields
		);
	}
};

class BlendFileFlattenedStruct
 : public BlendFileType
{
public:
	BlendFileFlattenedStruct(const BlendFileType& type)
	 : BlendFileType(type)
	{ }

	/// Returns a range of fields of the flattened structure
	BlendFileFlattenedStructFieldRange Fields(void) const
	{
		return BlendFileFlattenedStructFieldRange(
			_sdna,
			_struct_index,
			*_sdna->_struct_flatten_fields(_struct_index)
		);
	}

	/// Returns a field by its full name
	BlendFileFlattenedStructField FieldByName(const std::string& name) const
	{
		const BlendFileSDNA::_flat_struct_info& flat_fields =
			*_sdna->_struct_flatten_fields(_struct_index);
		auto pos = flat_fields._field_map.find(&name);

		if(pos == flat_fields._field_map.end())
		{
			std::string what("Cannot find field '");
			what.append(name);
			what.append("' in flattened structure");
			throw std::runtime_error(what);
		}

		const std::size_t flat_field_index = pos->second;

		return BlendFileFlattenedStructField(
			_sdna,
			_struct_index,
			flat_field_index,
			flat_fields
		);
	}
};

BlendFileFlattenedStruct BlendFileStruct::Flattened(void) const
{
	return BlendFileFlattenedStruct(*this);
}

} // imports
} // oglplus

#endif // include guard
