/**
 *  @file oglplus/ext/EXT_direct_state_access/texture.ipp
 *  @brief Implementation of DSA Texture functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/images/image_spec.hpp>
#include <oglplus/images/image.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {

#if GL_EXT_direct_state_access

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::GetImage(
	GLint level,
	PixelDataFormat format,
	Property::PixDataType type,
	GLsizei size,
	GLvoid* buffer
) const
{
	OGLPLUS_FAKE_USE(size);
	OGLPLUS_GLFUNC(GetTextureImageEXT)(
		_name,
		GLenum(target),
		level,
		GLenum(format),
		GLenum(type),
		buffer
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		GetTextureImageEXT,
		Texture,
		EnumValueName(target),
		_name
	));
}

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::GetCompressedImage(
	GLint level,
	GLsizei size,
	GLubyte* buffer
) const
{
	OGLPLUS_FAKE_USE(size);
	OGLPLUS_GLFUNC(GetCompressedTextureImageEXT)(
		_name,
		GLenum(target),
		level,
		buffer
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		GetCompressedTextureImageEXT,
		Texture,
		EnumValueName(target),
		_name
	));
}

OGLPLUS_LIB_FUNC
void DSATextureEXTOps::GetCompressedImage(
	GLint level,
	std::vector<GLubyte>& dest
) const
{
	dest.resize(CompressedImageSize(level));
	GetCompressedImage(
		level,
		dest.size()*sizeof(GLubyte),
		dest.data()
	);
}

OGLPLUS_LIB_FUNC
DSATextureEXTOps& DSATextureEXTOps::Image3D(
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
	return *this;
}

OGLPLUS_LIB_FUNC
DSATextureEXTOps& DSATextureEXTOps::SubImage3D(
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
	return *this;
}

OGLPLUS_LIB_FUNC
DSATextureEXTOps& DSATextureEXTOps::Image2D(
	TextureTarget tex_target,
	const images::Image& image,
	GLint level,
	GLint border
)
{
	OGLPLUS_GLFUNC(TextureImage2DEXT)(
		_name,
		GLenum(tex_target),
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
	return *this;
}

OGLPLUS_LIB_FUNC
DSATextureEXTOps& DSATextureEXTOps::SubImage2D(
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
	return *this;
}

OGLPLUS_LIB_FUNC
DSATextureEXTOps& DSATextureEXTOps::Image1D(
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
	return *this;
}

OGLPLUS_LIB_FUNC
DSATextureEXTOps& DSATextureEXTOps::SubImage1D(
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
	return *this;
}

OGLPLUS_LIB_FUNC
DSATextureEXTOps& DSATextureEXTOps::Image(
	Target tex_target,
	const images::Image& image,
	GLint level,
	GLint border
)
{
	switch(TextureTargetDimensions(tex_target))
	{
		case 3:
		{
			Image3D(image, level, border);
			break;
		}
		case 2:
		{
			Image2D(tex_target, image, level, border);
			break;
		}
		case 1:
		{
			Image1D(image, level, border);
			break;
		}
		default: assert(!"Invalid texture dimension");
	}
	return *this;
}

OGLPLUS_LIB_FUNC
DSATextureEXTOps& DSATextureEXTOps::Image(
	Target tex_target,
	const images::ImageSpec& image_spec,
	GLint level,
	GLint border
)
{
	switch(TextureTargetDimensions(tex_target))
	{
		case 3:
		{
			Image3D(
				level,
				image_spec.internal_format,
				image_spec.width,
				image_spec.height,
				image_spec.depth,
				border,
				image_spec.format,
				image_spec.data_type,
				image_spec.data_ptr
			);
			break;
		}
		case 2:
		{
			Image2D(
				target,
				level,
				image_spec.internal_format,
				image_spec.width,
				image_spec.height,
				border,
				image_spec.format,
				image_spec.data_type,
				image_spec.data_ptr
			);
			break;
		}
		case 1:
		{
			Image1D(
				level,
				image_spec.internal_format,
				image_spec.width,
				border,
				image_spec.format,
				image_spec.data_type,
				image_spec.data_ptr
			);
			break;
		}
		default: assert(!"Invalid texture dimension");
	}
	return *this;
}

#endif // GL_EXT_direct_state_access

} // namespace oglplus

