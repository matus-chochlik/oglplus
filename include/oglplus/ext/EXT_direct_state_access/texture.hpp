/**
 *  @file oglplus/ext/EXT_direct_state_access/texture.hpp
 *  @brief Texture object wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_DSA_1107121519_HPP
#define OGLPLUS_TEXTURE_DSA_1107121519_HPP

#include <oglplus/texture.hpp>
#include <oglplus/ext/EXT_direct_state_access/buffer.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Wrapper for texture and texture unit-related operations
/** @note Do not use this class directly, use DSATextureEXT instead.
 *
 *  @glsymbols
 *  @glfunref{GenTextures}
 *  @glfunref{DeleteTextures}
 *  @glfunref{IsTexture}
 */
class DSATextureEXTOps
 : public Named
 , public BaseObject<true>
 , public FriendOf<DSABufferEXTOps>
{
public:
	/// Texture bind and image specification targets
	/** @note Not all of the values enumerated here are valid
	 *  bind targets. Some of them are just image specification
	 *  targets.
	 */
	typedef TextureTarget Target;
	Target target;
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenTextures)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenTextures));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteTextures)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsTexture)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_TEXTURE
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Texture;
	}
#endif

	friend class FriendOf<DSATextureEXTOps>;
public:
	/// Types related to Texture
	struct Property
	{
		/// Depth texture comparison mode
		typedef TextureCompareMode CompareMode;

		/// Filter
		typedef TextureFilter Filter;

		/// Maginification filter
		typedef TextureMagFilter MagFilter;

		/// Minification filter
		typedef TextureMinFilter MinFilter;

		/// Texture swizzle coordinate
		typedef TextureSwizzleCoord SwizzleCoord;

		/// Texture swizzle value
		typedef TextureSwizzle Swizzle;

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
		/// Texture swizzle tuple
		typedef TextureSwizzleTuple SwizzleTuple;
#endif

		/// Texture wrap mode for coordinate
		typedef TextureWrapCoord WrapCoord;

		/// Texture wrap mode value
		typedef TextureWrap Wrap;

		/// The pixel data type
		typedef OneOf<
			GLenum,
			std::tuple<
				DataType,
				PixelDataType
			>
		> PixDataType;
	};

	/// Specify active texture unit for subsequent commands
	/**
	 *  @throws Error
	 *
	 *  @see Bind
	 *
	 *  @glsymbols
	 *  @glfunref{ActiveTexture}
	 */
	static void Active(TextureUnitSelector index)
	{
		OGLPLUS_GLFUNC(ActiveTexture)(
			GLenum(GL_TEXTURE0 + GLuint(index))
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ActiveTexture));
	}

	/// Returns active texture unit
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{ACTIVE_TEXTURE}
	 */
	static GLint Active(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_ACTIVE_TEXTURE, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return GL_TEXTURE0 - result;
	}

	/// Bind this texture to this->target
	void Bind(void)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindTexture)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindTexture,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Bind this texture to the specified target
	/**
	 *  @throws Error
	 */
	void Bind(Target new_target)
	{
		target = new_target;
		Bind();
	}

	/// Unbinds the current texture from its target
	/**
	 *  @deprecated This function is deprecated and will be removed.
	 *  Use DefaultTexture::Bind instead.
	 *
	 *  @throws Error
	 *
	 *  @see Active
	 *  @see Bind
	 *
	 *  @glsymbols
	 *  @glfunref{BindTexture}
	 */
	void Unbind(void) const
	{
		OGLPLUS_GLFUNC(BindTexture)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindTexture));
	}

	GLint GetIntParam(GLenum query) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetTextureParameterivEXT)(
			_name,
			GLenum(target),
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	GLfloat GetFloatParam(GLenum query) const
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetTextureParameterfvEXT)(
			_name,
			GLenum(target),
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterfvEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	GLint GetIntParam(GLint level, GLenum query) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetTextureLevelParameterivEXT)(
			_name,
			GLenum(target),
			level,
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureLevelParameterivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	GLfloat GetFloatParam(GLint level, GLenum query) const
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetTextureLevelParameterfvEXT)(
			_name,
			GLenum(target),
			level,
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureLevelParameterfvEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	/// Returns the width of the texture as it was specified by *Image*D
	/**
	 *  @see Height
	 *  @see Depth
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_WIDTH}
	 */
	GLsizei Width(GLint level = 0) const
	{
		return GLsizei(GetIntParam(level, GL_TEXTURE_WIDTH));
	}

	/// Returns the height of the texture as it was specified by *Image*D
	/**
	 *  @see Width
	 *  @see Depth
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_HEIGHT}
	 */
	GLsizei Height(GLint level = 0) const
	{
		return GLsizei(GetIntParam(level, GL_TEXTURE_HEIGHT));
	}

	/// Returns the depth of the texture as it was specified by *Image*D
	/**
	 *  @see Width
	 *  @see Height
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_DEPTH}
	 */
	GLsizei Depth(GLint level = 0) const
	{
		return GLsizei(GetIntParam(level, GL_TEXTURE_DEPTH));
	}

	/// Returns the data type used to store the RED component
	/**
	 *  @see GreenType
	 *  @see BlueType
	 *  @see AlphaType
	 *  @see DepthType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_RED_TYPE}
	 */
	PixelDataType RedType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_RED_TYPE
		));
	}

	/// Returns the data type used to store the GREEN component
	/**
	 *  @see RedType
	 *  @see BlueType
	 *  @see AlphaType
	 *  @see DepthType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_GREEN_TYPE}
	 */
	PixelDataType GreenType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_GREEN_TYPE
		));
	}

	/// Returns the data type used to store the BLUE component
	/**
	 *  @see RedType
	 *  @see GreenType
	 *  @see AlphaType
	 *  @see DepthType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_BLUE_TYPE}
	 */
	PixelDataType BlueType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_BLUE_TYPE
		));
	}

	/// Returns the data type used to store the ALPHA component
	/**
	 *  @see RedType
	 *  @see GreenType
	 *  @see BlueType
	 *  @see DepthType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_ALPHA_TYPE}
	 */
	PixelDataType AlphaType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_ALPHA_TYPE
		));
	}

	/// Returns the data type used to store the DEPTH component
	/**
	 *  @see RedType
	 *  @see GreenType
	 *  @see BlueType
	 *  @see AlphaType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_DEPTH_TYPE}
	 */
	PixelDataType DepthType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_DEPTH_TYPE
		));
	}

	/// Returns the actual resolution of the RED component
	/**
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_RED_SIZE}
	 */
	GLsizei RedSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_RED_SIZE
		));
	}

	/// Returns the actual resolution of the GREEN component
	/**
	 *  @see RedSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_GREEN_SIZE}
	 */
	GLsizei GreenSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_GREEN_SIZE
		));
	}

	/// Returns the actual resolution of the BLUE component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_BLUE_SIZE}
	 */
	GLsizei BlueSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_BLUE_SIZE
		));
	}

	/// Returns the actual resolution of the ALPHA component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_ALPHA_SIZE}
	 */
	GLsizei AlphaSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_ALPHA_SIZE
		));
	}

	/// Returns the actual resolution of the DEPTH component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_DEPTH_SIZE}
	 */
	GLsizei DepthSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_DEPTH_SIZE
		));
	}

	/// Returns the actual resolution of the STENCIL component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_STENCIL_SIZE}
	 */
	GLsizei StencilSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_STENCIL_SIZE
		));
	}

	/// Returns the size of all texture components
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_SHARED_SIZE}
	 */
	GLsizei SharedSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_SHARED_SIZE
		));
	}

	/// Returns the size (in bytes) of the image array if it is compressed
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_COMPRESSED_IMAGE_SIZE}
	 */
	GLsizei CompressedImageSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_COMPRESSED_IMAGE_SIZE
		));
	}

	/// Returns the internal data format of the image array
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_INTERNAL_FORMAT}
	 */
	PixelDataInternalFormat InternalFormat(GLint level = 0) const
	{
		return PixelDataInternalFormat(GetIntParam(
			level,
			GL_TEXTURE_INTERNAL_FORMAT
		));
	}

	/// Allows to obtain the texture image in uncompressed form
	/** This function stores the image of the texture bound to
	 *  the specified texture @p target with the specified @p level
	 *  of detail in uncompressed form into the @p dest buffer.
	 *
	 *  @note This function, unlike @c GetCompressedImage, does NOT
	 *  automatically resize the destination buffer so that
	 *  it can accomodate the texture data. The caller is responsible
	 *  for keeping track or querying the type of the texture, its
	 *  dimensions and current pixel transfer settings and resize
	 *  the @c dest buffer accordingly.
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexImage}
	 */
	void GetImage(
		GLint level,
		PixelDataFormat format,
		Property::PixDataType type,
		GLsizei size,
		GLvoid* buffer
	) const;

	/// Allows to obtain the texture image in uncompressed form
	/** This function stores the image of the texture bound to
	 *  the specified texture @p target with the specified @p level
	 *  of detail in uncompressed form into the @p dest buffer.
	 *
	 *  @note This function, unlike @c GetCompressedImage, does NOT
	 *  automatically resize the destination buffer so that
	 *  it can accomodate the texture data. The caller is responsible
	 *  for keeping track or querying the type of the texture, its
	 *  dimensions and current pixel transfer settings and resize
	 *  the @c dest buffer accordingly.
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexImage}
	 */
	template <typename T>
	void GetImage(
		GLint level,
		PixelDataFormat format,
		std::vector<T>& dest
	) const
	{
		GetImage(
			level,
			format,
			GetDataType<T>(),
			dest.size()*sizeof(T),
			dest.data()
		);
	}

	/// Allows to obtain the texture image in compressed form
	/** This function stores the image of the texture bound to
	 *  the specified texture @p target with the specified @p level
	 *  of detail in compressed form into the @p dest buffer.
	 *  This function automatically resizes the buffer so that
	 *  it can accomodate the texture data.
	 *
	 *  @glsymbols
	 *  @glfunref{GetCompressedTexImage}
	 */
	void GetCompressedImage(
		GLint level,
		GLsizei size,
		GLubyte* buffer
	) const;

	/// Allows to obtain the texture image in compressed form
	/** This function stores the image of the texture bound to
	 *  the specified texture @p target with the specified @p level
	 *  of detail in compressed form into the @p dest buffer.
	 *  This function automatically resizes the buffer so that
	 *  it can accomodate the texture data.
	 *
	 *  @glsymbols
	 *  @glfunref{GetCompressedTexImage}
	 */
	void GetCompressedImage(
		GLint level,
		std::vector<GLubyte>& dest
	) const;

	/// Specifies a three dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 */
	DSATextureEXTOps& Image3D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage3DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			depth,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a three dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 */
	DSATextureEXTOps& Image3D(
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	);

	/// Specifies a three dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage3D}
	 */
	DSATextureEXTOps& SubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage3DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			zoffs,
			width,
			height,
			depth,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a three dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage3D}
	 */
	DSATextureEXTOps& SubImage3D(
		const images::Image& image,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint level = 0
	);

	/// Specifies a two dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 */
	DSATextureEXTOps& Image2D(
		TextureTarget tex_target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage2DEXT)(
			_name,
			GLenum(tex_target),
			level,
			GLint(internal_format),
			width,
			height,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	DSATextureEXTOps& Image2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	)
	{
		return Image2D(
			target,
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

	/// Specifies a two dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 */
	DSATextureEXTOps& Image2D(
		TextureTarget tex_target,
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	);

	/// Specifies a two dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 */
	DSATextureEXTOps& Image2D(
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		return Image2D(target, image, level, border);
	}

	/// Specifies the image of the specified cube-map face
	/**
	 *  @pre (face >= 0) && (face <= 5)
	 *
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 *  @gldefref{TEXTURE_CUBE_MAP_POSITIVE_X}
	 *  @gldefref{TEXTURE_CUBE_MAP_NEGATIVE_X}
	 *  @gldefref{TEXTURE_CUBE_MAP_POSITIVE_Y}
	 *  @gldefref{TEXTURE_CUBE_MAP_NEGATIVE_Y}
	 *  @gldefref{TEXTURE_CUBE_MAP_POSITIVE_Z}
	 *  @gldefref{TEXTURE_CUBE_MAP_NEGATIVE_Z}
	 */
	DSATextureEXTOps& ImageCM(
		GLuint face,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	)
	{
		assert(face <= 5);
		OGLPLUS_GLFUNC(TextureImage2DEXT)(
			_name,
			GLenum(GL_TEXTURE_CUBE_MAP_POSITIVE_X+face),
			level,
			GLint(internal_format),
			width,
			height,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage2DEXT,
			Texture,
			EnumValueName(Target(GL_TEXTURE_CUBE_MAP_POSITIVE_X+face)),
			_name
		));
		return *this;
	}

	/// Specifies the image of the specified cube-map face
	/**
	 *  @pre (face >= 0) && (face <= 5)
	 *
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 *  @gldefref{TEXTURE_CUBE_MAP_POSITIVE_X}
	 *  @gldefref{TEXTURE_CUBE_MAP_NEGATIVE_X}
	 *  @gldefref{TEXTURE_CUBE_MAP_POSITIVE_Y}
	 *  @gldefref{TEXTURE_CUBE_MAP_NEGATIVE_Y}
	 *  @gldefref{TEXTURE_CUBE_MAP_POSITIVE_Z}
	 *  @gldefref{TEXTURE_CUBE_MAP_NEGATIVE_Z}
	 */
	DSATextureEXTOps& ImageCM(
		GLuint face,
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		assert(face <= 5);
		return Image2D(
			Target(GL_TEXTURE_CUBE_MAP_POSITIVE_X+face),
			image,
			level,
			border
		);
	}

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage2D}
	 */
	DSATextureEXTOps& SubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage2DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			width,
			height,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage2D}
	 */
	DSATextureEXTOps& SubImage2D(
		const images::Image& image,
		GLint xoffs,
		GLint yoffs,
		GLint level = 0
	);

	/// Specifies a one dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage1D}
	 */
	DSATextureEXTOps& Image1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage1DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a one dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage1D}
	 */
	DSATextureEXTOps& Image1D(
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	);

	/// Specifies a one dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage1D}
	 */
	DSATextureEXTOps& SubImage1D(
		GLint level,
		GLint xoffs,
		GLsizei width,
		PixelDataFormat format,
		Property::PixDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage1DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			width,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage1D}
	 */
	DSATextureEXTOps& SubImage1D(
		const images::Image& image,
		GLint xoffs,
		GLint level = 0
	);

	/// Specifies a texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 *  @glfunref{TexImage2D}
	 *  @glfunref{TexImage1D}
	 */
	DSATextureEXTOps& Image(
		Target tex_target,
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	);

	/// Specifies a texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 *  @glfunref{TexImage2D}
	 *  @glfunref{TexImage1D}
	 */
	DSATextureEXTOps& Image(
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		return Image(target, image, level, border);
	}

	/// Specifies a texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 *  @glfunref{TexImage2D}
	 *  @glfunref{TexImage1D}
	 */
	DSATextureEXTOps& Image(
		Target tex_target,
		const images::ImageSpec& image_spec,
		GLint level = 0,
		GLint border = 0
	);

	/// Specifies a texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 *  @glfunref{TexImage2D}
	 *  @glfunref{TexImage1D}
	 */
	DSATextureEXTOps& Image(
		const images::ImageSpec& image_spec,
		GLint level = 0,
		GLint border = 0
	)
	{
		return Image(target, image_spec, level, border);
	}

	/// Copies a two dimensional texture image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexImage2D}
	 */
	DSATextureEXTOps& CopyImage2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height,
		GLint border
	)
	{
		OGLPLUS_GLFUNC(CopyTextureImage2DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			x,
			y,
			width,
			height,
			border
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Copies a one dimensional texture image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexImage1D}
	 */
	DSATextureEXTOps& CopyImage1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLint border
	)
	{
		OGLPLUS_GLFUNC(CopyTextureImage1DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			x,
			y,
			width,
			border
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Copies a three dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage3D}
	 */
	DSATextureEXTOps& CopySubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage3DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			zoffs,
			x,
			y,
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Copies a two dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage2D}
	 */
	DSATextureEXTOps& CopySubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage2DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			x,
			y,
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Copies a one dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage1D}
	 */
	DSATextureEXTOps& CopySubImage1D(
		GLint level,
		GLint xoffs,
		GLint x,
		GLint y,
		GLsizei width
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage1DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			x,
			y,
			width
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a three dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage3D}
	 */
	DSATextureEXTOps& CompressedImage3D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureImage3DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			depth,
			border,
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a two dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage2D}
	 */
	DSATextureEXTOps& CompressedImage2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureImage2DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			border,
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a one dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage1D}
	 */
	DSATextureEXTOps& CompressedImage1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureImage1DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			border,
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a three dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage3D}
	 */
	DSATextureEXTOps& CompressedSubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		PixelDataFormat format,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureSubImage3DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			zoffs,
			width,
			height,
			depth,
			GLint(format),
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a two dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage2D}
	 */
	DSATextureEXTOps& CompressedSubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		PixelDataFormat format,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureSubImage2DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			width,
			height,
			GLint(format),
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Specifies a one dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage1D}
	 */
	DSATextureEXTOps& CompressedSubImage1D(
		GLint level,
		GLint xoffs,
		GLsizei width,
		PixelDataFormat format,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureSubImage1DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			width,
			GLint(format),
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
	/// Assigns a buffer storing the texel data to the texture
	/**
	 *  @glverreq{3,1}
	 *  @glsymbols
	 *  @glfunref{TexBuffer}
	 */
	DSATextureEXTOps& Buffer(
		PixelDataInternalFormat internal_format,
		const DSABufferEXTOps& buffer
	)
	{
		OGLPLUS_GLFUNC(TextureBufferEXT)(
			_name,
			GLenum(target),
			GLenum(internal_format),
			FriendOf<DSABufferEXTOps>::GetName(buffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureBufferEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	DSATextureEXTOps& Buffer(
		PixelDataInternalFormat internal_format,
		const BufferOps& buffer
	)
	{
		return Buffer(internal_format, Managed<DSABufferEXTOps>(buffer));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY ||GL_VERSION_4_3 ||GL_ARB_texture_view
	/// References and reinteprets a subset of the data of another texture
	/**
	 *  @glvoereq{4,3,ARB,texture_view}
	 *  @glsymbols
	 *  @glfunref{TextureView}
	 */
	DSATextureEXTOps& View(
		const DSATextureEXTOps& orig_texture,
		PixelDataInternalFormat internal_format,
		GLuint min_level,
		GLuint num_levels,
		GLuint min_layer,
		GLuint num_layers
	)
	{
		OGLPLUS_GLFUNC(TextureView)(
			_name,
			GLenum(target),
			orig_texture._name,
			GLenum(internal_format),
			min_level,
			num_levels,
			min_layer,
			num_layers
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureView,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY ||GL_VERSION_4_2 ||GL_ARB_shader_image_load_store
	/// Binds a @p level of this texture to an image @p unit
	/**
	 *  @glvoereq{4,2,ARB,shader_image_load_store}
	 *  @glsymbols
	 *  @glfunref{BindImageTexture}
	 */
	DSATextureEXTOps& BindImage(
		ImageUnitSelector unit,
		GLint level,
		bool layered,
		GLint layer,
		AccessSpecifier access,
		ImageUnitFormat format
	)
	{
		OGLPLUS_GLFUNC(BindImageTexture)(
			GLuint(unit),
			_name,
			level,
			layered? GL_TRUE : GL_FALSE,
			layer,
			GLenum(access),
			GLenum(format)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BindImageTexture,
			Texture,
			nullptr,
			_name
		));
		return *this;
	}
#endif

	/// Returns the texture base level (TEXTURE_BASE_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BASE_LEVEL}
	 */
	GLuint BaseLevel(void) const
	{
		return GetIntParam(GL_TEXTURE_BASE_LEVEL);
	}

	/// Sets the texture base level (TEXTURE_BASE_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BASE_LEVEL}
	 */
	DSATextureEXTOps& BaseLevel(GLuint level)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BASE_LEVEL,
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLfloat, 4> BorderColor(TypeTag<GLfloat>) const
	{
		GLfloat result[4];
		OGLPLUS_GLFUNC(GetTextureParameterfvEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterfvEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return Vector<GLfloat, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	DSATextureEXTOps& BorderColor(Vector<GLfloat, 4> color)
	{
		OGLPLUS_GLFUNC(TextureParameterfvEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfvEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLint, 4> BorderColor(TypeTag<GLint>) const
	{
		GLint result[4];
		OGLPLUS_GLFUNC(GetTextureParameterIivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterIivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return Vector<GLint, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	DSATextureEXTOps& BorderColor(Vector<GLint, 4> color)
	{
		OGLPLUS_GLFUNC(TextureParameterIivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterIivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLuint, 4> BorderColor(TypeTag<GLuint>) const
	{
		GLuint result[4];
		OGLPLUS_GLFUNC(GetTextureParameterIuivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterIuivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return Vector<GLuint, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	DSATextureEXTOps& BorderColor(Vector<GLuint, 4> color)
	{
		OGLPLUS_GLFUNC(TextureParameterIuivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterIuivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the compare mode (TEXTURE_COMPARE_MODE)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_COMPARE_MODE}
	 */
	TextureCompareMode CompareMode(void) const
	{
		return TextureCompareMode(GetIntParam(
			GL_TEXTURE_COMPARE_MODE
		));
	}

	/// Sets the compare mode (TEXTURE_COMPARE_MODE)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_COMPARE_MODE}
	 */
	DSATextureEXTOps& CompareMode(TextureCompareMode mode)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_COMPARE_MODE,
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_COMPARE_FUNC}
	 */
	CompareFunction CompareFunc(void) const
	{
		return CompareFunction(GetIntParam(
			GL_TEXTURE_COMPARE_FUNC
		));
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_COMPARE_FUNC}
	 */
	DSATextureEXTOps& CompareFunc(CompareFunction func)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_COMPARE_FUNC,
			GLenum(func)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the LOD bias value (TEXTURE_LOD_BIAS)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_LOD_BIAS}
	 */
	GLfloat LODBias(void) const
	{
		return GetFloatParam(GL_TEXTURE_LOD_BIAS);
	}

	/// Sets the LOD bias value (TEXTURE_LOD_BIAS)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_LOD_BIAS}
	 */
	DSATextureEXTOps& LODBias(GLfloat value)
	{
		OGLPLUS_GLFUNC(TextureParameterfEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_LOD_BIAS,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Sets both the minification and maginification filter
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	DSATextureEXTOps& Filter(TextureFilter filter)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the magnification filter (TEXTURE_MAG_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	TextureMagFilter MagFilter(void) const
	{
		return TextureMagFilter(GetIntParam(
			GL_TEXTURE_MAG_FILTER
		));
	}

	/// Sets the magnification filter (TEXTURE_MAG_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	DSATextureEXTOps& MagFilter(TextureMagFilter filter)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the minification filter (TEXTURE_MIN_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 */
	TextureMinFilter MinFilter(void) const
	{
		return TextureMinFilter(GetIntParam(
			GL_TEXTURE_MIN_FILTER
		));
	}

	/// Sets the minification filter (TEXTURE_MIN_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 */
	DSATextureEXTOps& MinFilter(TextureMinFilter filter)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets minimal LOD value (TEXTURE_MIN_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MIN_LOD}
	 */
	GLfloat MinLOD(void) const
	{
		return GetFloatParam(GL_TEXTURE_MIN_LOD);
	}

	/// Sets minimal LOD value (TEXTURE_MIN_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MIN_LOD}
	 */
	DSATextureEXTOps& MinLOD(GLfloat value)
	{
		OGLPLUS_GLFUNC(TextureParameterfEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MIN_LOD,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets maximum LOD value (TEXTURE_MAX_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAX_LOD}
	 */
	GLfloat MaxLOD(void) const
	{
		return GetFloatParam(GL_TEXTURE_MAX_LOD);
	}

	/// Sets maximum LOD value (TEXTURE_MAX_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAX_LOD}
	 */
	DSATextureEXTOps& MaxLOD(GLfloat value)
	{
		OGLPLUS_GLFUNC(TextureParameterfEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAX_LOD,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets maximum level value (TEXTURE_MAX_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAX_LEVEL}
	 */
	GLint MaxLevel(void) const
	{
		return GetIntParam(GL_TEXTURE_MAX_LEVEL);
	}

	/// Sets maximum level value (TEXTURE_MAX_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAX_LEVEL}
	 */
	DSATextureEXTOps& MaxLevel(GLint value)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAX_LEVEL,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the maximum anisotropy level
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{MAX_TEXTURE_MAX_ANISOTROPY_EXT}
	 */
	GLfloat MaxAnisotropy(void) const
	{
#ifdef  GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
		return GetFloatParam(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);
#else
		return GLfloat(1);
#endif
	}

	/// Gets the current anisotropy level
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAX_ANISOTROPY_EXT}
	 */
	GLfloat Anisotropy(void) const
	{
#ifdef  GL_TEXTURE_MAX_ANISOTROPY_EXT
		return GetFloatParam(GL_TEXTURE_MAX_ANISOTROPY_EXT);
#else
		return GLfloat(1);
#endif
	}

	/// Sets the anisotropy level
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAX_ANISOTROPY_EXT}
	 */
	DSATextureEXTOps& Anisotropy(GLfloat value)
	{
#ifdef  GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
		OGLPLUS_GLFUNC(TextureParameterfEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAX_ANISOTROPY_EXT,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfEXT,
			Texture,
			EnumValueName(target),
			_name
		));
#else
		OGLPLUS_FAKE_USE(value);
#endif
		return *this;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3 || GL_ARB_texture_swizzle
	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_*)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 */
	TextureSwizzle Swizzle(TextureSwizzleCoord coord) const
	{
		return TextureSwizzle(GetIntParam(
			GLenum(coord)
		));
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_*)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 */
	DSATextureEXTOps& Swizzle(
		TextureSwizzleCoord coord,
		TextureSwizzle mode
	)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_R)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_R}
	 */
	TextureSwizzle SwizzleR(void) const
	{
		return Swizzle(TextureSwizzleCoord::R);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_R)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_R}
	 */
	DSATextureEXTOps& SwizzleR(TextureSwizzle mode)
	{
		return Swizzle(TextureSwizzleCoord::R, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_G)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_G}
	 */
	TextureSwizzle SwizzleG(void) const
	{
		return Swizzle(TextureSwizzleCoord::G);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_G)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_G}
	 */
	DSATextureEXTOps& SwizzleG(TextureSwizzle mode)
	{
		return Swizzle(TextureSwizzleCoord::G, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_B)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_B}
	 */
	TextureSwizzle SwizzleB(void) const
	{
		return Swizzle(TextureSwizzleCoord::B);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_B)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_B}
	 */
	DSATextureEXTOps& SwizzleB(TextureSwizzle mode)
	{
		return Swizzle(TextureSwizzleCoord::B, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_A)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_A}
	 */
	TextureSwizzle SwizzleA(void) const
	{
		return Swizzle(TextureSwizzleCoord::A);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_A)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_A}
	 */
	DSATextureEXTOps& SwizzleA(TextureSwizzle mode)
	{
		return Swizzle(TextureSwizzleCoord::A, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_RGBA}
	 */
	TextureSwizzleTuple SwizzleRGBA(void) const
	{
		TextureSwizzleTuple result;
		OGLPLUS_GLFUNC(GetTextureParameterivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_SWIZZLE_RGBA,
			result._values
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_RGBA}
	 */
	DSATextureEXTOps& SwizzleRGBA(TextureSwizzle mode)
	{
		GLint m = GLint(GLenum(mode));
		GLint params[4] = {m, m, m, m};
		OGLPLUS_GLFUNC(TextureParameterivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_SWIZZLE_RGBA,
			params
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_RGBA}
	 */
	DSATextureEXTOps& SwizzleRGBA(
		TextureSwizzle mode_r,
		TextureSwizzle mode_g,
		TextureSwizzle mode_b,
		TextureSwizzle mode_a
	)
	{
		GLint params[4] = {
			GLint(GLenum(mode_r)),
			GLint(GLenum(mode_g)),
			GLint(GLenum(mode_b)),
			GLint(GLenum(mode_a))
		};
		OGLPLUS_GLFUNC(TextureParameterivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_SWIZZLE_RGBA,
			params
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_RGBA}
	 */
	DSATextureEXTOps& SwizzleRGBA(const TextureSwizzleTuple& modes)
	{
		OGLPLUS_GLFUNC(TextureParameterivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_SWIZZLE_RGBA,
			modes._values
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}
#endif // texture swizzle

	/// Gets the wrap parameter (TEXTURE_WRAP_*)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 */
	TextureWrap Wrap(TextureWrapCoord coord) const
	{
		return TextureWrap(GetIntParam(GLenum(coord)));
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_*)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 */
	DSATextureEXTOps& Wrap(
		TextureWrapCoord coord,
		TextureWrap mode
	)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_S)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_S}
	 */
	TextureWrap WrapS(void) const
	{
		return Wrap(TextureWrapCoord::S);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_S)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_S}
	 */
	DSATextureEXTOps& WrapS(TextureWrap mode)
	{
		return Wrap(TextureWrapCoord::S, mode);
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_T)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_T}
	 */
	TextureWrap WrapT(void) const
	{
		return Wrap(TextureWrapCoord::T);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_T)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_T}
	 */
	DSATextureEXTOps& WrapT(TextureWrap mode)
	{
		return Wrap(TextureWrapCoord::T, mode);
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_R)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_R}
	 */
	TextureWrap WrapR(void) const
	{
		return Wrap(TextureWrapCoord::R);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_R)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_R}
	 */
	DSATextureEXTOps& WrapR(TextureWrap mode)
	{
		return Wrap(TextureWrapCoord::R, mode);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
	/// Gets the depth stencil mode parameter (DEPTH_STENCIL_TEXTURE_MODE)
	/**
	 *  @glverreq{4,3}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{DEPTH_STENCIL_TEXTURE_MODE}
	 */
	PixelDataFormat DepthStencilMode(void) const
	{
		return PixelDataFormat(GetIntParam(
			GL_DEPTH_STENCIL_TEXTURE_MODE
		));
	}

	/// Sets the swizzle parameter (DEPTH_STENCIL_TEXTURE_MODE)
	/**
	 *  @glverreq{4,3}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{DEPTH_STENCIL_TEXTURE_MODE}
	 */
	DSATextureEXTOps& DepthStencilMode(PixelDataFormat mode)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_DEPTH_STENCIL_TEXTURE_MODE,
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_seamless_cubemap_per_texture
	/// Gets the seamless cubemap setting value
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_CUBE_MAP_SEAMLESS}
	 */
	bool Seamless(void) const
	{
		return GetIntParam(GL_TEXTURE_CUBE_MAP_SEAMLESS) == GL_TRUE;
	}

	/// Sets the seamless cubemap setting
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_CUBE_MAP_SEAMLESS}
	 */
	DSATextureEXTOps& Seamless(bool enable)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			GLenum(target),
			_name,
			GL_TEXTURE_CUBE_MAP_SEAMLESS,
			enable?GL_TRUE:GL_FALSE
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}
#endif

	/// Generate mipmap for the texture bound to the specified target
	/**
	 *  @glsymbols
	 *  @glfunref{GenerateMipmap}
	 */
	DSATextureEXTOps& GenerateMipmap(void)
	{
		OGLPLUS_GLFUNC(GenerateTextureMipmapEXT)(
			_name,
			GLenum(target)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GenerateTextureMipmapEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return *this;
	}

	// Utility functions:

	/// Returns the target for the i-th cube map @p face (0-5)
	/** This functions returns one of the values for cube map faces
	 *  from the Target enumeration. The value of @p face must
	 *  be between 0 and 5 with the following meaning:
	 *  0 = Target::CubeMapPositiveX,
	 *  1 = Target::CubeMapNegativeX,
	 *  2 = Target::CubeMapPositiveY,
	 *  3 = Target::CubeMapNegativeY,
	 *  4 = Target::CubeMapPositiveZ,
	 *  5 = Target::CubeMapNegativeZ.
	 */
	static Target CubeMapFace(GLuint face)
	{
		assert(face <= 5);
		return Target(GL_TEXTURE_CUBE_MAP_POSITIVE_X+face);
	}
};

// Helper class for syntax-sugar operators
struct DSATextureEXTOpsAndSlot
{
	DSATextureEXTOps& tex;
	GLint slot;

	DSATextureEXTOpsAndSlot(DSATextureEXTOps& t, GLint s)
	 : tex(t)
	 , slot(s)
	{ }
};

// syntax sugar operators
inline DSATextureEXTOpsAndSlot operator | (
	DSATextureEXTOps& tex,
	GLuint slot
)
{
	return DSATextureEXTOpsAndSlot(tex, slot);
}

// Bind
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	TextureTarget target
)
{
	tex.Bind(target);
	return tex;
}

// Filter
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	TextureFilter filter
)
{
	tex.Filter(filter);
	return tex;
}

// MinFilter
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	TextureMinFilter filter
)
{
	tex.MinFilter(filter);
	return tex;
}

// MagFilter
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	TextureMagFilter filter
)
{
	tex.MagFilter(filter);
	return tex;
}

// CompareMode
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	TextureCompareMode mode
)
{
	tex.CompareMode(mode);
	return tex;
}

// CompareFunc
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	CompareFunction func
)
{
	tex.CompareFunc(func);
	return tex;
}

// Wrap
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	TextureWrap wrap
)
{
	switch(TextureTargetDimensions(tex.target))
	{
		case 3: tex.WrapR(wrap);
		case 2: tex.WrapT(wrap);
		case 1: tex.WrapS(wrap);
		case 0: break;
		default: assert(!"Invalid texture wrap dimension");
	}
	return tex;
}

// Wrap
inline DSATextureEXTOps& operator << (
	DSATextureEXTOpsAndSlot tas,
	TextureWrap wrap
)
{
	switch(tas.slot)
	{
		case 0: tas.tex.WrapS(wrap); break;
		case 1: tas.tex.WrapT(wrap); break;
		case 2: tas.tex.WrapR(wrap); break;
		default: assert(!"Invalid texture wrap slot");
	}
	return tas.tex;
}

// Swizzle
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	TextureSwizzle swizzle
)
{
	tex.SwizzleRGBA(swizzle);
	return tex;
}

// Swizzle
inline DSATextureEXTOps& operator << (
	DSATextureEXTOpsAndSlot tas,
	TextureSwizzle swizzle
)
{
	switch(tas.slot)
	{
		case 0: tas.tex.SwizzleR(swizzle); break;
		case 1: tas.tex.SwizzleG(swizzle); break;
		case 2: tas.tex.SwizzleB(swizzle); break;
		case 3: tas.tex.SwizzleA(swizzle); break;
		default: assert(!"Invalid texture swizzle slot");
	}
	return tas.tex;
}

// BorderColor
template <typename T>
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	const Vector<T, 4>& col
)
{
	tex.BorderColor(col);
	return tex;
}

