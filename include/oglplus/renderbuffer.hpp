/**
 *  @file oglplus/renderbuffer.hpp
 *  @brief Renderbuffer object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_RENDERBUFFER_1107121519_HPP
#define OGLPLUS_RENDERBUFFER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/images/fwd.hpp>
#include <oglplus/binding_query.hpp>
#include <cassert>

namespace oglplus {

/// Renderbuffer bind targets
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(RenderbufferTarget, GLenum)
#include <oglplus/enums/renderbuffer_target.ipp>
OGLPLUS_ENUM_CLASS_END(RenderbufferTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/renderbuffer_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/renderbuffer_target_range.ipp>
#endif

template <>
struct ObjectTargetOps<RenderbufferTarget>
{
	typedef RenderbufferOps Type;
};

/// Class wrapping renderbuffer-related functionality
/** @note Do not use this class directly, use Renderbuffer instead.
 *
 *  @glsymbols
 *  @glfunref{GenRenderbuffers}
 *  @glfunref{DeleteRenderbuffers}
 *  @glfunref{IsRenderbuffer}
 */
class RenderbufferOps
 : public Named
 , public BaseObject<true>
{
public:
	/// Renderbuffer bind targets
	typedef RenderbufferTarget Target;
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenRenderbuffers)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenRenderbuffers));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteRenderbuffers)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsRenderbuffer)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_RENDERBUFFER
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Renderbuffer;
	}
#endif

	static void _bind(GLuint _name, Target target)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindRenderbuffer)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindRenderbuffer));
	}

	friend class FriendOf<RenderbufferOps>;

	static GLuint _binding(Target);
	static GLenum _binding_query(Target target);
	friend class BindingQuery<RenderbufferOps>;

	static GLint GetIntParam(Target target, GLenum query)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetRenderbufferParameteriv)(
			GLenum(target),
			query,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetRenderbufferParameteriv,
			Renderbuffer,
			EnumValueName(target),
			_binding(target)
		));
		return result;
	}
public:

	/// Binds this renderbuffer to the @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindRenderbuffer}
	 */
	void Bind(Target target = Target::Renderbuffer) const
	{
		_bind(_name, target);
	}

	/// Bind the name 0 to the @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindRenderbuffer}
	 */
	static void Unbind(Target target = Target::Renderbuffer)
	{
		OGLPLUS_GLFUNC(BindRenderbuffer)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindRenderbuffer));
	}

	/// Set the renderbuffer storage parameters
	/**
	 *  @glsymbols
	 *  @glfunref{RenderbufferStorage}
	 */
	static void Storage(
		Target target,
		PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(RenderbufferStorage)(
			GLenum(target),
			GLenum(internalformat),
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			RenderbufferStorage,
			Renderbuffer,
			EnumValueName(target),
			_binding(target)
		));
	}

	/// Set the renderbuffer storage parameters
	/**
	 *  @glsymbols
	 *  @glfunref{RenderbufferStorage}
	 */
	static void Storage(Target target, const images::ImageSpec& image_spec);

	/// Set the renderbuffer multisample storage parameters
	/**
	 *  @glsymbols
	 *  @glfunref{RenderbufferStorageMultisample}
	 */
	static void StorageMultisample(
		Target target,
		GLsizei samples,
		PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(RenderbufferStorageMultisample)(
			GLenum(target),
			samples,
			GLenum(internalformat),
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			RenderbufferStorageMultisample,
			Renderbuffer,
			EnumValueName(target),
			_binding(target)
		));
	}


	/// Returns the width of the renderbuffer as it was specified by Storage*
	/**
	 *  @see Height
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_WIDTH}
	 */
	static GLsizei Width(Target target)
	{
		return GLsizei(GetIntParam(target, GL_RENDERBUFFER_WIDTH));
	}

	/// Returns the height of the renderbuffer as it was specified by Storage*
	/**
	 *  @see Width
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_HEIGHT}
	 */
	static GLsizei Height(Target target)
	{
		return GLsizei(GetIntParam(target, GL_RENDERBUFFER_HEIGHT));
	}

	/// Returns the size in bits of the renderbuffer's red component
	/**
	 *  @see Green
	 *  @see Blue
	 *  @see Alpha
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_RED_SIZE}
	 */
	static GLsizei RedSize(Target target)
	{
		return GLsizei(GetIntParam(target, GL_RENDERBUFFER_RED_SIZE));
	}

	/// Returns the size in bits of the renderbuffer's green component
	/**
	 *  @see RedSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_GREEN_SIZE}
	 */
	static GLsizei GreenSize(Target target)
	{
		return GLsizei(GetIntParam(target, GL_RENDERBUFFER_GREEN_SIZE));
	}

	/// Returns the size in bits of the renderbuffer's blue component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_BLUE_SIZE}
	 */
	static GLsizei BlueSize(Target target)
	{
		return GLsizei(GetIntParam(target, GL_RENDERBUFFER_BLUE_SIZE));
	}

	/// Returns the size in bits of the renderbuffer's alpha component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_ALPHA_SIZE}
	 */
	static GLsizei AlphaSize(Target target)
	{
		return GLsizei(GetIntParam(target, GL_RENDERBUFFER_ALPHA_SIZE));
	}

	/// Returns the size in bits of the renderbuffer's depth component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_DEPTH_SIZE}
	 */
	static GLsizei DepthSize(Target target)
	{
		return GLsizei(GetIntParam(target, GL_RENDERBUFFER_DEPTH_SIZE));
	}

	/// Returns the size in bits of the renderbuffer's stencil component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_STENCIL_SIZE}
	 */
	static GLsizei StencilSize(Target target)
	{
		return GLsizei(GetIntParam(target,GL_RENDERBUFFER_STENCIL_SIZE));
	}

	/// Returns the number of samples of the renderbuffer
	/**
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_SAMPLES}
	 */
	static GLsizei Samples(Target target)
	{
		return GLsizei(GetIntParam(target,GL_RENDERBUFFER_SAMPLES));
	}

	/// Returns the internal format of the renderbuffer
	/**
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_INTERNAL_FORMAT}
	 */
	static PixelDataInternalFormat InternalFormat(Target target)
	{
		return PixelDataInternalFormat(
			GetIntParam(target, GL_RENDERBUFFER_INTERNAL_FORMAT)
		);
	}
};

// syntax-sugar operators

// Bind
inline RenderbufferTarget operator << (
	const RenderbufferOps& rbo,
	RenderbufferTarget target
)
{
	rbo.Bind(target);
	return target;
}

// Storage
inline RenderbufferTarget operator << (
	RenderbufferTarget target,
	const images::ImageSpec& image_spec
)
{
	RenderbufferOps::Storage(target, image_spec);
	return target;
}

/// Class that can be used to unbind the currently bound renderbuffer
class NoRenderbuffer
{
public:
	/// Renderbuffer bind targets
	typedef RenderbufferTarget Target;

	/// Bind the name zero to the @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindRenderbuffer}
	 */
	static void Bind(Target target = Target::Renderbuffer)
	{
		OGLPLUS_GLFUNC(BindRenderbuffer)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindRenderbuffer));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL renderbuffer functionality
/**
 *  @ingroup oglplus_objects
 */
class Renderbuffer
 : public RenderbufferOps
{ };
#else
typedef Object<RenderbufferOps> Renderbuffer;
#endif

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/renderbuffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
