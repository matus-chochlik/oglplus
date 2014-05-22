/**
 *  .file oglplus/detail/glsl_source.hpp
 *  .brief Helper classes storing source code in GLSL
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_GLSL_SOURCE_1207111232_HPP
#define OGLPLUS_AUX_GLSL_SOURCE_1207111232_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/string/def.hpp>
#include <oglplus/string/literal.hpp>

#include <oglplus/detail/any_iter.hpp>

#include <vector>
#include <cassert>
#include <fstream>

namespace oglplus {
namespace aux {

struct GLSLSourceWrapper
{
	virtual ~GLSLSourceWrapper(void){ }

	virtual GLsizei Count(void) const = 0;

	virtual const GLchar** Parts(void) const = 0;

	virtual const GLint* Lengths(void) const = 0;
};

class LitGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	const GLchar* _ptr;
	const GLint _size;
public:
	LitGLSLSrcWrap(const StrLit& source)
	 : _ptr(source.c_str())
	 , _size(GLint(source.size()))
	{
		assert(_ptr != nullptr);
	}

	GLsizei Count(void) const
	{
		return GLsizei(1);
	}

	const GLchar** Parts(void) const
	{
		return const_cast<const GLchar**>(&_ptr);
	}

	const GLint* Lengths(void) const
	{
		return &_size;
	}
};

class LitsGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	std::vector<const GLchar*> _ptrs;
	std::vector<GLint> _sizes;
public:
	LitsGLSLSrcWrap(
		AnyInputIter<StrLit>&& i,
		AnyInputIter<StrLit>&& e
	);

	GLsizei Count(void) const
	{
		return GLsizei(_ptrs.size());
	}

	const GLchar** Parts(void) const
	{
		return const_cast<const GLchar**>(_ptrs.data());
	}

	const GLint* Lengths(void) const
	{
		return _sizes.data();
	}
};

class StrGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	const String _storage;
	const GLchar* _ptr;
	const GLint _size;
public:
	StrGLSLSrcWrap(const String& source)
	 : _storage(source)
	 , _ptr(_storage.c_str())
	 , _size(GLint(_storage.size()))
	{
		assert(_ptr != nullptr);
	}

	StrGLSLSrcWrap(String&& source)
	 : _storage(std::move(source))
	 , _ptr(_storage.c_str())
	 , _size(GLint(_storage.size()))
	{
		assert(_ptr != nullptr);
	}

	GLsizei Count(void) const
	{
		return GLsizei(1);
	}

	const GLchar** Parts(void) const
	{
		return const_cast<const GLchar**>(&_ptr);
	}

	const GLint* Lengths(void) const
	{
		return &_size;
	}
};

class InputStreamGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	std::vector<GLchar> _storage;
	GLchar* _pdata;
	GLint _size;

	static GLint _check_and_get_size(std::istream& in);
	static std::vector<GLchar> _read_data(std::istream&, std::size_t);
public:
	InputStreamGLSLSrcWrap(std::istream& input);

	GLsizei Count(void) const
	{
		return GLsizei(1);
	}

	const GLchar** Parts(void) const
	{
		return const_cast<const GLchar**>(&_pdata);
	}

	const GLint* Lengths(void) const
	{
		return &_size;
	}
};

class FileGLSLSrcWrapOpener
{
protected:
	std::ifstream _file;

	FileGLSLSrcWrapOpener(const char* path);
};

class FileGLSLSrcWrap
 : public FileGLSLSrcWrapOpener
 , public InputStreamGLSLSrcWrap
{
public:
	FileGLSLSrcWrap(const char* path);
};

} // namespace aux
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/detail/glsl_source.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
