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

#include <oglplus/glfunc.hpp>
#include <oglplus/math/vector.hpp>
#include <oglplus/error/object.hpp>
#include <oglplus/object/wrapper.hpp>
#include <oglplus/object/sequence.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/compare_func.hpp>
#include <oglplus/texture_wrap.hpp>
#include <oglplus/texture_compare.hpp>
#include <oglplus/texture_filter.hpp>
#include <oglplus/texture_unit.hpp>
#include <cassert>

namespace oglplus {

// if samplers are available
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3 || GL_ARB_sampler_objects

/// Class wrapping sampler construction/destruction functions
/** @note Do not use this class directly, use Sampler instead.
 *
 *  @glvoereq{3,3,ARB,sampler_objects}
 *  @glsymbols
 *  @glfunref{GenSamplers}
 *  @glfunref{DeleteSamplers}
 *  @glfunref{IsSampler}
 */
template <>
class ObjGenDelOps<tag::Sampler>
{
protected:
	static void Gen(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(GenSamplers)(count, names);
		OGLPLUS_CHECK_SIMPLE(GenSamplers);
	}

	static void Delete(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(DeleteSamplers)(count, names);
		OGLPLUS_VERIFY_SIMPLE(DeleteSamplers);
	}

	static GLboolean IsA(GLuint name)
	{
		assert(name != 0);
		GLboolean result = OGLPLUS_GLFUNC(IsSampler)(name);
		OGLPLUS_VERIFY_SIMPLE(IsSampler);
		return result;
	}
};

/// Sampler binding operations
template <>
class ObjBindingOps<tag::Sampler>
{
private:
	static GLenum _binding_query(TextureUnitSelector target);
protected:
	static GLuint _binding(TextureUnitSelector target);
public:
	/// Sampler bind targets
	typedef TextureUnitSelector Target;

	/// Returns the current Sampler bound to specified @p target (tex. unit)
	/**
	 *  @glsymbols
	 *  @glfunref{GetIntegerv}
	 */
	static SamplerName Binding(Target target)
	{
		return SamplerName(_binding(target));
	}

	/// Binds the specified @p sampler to the specified @p target (tex. unit)
	/**
	 *  @glsymbols
	 *  @glfunref{BindSampler}
	 */
	static void Bind(
		Target target,
		SamplerName sampler
	)
	{
		OGLPLUS_GLFUNC(BindSampler)(
			GLuint(target),
			GetGLName(sampler)
		);
		OGLPLUS_VERIFY(
			BindSampler,
			ObjectError,
			Object(sampler).
			Index(GLuint(target))
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
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
		OGLPLUS_VERIFY_SIMPLE(BindSamplers);
	}

	/// Sequentially bind @p samplers to texture units starting with @p first
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{BindSamplers}
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	static void Bind(
		GLuint first,
		const Sequence<SamplerName>& samplers
	)
	{
		Bind(first, GLsizei(samplers.size()), GetGLNames(samplers));
	}
#endif
};

/// Common sampler operations
/** @note Do not use this class directly, use Sampler
 *  or NoSampler instead.
 */
template <>
class ObjCommonOps<tag::Sampler>
 : public SamplerName
 , public ObjBindingOps<tag::Sampler>
{
protected:
	ObjCommonOps(void){ }
public:
	using ObjBindingOps<tag::Sampler>::Bind;

	/// Binds this sampler to the specified @p target (texture unit)
	/**
	 *  @glsymbols
	 *  @glfunref{BindSampler}
	 */
	void Bind(Target target) const
	{
		Bind(target, *this);
	}
};

/// Class wrapping sampler functions (with direct state access)
/** @note Do not use this class directly, use Sampler instead.
 */
template <>
class ObjectOps<tag::DirectState, tag::Sampler>
 : public ObjZeroOps<tag::DirectState, tag::Sampler>
{
protected:
	ObjectOps(void){ }
public:
	GLint GetIntParam(GLenum query) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetSamplerParameteriv)(
			_name,
			query,
			&result
		);
		OGLPLUS_CHECK(
			GetSamplerParameteriv,
			ObjectError,
			Object(*this).
			EnumParam(query)
		);
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
		OGLPLUS_CHECK(
			GetSamplerParameterfv,
			ObjectError,
			Object(*this).
			EnumParam(query)
		);
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
		OGLPLUS_CHECK(
			GetSamplerParameterfv,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			SamplerParameterfv,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			GetSamplerParameterIiv,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			SamplerParameterIiv,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			GetSamplerParameterIuiv,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			SamplerParameterIuiv,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			SamplerParameteri,
			ObjectError,
			Object(*this).
			EnumParam(mode)
		);
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
		OGLPLUS_CHECK(
			SamplerParameteri,
			ObjectError,
			Object(*this).
			EnumParam(func)
		);
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
		OGLPLUS_CHECK(
			SamplerParameterf,
			ObjectError,
			Object(*this)
		);
	}

