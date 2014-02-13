/**
 *  @file oglplus/ext/EXT_direct_state_access/renderbuffer.hpp
 *  @brief Renderbuffer object wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_RENDERBUFFER_DSA_1107121519_HPP
#define OGLPLUS_RENDERBUFFER_DSA_1107121519_HPP

#include <oglplus/renderbuffer.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Class wrapping renderbuffer-related functionality
/** @note Do not use this class directly, use DSARenderbufferEXT instead.
 *
 *  @glsymbols
 *  @glfunref{GenRenderbuffers}
 *  @glfunref{DeleteRenderbuffers}
 *  @glfunref{IsRenderbuffer}
 */
class DSARenderbufferEXTOps
 : public Named
 , public BaseObject<true>
{
public:
	/// Renderbuffer bind targets
	typedef RenderbufferTarget Target;
	Target target;
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

	friend class FriendOf<DSARenderbufferEXTOps>;

	GLint GetIntParam(GLenum query) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetNamedRenderbufferParameterivEXT)(
			_name,
			query,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetRenderbufferParameteriv,
			Renderbuffer,
			EnumValueName(target),
			_name
		));
		return result;
	}
public:

	/// Binds this renderbuffer to the @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindRenderbuffer}
	 */
	void Bind(void)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindRenderbuffer)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindRenderbuffer));
	}

	/// Bind this renderbuffer to the specified target
	/**
	 *  @throws Error
	 */
	void Bind(Target new_target)
	{
		target = new_target;
		Bind();
	}

	/// Bind the name 0 to this Renderbuffer's target
	/**
	 *  @glsymbols
	 *  @glfunref{BindRenderbuffer}
	 */
	void Unbind(void) const
	{
		OGLPLUS_GLFUNC(BindRenderbuffer)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindRenderbuffer));
	}

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
		OGLPLUS_GLFUNC(NamedRenderbufferStorageEXT)(
			_name,
			GLenum(internalformat),
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedRenderbufferStorageEXT,
			Renderbuffer,
			EnumValueName(target),
			_name
		));
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
		OGLPLUS_GLFUNC(NamedRenderbufferStorageMultisampleEXT)(
			_name,
			samples,
			GLenum(internalformat),
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedRenderbufferStorageMultisampleEXT,
			Renderbuffer,
			EnumValueName(target),
			_name
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

// syntax-sugar operators

// Bind
inline DSARenderbufferEXTOps& operator << (
	DSARenderbufferEXTOps& rbo,
	RenderbufferTarget target
)
{
	rbo.Bind(target);
	return rbo;
}

// Storage
inline DSARenderbufferEXTOps& operator << (
	DSARenderbufferEXTOps& rbo,
	const images::ImageSpec& image_spec
)
{
	rbo.Storage(image_spec);
	return rbo;
}

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL renderbuffer functionality
/**
 *  @ingroup oglplus_objects
 */
class DSARenderbufferEXT
 : public DSARenderbufferEXTOps
{ };
#else
typedef Object<DSARenderbufferEXTOps> DSARenderbufferEXT;
#endif

template <>
struct NonDSAtoDSA<RenderbufferOps>
{
	typedef DSARenderbufferEXTOps Type;
};

template <>
struct DSAtoNonDSA<DSARenderbufferEXTOps>
{
	typedef RenderbufferOps Type;
};

template <>
class ConvertibleObjectBaseOps<RenderbufferOps, DSARenderbufferEXTOps>
 : public std::true_type
{ };

template <>
class ConvertibleObjectBaseOps<DSARenderbufferEXTOps, RenderbufferOps>
 : public std::true_type
{ };

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/ext/EXT_direct_state_access/renderbuffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
