/**
 *  @file oglplus/sampler.hpp
 *  @brief Sampler object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SAMPLER_1107121519_HPP
#define OGLPLUS_SAMPLER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
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
 *
 *  @glvoereq{3,3,ARB,sampler_objects}
 *  @glsymbols
 *  @glfunref{GenSamplers}
 *  @glfunref{DeleteSamplers}
 *  @glfunref{IsSampler}
 */
class SamplerOps
 : public Named
 , public BaseObject<true>
{
public:
	/// The target for sampler binding
	typedef TextureUnitSelector Target;
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenSamplers)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenSamplers));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteSamplers)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsSampler)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_SAMPLER
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Sampler;
	}
#endif

	static void _bind(GLuint _name, TextureUnitSelector unit)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindSampler)(GLuint(unit), _name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindSampler,
			Sampler,
			nullptr,
			_name
		));
	}

	friend class FriendOf<SamplerOps>;
public:
	/// Bind this sampler to the specified texture unit
	/**
	 *  @glsymbols
	 *  @glfunref{BindSampler}
	 */
	void Bind(TextureUnitSelector unit)
	{
		_bind(_name, unit);
	}

	/// Unbind the current sampler from the specified texture unit
	/**
	 *  @glsymbols
	 *  @glfunref{BindSampler}
	 */
	static void Unbind(TextureUnitSelector unit)
	{
		OGLPLUS_GLFUNC(BindSampler)(GLuint(unit), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindSampler));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
	/// Bind the specified samplers to the specified texture units
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	static void Bind(
		GLuint first,
		GLsizei count,
		const GLuint* names
	)
	{
		OGLPLUS_GLFUNC(BindSamplers)(
			first,
			count,
			names
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindSamplers));
	}
#endif

	GLint GetIntParam(GLenum query) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetSamplerParameteriv)(
			_name,
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetSamplerParameteriv,
			Sampler,
			nullptr,
			_name
		));
		return result;
	}

	GLfloat GetFloatParam(GLenum query) const
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetSamplerParameterfv)(
			_name,
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetSamplerParameterfv,
			Sampler,
			nullptr,
			_name
		));
		return result;
	}

	/// Gets the texture border color
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLfloat, 4> BorderColor(TypeTag<GLfloat>) const
	{
		GLfloat result[4];
		OGLPLUS_GLFUNC(GetSamplerParameterfv)(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetSamplerParameterfv,
			Sampler,
			nullptr,
			_name
		));
		return Vector<GLfloat, 4>(result, 4);
	}

	/// Sets the texture border color
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	void BorderColor(Vector<GLfloat, 4> color)
	{
		OGLPLUS_GLFUNC(SamplerParameterfv)(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(SamplerParameterfv));
	}

	/// Gets the texture border color
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLint, 4> BorderColor(TypeTag<GLint>) const
	{
		GLint result[4];
		OGLPLUS_GLFUNC(GetSamplerParameterIiv)(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetSamplerParameterIiv,
			Sampler,
			nullptr,
			_name
		));
		return Vector<GLint, 4>(result, 4);
	}

	/// Sets the texture border color
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	void BorderColor(Vector<GLint, 4> color)
	{
		OGLPLUS_GLFUNC(SamplerParameterIiv)(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameterIiv,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets the texture border color
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLuint, 4> BorderColor(TypeTag<GLuint>) const
	{
		GLuint result[4];
		OGLPLUS_GLFUNC(GetSamplerParameterIuiv)(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetSamplerParameterIuiv,
			Sampler,
			nullptr,
			_name
		));
		return Vector<GLuint, 4>(result, 4);
	}

	/// Sets the texture border color
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	void BorderColor(Vector<GLuint, 4> color)
	{
		OGLPLUS_GLFUNC(SamplerParameterIuiv)(
			_name,
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameterIuiv,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets the compare mode
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_COMPARE_MODE}
	 */
	TextureCompareMode CompareMode(void) const
	{
		return TextureCompareMode(GetIntParam(
			GL_TEXTURE_COMPARE_MODE
		));
	}

	/// Sets the compare mode
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_COMPARE_MODE}
	 */
	void CompareMode(TextureCompareMode mode)
	{
		OGLPLUS_GLFUNC(SamplerParameteri)(
			_name,
			GL_TEXTURE_COMPARE_MODE,
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameteri,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets the compare function
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_COMPARE_FUNC}
	 */
	CompareFunction CompareFunc(void) const
	{
		return CompareFunction(GetIntParam(
			GL_TEXTURE_COMPARE_FUNC
		));
	}

	/// Sets the compare function
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_COMPARE_FUNC}
	 */
	void CompareFunc(CompareFunction func)
	{
		OGLPLUS_GLFUNC(SamplerParameteri)(
			_name,
			GL_TEXTURE_COMPARE_FUNC,
			GLenum(func)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameteri,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets the LOD bias value
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_LOD_BIAS}
	 */
	GLfloat LODBias(void) const
	{
		return GetFloatParam(GL_TEXTURE_LOD_BIAS);
	}

	/// Sets the LOD bias value
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_LOD_BIAS}
	 */
	void LODBias(GLfloat value)
	{
		OGLPLUS_GLFUNC(SamplerParameterf)(
			_name,
			GL_TEXTURE_LOD_BIAS,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameterf,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets the magnification filter
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	TextureMagFilter MagFilter(void) const
	{
		return TextureMagFilter(GetIntParam(
			GL_TEXTURE_MAG_FILTER
		));
	}

	/// Sets the magnification filter
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	void MagFilter(TextureMagFilter filter)
	{
		OGLPLUS_GLFUNC(SamplerParameteri)(
			_name,
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameteri,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets the minification filter
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 */
	TextureMinFilter MinFilter(void) const
	{
		return TextureMinFilter(GetIntParam(
			GL_TEXTURE_MIN_FILTER
		));
	}

	/// Sets the minification filter
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 */
	void MinFilter(TextureMinFilter filter)
	{
		OGLPLUS_GLFUNC(SamplerParameteri)(
			_name,
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameteri,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets minimal LOD value
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_MIN_LOD}
	 */
	GLfloat MinLOD(void) const
	{
		return GetFloatParam(GL_TEXTURE_MIN_LOD);
	}

	/// Sets minimal LOD value
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_MIN_LOD}
	 */
	void MinLOD(GLfloat value)
	{
		OGLPLUS_GLFUNC(SamplerParameterf)(
			_name,
			GL_TEXTURE_MIN_LOD,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameterf,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets maximal LOD value
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_MAX_LOD}
	 */
	GLfloat MaxLOD(void) const
	{
		return GetFloatParam(GL_TEXTURE_MAX_LOD);
	}

	/// Sets maximal LOD value
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_MAX_LOD}
	 */
	void MaxLOD(GLfloat value)
	{
		OGLPLUS_GLFUNC(SamplerParameterf)(
			_name,
			GL_TEXTURE_MAX_LOD,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameterf,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_*)
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 */
	TextureWrap Wrap(TextureWrapCoord coord) const
	{
		return TextureWrap(GetIntParam(GLenum(coord)));
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_*)
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 */
	void Wrap(TextureWrapCoord coord, TextureWrap mode)
	{
		OGLPLUS_GLFUNC(SamplerParameteri)(
			_name,
			GLenum(coord),
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameteri,
			Sampler,
			nullptr,
			_name
		));
	}

	/// Gets the wrap parameter for the S coordinate
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_WRAP_S}
	 */
	TextureWrap WrapS(void) const
	{
		return Wrap(TextureWrapCoord::S);
	}

	/// Sets the wrap parameter for the S coordinate
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_WRAP_S}
	 */
	void WrapS(TextureWrap mode)
	{
		Wrap(TextureWrapCoord::S, mode);
	}

	/// Gets the wrap parameter for the T coordinate
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_WRAP_T}
	 */
	TextureWrap WrapT(void) const
	{
		return Wrap(TextureWrapCoord::T);
	}

	/// Sets the wrap parameter for the T coordinate
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_WRAP_T}
	 */
	void WrapT(TextureWrap mode)
	{
		Wrap(TextureWrapCoord::T, mode);
	}

	/// Gets the wrap parameter for the R coordinate
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_WRAP_R}
	 */
	TextureWrap WrapR(void) const
	{
		return Wrap(TextureWrapCoord::R);
	}

	/// Sets the wrap parameter for the R coordinate
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_WRAP_R}
	 */
	void WrapR(TextureWrap mode)
	{
		Wrap(TextureWrapCoord::R, mode);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_seamless_cubemap_per_texture
	/// Gets the seamless cubemap setting
	/**
	 *  @glsymbols
	 *  @glfunref{GetSamplerParameter}
	 *  @gldefref{TEXTURE_CUBE_MAP_SEAMLESS}
	 */
	bool Seamless(void) const
	{
		return GetIntParam(GL_TEXTURE_CUBE_MAP_SEAMLESS) == GL_TRUE;
	}

	/// Sets the seamless cubemap setting
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_CUBE_MAP_SEAMLESS}
	 */
	void Seamless(bool enable)
	{
		OGLPLUS_GLFUNC(SamplerParameteri)(
			_name,
			GL_TEXTURE_CUBE_MAP_SEAMLESS,
			enable?GL_TRUE:GL_FALSE
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			SamplerParameteri,
			Sampler,
			nullptr,
			_name
		));
	}
