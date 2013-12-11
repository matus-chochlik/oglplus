/**
 *  @file oglplus/texture.ipp
 *  @brief Implementation of Texture functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/images/image.hpp>

namespace oglplus {

OGLPLUS_LIB_FUNC
void TextureOps::Image3D(
	Target target,
	const images::Image& image,
	GLint level,
	GLint border
)
{
	OGLPLUS_GLFUNC(TexImage3D)(
		GLenum(target),
		level,
		GLint(image.InternalFormat()),
		image.Width(),
		image.Height(),
		image.Depth(),
		border,
		GLenum(image.Format()),
		GLenum(image.Type()),
		image.RawData()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TexImage3D,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
}

OGLPLUS_LIB_FUNC
void TextureOps::SubImage3D(
	Target target,
	const images::Image& image,
	GLint xoffs,
	GLint yoffs,
	GLint zoffs,
	GLint level
)
{
	OGLPLUS_GLFUNC(TexSubImage3D)(
		GLenum(target),
		level,
		xoffs,
		yoffs,
		zoffs,
		image.Width(),
		image.Height(),
		image.Depth(),
		GLenum(image.Format()),
		GLenum(image.Type()),
		image.RawData()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TexSubImage3D,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
}

OGLPLUS_LIB_FUNC
void TextureOps::Image2D(
	Target target,
	const images::Image& image,
	GLint level,
	GLint border
)
{
	OGLPLUS_GLFUNC(TexImage2D)(
		GLenum(target),
		level,
		GLint(image.InternalFormat()),
		image.Width(),
		image.Height(),
		border,
		GLenum(image.Format()),
		GLenum(image.Type()),
		image.RawData()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TexImage2D,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
}

OGLPLUS_LIB_FUNC
void TextureOps::SubImage2D(
	Target target,
	const images::Image& image,
	GLint xoffs,
	GLint yoffs,
	GLint level
)
{
	OGLPLUS_GLFUNC(TexSubImage2D)(
		GLenum(target),
		level,
		xoffs,
		yoffs,
		image.Width(),
		image.Height(),
		GLenum(image.Format()),
		GLenum(image.Type()),
		image.RawData()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TexSubImage2D,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
}

OGLPLUS_LIB_FUNC
void TextureOps::Image1D(
	Target target,
	const images::Image& image,
	GLint level,
	GLint border
)
{
	OGLPLUS_GLFUNC(TexImage1D)(
		GLenum(target),
		level,
		GLint(image.InternalFormat()),
		image.Width(),
		border,
		GLenum(image.Format()),
		GLenum(image.Type()),
		image.RawData()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TexImage1D,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
}

OGLPLUS_LIB_FUNC
void TextureOps::SubImage1D(
	Target target,
	const images::Image& image,
	GLint xoffs,
	GLint level
)
{
	OGLPLUS_GLFUNC(TexSubImage1D)(
		GLenum(target),
		level,
		xoffs,
		image.Width(),
		GLenum(image.Format()),
		GLenum(image.Type()),
		image.RawData()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TexSubImage1D,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
}

} // namespace oglplus

