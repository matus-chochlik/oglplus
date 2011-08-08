/**
 *  @file oglplus/texture.hpp
 *  @brief Texture object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXTURE_1107121519_HPP
#define OGLPLUS_TEXTURE_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/compare_func.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/limited_value.hpp>
#include <cassert>

namespace oglplus {

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Type for the texture unit selector (implementation-dependent limited) number
class TextureUnitSelector
 : public LimitedCount
{
public:
	TextureUnitSelector(GLuint count);
};
#else
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	TextureUnitSelector,
	MAX_COMBINED_TEXTURE_IMAGE_UNITS
)
#endif


/// Texture compare mode enumeration
enum class TextureCompareMode : GLenum {
	None = GL_NONE,
	CompareRefToTexture = GL_COMPARE_REF_TO_TEXTURE
};

/// Texture magnification filter enumeration
enum class TextureMagFilter : GLenum {
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR
};

/// Texture minification filter enumeration
enum class TextureMinFilter : GLenum {
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR,
	NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
	NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
	LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
	LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
};

/// Texture swizzle enumeration
enum class TextureSwizzle : GLenum {
	Red = GL_RED,
	Green = GL_GREEN,
	Blue = GL_BLUE,
	Alpha = GL_ALPHA,
	Zero = GL_ZERO,
	One = GL_ONE
};

/// Texture wrap enumeration
enum class TextureWrap : GLenum {
	ClampToEdge = GL_CLAMP_TO_EDGE,
	Repeat = GL_REPEAT,
	ClampToBorder = GL_CLAMP_TO_BORDER,
	MirroredRepeat = GL_MIRRORED_REPEAT
};

/// Wrapper for texture and texture unit-related operations
/** @note Do not use this class directly, use Texture instead.
 */
class TextureOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenTextures(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(GenTextures));
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteTextures(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsTexture(_name);
	}

	friend class FriendOf<TextureOps>;
