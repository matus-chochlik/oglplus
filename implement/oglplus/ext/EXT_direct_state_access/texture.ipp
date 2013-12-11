/**
 *  @file oglplus/ext/EXT_direct_state_access/texture.ipp
 *  @brief Implementation of DSA Texture functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/images/image.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::Image3D(
	const images::Image& image,
	GLint level,
	GLint border
)
{
	OGLPLUS_GLFUNC(TextureImage3DEXT)(
		_name,
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
		TextureImage3DEXT,
		Texture,
		EnumValueName(target),
		_name
	));
}

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::SubImage3D(
	const images::Image& image,
	GLint xoffs,
	GLint yoffs,
	GLint zoffs,
	GLint level
)
{
	OGLPLUS_GLFUNC(TextureSubImage3DEXT)(
		_name,
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
		TextureSubImage3DEXT,
		Texture,
		EnumValueName(target),
		_name
	));
}

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::Image2D(
	const images::Image& image,
	GLint level,
	GLint border
)
{
	OGLPLUS_GLFUNC(TextureImage2DEXT)(
		_name,
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
		TextureImage2DEXT,
		Texture,
		EnumValueName(target),
		_name
	));
}

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::SubImage2D(
	const images::Image& image,
	GLint xoffs,
	GLint yoffs,
	GLint level
)
{
	OGLPLUS_GLFUNC(TextureSubImage2DEXT)(
		_name,
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
		TextureSubImage2DEXT,
		Texture,
		EnumValueName(target),
		_name
	));
}

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::Image1D(
	const images::Image& image,
	GLint level,
	GLint border
)
{
	OGLPLUS_GLFUNC(TextureImage1DEXT)(
		_name,
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
		TextureImage1DEXT,
		Texture,
		EnumValueName(target),
		_name
	));
}

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::SubImage1D(
	const images::Image& image,
	GLint xoffs,
	GLint level
)
{
	OGLPLUS_GLFUNC(TextureSubImage1DEXT)(
		_name,
		GLenum(target),
		level,
		xoffs,
		image.Width(),
		GLenum(image.Format()),
		GLenum(image.Type()),
		image.RawData()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TextureSubImage1DEXT,
		Texture,
		EnumValueName(target),
		_name
	));
}

#endif // GL_EXT_direct_state_access

} // namespace oglplus

