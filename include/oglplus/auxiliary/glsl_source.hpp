/**
 *  .file oglplus/auxiliary/glsl_source.hpp
 *  .brief Helper class storing source code in GLSL
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_GLSL_SOURCE_1207111232_HPP
#define OGLPLUS_AUX_GLSL_SOURCE_1207111232_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/string.hpp>

#include <vector>
#include <cassert>
#include <fstream>
#include <stdexcept>

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
	template <typename Iterator>
	LitsGLSLSrcWrap(Iterator i, Iterator e)
	 : _ptrs(std::distance(i, e))
	 , _sizes(std::distance(i, e))
	{
		auto pptr = _ptrs.begin();
		auto psize = _sizes.begin();
		while(i != e)
		{
			assert(pptr != _ptrs.end());
			assert(psize != _sizes.end());
			*pptr = i->c_str();
			*psize = i->size();
			++i;
			++pptr;
			++psize;
		}
		assert(_ptrs.size() == _sizes.size());
	}

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
	GLint _size;
	std::vector<GLchar> _storage;
	GLchar* _pdata;

	static GLint _check_and_get_size(std::istream& in)
	{
		if(!in.good())
		{
			std::string msg("Failed to read GLSL input stream.");
			throw std::runtime_error(msg);
		}
		std::streampos begin = in.tellg();
		in.seekg(0, std::ios::end);
		std::streampos end = in.tellg();
		in.seekg(0, std::ios::beg);
		return GLint(end - begin);
	}
public:
	InputStreamGLSLSrcWrap(std::istream& input)
	 : _size(_check_and_get_size(input))
	 , _storage(_size+1, GLchar(0))
	 , _pdata(_storage.data())
	{
		input.read(_pdata, _size);
	}

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

	FileGLSLSrcWrapOpener(const char* path)
	 : _file(path, std::ios::in)
	{
		if(!_file.good())
		{
			std::string msg("Failed to open file '");
			msg.append(path);
			msg.append("' for reading.");
			throw std::runtime_error(msg);
		}
	}
};

class FileGLSLSrcWrap
 : public FileGLSLSrcWrapOpener
 , public InputStreamGLSLSrcWrap
{
public:
	FileGLSLSrcWrap(const char* path)
	 : FileGLSLSrcWrapOpener(path)
	 , InputStreamGLSLSrcWrap(_file)
	{
		_file.close();
	}
};

} // namespace aux
} // namespace oglplus

#endif // include guard
