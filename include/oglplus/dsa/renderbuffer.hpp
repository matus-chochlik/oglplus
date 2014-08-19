/**
 *  @file oglplus/dsa/renderbuffer.hpp
 *  @brief Renderbuffer object wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DSA_RENDERBUFFER_1107121519_HPP
#define OGLPLUS_DSA_RENDERBUFFER_1107121519_HPP

#include <oglplus/renderbuffer.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_5 || GL_ARB_direct_state_access

template <>
struct ObjGenTag<tag::DirectState, tag::Renderbuffer>
{
	typedef tag::Create Type;
};

/// Class wrapping renderbuffer-related functionality with direct state access
/** @note Do not use this class directly, use DSARenderbuffer instead.
 *
 */
template <>
class ObjectOps<tag::DirectState, tag::Renderbuffer>
 : public ObjZeroOps<tag::DirectState, tag::Renderbuffer>
{
protected:
	ObjectOps(void){ }
public:
	GLint GetIntParam(GLenum query) const;

	/// Set the renderbuffer storage parameters
	/**
	 *  @glsymbols
	 *  @glfunref{RenderbufferStorage}
	 */
	void Storage(
		PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(NamedRenderbufferStorage)(
			_name,
			GLenum(internalformat),
			width,
			height
		);
		OGLPLUS_CHECK(
			NamedRenderbufferStorage,
			ObjectError,
			Object(*this).
			EnumParam(internalformat)
		);
	}

	/// Set the renderbuffer storage parameters
	/**
	 *  @glsymbols
	 *  @glfunref{RenderbufferStorage}
	 */
	void Storage(const images::ImageSpec& image_spec);

	/// Set the renderbuffer multisample storage parameters
	/**
	 *  @glsymbols
	 *  @glfunref{RenderbufferStorageMultisample}
	 */
	void StorageMultisample(
		GLsizei samples,
		PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(NamedRenderbufferStorageMultisample)(
			_name,
			samples,
			GLenum(internalformat),
			width,
			height
		);
		OGLPLUS_CHECK(
			NamedRenderbufferStorageMultisample,
			ObjectError,
			Object(*this).
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
	GLsizei Width(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_WIDTH));
	}

	/// Returns the height of the renderbuffer as it was specified by Storage*
	/**
	 *  @see Width
	 *
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_HEIGHT}
	 */
	GLsizei Height(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_HEIGHT));
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
	GLsizei RedSize(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_RED_SIZE));
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
	GLsizei GreenSize(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_GREEN_SIZE));
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
	GLsizei BlueSize(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_BLUE_SIZE));
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
	GLsizei AlphaSize(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_ALPHA_SIZE));
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
	GLsizei DepthSize(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_DEPTH_SIZE));
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
	GLsizei StencilSize(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_STENCIL_SIZE));
	}

	/// Returns the number of samples of the renderbuffer
	/**
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_SAMPLES}
	 */
	GLsizei Samples(void) const
	{
		return GLsizei(GetIntParam(GL_RENDERBUFFER_SAMPLES));
	}

	/// Returns the internal format of the renderbuffer
	/**
	 *  @glsymbols
	 *  @glfunref{GetRenderbufferParameter}
	 *  @gldefref{RENDERBUFFER_INTERNAL_FORMAT}
	 */
	PixelDataInternalFormat InternalFormat(void) const
	{
		return PixelDataInternalFormat(
			GetIntParam(GL_RENDERBUFFER_INTERNAL_FORMAT)
		);
	}
};

/// Renderbuffer operations with direct state access
typedef ObjectOps<tag::DirectState, tag::Renderbuffer>
	DSARenderbufferOps;

// syntax-sugar operators

// Bind
inline DSARenderbufferOps& operator << (
	DSARenderbufferOps& rbo,
	RenderbufferTarget target
)
{
	rbo.Bind(target);
	return rbo;
}

// Storage
inline DSARenderbufferOps& operator << (
	DSARenderbufferOps& rbo,
	const images::ImageSpec& image_spec
)
{
	rbo.Storage(image_spec);
	return rbo;
}

/// An @ref oglplus_object encapsulating the OpenGL renderbuffer functionality
/**
 *  @ingroup oglplus_objects
 */
typedef Object<DSARenderbufferOps> DSARenderbuffer;

#endif // GL_ARB_direct_state_access

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/dsa/renderbuffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