#endif
};

/// Class that can be used for unbinding of currently bound sampler
class NoSampler
{
public:
	/// The target for sampler binding
	typedef TextureUnitSelector Target;

	/// Unbind the current sampler from the specified texture unit
	/**
	 *  @glsymbols
	 *  @glfunref{BindSampler}
	 */
	static void Bind(TextureUnitSelector unit)
	{
		OGLPLUS_GLFUNC(BindSampler)(GLuint(unit), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindSampler));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL sampler functionality
/**
 *  @ingroup oglplus_objects
 */
class Sampler
 : public SamplerOps
{ };
#else
typedef Object<SamplerOps> Sampler;
#endif

template <>
class Group<Sampler>
 : public BaseGroup<Sampler>
{
public:
	/// Constructs an empty group of Samplers
	Group(void)
	{ }

	/// Constructs an empty group and reserves space for @c n Samplers
	Group(std::size_t n)
	 : BaseGroup<Sampler>(n)
	{ }

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
	/// Bind the samplers in this group to the specified texture units
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	void Bind(GLuint first) const
	{
		if(!this->empty())
		{
			SamplerOps::Bind(
				first,
				GLsizei(this->size()),
				this->_names.data()
			);
		}
	}
#endif
};

template <>
class Array<Sampler>
 : public aux::BaseArray<
	Sampler,
	Sampler::IsMultiObject::value
>
{
private:
	typedef aux::BaseArray<
		Sampler,
		Sampler::IsMultiObject::value
	> BaseArray;
public:
	/// Constructs an Array of @c c Samplers
	Array(GLsizei c)
	 : BaseArray(c)
	{ }

	Array(Array&& tmp)
	 : BaseArray(std::move(tmp))
	{ }

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
	/// Bind the in this array to the specified texture units
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	void Bind(GLuint first) const
	{
		if(!this->empty())
		{
			SamplerOps::Bind(
				first,
				GLsizei(this->size()),
				this->_names.data()
			);
		}
	}
#endif
};

#endif // sampler object

} // namespace oglplus

#endif // include guard
