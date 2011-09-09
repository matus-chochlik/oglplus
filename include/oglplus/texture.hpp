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
#include <oglplus/image.hpp>
#include <oglplus/auxiliary/binding_query.hpp>
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

/// Texture swizzle parameter coordinate enumeration
enum class TextureSwizzleCoord : GLenum {
	R = GL_TEXTURE_SWIZZLE_R,
	G = GL_TEXTURE_SWIZZLE_G,
	B = GL_TEXTURE_SWIZZLE_B,
	A = GL_TEXTURE_SWIZZLE_A,
	RGBA = GL_TEXTURE_SWIZZLE_RGBA
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

/// Texture wrap parameter coordinate enumeration
enum class TextureWrapCoord : GLenum {
	S = GL_TEXTURE_WRAP_S,
	T = GL_TEXTURE_WRAP_T,
	R = GL_TEXTURE_WRAP_R
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
	/// Texture bind and image specification targets
	/** @note Not all of the values enumerated here are valid
	 *  bind targets. Some of them are just image specification
	 *  targets.
	 */
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
		_2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
		CubeMapPositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		CubeMapNegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		CubeMapPositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		CubeMapNegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		CubeMapPositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		CubeMapNegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

protected:
	static GLenum _binding_query(Target target)
	{
		switch(GLenum(target))
		{
			case GL_TEXTURE_1D:
				return GL_TEXTURE_BINDING_1D;
			case GL_TEXTURE_2D:
				return GL_TEXTURE_BINDING_2D;
			case GL_TEXTURE_3D:
				return GL_TEXTURE_BINDING_3D;
			case GL_TEXTURE_1D_ARRAY:
				return GL_TEXTURE_BINDING_1D_ARRAY;
			case GL_TEXTURE_2D_ARRAY:
				return GL_TEXTURE_BINDING_2D_ARRAY;
			case GL_TEXTURE_RECTANGLE:
				return GL_TEXTURE_BINDING_RECTANGLE;
			case GL_TEXTURE_BUFFER:
				return GL_TEXTURE_BINDING_BUFFER;
			case GL_TEXTURE_CUBE_MAP:
				return GL_TEXTURE_BINDING_CUBE_MAP;
			case GL_TEXTURE_CUBE_MAP_ARRAY:
				return GL_TEXTURE_BINDING_CUBE_MAP_ARRAY;
			case GL_TEXTURE_2D_MULTISAMPLE:
				return GL_TEXTURE_BINDING_2D_MULTISAMPLE;
			case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
				return GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
				return GL_TEXTURE_BINDING_CUBE_MAP;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
				return GL_TEXTURE_BINDING_CUBE_MAP;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
				return GL_TEXTURE_BINDING_CUBE_MAP;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
				return GL_TEXTURE_BINDING_CUBE_MAP;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
				return GL_TEXTURE_BINDING_CUBE_MAP;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
				return GL_TEXTURE_BINDING_CUBE_MAP;
			default:;
		}
		return 0;
	}
	friend class BindingQuery<TextureOps>;
public:

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
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			BindTexture,
			Texture,
			_name
		));
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
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexImage3D,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a three dimensional texture image
	template <typename T>
	static void Image3D(
		Target target,
		const Image<T>& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		::glTexImage3D(
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
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexImage3D,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a two dimensional texture image
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
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexImage2D,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a two dimensional texture image
	template <typename T>
	static void Image2D(
		Target target,
		const Image<T>& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		::glTexImage2D(
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
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexImage2D,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a one dimensional texture image
	static void Image1D(
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
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexImage1D,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Specifies a one dimensional texture image
	template <typename T>
	static void Image1D(
		Target target,
		const Image<T>& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		::glTexImage1D(
			GLenum(target),
			level,
			GLint(image.InternalFormat()),
			image.Width(),
			border,
			GLenum(image.Format()),
			GLenum(image.Type()),
			image.RawData()
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexImage1D,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the texture base level (TEXTURE_BASE_LEVEL)
	static void BaseLevel(Target target, GLuint level)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_BASE_LEVEL,
			level
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	static void BorderColor(Target target, Vector<GLfloat, 4> color)
	{
		::glTexParameterfv(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterfv,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	static void BorderColor(Target target, Vector<GLint, 4> color)
	{
		::glTexParameterIiv(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterIiv,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	static void BorderColor(Target target, Vector<GLuint, 4> color)
	{
		::glTexParameterIuiv(
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterIuiv,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the compare mode (TEXTURE_COMPARE_MODE)
	static void CompareMode(Target target, TextureCompareMode mode)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_COMPARE_MODE,
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	static void CompareFunc(Target target, CompareFunction func)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_COMPARE_FUNC,
			GLenum(func)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the LOD bias value (TEXTURE_LOD_BIAS)
	static void LODBias(Target target, GLfloat value)
	{
		::glTexParameterf(
			GLenum(target),
			GL_TEXTURE_LOD_BIAS,
			value
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterf,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the magnification filter (TEXTURE_MAG_FILTER)
	static void MagFilter(Target target, TextureMagFilter filter)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the minnification filter (TEXTURE_MAG_FILTER)
	static void MinFilter(Target target, TextureMinFilter filter)
	{
		::glTexParameteri(
			GLenum(target),
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets minimal LOD value (TEXTURE_MIN_LOD)
	static void MinLOD(Target target, GLfloat value)
	{
		::glTexParameterf(
			GLenum(target),
			GL_TEXTURE_MIN_LOD,
			value
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterf,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets maximal LOD value (TEXTURE_MAX_LOD)
	static void MaxLOD(Target target, GLfloat value)
	{
		::glTexParameterf(
			GLenum(target),
			GL_TEXTURE_MAX_LOD,
			value
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameterf,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_*)
	static void Swizzle(
		Target target,
		TextureSwizzleCoord coord,
		TextureSwizzle mode
	)
	{
		::glTexParameteri(
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_R)
	static void SwizzleR(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::R, mode);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_G)
	static void SwizzleG(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::G, mode);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_B)
	static void SwizzleB(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::B, mode);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_A)
	static void SwizzleA(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::A, mode);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	static void SwizzleRGBA(Target target, TextureSwizzle mode)
	{
		Swizzle(target, TextureSwizzleCoord::RGBA, mode);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_*)
	static void Wrap(
		Target target,
		TextureWrapCoord coord,
		TextureWrap mode
	)
	{
		::glTexParameteri(
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TexParameteri,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_S)
	static void WrapS(Target target, TextureWrap mode)
	{
		Wrap(target, TextureWrapCoord::S, mode);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_T)
	static void WrapT(Target target, TextureWrap mode)
	{
		Wrap(target, TextureWrapCoord::T, mode);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_R)
	static void WrapR(Target target, TextureWrap mode)
	{
		Wrap(target, TextureWrapCoord::R, mode);
	}

	/// Generate mipmap for the texture bound to the specified target
	static void GenerateMipmap(Target target)
	{
		::glGenerateMipmap(GLenum(target));
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			GenerateMipmap,
			Texture,
			BindingQuery<TextureOps>::QueryBinding(target)
		));
	}
};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Encapsulates the OpenGL texture-related functionality
class Texture
 : public TextureOps
{ };
#else
typedef Object<TextureOps, true> Texture;
#endif

} // namespace oglplus

#endif // include guard
