/**
 *  @file oglplus/texture.hpp
 *  @brief Texture object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXTURE_1107121519_HPP
#define OGLPLUS_TEXTURE_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/error.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/compare_func.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/access_specifier.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/texture_unit.hpp>
#include <oglplus/image.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/auxiliary/binding_query.hpp>
#include <cassert>

namespace oglplus {

/// Texture compare mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_COMPARE_MODE}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureCompareMode, GLenum)
#include <oglplus/enums/texture_compare_mode.ipp>
OGLPLUS_ENUM_CLASS_END


#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_compare_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_compare_mode_range.ipp>
#endif

/// Texture magnification filter enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_MAG_FILTER}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureMagFilter, GLenum)
#include <oglplus/enums/texture_mag_filter.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_mag_filter_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_mag_filter_range.ipp>
#endif

/// Texture minification filter enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_MIN_FILTER}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureMinFilter, GLenum)
#include <oglplus/enums/texture_min_filter.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_min_filter_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_min_filter_range.ipp>
#endif

/// Texture swizzle parameter coordinate enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureSwizzleCoord, GLenum)
#include <oglplus/enums/texture_swizzle_coord.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_swizzle_coord_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_swizzle_coord_range.ipp>
#endif

/// Texture swizzle enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_SWIZZLE_S}
 *  @gldefref{TEXTURE_SWIZZLE_T}
 *  @gldefref{TEXTURE_SWIZZLE_R}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureSwizzle, GLenum)
#include <oglplus/enums/texture_swizzle.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_swizzle_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_swizzle_range.ipp>
#endif

/// Texture wrap parameter coordinate enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureWrapCoord, GLenum)
#include <oglplus/enums/texture_wrap_coord.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_wrap_coord_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_wrap_coord_range.ipp>
#endif

/// Texture wrap enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_WRAP_S}
 *  @gldefref{TEXTURE_WRAP_T}
 *  @gldefref{TEXTURE_WRAP_R}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureWrap, GLenum)
#include <oglplus/enums/texture_wrap.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_wrap_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_wrap_range.ipp>
#endif

/// Texture bind and image specification targets
/** @note Not all of the values enumerated here are valid
 *  bind targets. Some of them are just image specification
 *  targets.
 *
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureTarget, GLenum)
#include <oglplus/enums/texture_target.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_target_range.ipp>
#endif

/// Wrapper for texture and texture unit-related operations
/** @note Do not use this class directly, use Texture instead.
 *
 *  @glsymbols
 *  @glfunref{GenTextures}
 *  @glfunref{DeleteTextures}
 *  @glfunref{IsTexture}
 */
class TextureOps
 : public Named
 , public BaseObject<true>
 , public FriendOf<BufferOps>
{
public:
	/// Texture bind and image specification targets
	/** @note Not all of the values enumerated here are valid
	 *  bind targets. Some of them are just image specification
	 *  targets.
	 */
	typedef TextureTarget Target;
protected:
	static void _init(GLsizei count, GLuint* _name, std::true_type)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		try{OGLPLUS_GLFUNC(GenTextures)(count, _name);}
		catch(...){ }
	}

	static void _init(GLsizei count, GLuint* _name, std::false_type)
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

	static void _bind(GLuint _name, Target target)
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

	friend class FriendOf<TextureOps>;

	static GLenum _binding_query(Target target)
	{
		switch(GLenum(target))
		{
#include <oglplus/enums/texture_target_bq.ipp>
			default:;
		}
		return 0;
	}
	friend class BindingQuery<TextureOps>;
