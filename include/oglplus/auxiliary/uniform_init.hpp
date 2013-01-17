/**
 *  @file oglplus/auxiliary/uniform_init.hpp
 *  @brief Helper base class templates used for uniform variable initialization
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
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
	GLint _do_init_location(const GLchar* identifier) const
	{
		return Operations::_do_init_location(_program, identifier);
	}

	GLint _init_location(const GLchar* identifier) const
	{
		return Operations::_init_location(_program, identifier);
	}

	UniformInitBaseTpl(const ProgramOps& program, ParamType param)
	 : Operations(param)
	 , _program(FriendOf<ProgramOps>::GetName(program))
	{ }
public:
	GLuint _get_program(void) const
	{
		return _program;
	}
};

template <class Operations>
class EagerUniformInitTpl
 : public UniformInitBaseTpl<Operations>
{
private:
	GLint _location;
	typedef typename Operations::ParamType ParamType;
	typedef UniformInitBaseTpl<Operations> InitBase;
public:
	EagerUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const GLchar* identifier
	): InitBase(program, param)
	 , _location(InitBase::_init_location(identifier))
	{ }

	EagerUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const String& identifier
	): InitBase(program, param)
	 , _location(InitBase::_init_location(identifier.c_str()))
	{ }

	EagerUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		String&& identifier
	): InitBase(program, param)
	 , _location(InitBase::_init_location(identifier.c_str()))
	{ }

	GLint _get_location(void) const
	{
		return _location;
	}

	bool _try_init_location(void) const
	{
		return (_location != GLint(-1));
	}
};

template <class Operations>
class LazyUniformInitTpl
 : public UniformInitBaseTpl<Operations>
{
private:
	String _identifier;
	GLint _location;
	typedef typename Operations::ParamType ParamType;
	typedef UniformInitBaseTpl<Operations> InitBase;

	bool _location_initialized(void) const
	{
		return _location != GLint(-1);
	}
public:
	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const GLchar* identifier
	): InitBase(program, param)
	 , _identifier(identifier)
	 , _location(GLint(-1))
	{ }

	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const String& identifier
	): InitBase(program, param)
	 , _identifier(identifier)
	 , _location(GLint(-1))
	{ }

	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		String&& identifier
	): InitBase(program, param)
	 , _identifier(std::move(identifier))
	 , _location(GLint(-1))
	{ }

	bool _try_init_location(void)
	{
		if(!_location_initialized())
			 _location = this->_do_init_location(_identifier.c_str());
		return _location_initialized();
	}

	GLint _get_location(void)
	{
		if(!_location_initialized())
		{
			_location = this->_init_location(_identifier.c_str());
			_identifier.clear();
		}
		return _location;
	}
};

class OptionalUniformInitOps
{
protected:
	typedef Nothing ParamType;

	OptionalUniformInitOps(Nothing)
	{ }

	GLint _init_location(GLuint program, const GLchar* identifier) const
	{
		return OGLPLUS_GLFUNC(GetUniformLocation)(
			program,
			identifier
		);
	}
};

class UniformInitOps
{
protected:
	typedef Nothing ParamType;

	UniformInitOps(Nothing)
	{ }

	GLint _do_init_location(GLuint program, const GLchar* identifier) const
	{
		return OGLPLUS_GLFUNC(GetUniformLocation)(
			program,
			identifier
		);
	}

	GLint _init_location(GLuint program, const GLchar* identifier) const
	{
		GLint location = _do_init_location(program, identifier);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetUniformLocation));
		if(OGLPLUS_IS_ERROR(location == GLint(-1)))
		{
			Error::PropertyMapInit props;
			Error::AddPropertyValue(
				props,
				"identifier",
				identifier
			);
			Error::AddPropertyValue(
				props,
				"program",
				aux::ObjectDescRegistry<ProgramOps>::
						_get_desc(program)
			);
			HandleShaderVariableError(
				GL_INVALID_OPERATION,
				location,
				"Getting the location of inactive uniform",
				OGLPLUS_ERROR_INFO(GetUniformLocation),
				std::move(props)
			);
		}
		return location;
	}
};

typedef EagerUniformInitTpl<UniformInitOps>
	EagerUniformInit;

typedef LazyUniformInitTpl<UniformInitOps>
	LazyUniformInit;

typedef EagerUniformInitTpl<OptionalUniformInitOps>
	OptionalUniformInit;


class DirectUniformInit
 : public FriendOf<ProgramOps>
{
private:
	GLuint _program;
	GLint _location;
public:
	DirectUniformInit(const ProgramOps& program, Nothing, GLint location)
	 : _program(FriendOf<ProgramOps>::GetName(program))
	 , _location(location)
	{ }

	DirectUniformInit(GLuint program, Nothing, GLint location)
	 : _program(program)
	 , _location(location)
	{ }

	GLuint _get_program(void) const
	{
		return _program;
	}

	GLint _get_location(void) const
	{
		return _location;
	}

	bool _try_init_location(void) const
	{
		return true;
	}
};

} // namespace aux
} // namespace oglplus

#endif // include guard
