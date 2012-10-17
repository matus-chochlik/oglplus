/**
 *  @file oglplus/auxiliary/uniform_init.hpp
 *  @brief Helper base class templates used for uniform variable initialization
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_UNIFORM_INIT_1107121519_HPP
#define OGLPLUS_AUX_UNIFORM_INIT_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <cassert>

namespace oglplus {
namespace aux {

template <class Operations>
class UniformInitBaseTpl
 : public FriendOf<ProgramOps>
 , public Operations
{
private:
	GLuint _program;
	typedef typename Operations::ParamType ParamType;
protected:
	UniformInitBaseTpl(const ProgramOps& program, ParamType param)
	 : Operations(param)
	 , _program(FriendOf<ProgramOps>::GetName(program))
	{ }

	GLuint _get_program(void) const
	{
		return _program;
	}

	GLint _do_init_index(const GLchar* identifier) const
	{
		return Operations::_do_init_index(_program, identifier);
	}

	GLint _init_index(const GLchar* identifier) const
	{
		return Operations::_init_index(_program, identifier);
	}
};

template <class Operations>
class EagerUniformInitTpl
 : public UniformInitBaseTpl<Operations>
{
private:
	GLint _index;
	typedef typename Operations::ParamType ParamType;
	typedef UniformInitBaseTpl<Operations> InitBase;
protected:
	GLint _get_index(void) const
	{
		return _index;
	}

	bool _try_init_index(void) const
	{
		return (_index != GLint(-1));
	}

	EagerUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const GLchar* identifier
	): InitBase(program, param)
	 , _index(InitBase::_init_index(identifier))
	{ }

	EagerUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const String& identifier
	): InitBase(program, param)
	 , _index(InitBase::_init_index(identifier.c_str()))
	{ }

	EagerUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		String&& identifier
	): InitBase(program, param)
	 , _index(InitBase::_init_index(identifier.c_str()))
	{ }
};

template <class Operations>
class LazyUniformInitTpl
 : public UniformInitBaseTpl<Operations>
{
private:
	String _identifier;
	GLint _index;
	typedef typename Operations::ParamType ParamType;
	typedef UniformInitBaseTpl<Operations> InitBase;
protected:
	bool _index_initialized(void) const
	{
		return _index != GLint(-1);
	}

	bool _try_init_index(void)
	{
		if(!_index_initialized())
			 _index = this->_do_init_index(_identifier.c_str());
		return _index_initialized();
	}

	GLint _get_index(void)
	{
		if(!_index_initialized())
		{
			_index = this->_init_index(_identifier.c_str());
			_identifier.clear();
		}
		return _index;
	}

	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const GLchar* identifier
	): InitBase(program, param)
	 , _identifier(identifier)
	 , _index(GLint(-1))
	{ }

	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const String& identifier
	): InitBase(program, param)
	 , _identifier(identifier)
	 , _index(GLint(-1))
	{ }

	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		String&& identifier
	): InitBase(program, param)
	 , _identifier(std::move(identifier))
	 , _index(GLint(-1))
	{ }
};


} // namespace aux
} // namespace oglplus

#endif // include guard
