/**
 *  @file oglplus/glsl_source.hpp
 *  @brief Helper class storing source code in GLSL
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_GLSL_SOURCE_1207111232_HPP
#define OGLPLUS_GLSL_SOURCE_1207111232_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/string.hpp>
#include <oglplus/auxiliary/glsl_source.hpp>

#include <cassert>

namespace oglplus {

/// Class storing source code in GLSL
class GLSLSource
{
private:
	aux::GLSLSourceWrapper* _impl;

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename Impl, typename ... P>
	static aux::GLSLSourceWrapper* make_impl(P&& ... p)
	{
		return new Impl(std::forward<P>(p)...);
	}
#else
	template <typename Impl, typename P1>
	static aux::GLSLSourceWrapper* make_impl(P1&& p1)
	{
		return new Impl(std::forward<P1>(p1));
	}

	template <typename Impl, typename P1, typename P2>
	static aux::GLSLSourceWrapper* make_impl(P1&& p1, P2&& p2)
	{
		return new Impl(
			std::forward<P1>(p1),
			std::forward<P2>(p2)
		);
	}
#endif
public:
	~GLSLSource(void)
	{
		if(_impl) delete _impl;
	}

	GLSLSource(GLSLSource&& tmp)
	 : _impl(tmp._impl)
	{
		tmp._impl = nullptr;
	}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	GLSLSource(const GLSLSource&) = delete;
#else
private:
	GLSLSource(const GLSLSource&);
public:
#endif

	GLSLSource(const StrLit& source)
	 : _impl(make_impl<aux::LitGLSLSrcWrap>(source))
	{ }

	GLSLSource(const std::vector<StrLit>& lits)
	 : _impl(make_impl<aux::LitsGLSLSrcWrap>(
		lits.begin(),
		lits.end()
	))
	{ }

	template <size_t N>
	GLSLSource(const StrLit (&lits)[N])
	 : _impl(make_impl<aux::LitsGLSLSrcWrap>(
		lits,
		lits+N
	))
	{ }

#if !OGLPLUS_NO_INITIALIZER_LISTS
	GLSLSource(std::initializer_list<StrLit> lits)
	 : _impl(make_impl<aux::LitsGLSLSrcWrap>(
		lits.begin(),
		lits.end()
	))
	{ }
#endif

	template <typename Head, typename Tail>
	GLSLSource(const aux::StrLitCat<Head, Tail>& source)
	 : _impl(make_impl<aux::StrGLSLSrcWrap>(source.str()))
	{ }

	GLSLSource(const String& source)
	 : _impl(make_impl<aux::StrGLSLSrcWrap>(source))
	{ }

	GLSLSource(String&& source)
	 : _impl(make_impl<aux::StrGLSLSrcWrap>(std::move(source)))
	{ }

	struct FromStream_ { };

	GLSLSource(std::istream& input, FromStream_)
	 : _impl(make_impl<aux::InputStreamGLSLSrcWrap>(input))
	{ }

	static GLSLSource FromStream(std::istream& input)
	{
		return GLSLSource(input, FromStream_());
	}

	struct FromFile_ { };

	GLSLSource(const char* path, FromFile_)
	 : _impl(make_impl<aux::FileGLSLSrcWrap>(path))
	{ }

	static GLSLSource FromFile(const char* path)
	{
		return GLSLSource(path, FromFile_());
	}

	static GLSLSource FromFile(const String& path)
	{
		return GLSLSource(path.c_str(), FromFile_());
	}

	/// Count of buffers storing the individual parts of the source
	GLsizei Count(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_impl);
		return _impl->Count();
	}

	/// Pointers to the individual parts of the source
	const GLchar** Parts(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_impl);
		return _impl->Parts();
	}

	/// Pointer to the lengths of the individual parts of the source
	const GLint* Lengths(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_impl);
		return _impl->Lengths();
	}
};

} // namespace oglplus

#endif // include guard