	/// Sets both the minification and magnification filter
	/**
	 *  @glsymbols
	 *  @glfunref{SamplerParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	void Filter(TextureFilter filter) const
	{
		OGLPLUS_GLFUNC(SamplerParameteri)(
			_name,
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(
			SamplerParameteri,
			ObjectError,
			Object(*this).
			EnumParam(filter)
		);
		OGLPLUS_GLFUNC(SamplerParameteri)(
			_name,
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(
			SamplerParameteri,
			ObjectError,
			Object(*this).
			EnumParam(filter)
		);
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
		OGLPLUS_CHECK(
			SamplerParameteri,
			ObjectError,
			Object(*this).
			EnumParam(filter)
		);
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
		OGLPLUS_CHECK(
			SamplerParameteri,
			ObjectError,
			Object(*this).
			EnumParam(filter)
		);
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
		OGLPLUS_CHECK(
			SamplerParameterf,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			SamplerParameterf,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			SamplerParameteri,
			ObjectError,
			Object(*this).
			EnumParam(mode)
		);
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
		OGLPLUS_CHECK(
			SamplerParameteri,
			ObjectError,
			Object(*this)
		);
	}
#endif
};

/// Sampler operations with direct state access
typedef ObjectOps<tag::DirectState, tag::Sampler>
	SamplerOps;

// Helper class for syntax-sugar operators
struct SamplerOpsAndSlot
{
	SamplerOps& sam;
	GLint slot;

	SamplerOpsAndSlot(SamplerOps& sa, GLint sl)
	 : sam(sa)
	 , slot(sl)
	{ }
};

// syntax sugar operators
inline SamplerOpsAndSlot operator | (
	SamplerOps& sam,
	GLuint slot
)
{
	return SamplerOpsAndSlot(sam, slot);
}

// Bind
inline SamplerOps& operator << (
	SamplerOps& sam,
	TextureUnitSelector tus
)
{
	sam.Bind(tus);
	return sam;
}

// Filter
inline SamplerOps& operator << (
	SamplerOps& sam,
	TextureFilter filter
)
{
	sam.Filter(filter);
	return sam;
}

// MinFilter
inline SamplerOps& operator << (
	SamplerOps& sam,
	TextureMinFilter filter
)
{
	sam.MinFilter(filter);
	return sam;
}

// MagFilter
inline SamplerOps& operator << (
	SamplerOps& sam,
	TextureMagFilter filter
)
{
	sam.MagFilter(filter);
	return sam;
}

// CompareMode
inline SamplerOps& operator << (
	SamplerOps& sam,
	TextureCompareMode mode
)
{
	sam.CompareMode(mode);
	return sam;
}

// CompareFunc
inline SamplerOps& operator << (
	SamplerOps& sam,
	CompareFunction func
)
{
	sam.CompareFunc(func);
	return sam;
}

// Wrap
inline SamplerOps& operator << (
	SamplerOps& sam,
	TextureWrap wrap
)
{
	sam.WrapR(wrap);
	sam.WrapT(wrap);
	sam.WrapS(wrap);
	return sam;
}

// Wrap
inline SamplerOps& operator << (
	SamplerOpsAndSlot sas,
	TextureWrap wrap
)
{
	switch(sas.slot)
	{
		case 0: sas.sam.WrapS(wrap); break;
		case 1: sas.sam.WrapT(wrap); break;
		case 2: sas.sam.WrapR(wrap); break;
		default: assert(!"Invalid texture wrap slot");
	}
	return sas.sam;
}

// BorderColor
template <typename T>
inline SamplerOps& operator << (
	SamplerOps& sam,
	const Vector<T, 4>& col
)
{
	sam.BorderColor(col);
	return sam;
}

/// Class that can be used to unbind the currently bound sampler
/**
 *  @ingroup oglplus_objects
 */
typedef ObjectZero<ObjZeroOps<tag::DirectState, tag::Sampler>>
	NoSampler;

/// An @ref oglplus_object encapsulating the OpenGL sampler functionality
/**
 *  @ingroup oglplus_objects
 */
typedef Object<SamplerOps> Sampler;

#endif // sampler object

} // namespace oglplus

#endif // include guard
