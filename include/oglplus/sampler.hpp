/**
 *  @file oglplus/sampler.hpp
 *  @brief Sampler object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SAMPLER_1107121519_HPP
#define OGLPLUS_SAMPLER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/texture.hpp>
#include <cassert>

namespace oglplus {

// if samplers are available
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3 || GL_ARB_sampler_objects

/// Encapsulates sampler-related functions
/** @note Do not use this class directly, use Sampler instead.
 *  @see Sampler
 */
class SamplerOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenSamplers(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(GenSamplers));
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteSamplers(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsSampler(_name);
	}

	friend class FriendOf<SamplerOps>;
public:
	/// Bind this sampler to the specified texture unit
	void Bind(TextureUnitSelector unit) const
	{
		assert(_name != 0);
		::glBindSampler(GLuint(unit), _name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindSampler));
	}

	/// Unbind the current sampler from the specified texture unit
	static void Unbind(TextureUnitSelector unit)
	{
		::glBindSampler(GLuint(unit), 0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindSampler));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	void BorderColor(Vector<GLfloat, 4> color) const
	{
		::glSamplerParameterfv(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameterfv));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	void BorderColor(Vector<GLint, 4> color) const
	{
		::glSamplerParameterIiv(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameterIiv));
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	void BorderColor(Vector<GLuint, 4> color) const
	{
		::glSamplerParameterIuiv(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameterIuiv));
	}

	/// Sets the compare mode (TEXTURE_COMPARE_MODE)
	void CompareMode(TextureCompareMode mode) const
	{
		::glSamplerParameteri(
			_name,
			GL_TEXTURE_COMPARE_MODE,
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameteri));
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	void CompareFunc(CompareFunction func) const
	{
		::glSamplerParameteri(
			_name,
			GL_TEXTURE_COMPARE_FUNC,
			GLenum(func)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameteri));
	}

	/// Sets the LOD bias value (TEXTURE_LOD_BIAS)
	void LODBias(GLfloat value) const
	{
		::glSamplerParameterf(
			_name,
			GL_TEXTURE_LOD_BIAS,
			value
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameterf));
	}

	/// Sets the magnification filter (TEXTURE_MAG_FILTER)
	void MagFilter(TextureMagFilter filter) const
	{
		::glSamplerParameteri(
			_name,
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameteri));
	}

	/// Sets the minnification filter (TEXTURE_MAG_FILTER)
	void MinFilter(TextureMinFilter filter) const
	{
		::glSamplerParameteri(
			_name,
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameteri));
	}

	/// Sets minimal LOD value (TEXTURE_MIN_LOD)
	void MinLOD(GLfloat value) const
	{
		::glSamplerParameterf(
			_name,
			GL_TEXTURE_MIN_LOD,
			value
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameterf));
	}

	/// Sets maximal LOD value (TEXTURE_MAX_LOD)
	void MaxLOD(GLfloat value) const
	{
		::glSamplerParameterf(
			_name,
			GL_TEXTURE_MAX_LOD,
			value
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameterf));
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_*)
	void Wrap(TextureWrapCoord coord, TextureWrap mode) const
	{
		::glSamplerParameteri(
			_name,
			GLenum(coord),
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(SamplerParameteri));
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_S)
	void WrapS(TextureWrap mode) const
	{
		Wrap(TextureWrapCoord::S, mode);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_T)
	void WrapT(TextureWrap mode) const
	{
		Wrap(TextureWrapCoord::T, mode);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_R)
	void WrapR(TextureWrap mode) const
	{
		Wrap(TextureWrapCoord::R, mode);
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL sampler functionality
/**
 *  @ingroup objects
 */
class Sampler
 : public SamplerOps
{ };
#else
typedef Object<SamplerOps, true> Sampler;
#endif

#endif // sampler object

} // namespace oglplus

#endif // include guard
