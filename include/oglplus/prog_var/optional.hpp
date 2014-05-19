/**
 *  @file oglplus/prog_var/optional.hpp
 *  @brief Optional program variable wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_OPTIONAL_1405052234_HPP
#define OGLPLUS_PROG_VAR_OPTIONAL_1405052234_HPP

#include <oglplus/prog_var/wrapper.hpp>

namespace oglplus {

template <typename OpsTag, typename VarTag, typename ChkTag, typename T>
class Optional<ProgVar<OpsTag, VarTag, ChkTag, T>>
 : public ProgVar<OpsTag, VarTag, ChkTag, T>
{
private:
	typedef ProgVar<OpsTag, VarTag, ChkTag, T> Base;
public:
	Optional(ProgramName program, StrCRef identifier)
	 : Base(program, identifier, false)
	{ }
};

template <template <class> class Wrapper, typename OpsTag, typename VarTag, typename ChkTag, typename T>
class Optional<Wrapper<ProgVar<OpsTag, VarTag, ChkTag, T>>>
 : public Wrapper<ProgVar<OpsTag, VarTag, ChkTag, T>>
{
private:
	typedef Wrapper<ProgVar<OpsTag, VarTag, ChkTag, T>> Base;
public:
	Optional(ProgramName program, StrCRef identifier)
	 : Base(program, identifier, false)
	{ }
};

} // namespace oglplus

#endif // include guard