// Image
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	const images::Image& image
)
{
	tex.Image(image);
	return tex;
}

// Image
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	const images::ImageSpec& image_spec
)
{
	tex.Image(image_spec);
	return tex;
}

// Image + Level
inline DSATextureEXTOps& operator << (
	DSATextureEXTOpsAndSlot tas,
	const images::Image& image
)
{
	tas.tex.Image(image, tas.slot);
	return tas.tex;
}

// Image + Level
inline DSATextureEXTOps& operator << (
	DSATextureEXTOpsAndSlot tas,
	const images::ImageSpec& image_spec
)
{
	tas.tex.Image(image_spec, tas.slot);
	return tas.tex;
}

// GenerateMipmaps
inline DSATextureEXTOps& operator << (
	DSATextureEXTOps& tex,
	TextureMipmap
)
{
	tex.GenerateMipmap();
	return tex;
}

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL DSA texture functionality
/**
 *  @ingroup oglplus_objects
 */
class DSATextureEXT
 : public DSATextureEXTOps
{ };
#else
typedef Object<DSATextureEXTOps> DSATextureEXT;
#endif

template <>
struct NonDSAtoDSA<TextureOps>
{
	typedef DSATextureEXTOps Type;
};

template <>
struct DSAtoNonDSA<DSATextureEXTOps>
{
	typedef TextureOps Type;
};

template <>
class ConvertibleObjectBaseOps<TextureOps, DSATextureEXTOps>
 : public std::true_type
{ };

template <>
class ConvertibleObjectBaseOps<DSATextureEXTOps, TextureOps>
 : public std::true_type
{ };

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/ext/EXT_direct_state_access/texture.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
