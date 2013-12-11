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

#if GL_VERSION_3_0

OGLPLUS_LIB_FUNC
void TextureOps::GetImage(
	Target target,
	GLint level,
	PixelDataFormat format,
	PixelDataType type,
	GLsizei size,
	GLvoid* buffer
)
{
#if GL_ARB_robustness
	OGLPLUS_GLFUNC(GetnTexImageARB)(
		GLenum(target),
		level,
		GLenum(format),
		GLenum(type),
		size,
		buffer
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		GetnTexImageARB,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
#else
	OGLPLUS_FAKE_USE(size);
	OGLPLUS_GLFUNC(GetTexImage)(
		GLenum(target),
		level,
		GLenum(format),
		GLenum(type),
		buffer
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		GetTexImage,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
#endif
}

OGLPLUS_LIB_FUNC
void TextureOps::GetCompressedImage(
	Target target,
	GLint level,
	GLsizei size,
	GLubyte* buffer
)
{
#if GL_ARB_robustness
	OGLPLUS_GLFUNC(GetnCompressedTexImageARB)(
		GLenum(target),
		level,
		size,
		buffer
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		GetnCompressedTexImageARB,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
#else
	OGLPLUS_FAKE_USE(size);
	OGLPLUS_GLFUNC(GetCompressedTexImage)(
		GLenum(target),
		level,
		buffer
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		GetCompressedTexImage,
		Texture,
		EnumValueName(target),
		BindingQuery<TextureOps>::QueryBinding(target)
	));
#endif
}

OGLPLUS_LIB_FUNC
void TextureOps::GetCompressedImage(
	Target target,
	GLint level,
	std::vector<GLubyte>& dest
)
{
	dest.resize(CompressedImageSize(target, level));
	GetCompressedImage(
		target,
		level,
		dest.size()*sizeof(GLubyte),
		dest.data()
	);
}

#endif

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

#if GL_VERSION_3_0

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

#endif // GL_VERSION_3_0

} // namespace oglplus

