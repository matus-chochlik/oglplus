/**
 *  @file oglplus/prog_var/type_ops.hpp
 *  @brief Program variable type operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_TYPE_OPS_1405052234_HPP
#define OGLPLUS_PROG_VAR_TYPE_OPS_1405052234_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/object/name.hpp>

namespace oglplus {

template <>
class ProgVarTypeOps<tag::Uniform>
{
protected:
	static GLenum GetType(ProgramName, GLint location, StrCRef identifier);
};

} // namespace oglplus

#endif // include guard
