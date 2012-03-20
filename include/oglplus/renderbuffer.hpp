/**
 *  @file oglplus/renderbuffer.hpp
 *  @brief Renderbuffer object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_RENDERBUFFER_1107121519_HPP
#define OGLPLUS_RENDERBUFFER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/auxiliary/binding_query.hpp>
#include <cassert>

namespace oglplus {

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
{
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenRenderbuffers)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenRenderbuffers));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		OGLPLUS_GLFUNC(DeleteRenderbuffers)(count, _name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsRenderbuffer)(_name);
	}

	friend class FriendOf<RenderbufferOps>;
public:
	/// Renderbuffer bind targets
	enum class Target : GLenum {
#include <oglplus/enums/renderbuffer_target.ipp>
	};
protected:
	static GLenum _binding_query(Target target)
	{
		switch(GLenum(target))
		{
#include <oglplus/enums/renderbuffer_target_bq.ipp>
			default:;
		}
		return 0;
	}
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
			EnumValueNameTpl(target),
			BindingQuery<RenderbufferOps>::QueryBinding(target)
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
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindRenderbuffer)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindRenderbuffer));
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
			EnumValueNameTpl(target),
			BindingQuery<RenderbufferOps>::QueryBinding(target)
		));
	}

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
			EnumValueNameTpl(target),
			BindingQuery<RenderbufferOps>::QueryBinding(target)
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

inline const GLchar* EnumValueName(RenderbufferOps::Target value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/renderbuffer_target.ipp>
#endif
	return "";
}

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL renderbuffer functionality
/**
 *  @ingroup objects
 */
class Renderbuffer
 : public RenderbufferOps
{ };
#else
typedef Object<RenderbufferOps, true> Renderbuffer;
#endif

} // namespace oglplus

#endif // include guard
