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

#pragma once
#ifndef OGLPLUS_AUX_UNIFORM_INIT_1107121519_HPP
#define OGLPLUS_AUX_UNIFORM_INIT_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/program.hpp>

#include <oglplus/auxiliary/uniform_typecheck.hpp>

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

	UniformInitBaseTpl(
		const ProgramOps& program,
		ParamType param
	): Operations(param)
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
 , public UniformInitTypecheckUtils
{
private:
	typedef UniformInitBaseTpl<Operations> InitBase;
	typedef typename Operations::ParamType ParamType;

	GLint _location;

	template <class Typechecker>
	GLint _init_location(Typechecker& typechecker, const GLchar* identifier)
	{
		return UniformInitTypecheckUtils::_typecheck(
			typechecker,
			this->_get_program(),
			InitBase::_init_location(identifier),
			identifier
		);
	}
public:
	template <class Typechecker>
	EagerUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const GLchar* identifier,
		Typechecker typechecker
	): InitBase(program, param)
	 , _location(_init_location(typechecker, identifier))
	{ }

	template <class Typechecker>
	EagerUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const String& identifier,
		Typechecker typechecker
	): InitBase(program, param)
	 , _location(_init_location(typechecker, identifier.c_str()))
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

template <class Operations, class Typechecker>
class LazyUniformInitTpl
 : public UniformInitBaseTpl<Operations>
 , public UniformInitTypecheckUtils
{
private:
	typedef UniformInitBaseTpl<Operations> InitBase;
	typedef typename Operations::ParamType ParamType;

	String _identifier;
	GLint _location;

	Typechecker _typechecker;

	bool _location_initialized(void) const
	{
		return _location != GLint(-1);
	}
public:
	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const GLchar* identifier,
		Typechecker typechecker
	): InitBase(program, param)
	 , _identifier(identifier)
	 , _location(GLint(-1))
	 , _typechecker(typechecker)
	{ }

	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		const String& identifier,
		Typechecker typechecker
	): InitBase(program, param)
	 , _identifier(identifier)
	 , _location(GLint(-1))
	 , _typechecker(typechecker)
	{ }

	LazyUniformInitTpl(
		const ProgramOps& program,
		const ParamType param,
		String&& identifier,
		Typechecker typechecker
	): InitBase(program, param)
	 , _identifier(std::move(identifier))
	 , _location(GLint(-1))
	 , _typechecker(typechecker)
	{ }

	bool _try_init_location(void)
	{
		if(!_location_initialized())
			 _location = this->_typecheck(
				_typechecker,
				this->_get_program(),
				this->_do_init_location(_identifier.c_str()),
				_identifier.c_str()
			);
		return _location_initialized();
	}

	GLint _get_location(void)
	{
		if(!_location_initialized())
		{
			_location = this->_typecheck(
				_typechecker,
				this->_get_program(),
				this->_init_location(_identifier.c_str()),
				_identifier.c_str()
			);
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
		GLint result = OGLPLUS_GLFUNC(GetUniformLocation)(
			program,
			identifier
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetUniformLocation));
		return result;
	}

	void _handle_error(
		GLuint program,
		const GLchar* identifier,
		GLint location
	) const;

	GLint _init_location(GLuint program, const GLchar* identifier) const
	{
		GLint location = _do_init_location(program, identifier);
		if(OGLPLUS_IS_ERROR(location == GLint(-1)))
		{
			_handle_error(program, identifier, location);
		}
		return location;
	}
};

typedef EagerUniformInitTpl<UniformInitOps> EagerUniformInit;
typedef EagerUniformInitTpl<OptionalUniformInitOps> OptionalUniformInit;

template <typename Typechecker>
class LazyUniformInit
 : public LazyUniformInitTpl<UniformInitOps, Typechecker>
{
public:
	template <typename String_>
	LazyUniformInit(
		const ProgramOps& program,
		const typename UniformInitOps::ParamType param,
		String_&& identifier,
		Typechecker typechecker
	): LazyUniformInitTpl<UniformInitOps, Typechecker>(
		program,
		param,
		std::forward<String_>(identifier),
		typechecker
	){ }
};

class DirectUniformInit
 : public FriendOf<ProgramOps>
 , public UniformInitTypecheckUtils
{
private:
	GLuint _program;
	GLint _location;

	template <class Typechecker>
	GLint _init_location(Typechecker& typechecker, GLint location)
	{
		return UniformInitTypecheckUtils::_typecheck(
			typechecker,
			_program,
			location,
			"<N/A>"
		);
	}
public:
	template <class Typechecker>
	DirectUniformInit(
		const ProgramOps& program,
		Nothing,
		GLint location,
		Typechecker typechecker
	): _program(FriendOf<ProgramOps>::GetName(program))
	 , _location(_init_location(typechecker, location))
	{ }

	template <class Typechecker>
	DirectUniformInit(
		GLuint program,
		Nothing,
		GLint location,
		Typechecker typechecker
	): _program(program)
	 , _location(_init_location(typechecker, location))
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

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/auxiliary/uniform_init.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
