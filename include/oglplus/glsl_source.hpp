/**
 *  @file oglplus/glsl_source.hpp
 *  @brief Helper class storing source code in GLSL
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_GLSL_SOURCE_1207111232_HPP
#define OGLPLUS_GLSL_SOURCE_1207111232_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/string/literal.hpp>
#include <oglplus/detail/glsl_source.hpp>

#include <utility>
#include <cassert>

namespace oglplus {

/// Class for passing a single string as a Source to a Shader
class GLSLString
{
private:
	const GLchar* _str;
	GLint _len;

	GLSLString(const GLSLString&);
public:
	GLSLString(const GLchar* str)
	OGLPLUS_NOEXCEPT(true)
	 : _str(str)
	 , _len(-1)
	{ }

	template <std::size_t N>
	GLSLString(const GLchar (&str)[N])
	OGLPLUS_NOEXCEPT(true)
	 : _str(str)
	 , _len(N)
	{ }

	GLSLString(const String& str)
	 : _str(str.c_str())
	 , _len(GLint(str.size()))
	{ }

	GLSLString(const StrLit& lit)
	 : _str(lit.c_str())
	 , _len(GLint(lit.size()))
	{ }

	GLSLString(const std::vector<GLchar>& v)
	 : _str(v.data())
	 , _len(GLint(v.size()))
	{ }

	GLsizei Count(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return 1;
	}

	const GLchar** Parts(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return const_cast<const GLchar**>(&_str);
	}

	const GLint* Lengths(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return (_len<0)?(nullptr):(&_len);
	}
};


/// Class for passing a set of strings as a Source to a Shader
class GLSLStrings
{
private:
	GLsizei _count;
	const GLchar** _strs;
	const GLint* _lens;

	GLSLStrings(const GLSLStrings&);
public:
	GLSLStrings(GLsizei count, const GLchar** strs)
	OGLPLUS_NOEXCEPT(true)
	 : _count(count)
	 , _strs(strs)
	 , _lens(nullptr)
	{ }

	template <std::size_t N>
	GLSLStrings(const GLchar* (&strs)[N])
	OGLPLUS_NOEXCEPT(true)
	 : _count(GLsizei(N))
	 , _strs(strs)
	 , _lens(nullptr)
	{ }

	GLSLStrings(const std::vector<const GLchar*>& v)
	 : _count(GLsizei(v.size()))
	 , _strs(const_cast<const GLchar**>(v.data()))
	 , _lens(nullptr)
	{ }

	template <std::size_t N>
	GLSLStrings(const std::array<const GLchar*, N>& a)
	 : _count(GLsizei(a.size()))
	 , _strs(const_cast<const GLchar**>(a.data()))
	 , _lens(nullptr)
	{ }

	GLsizei Count(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _count;
	}

	const GLchar** Parts(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _strs;
	}

	const GLint* Lengths(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _lens;
	}
};


/// Class storing source code in GLSL
class GLSLSource
{
private:
	aux::GLSLSourceWrapper* _impl;

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

	explicit GLSLSource(const StrLit& source)
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
	GLSLSource(const aux::StrLitCatTpl<GLchar, Head, Tail>& source)
	 : _impl(make_impl<aux::StrGLSLSrcWrap>(source.str()))
	{ }

	explicit GLSLSource(const String& source)
	 : _impl(make_impl<aux::StrGLSLSrcWrap>(source))
	{ }

	explicit GLSLSource(String&& source)
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
