/**
 *  @file oglplus/renderbuffer.hpp
 *  @brief Renderbuffer object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_RENDERBUFFER_1107121519_HPP
#define OGLPLUS_RENDERBUFFER_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/auxiliary/binding_query.hpp>
#include <cassert>

namespace oglplus {

/// Class wrapping renderbuffer-related functionality
/** @note Do not use this class directly, use Renderbuffer instead.
 */
class RenderbufferOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenRenderbuffers(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(GenRenderbuffers));
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteRenderbuffers(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsRenderbuffer(_name);
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
public:

	/// Binds this renderbuffer to the @p target
	void Bind(Target target = Target::Renderbuffer) const
	{
		assert(_name != 0);
		::glBindRenderbuffer(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindRenderbuffer));
	}

	/// Bind the name 0 to the @p target
	static void Unbind(Target target = Target::Renderbuffer)
	{
		::glBindRenderbuffer(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindRenderbuffer));
	}

	/// Set the renderbuffer storage parameters
	static void Storage(
		Target target,
		PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	)
	{
		::glRenderbufferStorage(
			GLenum(target),
			GLenum(internalformat),
			width,
			height
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			RenderbufferStorage,
			Renderbuffer,
			BindingQuery<RenderbufferOps>::QueryBinding(target)
		));
	}

	/// Set the renderbuffer multisample storage parameters
	static void StorageMultisample(
		Target target,
		GLsizei samples,
		PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	)
	{
		::glRenderbufferStorageMultisample(
			GLenum(target),
			samples,
			GLenum(internalformat),
			width,
			height
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			RenderbufferStorageMultisample,
			Renderbuffer,
			BindingQuery<RenderbufferOps>::QueryBinding(target)
		));
	}
};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
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
