/**
 *  @file oglplus/prog_var/typechecked.hpp
 *  @brief Typechecked program variable wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_TYPECHECKED_1405052234_HPP
#define OGLPLUS_PROG_VAR_TYPECHECKED_1405052234_HPP

#include <oglplus/prog_var/wrapper.hpp>

namespace oglplus {

template <typename OpsTag, typename VarTag, typename ChkTag, typename T>
class Typechecked<ProgVar<OpsTag, VarTag, ChkTag, T>>
 : public ProgVar<OpsTag, VarTag, tag::Typecheck, T>
{
private:
	typedef ProgVar<OpsTag, VarTag, tag::Typecheck, T> Base;
public:
#if !OGLPLUS_NO_INHERITED_CONSTRUCTORS
	using Base::Base;
#else
	OGLPLUS_IMPLEMENT_PROG_VAR_CTRS(VarTag, Typechecked, Base)
#endif
};

template <typename ProgVar>
class Typechecked
 : public Typechecked<typename BaseProgVar<ProgVar>::Type>
{
private:
	typedef Typechecked<typename BaseProgVar<ProgVar>::Type> Base;
public:
#if !OGLPLUS_NO_INHERITED_CONSTRUCTORS
	using Base::Base;
#else
	template <typename VarTag>
	OGLPLUS_IMPLEMENT_PROG_VAR_CTRS(VarTag, Typechecked, Base)
#endif
};

template <typename ProgVar>
struct BaseProgVar<Typechecked<ProgVar>>
{
	typedef typename BaseProgVar<ProgVar>::Type Type;
};

} // namespace oglplus

#endif // include guard