public:
	/// Texture bind targets
	enum class Target : GLenum {
		_1D = GL_TEXTURE_1D,
		_2D = GL_TEXTURE_2D,
		_3D = GL_TEXTURE_3D,
		_1DArray = GL_TEXTURE_1D_ARRAY,
		_2DArray = GL_TEXTURE_2D_ARRAY,
		Rectangle = GL_TEXTURE_RECTANGLE,
		Buffer = GL_TEXTURE_BUFFER,
		CubeMap = GL_TEXTURE_CUBE_MAP,
		CubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
		_2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
		_2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
	};

	/// Texture image specification targets
	enum class ImageTarget : GLenum {
		_1D = GL_TEXTURE_1D,
		_2D = GL_TEXTURE_2D,
		_3D = GL_TEXTURE_3D,
		_1DArray = GL_TEXTURE_1D_ARRAY,
		_2DArray = GL_TEXTURE_2D_ARRAY,
		Rectangle = GL_TEXTURE_RECTANGLE,
		Buffer = GL_TEXTURE_BUFFER,
		CubeMap = GL_TEXTURE_CUBE_MAP,
		CubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
		_2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
		_2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
		CubeMapPositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		CubeMapNegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		CubeMapPositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		CubeMapNegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		CubeMapPositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		CubeMapNegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	/// Specify active texture unit for subsequent commands
	/**
	 *  @throws Error
	 *
	 *  @see Bind
	 */
	static void Active(TextureUnitSelector index)
	{
		::glActiveTexture(GLenum(GL_TEXTURE0 + GLuint(index)));
		AssertNoError(OGLPLUS_ERROR_INFO(ActiveTexture));
	}

	/// Bind the texture to the target on the Active unit
	/**
	 *  @throws Error
	 *
	 *  @see Active
	 *  @see Unbind
	 */
	void Bind(Target target) const
	{
		assert(_name != 0);
		::glBindTexture(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindTexture));
	}

	/// Unbinds the current texture from the target on the Active unit
	/**
	 *  @throws Error
	 *
	 *  @see Active
	 *  @see Bind
	 */
	static void Unbind(Target target)
	{
		::glBindTexture(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindTexture));
	}

	/// Specifies a three dimensional texture image
	static void Image3D(
		ImageTarget target,
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
		::glTexImage3D(
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
		AssertNoError(OGLPLUS_ERROR_INFO(TexImage3D));
	}

	/// Specifies a two dimensional texture image
	static void Image2D(
		ImageTarget target,
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
		::glTexImage2D(
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
		AssertNoError(OGLPLUS_ERROR_INFO(TexImage2D));
	}

	/// Specifies a one dimensional texture image
	static void Image1D(
		ImageTarget target,
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		::glTexImage1D(
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		AssertNoError(OGLPLUS_ERROR_INFO(TexImage1D));
	}

	/// Sets the texture base level (TEXTURE_BASE_LEVEL)
	static void BaseLevel(Target target, GLuint level)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_BASE_LEVEL,
			level
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameteri));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	static void BorderColor(Target target, Vector<GLfloat, 4> color)
	{
		::glTexParameterfv(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameterfv));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	static void BorderColor(Target target, Vector<GLint, 4> color)
	{
		::glTexParameterIiv(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameterIiv));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	static void BorderColor(Target target, Vector<GLuint, 4> color)
	{
		::glTexParameterIuiv(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameterIuiv));
	}

	/// Sets the compare mode (TEXTURE_COMPARE_MODE)
	static void CompareMode(Target target, TextureCompareMode mode)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_COMPARE_MODE,
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameteri));
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	static void CompareFunc(Target target, CompareFunction func)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_COMPARE_FUNC,
			GLenum(func)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameteri));
	}

	/// Sets the LOD bias value (TEXTURE_LOD_BIAS)
	static void LODBias(Target target, GLfloat value)
	{
		::glTexParameterf(
			GLenum(target),
			GL_TEXTURE_LOD_BIAS,
			value
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameterf));
	}

	/// Sets the magnification filter (TEXTURE_MAG_FILTER)
	static void MagFilter(Target target, TextureMagFilter filter)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameteri));
	}

	/// Sets the minnification filter (TEXTURE_MAG_FILTER)
	static void MinFilter(Target target, TextureMinFilter filter)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameteri));
	}

	/// Sets minimal LOD value (TEXTURE_MIN_LOD)
	static void MinLOD(Target target, GLfloat value)
	{
		::glTexParameterf(
			GLenum(target),
			GL_TEXTURE_MIN_LOD,
			value
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameterf));
	}

	/// Swizzle parameter coordinate enumeration
	enum class SwizzleCoord : GLenum {
		R = GL_TEXTURE_SWIZZLE_R,
		G = GL_TEXTURE_SWIZZLE_G,
		B = GL_TEXTURE_SWIZZLE_B,
		A = GL_TEXTURE_SWIZZLE_A,
		RGBA = GL_TEXTURE_SWIZZLE_RGBA
	};

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_*)
	static void Swizzle(
		Target target,
		SwizzleCoord coord,
		TextureSwizzle mode
	)
	{
		::glTexParameteri(
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameteri));
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_R)
	static void SwizzleR(Target target, TextureSwizzle mode)
	{
		Swizzle(target, SwizzleCoord::R, mode);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_G)
	static void SwizzleG(Target target, TextureSwizzle mode)
	{
		Swizzle(target, SwizzleCoord::G, mode);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_B)
	static void SwizzleB(Target target, TextureSwizzle mode)
	{
		Swizzle(target, SwizzleCoord::B, mode);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_A)
	static void SwizzleA(Target target, TextureSwizzle mode)
	{
		Swizzle(target, SwizzleCoord::A, mode);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	static void SwizzleRGBA(Target target, TextureSwizzle mode)
	{
		Swizzle(target, SwizzleCoord::RGBA, mode);
	}

	/// Wrap parameter coordinate enumeration
	enum class WrapCoord : GLenum {
		S = GL_TEXTURE_WRAP_S,
		T = GL_TEXTURE_WRAP_T,
		R = GL_TEXTURE_WRAP_R
	};

	/// Sets the wrap parameter (TEXTURE_WRAP_*)
	static void Wrap(
		Target target,
		WrapCoord coord,
		TextureWrap mode
	)
	{
		::glTexParameteri(
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(TexParameteri));
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_S)
	static void WrapS(Target target, TextureWrap mode)
	{
		Wrap(target, WrapCoord::S, mode);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_T)
	static void WrapT(Target target, TextureWrap mode)
	{
		Wrap(target, WrapCoord::T, mode);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_R)
	static void WrapR(Target target, TextureWrap mode)
	{
		Wrap(target, WrapCoord::R, mode);
	}
};

typedef Object<TextureOps, true> Texture;

} // namespace oglplus

#endif // include guard
