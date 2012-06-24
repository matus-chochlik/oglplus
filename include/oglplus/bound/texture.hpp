
/**
 *  @file oglplus/bound/texture.hpp
 *  @brief BoundTemplate Texture wrapper
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef OGLPLUS_BOUND_TEXTURE_1107121519_HPP
#define OGLPLUS_BOUND_TEXTURE_1107121519_HPP

#include <oglplus/texture.hpp>
#include <oglplus/bound.hpp>
#include <oglplus/auto_bind.hpp>
#include <utility>

namespace oglplus {

template <template <class> class Base, class BaseParam>
class BoundTemplate<Base, BaseParam, TextureOps>
 : public Base<BaseParam>
{
public:
	BoundTemplate(
		const TextureOps& bindable,
		TextureOps::Target target
	): Base<TextureOps>(bindable, target)
	{ }

	BoundTemplate(
		TextureOps::Target target
	): Base<BaseParam>(target)
	{ }

	GLint GetIntParam(
		GLenum query
	) const
	{
		return TextureOps::GetIntParam(
			this->BindTarget(),
			query
		);
	}

	GLfloat GetFloatParam(
		GLenum query
	) const
	{
		return TextureOps::GetFloatParam(
			this->BindTarget(),
			query
		);
	}

	GLint GetIntParam(
		GLint level,
		GLenum query
	) const
	{
		return TextureOps::GetIntParam(
			this->BindTarget(),
			level,
			query
		);
	}

	GLfloat GetFloatParam(
		GLint level,
		GLenum query
	) const
	{
		return TextureOps::GetFloatParam(
			this->BindTarget(),
			level,
			query
		);
	}

	GLsizei Width(
		GLint level = 0
	) const
	{
		return TextureOps::Width(
			this->BindTarget(),
			level
		);
	}

	GLsizei Height(
		GLint level = 0
	) const
	{
		return TextureOps::Height(
			this->BindTarget(),
			level
		);
	}

	GLsizei Depth(
		GLint level = 0
	) const
	{
		return TextureOps::Depth(
			this->BindTarget(),
			level
		);
	}

	PixelDataType RedType(
		GLint level = 0
	) const
	{
		return TextureOps::RedType(
			this->BindTarget(),
			level
		);
	}

	PixelDataType GreenType(
		GLint level = 0
	) const
	{
		return TextureOps::GreenType(
			this->BindTarget(),
			level
		);
	}

	PixelDataType BlueType(
		GLint level = 0
	) const
	{
		return TextureOps::BlueType(
			this->BindTarget(),
			level
		);
	}

	PixelDataType AlphaType(
		GLint level = 0
	) const
	{
		return TextureOps::AlphaType(
			this->BindTarget(),
			level
		);
	}

	PixelDataType DepthType(
		GLint level = 0
	) const
	{
		return TextureOps::DepthType(
			this->BindTarget(),
			level
		);
	}

	GLsizei RedSize(
		GLint level = 0
	) const
	{
		return TextureOps::RedSize(
			this->BindTarget(),
			level
		);
	}

	GLsizei GreenSize(
		GLint level = 0
	) const
	{
		return TextureOps::GreenSize(
			this->BindTarget(),
			level
		);
	}

	GLsizei BlueSize(
		GLint level = 0
	) const
	{
		return TextureOps::BlueSize(
			this->BindTarget(),
			level
		);
	}

	GLsizei AlphaSize(
		GLint level = 0
	) const
	{
		return TextureOps::AlphaSize(
			this->BindTarget(),
			level
		);
	}

	GLsizei DepthSize(
		GLint level = 0
	) const
	{
		return TextureOps::DepthSize(
			this->BindTarget(),
			level
		);
	}

	GLsizei StencilSize(
		GLint level = 0
	) const
	{
		return TextureOps::StencilSize(
			this->BindTarget(),
			level
		);
	}

	GLsizei SharedSize(
		GLint level = 0
	) const
	{
		return TextureOps::SharedSize(
			this->BindTarget(),
			level
		);
	}

	GLsizei CompressedImageSize(
		GLint level = 0
	) const
	{
		return TextureOps::CompressedImageSize(
			this->BindTarget(),
			level
		);
	}

	PixelDataInternalFormat InternalFormat(
		GLint level = 0
	) const
	{
		return TextureOps::InternalFormat(
			this->BindTarget(),
			level
		);
	}

	void GetCompressedImage(
		GLint level,
		std::vector< GLubyte > & dest
	) const
	{
		TextureOps::GetCompressedImage(
			this->BindTarget(),
			level,
			dest
		);
	}

	void Image3D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void * data
	) const
	{
		TextureOps::Image3D(
			this->BindTarget(),
			level,
			internal_format,
			width,
			height,
			depth,
			border,
			format,
			type,
			data
		);
	}

	template <typename T>
	void Image3D(
		const Image< T > & image,
		GLint level = 0,
		GLint border = 0
	) const
	{
		TextureOps::Image3D(
			this->BindTarget(),
			image,
			level,
			border
		);
	}

	void SubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		PixelDataFormat format,
		PixelDataType type,
		const void * data
	) const
	{
		TextureOps::SubImage3D(
			this->BindTarget(),
			level,
			xoffs,
			yoffs,
			zoffs,
			width,
			height,
			depth,
			format,
			type,
			data
		);
	}

	template <typename T>
	void SubImage3D(
		const Image< T > & image,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint level = 0
	) const
	{
		TextureOps::SubImage3D(
			this->BindTarget(),
			image,
			xoffs,
			yoffs,
			zoffs,
			level
		);
	}

	void Image2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void * data
	) const
	{
		TextureOps::Image2D(
			this->BindTarget(),
			level,
			internal_format,
			width,
			height,
			border,
			format,
			type,
			data
		);
	}

	template <typename T>
	void Image2D(
		const Image< T > & image,
		GLint level = 0,
		GLint border = 0
	) const
	{
		TextureOps::Image2D(
			this->BindTarget(),
			image,
			level,
			border
		);
	}

	void SubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		PixelDataFormat format,
		PixelDataType type,
		const void * data
	) const
	{
		TextureOps::SubImage2D(
			this->BindTarget(),
			level,
			xoffs,
			yoffs,
			width,
			height,
			format,
			type,
			data
		);
	}

	template <typename T>
	void SubImage2D(
		const Image< T > & image,
		GLint xoffs,
		GLint yoffs,
		GLint level = 0
	) const
	{
		TextureOps::SubImage2D(
			this->BindTarget(),
			image,
			xoffs,
			yoffs,
			level
		);
	}

	void Image1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void * data
	) const
	{
		TextureOps::Image1D(
			this->BindTarget(),
			level,
			internal_format,
			width,
			border,
			format,
			type,
			data
		);
	}

	template <typename T>
	void Image1D(
		const Image< T > & image,
		GLint level = 0,
		GLint border = 0
	) const
	{
		TextureOps::Image1D(
			this->BindTarget(),
			image,
			level,
			border
		);
	}

	void SubImage1D(
		GLint level,
		GLint xoffs,
		GLsizei width,
		PixelDataFormat format,
		PixelDataType type,
		const void * data
	) const
	{
		TextureOps::SubImage1D(
			this->BindTarget(),
			level,
			xoffs,
			width,
			format,
			type,
			data
		);
	}

	template <typename T>
	void SubImage1D(
		const Image< T > & image,
		GLint xoffs,
		GLint level = 0
	) const
	{
		TextureOps::SubImage1D(
			this->BindTarget(),
			image,
			xoffs,
			level
		);
	}

	void CopyImage2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height,
		GLint border
	) const
	{
		TextureOps::CopyImage2D(
			this->BindTarget(),
			level,
			internal_format,
			x,
			y,
			width,
			height,
			border
		);
	}

	void CopyImage1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLint border
	) const
	{
		TextureOps::CopyImage1D(
			this->BindTarget(),
			level,
			internal_format,
			x,
			y,
			width,
			border
		);
	}

	void CopySubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	) const
	{
		TextureOps::CopySubImage3D(
			this->BindTarget(),
			level,
			xoffs,
			yoffs,
			zoffs,
			x,
			y,
			width,
			height
		);
	}

	void CopySubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	) const
	{
		TextureOps::CopySubImage2D(
			this->BindTarget(),
			level,
			xoffs,
			yoffs,
			x,
			y,
			width,
			height
		);
	}

	void CopySubImage1D(
		GLint level,
		GLint xoffs,
		GLint x,
		GLint y,
		GLsizei width
	) const
	{
		TextureOps::CopySubImage1D(
			this->BindTarget(),
			level,
			xoffs,
			x,
			y,
			width
		);
	}

	void CompressedImage3D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		GLsizei image_size,
		const void * data
	) const
	{
		TextureOps::CompressedImage3D(
			this->BindTarget(),
			level,
			internal_format,
			width,
			height,
			depth,
			border,
			image_size,
			data
		);
	}

	void CompressedImage2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		GLsizei image_size,
		const void * data
	) const
	{
		TextureOps::CompressedImage2D(
			this->BindTarget(),
			level,
			internal_format,
			width,
			height,
			border,
			image_size,
			data
		);
	}

	void CompressedImage1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		GLsizei image_size,
		const void * data
	) const
	{
		TextureOps::CompressedImage1D(
			this->BindTarget(),
			level,
			internal_format,
			width,
			border,
			image_size,
			data
		);
	}

	void CompressedSubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		PixelDataFormat format,
		GLsizei image_size,
		const void * data
	) const
	{
		TextureOps::CompressedSubImage3D(
			this->BindTarget(),
			level,
			xoffs,
			yoffs,
			zoffs,
			width,
			height,
			depth,
			format,
			image_size,
			data
		);
	}

	void CompressedSubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		PixelDataFormat format,
		GLsizei image_size,
		const void * data
	) const
	{
		TextureOps::CompressedSubImage2D(
			this->BindTarget(),
			level,
			xoffs,
			yoffs,
			width,
			height,
			format,
			image_size,
			data
		);
	}

	void CompressedSubImage1D(
		GLint level,
		GLint xoffs,
		GLsizei width,
		PixelDataFormat format,
		GLsizei image_size,
		const void * data
	) const
	{
		TextureOps::CompressedSubImage1D(
			this->BindTarget(),
			level,
			xoffs,
			width,
			format,
			image_size,
			data
		);
	}

	GLuint BaseLevel(void) const
	{
		return TextureOps::BaseLevel(
			this->BindTarget()
		);
	}

	void BaseLevel(
		GLuint level
	) const
	{
		TextureOps::BaseLevel(
			this->BindTarget(),
			level
		);
	}

	Vector< GLfloat, 4 > BorderColor(
		TypeTag< GLfloat > _auto_param_2
	) const
	{
		return TextureOps::BorderColor(
			this->BindTarget(),
			_auto_param_2
		);
	}

	void BorderColor(
		Vector< GLfloat, 4 > color
	) const
	{
		TextureOps::BorderColor(
			this->BindTarget(),
			color
		);
	}

	Vector< GLint, 4 > BorderColor(
		TypeTag< GLint > _auto_param_2
	) const
	{
		return TextureOps::BorderColor(
			this->BindTarget(),
			_auto_param_2
		);
	}

	void BorderColor(
		Vector< GLint, 4 > color
	) const
	{
		TextureOps::BorderColor(
			this->BindTarget(),
			color
		);
	}

	Vector< GLuint, 4 > BorderColor(
		TypeTag< GLuint > _auto_param_2
	) const
	{
		return TextureOps::BorderColor(
			this->BindTarget(),
			_auto_param_2
		);
	}

	void BorderColor(
		Vector< GLuint, 4 > color
	) const
	{
		TextureOps::BorderColor(
			this->BindTarget(),
			color
		);
	}

	TextureCompareMode CompareMode(void) const
	{
		return TextureOps::CompareMode(
			this->BindTarget()
		);
	}

	void CompareMode(
		TextureCompareMode mode
	) const
	{
		TextureOps::CompareMode(
			this->BindTarget(),
			mode
		);
	}

	CompareFunction CompareFunc(void) const
	{
		return TextureOps::CompareFunc(
			this->BindTarget()
		);
	}

	void CompareFunc(
		CompareFunction func
	) const
	{
		TextureOps::CompareFunc(
			this->BindTarget(),
			func
		);
	}

	GLfloat LODBias(void) const
	{
		return TextureOps::LODBias(
			this->BindTarget()
		);
	}

	void LODBias(
		GLfloat value
	) const
	{
		TextureOps::LODBias(
			this->BindTarget(),
			value
		);
	}

	TextureMagFilter MagFilter(void) const
	{
		return TextureOps::MagFilter(
			this->BindTarget()
		);
	}

	void MagFilter(
		TextureMagFilter filter
	) const
	{
		TextureOps::MagFilter(
			this->BindTarget(),
			filter
		);
	}

	TextureMinFilter MinFilter(void) const
	{
		return TextureOps::MinFilter(
			this->BindTarget()
		);
	}

	void MinFilter(
		TextureMinFilter filter
	) const
	{
		TextureOps::MinFilter(
			this->BindTarget(),
			filter
		);
	}

	GLfloat MinLOD(void) const
	{
		return TextureOps::MinLOD(
			this->BindTarget()
		);
	}

	void MinLOD(
		GLfloat value
	) const
	{
		TextureOps::MinLOD(
			this->BindTarget(),
			value
		);
	}

	GLfloat MaxLOD(void) const
	{
		return TextureOps::MaxLOD(
			this->BindTarget()
		);
	}

	void MaxLOD(
		GLfloat value
	) const
	{
		TextureOps::MaxLOD(
			this->BindTarget(),
			value
		);
	}

	TextureWrap Wrap(
		TextureWrapCoord coord
	) const
	{
		return TextureOps::Wrap(
			this->BindTarget(),
			coord
		);
	}

	void Wrap(
		TextureWrapCoord coord,
		TextureWrap mode
	) const
	{
		TextureOps::Wrap(
			this->BindTarget(),
			coord,
			mode
		);
	}

	TextureWrap WrapS(void) const
	{
		return TextureOps::WrapS(
			this->BindTarget()
		);
	}

	void WrapS(
		TextureWrap mode
	) const
	{
		TextureOps::WrapS(
			this->BindTarget(),
			mode
		);
	}

	TextureWrap WrapT(void) const
	{
		return TextureOps::WrapT(
			this->BindTarget()
		);
	}

	void WrapT(
		TextureWrap mode
	) const
	{
		TextureOps::WrapT(
			this->BindTarget(),
			mode
		);
	}

	TextureWrap WrapR(void) const
	{
		return TextureOps::WrapR(
			this->BindTarget()
		);
	}

	void WrapR(
		TextureWrap mode
	) const
	{
		TextureOps::WrapR(
			this->BindTarget(),
			mode
		);
	}

	void GenerateMipmap(void) const
	{
		TextureOps::GenerateMipmap(
			this->BindTarget()
		);
	}


}; // class BoundTemplate

} // namespace oglplus

#endif // include guard
