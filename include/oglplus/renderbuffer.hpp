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

#include <oglplus/glfunc.hpp>
#include <oglplus/error/object.hpp>
#include <oglplus/renderbuffer_target.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/object/wrapper.hpp>
#include <oglplus/images/fwd.hpp>
#include <cassert>

namespace oglplus {

/// Class wrapping renderbuffer construction/destruction functions
/** @note Do not use this class directly, use Renderbuffer instead.
 *
 *  @glsymbols
 *  @glfunref{GenRenderbuffers}
 *  @glfunref{DeleteRenderbuffers}
 *  @glfunref{IsRenderbuffer}
 */
template <>
class ObjGenDelOps<tag::Renderbuffer>
{
protected:
	static void Gen(tag::Generate, GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(GenRenderbuffers)(count, names);
		OGLPLUS_CHECK_SIMPLE(GenRenderbuffers);
	}
#if GL_VERSION_4_5 || GL_ARB_direct_state_access
	static void Gen(tag::Create, GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(CreateRenderbuffers)(count, names);
		OGLPLUS_CHECK_SIMPLE(CreateRenderbuffers);
	}
#endif

	static void Delete(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(DeleteRenderbuffers)(count, names);
		OGLPLUS_VERIFY_SIMPLE(DeleteRenderbuffers);
	}

	static GLboolean IsA(GLuint name)
	{
		assert(name != 0);
		GLboolean result = OGLPLUS_GLFUNC(IsRenderbuffer)(name);
		OGLPLUS_VERIFY_SIMPLE(IsRenderbuffer);
		return result;
	}
};

/// Renderbuffer binding operations
template <>
class ObjBindingOps<tag::Renderbuffer>
{
private:
	static GLenum _binding_query(RenderbufferTarget target);
protected:
	static GLuint _binding(RenderbufferTarget target);
public:
	/// Renderbuffer bind targets
	typedef RenderbufferTarget Target;

	/// Returns the current Renderbuffer bound to specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{GetIntegerv}
	 */
	static RenderbufferName Binding(Target target)
	{
		return RenderbufferName(_binding(target));
	}

	/// Binds the specified @p renderbuffer to the specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindRenderbuffer}
	 */
	static void Bind(
		Target target,
		RenderbufferName renderbuffer
	)
	{
		OGLPLUS_GLFUNC(BindRenderbuffer)(
			GLenum(target),
			GetGLName(renderbuffer)
		);
		OGLPLUS_VERIFY(
			BindRenderbuffer,
			ObjectError,
			Object(renderbuffer).
			BindTarget(target)
		);
	}
};

/// Common renderbuffer operations
/** @note Do not use this class directly, use Renderbuffer
 *  or NoRenderbuffer instead.
 */
template <>
class ObjCommonOps<tag::Renderbuffer>
 : public RenderbufferName
 , public ObjBindingOps<tag::Renderbuffer>
{
protected:
	ObjCommonOps(void){ }
public:
	using ObjBindingOps<tag::Renderbuffer>::Bind;

	/// Binds this renderbuffer to the specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindRenderbuffer}
	 */
	void Bind(Target target = Target::Renderbuffer) const
	{
		Bind(target, *this);
	}
};

/// Class wrapping renderbuffer functions with explicit target selector
/** @note Do not use this class directly, use Renderbuffer instead.
 */
template <>
class ObjectOps<tag::ExplicitSel, tag::Renderbuffer>
 : public ObjZeroOps<tag::ExplicitSel, tag::Renderbuffer>
{
protected:
	ObjectOps(void){ }
public:
	static GLint GetIntParam(Target target, GLenum query);

	/// Set the renderbuffer storage parameters for the rbo bound to target
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
		OGLPLUS_CHECK(
			RenderbufferStorage,
			ObjectError,
			ObjectBinding(target).
			EnumParam(internalformat)
		);
	}

	/// Set the renderbuffer storage parameters for the rbo bound to target
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
		OGLPLUS_CHECK(
			RenderbufferStorageMultisample,
			ObjectError,
			ObjectBinding(target).
			EnumParam(internalformat)
		);
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

/// Renderbuffer operations with explicit selector
typedef ObjectOps<tag::ExplicitSel, tag::Renderbuffer>
	RenderbufferOps;

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
/**
 *  @ingroup oglplus_objects
 */
typedef ObjectZero<ObjZeroOps<tag::ExplicitSel, tag::Renderbuffer>>
	NoRenderbuffer;

/// An @ref oglplus_object encapsulating the renderbuffer object functionality
/**
 *  @ingroup oglplus_objects
 */
typedef Object<RenderbufferOps> Renderbuffer;

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/renderbuffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
