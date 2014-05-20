/**
 *  @file oglplus/prog_var/lazy.hpp
 *  @brief Lazy program variable wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_LAZY_1405052234_HPP
#define OGLPLUS_PROG_VAR_LAZY_1405052234_HPP

#include <oglplus/prog_var/wrapper.hpp>
#include <oglplus/string/def.hpp>
#include <oglplus/string/ref.hpp>

namespace oglplus {

template <typename ProgVar>
class Lazy
 : public ProgVar
{
private:
	String _identifier;
public:
	Lazy(ProgramName program, String&& identifier)
	 : ProgVar(program)
	 , _identifier(std::move(identifier))
	{ }

	Lazy& Init(void)
	{
		if(!this->IsActive())
		{
			this->BindTo(_identifier);
			ProgVar::RequireActive(_identifier);
			_identifier.clear();
		}
		return *this;
	}

	Lazy& TryInit(void)
	{
		if(!this->IsActive())
		{
			if(this->BindTo(_identifier, false).IsActive())
			{
				_identifier.clear();
			}
		}
		return *this;
	}

	ProgVar operator[](std::size_t offset)
	{
		Init();
		return ProgVar(
			ProgramName(this->_program),
			this->_location+offset
		);
	}

	template <typename T>
	void Set(T&& value)
	{
		Init();
		ProgVar::Set(std::forward<T>(value));
	}

	template <typename T0, typename T1>
	void Set(T0&& v0, T1&& v1)
	{
		Init();
		ProgVar::Set(
			std::forward<T0>(v0),
			std::forward<T1>(v1)
		);
	}

	template <typename T0, typename T1, typename T2>
	void Set(T0&& v0, T1&& v1, T2&& v2)
	{
		Init();
		ProgVar::Set(
			std::forward<T0>(v0),
			std::forward<T1>(v1),
			std::forward<T1>(v2)
		);
	}

	template <typename T0, typename T1, typename T2, typename T3>
	void Set(T0&& v0, T1&& v1, T2&& v2, T3&& v3)
	{
		Init();
		ProgVar::Set(
			std::forward<T0>(v0),
			std::forward<T1>(v1),
			std::forward<T1>(v2),
			std::forward<T1>(v3)
		);
	}
};

} // namespace oglplus

#endif // include guard
