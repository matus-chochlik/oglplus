/**
 *  @file oglplus/tex_image_spec.hpp
 *  @brief Texture image specification
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEX_IMAGE_SPEC_1202210916_HPP
#define OGLPLUS_TEX_IMAGE_SPEC_1202210916_HPP

#include <oglplus/pixel_data.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/one_of.hpp>

namespace oglplus {

/// Class containing data for texture image specification
struct TexImageSpec
{
	typedef OneOf<
		GLenum,
		std::tuple<
			DataType,
			PixelDataType
		>
	> PixDataType;

	GLsizei width;
	GLsizei height;
	GLsizei depth;
	PixelDataFormat format;
	PixelDataInternalFormat internal_format;
	PixDataType data_type;
	const void* data_ptr;

	TexImageSpec(void)
	 : width(1)
	 , height(1)
	 , depth(1)
	 , format(PixelDataFormat(0))
	 , internal_format(PixelDataInternalFormat(0))
	 , data_type(PixelDataType(0))
	 , data_ptr(nullptr)
	{ }

	TexImageSpec(
		GLsizei w,
		PixelDataFormat fmt,
		PixelDataInternalFormat ifmt,
		PixDataType type,
		const void* data = nullptr
	): width(w)
	 , height(1)
	 , depth(1)
	 , format(fmt)
	 , internal_format(ifmt)
	 , data_type(type)
	 , data_ptr(data)
	{ }

	TexImageSpec(
		GLsizei w,
		GLsizei h,
		PixelDataFormat fmt,
		PixelDataInternalFormat ifmt,
		PixDataType type,
		const void* data = nullptr
	): width(w)
	 , height(h)
	 , depth(1)
	 , format(fmt)
	 , internal_format(ifmt)
	 , data_type(type)
	 , data_ptr(data)
	{ }

	TexImageSpec(
		GLsizei w,
		GLsizei h,
		GLsizei d,
		PixelDataFormat fmt,
		PixelDataInternalFormat ifmt,
		PixDataType type,
		const void* data = nullptr
	): width(w)
	 , height(h)
	 , depth(d)
	 , format(fmt)
	 , internal_format(ifmt)
	 , data_type(type)
	 , data_ptr(data)
	{ }

	TexImageSpec& NextDim(GLsizei dim)
	{
		assert(dim > 0);
		if(width <= 1)
		{
			width = dim;
		}
		else if(height <= 1)
		{
			height = dim;
		}
		else if(depth <= 1)
		{
			depth = dim;
		}
		else assert(!"Too many dimensions specified!");
		return *this;
	}

	TexImageSpec& Format(PixelDataFormat fmt)
	{
		format = fmt;
		return *this;
	}

	TexImageSpec& Format(PixelDataInternalFormat ifmt)
	{
		internal_format = ifmt;
		return *this;
	}

	TexImageSpec& Type(PixDataType type)
	{
		data_type = type;
		return *this;
	}
};

inline TexImageSpec& operator << (
	TexImageSpec& that,
	GLsizei dim
)
{
	return that.NextDim(dim);
}

inline TexImageSpec&& operator << (
	TexImageSpec&& that,
	GLsizei dim
)
{
	return std::move(that.NextDim(dim));
}

inline TexImageSpec& operator << (
	TexImageSpec& that,
	PixelDataFormat f
)
{
	return that.Format(f);
}

inline TexImageSpec&& operator << (
	TexImageSpec&& that,
	PixelDataFormat f
)
{
	return std::move(that.Format(f));
}

inline TexImageSpec& operator << (
	TexImageSpec& that,
	PixelDataInternalFormat f
)
{
	return that.Format(f);
}

inline TexImageSpec&& operator << (TexImageSpec&& that, PixelDataInternalFormat f)
{
	return std::move(that.Format(f));
}

} // namespace oglplus

#endif // include guard