public:
	/// Types related to Texture
	struct Property
	{
		/// Depth texture comparison mode
		typedef TextureCompareMode CompareMode;

		/// Maginification filter
		typedef TextureMagFilter MagFilter;

		/// Minification filter
		typedef TextureMinFilter MinFilter;

		/// Texture swizzle coordinate
		typedef TextureSwizzleCoord SwizzleCoord;

		/// Texture swizzle value
		typedef TextureSwizzle Swizzle;

		/// Texture wrap mode for coordinate
		typedef TextureWrapCoord WrapCoord;

		/// Texture wrap mode value
		typedef TextureWrap Wrap;
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

	/// Bind the texture to the target on the Active unit
	/**
	 *  @throws Error
	 *
	 *  @see Active
	 *  @see Unbind
	 *
	 *  @glsymbols
	 *  @glfunref{BindTexture}
	 */
	void Bind(Target target) const
	{
		_bind(_name, target);
	}

	/// Unbinds the current texture from the target on the Active unit
	/**
	 *  @throws Error
	 *
	 *  @see Active
	 *  @see Bind
	 *
	 *  @glsymbols
	 *  @glfunref{BindTexture}
	 */
	static void Unbind(Target target)
	{
		OGLPLUS_GLFUNC(BindTexture)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindTexture));
	}

	static GLint GetIntParam(Target target, GLenum query)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetTexParameteriv)(
			GLenum(target),
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTexParameteriv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
		return result;
	}

	static GLfloat GetFloatParam(Target target, GLenum query)
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetTexParameterfv)(
			GLenum(target),
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTexParameterfv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
		return result;
	}

	static GLint GetIntParam(Target target, GLint level, GLenum query)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetTexLevelParameteriv)(
			GLenum(target),
			level,
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTexLevelParameteriv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
		return result;
	}

	static GLfloat GetFloatParam(Target target, GLint level, GLenum query)
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetTexLevelParameterfv)(
			GLenum(target),
			level,
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTexLevelParameterfv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
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
	static GLsizei Width(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(target, level, GL_TEXTURE_WIDTH));
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
	static GLsizei Height(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(target, level, GL_TEXTURE_HEIGHT));
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
	static GLsizei Depth(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(target, level, GL_TEXTURE_DEPTH));
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
	static PixelDataType RedType(Target target, GLint level = 0)
	{
		return PixelDataType(GetIntParam(
			target,
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
	static PixelDataType GreenType(Target target, GLint level = 0)
	{
		return PixelDataType(GetIntParam(
			target,
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
	static PixelDataType BlueType(Target target, GLint level = 0)
	{
		return PixelDataType(GetIntParam(
			target,
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
	static PixelDataType AlphaType(Target target, GLint level = 0)
	{
		return PixelDataType(GetIntParam(
			target,
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
	static PixelDataType DepthType(Target target, GLint level = 0)
	{
		return PixelDataType(GetIntParam(
			target,
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
	static GLsizei RedSize(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(
			target,
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
	static GLsizei GreenSize(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(
			target,
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
	static GLsizei BlueSize(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(
			target,
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
	static GLsizei AlphaSize(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(
			target,
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
	static GLsizei DepthSize(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(
			target,
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
	static GLsizei StencilSize(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(
			target,
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
	static GLsizei SharedSize(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(
			target,
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
	static GLsizei CompressedImageSize(Target target, GLint level = 0)
	{
		return GLsizei(GetIntParam(
			target,
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
	static PixelDataInternalFormat InternalFormat(
		Target target,
		GLint level = 0
	)
	{
		return PixelDataInternalFormat(GetIntParam(
			target,
			level,
			GL_TEXTURE_INTERNAL_FORMAT
		));
	}

/*
	template <typename T>
	static void GetImage(
		Target target,
		GLint level,
		PixelDataFormat format,
		std::vector<T>& dest
	)
	{
		dest.resize(...); TODO (see ReadPixel &co.)
		and/or ARB_robustness
		OGLPLUS_GLFUNC(GetTexImage)(
			GLenum(target),
			level,
			GLenum(format),
			GLenum(GetDataType<T>()),
			dest.data()
		);
	}
*/

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
	static void GetCompressedImage(
		Target target,
		GLint level,
		std::vector<GLubyte>& dest
	)
	{
		dest.resize(CompressedImageSize(target, level));
#if GL_ARB_robustness
		OGLPLUS_GLFUNC(GetnCompressedTexImageARB)(
			GLenum(target),
			level,
			dest.size()*sizeof(GLubyte),
			dest.data()
		);
#else
		OGLPLUS_GLFUNC(GetCompressedTexImage)(
			GLenum(target),
			level,
			dest.data()
		);
#endif
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetCompressedTexImage,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a three dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 */
	static void Image3D(
		Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TexImage3D)(
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
			TexImage3D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a three dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 */
	template <typename T>
	static void Image3D(
		Target target,
		const Image<T>& image,
		GLint level = 0,
		GLint border = 0
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

	/// Specifies a three dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage3D}
	 */
	static void SubImage3D(
		Target target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TexSubImage3D)(
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
			TexSubImage3D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a three dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage3D}
	 */
	template <typename T>
	static void SubImage3D(
		Target target,
		const Image<T>& image,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint level = 0
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

	/// Specifies a two dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 */
	static void Image2D(
		Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TexImage2D)(
			GLenum(target),
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
			TexImage2D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a two dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 */
	template <typename T>
	static void Image2D(
		Target target,
		const Image<T>& image,
		GLint level = 0,
		GLint border = 0
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

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage2D}
	 */
	static void SubImage2D(
		Target target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TexSubImage2D)(
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
			TexSubImage2D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage2D}
	 */
	template <typename T>
	static void SubImage2D(
		Target target,
		const Image<T>& image,
		GLint xoffs,
		GLint yoffs,
		GLint level = 0
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

	/// Specifies a one dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage1D}
	 */
	static void Image1D(
		Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TexImage1D)(
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
			TexImage1D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a one dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage1D}
	 */
	template <typename T>
	static void Image1D(
		Target target,
		const Image<T>& image,
		GLint level = 0,
		GLint border = 0
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

	/// Specifies a one dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage1D}
	 */
	static void SubImage1D(
		Target target,
		GLint level,
		GLint xoffs,
		GLsizei width,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TexSubImage1D)(
			GLenum(target),
			level,
			xoffs,
			width,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexSubImage1D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage1D}
	 */
	template <typename T>
	static void SubImage1D(
		Target target,
		const Image<T>& image,
		GLint xoffs,
		GLint level = 0
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

	/// Copies a two dimensional texture image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexImage2D}
	 */
	static void CopyImage2D(
		Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height,
		GLint border
	)
	{
		OGLPLUS_GLFUNC(CopyTexImage2D)(
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
			CopyTexImage2D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Copies a one dimensional texture image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexImage1D}
	 */
	static void CopyImage1D(
		Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLint border
	)
	{
		OGLPLUS_GLFUNC(CopyTexImage1D)(
			GLenum(target),
			level,
			GLint(internal_format),
			x,
			y,
			width,
			border
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTexImage1D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Copies a three dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage3D}
	 */
	static void CopySubImage3D(
		Target target,
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
		OGLPLUS_GLFUNC(CopyTexSubImage3D)(
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
			CopyTexSubImage3D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Copies a two dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage2D}
	 */
	static void CopySubImage2D(
		Target target,
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(CopyTexSubImage2D)(
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
			CopyTexSubImage2D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Copies a one dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage1D}
	 */
	static void CopySubImage1D(
		Target target,
		GLint level,
		GLint xoffs,
		GLint x,
		GLint y,
		GLsizei width
	)
	{
		OGLPLUS_GLFUNC(CopyTexSubImage1D)(
			GLenum(target),
			level,
			xoffs,
			x,
			y,
			width
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTexSubImage1D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a three dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage3D}
	 */
	static void CompressedImage3D(
		Target target,
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
		OGLPLUS_GLFUNC(CompressedTexImage3D)(
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
			CompressedTexImage3D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a two dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage2D}
	 */
	static void CompressedImage2D(
		Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTexImage2D)(
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
			CompressedTexImage2D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a one dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage1D}
	 */
	static void CompressedImage1D(
		Target target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTexImage1D)(
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			border,
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTexImage1D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a three dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage3D}
	 */
	static void CompressedSubImage3D(
		Target target,
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
		OGLPLUS_GLFUNC(CompressedTexSubImage3D)(
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
			CompressedTexSubImage3D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a two dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage2D}
	 */
	static void CompressedSubImage2D(
		Target target,
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
		OGLPLUS_GLFUNC(CompressedTexSubImage2D)(
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
			CompressedTexSubImage2D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a one dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage1D}
	 */
	static void CompressedSubImage1D(
		Target target,
		GLint level,
		GLint xoffs,
		GLsizei width,
		PixelDataFormat format,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTexSubImage1D)(
			GLenum(target),
			level,
			xoffs,
			width,
			GLint(format),
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTexSubImage1D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2 || GL_ARB_texture_multisample
	/// Sets-up a three dimensional multisample texture
	/**
	 *  @glvoereq{3,2,ARB,texture_multisample}
	 *  @glsymbols
	 *  @glfunref{TexImage3DMultisample}
	 */
	static void Image3DMultisample(
		Target target,
		GLsizei samples,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		bool fixed_sample_locations
	)
	{
		OGLPLUS_GLFUNC(TexImage3DMultisample)(
			GLenum(target),
			samples,
			GLint(internal_format),
			width,
			height,
			depth,
			fixed_sample_locations ? GL_TRUE : GL_FALSE
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexImage3DMultisample,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets-up a two dimensional multisample texture
	/**
	 *  @glvoereq{3,2,ARB,texture_multisample}
	 *  @glsymbols
	 *  @glfunref{TexImage2DMultisample}
	 */
	static void Image2DMultisample(
		Target target,
		GLsizei samples,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		bool fixed_sample_locations
	)
	{
		OGLPLUS_GLFUNC(TexImage2DMultisample)(
			GLenum(target),
			samples,
			GLint(internal_format),
			width,
			height,
			fixed_sample_locations ? GL_TRUE : GL_FALSE
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexImage2DMultisample,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}
#endif // texture multisample

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
	/// Assigns a buffer storing the texel data to the texture
	/**
	 *  @glverreq{3,1}
	 *  @glsymbols
	 *  @glfunref{TexBuffer}
	 */
	static void Buffer(
		Target target,
		PixelDataInternalFormat internal_format,
		const BufferOps& buffer
	)
	{
		OGLPLUS_GLFUNC(TexBuffer)(
			GLenum(target),
			GLenum(internal_format),
			FriendOf<BufferOps>::GetName(buffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexBuffer,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
	/// Assigns a buffer range storing the texel data to the texture
	/**
	 *  @glverreq{4,3}
	 *  @glsymbols
	 *  @glfunref{TexBufferRange}
	 */
	static void BufferRange(
		Target target,
		PixelDataInternalFormat internal_format,
		const BufferOps& buffer,
		GLintptr offset,
		GLsizeiptr size
	)
	{
		OGLPLUS_GLFUNC(TexBufferRange)(
			GLenum(target),
			GLenum(internal_format),
			FriendOf<BufferOps>::GetName(buffer),
			offset,
			size
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexBufferRange,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2 || GL_ARB_texture_storage
	/// Specifies all levels of 1D texture at the same time
	/**
	 *  @glvoereq{4,2,ARB,texture_storage}
	 *  @glsymbols
	 *  @glfunref{TexStorage1D}
	 */
	static void Storage1D(
		Target target,
		GLsizei levels,
		PixelDataInternalFormat internal_format,
		GLsizei width
	)
	{
		OGLPLUS_GLFUNC(TexStorage1D)(
			GLenum(target),
			levels,
			GLenum(internal_format),
			width
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexStorage1D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies all levels of 2D texture at the same time
	/**
	 *  @glvoereq{4,2,ARB,texture_storage}
	 *  @glsymbols
	 *  @glfunref{TexStorage2D}
	 */
	static void Storage2D(
		Target target,
		GLsizei levels,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(TexStorage2D)(
			GLenum(target),
			levels,
			GLenum(internal_format),
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexStorage2D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies all levels of 3D texture at the same time
	/**
	 *  @glvoereq{4,2,ARB,texture_storage}
	 *  @glsymbols
	 *  @glfunref{TexStorage3D}
	 */
	static void Storage3D(
		Target target,
		GLsizei levels,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth
	)
	{
		OGLPLUS_GLFUNC(TexStorage3D)(
			GLenum(target),
			levels,
			GLenum(internal_format),
			width,
			height,
			depth
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexStorage3D,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY ||GL_VERSION_4_2 ||GL_ARB_shader_image_load_store
	/// Binds a @p level of this texture to an image @p unit
	/**
	 *  @glvoereq{4,2,ARB,shader_image_load_store}
	 *  @glsymbols
	 *  @glfunref{BindImageTexture}
	 */
	void BindImage(
		ImageUnitSelector unit,
		GLint level,
		bool layered,
		GLint layer,
		AccessSpecifier access,
		ImageUnitFormat format
	) const
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
	}
#endif

	/// Returns the texture base level (TEXTURE_BASE_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BASE_LEVEL}
	 */
	static GLuint BaseLevel(Target target)
	{
		return GetIntParam(target, GL_TEXTURE_BASE_LEVEL);
	}

	/// Sets the texture base level (TEXTURE_BASE_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BASE_LEVEL}
	 */
	static void BaseLevel(Target target, GLuint level)
	{
		OGLPLUS_GLFUNC(TexParameteri)(
			GLenum(target),
			GL_TEXTURE_BASE_LEVEL,
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	static Vector<GLfloat, 4> BorderColor(Target target, TypeTag<GLfloat>)
	{
		GLfloat result[4];
		OGLPLUS_GLFUNC(GetTexParameterfv)(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTexParameterfv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
		return Vector<GLfloat, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	static void BorderColor(Target target, Vector<GLfloat, 4> color)
	{
		OGLPLUS_GLFUNC(TexParameterfv)(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterfv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	static Vector<GLint, 4> BorderColor(Target target, TypeTag<GLint>)
	{
		GLint result[4];
		OGLPLUS_GLFUNC(GetTexParameterIiv)(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTexParameterIiv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
		return Vector<GLint, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	static void BorderColor(Target target, Vector<GLint, 4> color)
	{
		OGLPLUS_GLFUNC(TexParameterIiv)(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterIiv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	static Vector<GLuint, 4> BorderColor(Target target, TypeTag<GLuint>)
	{
		GLuint result[4];
		OGLPLUS_GLFUNC(GetTexParameterIuiv)(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTexParameterIuiv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
		return Vector<GLuint, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	static void BorderColor(Target target, Vector<GLuint, 4> color)
	{
		OGLPLUS_GLFUNC(TexParameterIuiv)(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterIuiv,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the compare mode (TEXTURE_COMPARE_MODE)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_COMPARE_MODE}
	 */
	static TextureCompareMode CompareMode(Target target)
	{
		return TextureCompareMode(GetIntParam(
			target,
			GL_TEXTURE_COMPARE_MODE
		));
	}

	/// Sets the compare mode (TEXTURE_COMPARE_MODE)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_COMPARE_MODE}
	 */
	static void CompareMode(Target target, TextureCompareMode mode)
	{
		OGLPLUS_GLFUNC(TexParameteri)(
			GLenum(target),
			GL_TEXTURE_COMPARE_MODE,
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_COMPARE_FUNC}
	 */
	static CompareFunction CompareFunc(Target target)
	{
		return CompareFunction(GetIntParam(
			target,
			GL_TEXTURE_COMPARE_FUNC
		));
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_COMPARE_FUNC}
	 */
	static void CompareFunc(Target target, CompareFunction func)
	{
		OGLPLUS_GLFUNC(TexParameteri)(
			GLenum(target),
			GL_TEXTURE_COMPARE_FUNC,
			GLenum(func)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the LOD bias value (TEXTURE_LOD_BIAS)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_LOD_BIAS}
	 */
	static GLfloat LODBias(Target target)
	{
		return GetFloatParam(target, GL_TEXTURE_LOD_BIAS);
	}

	/// Sets the LOD bias value (TEXTURE_LOD_BIAS)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_LOD_BIAS}
	 */
	static void LODBias(Target target, GLfloat value)
	{
		OGLPLUS_GLFUNC(TexParameterf)(
			GLenum(target),
			GL_TEXTURE_LOD_BIAS,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterf,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the magnification filter (TEXTURE_MAG_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	static TextureMagFilter MagFilter(Target target)
	{
		return TextureMagFilter(GetIntParam(
			target,
			GL_TEXTURE_MAG_FILTER
		));
	}

	/// Sets the magnification filter (TEXTURE_MAG_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	static void MagFilter(Target target, TextureMagFilter filter)
	{
		OGLPLUS_GLFUNC(TexParameteri)(
			GLenum(target),
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the minification filter (TEXTURE_MIN_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 */
	static TextureMinFilter MinFilter(Target target)
	{
		return TextureMinFilter(GetIntParam(
			target,
			GL_TEXTURE_MIN_FILTER
		));
	}

	/// Sets the minification filter (TEXTURE_MIN_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 */
	static void MinFilter(Target target, TextureMinFilter filter)
	{
		OGLPLUS_GLFUNC(TexParameteri)(
			GLenum(target),
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets minimal LOD value (TEXTURE_MIN_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MIN_LOD}
	 */
	static GLfloat MinLOD(Target target)
	{
		return GetFloatParam(target, GL_TEXTURE_MIN_LOD);
	}

	/// Sets minimal LOD value (TEXTURE_MIN_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MIN_LOD}
	 */
	static void MinLOD(Target target, GLfloat value)
	{
		OGLPLUS_GLFUNC(TexParameterf)(
			GLenum(target),
			GL_TEXTURE_MIN_LOD,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterf,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets maximal LOD value (TEXTURE_MAX_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAX_LOD}
	 */
	static GLfloat MaxLOD(Target target)
	{
		return GetFloatParam(target, GL_TEXTURE_MAX_LOD);
	}

	/// Sets maximal LOD value (TEXTURE_MAX_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAX_LOD}
	 */
	static void MaxLOD(Target target, GLfloat value)
	{
		OGLPLUS_GLFUNC(TexParameterf)(
			GLenum(target),
			GL_TEXTURE_MAX_LOD,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterf,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3 || GL_ARB_texture_swizzle
	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_*)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 */
	static TextureSwizzle Swizzle(Target target, TextureSwizzleCoord coord)
	{
		return TextureSwizzle(GetIntParam(
			target,
			GLenum(coord)
		));
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_*)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 */
	static void Swizzle(
		Target target,
		TextureSwizzleCoord coord,
		TextureSwizzle mode
	)
	{
		OGLPLUS_GLFUNC(TexParameteri)(
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_R)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_R}
	 */
	static TextureSwizzle SwizzleR(Target target)
	{
		return Swizzle(target, TextureSwizzleCoord::R);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_R)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_R}
	 */
	static void SwizzleR(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::R, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_G)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_G}
	 */
	static TextureSwizzle SwizzleG(Target target)
	{
		return Swizzle(target, TextureSwizzleCoord::G);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_G)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_G}
	 */
	static void SwizzleG(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::G, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_B)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_B}
	 */
	static TextureSwizzle SwizzleB(Target target)
	{
		return Swizzle(target, TextureSwizzleCoord::B);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_B)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_B}
	 */
	static void SwizzleB(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::B, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_A)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_A}
	 */
	static TextureSwizzle SwizzleA(Target target)
	{
		return Swizzle(target, TextureSwizzleCoord::A);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_A)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_A}
	 */
	static void SwizzleA(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::A, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_RGBA}
	 */
	static TextureSwizzle SwizzleRGBA(Target target)
	{
		return Swizzle(target, TextureSwizzleCoord::RGBA);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_RGBA}
	 */
	static void SwizzleRGBA(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::RGBA, mode);
	}
#endif // texture swizzle

	/// Gets the wrap parameter (TEXTURE_WRAP_*)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 */
	static TextureWrap Wrap(Target target, TextureWrapCoord coord)
	{
		return TextureWrap(GetIntParam(
			target,
			GLenum(coord)
		));
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_*)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 */
	static void Wrap(
		Target target,
		TextureWrapCoord coord,
		TextureWrap mode
	)
	{
		OGLPLUS_GLFUNC(TexParameteri)(
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_S)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_S}
	 */
	static TextureWrap WrapS(Target target)
	{
		return Wrap(target, TextureWrapCoord::S);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_S)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_S}
	 */
	static void WrapS(Target target, TextureWrap mode)
	{
		Wrap(target, TextureWrapCoord::S, mode);
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_T)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_T}
	 */
	static TextureWrap WrapT(Target target)
	{
		return Wrap(target, TextureWrapCoord::T);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_T)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_T}
	 */
	static void WrapT(Target target, TextureWrap mode)
	{
		Wrap(target, TextureWrapCoord::T, mode);
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_R)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_R}
	 */
	static TextureWrap WrapR(Target target)
	{
		return Wrap(target, TextureWrapCoord::R);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_R)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_R}
	 */
	static void WrapR(Target target, TextureWrap mode)
	{
		Wrap(target, TextureWrapCoord::R, mode);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
	/// Gets the depth stencil mode parameter (DEPTH_STENCIL_TEXTURE_MODE)
	/**
	 *  @glverreq{4,3}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{DEPTH_STENCIL_TEXTURE_MODE}
	 */
	static PixelDataFormat DepthStencilMode(Target target)
	{
		return PixelDataFormat(GetIntParam(
			target,
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
	static void DepthStencilMode(
		Target target,
		PixelDataFormat mode
	)
	{
		OGLPLUS_GLFUNC(TexParameteri)(
			GLenum(target),
			GL_DEPTH_STENCIL_TEXTURE_MODE,
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}
#endif

	/// Generate mipmap for the texture bound to the specified target
	/**
	 *  @glsymbols
	 *  @glfunref{GenerateMipmap}
	 */
	static void GenerateMipmap(Target target)
	{
		OGLPLUS_GLFUNC(GenerateMipmap)(GLenum(target));
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GenerateMipmap,
			Texture,
			EnumValueName(target),
			BindingQuery<TextureOps>::QueryBinding(target)
		));
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

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL texture functionality
/**
 *  @ingroup objects
 */
class Texture
 : public TextureOps
{ };
#else
typedef Object<TextureOps> Texture;
OGLPLUS_OBJECT_TYPE_ID(Texture, 3)
#endif

} // namespace oglplus

#endif // include guard
