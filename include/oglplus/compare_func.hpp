/**
 *  @file oglplus/compare_func.hpp
 *  @brief OpenGL test/comparison function enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CMP_FUNC_1107121519_HPP
#define OGLPLUS_CMP_FUNC_1107121519_HPP

namespace oglplus {

enum class CompareFunc : GLenum
{
	LEqual = GL_LEQUAL,
	GEqual = GL_GEQUAL,
	Less  = GL_LESS,
	Greater = GL_GREATER,
	Equal = GL_EQUAL,
	NotEqual = GL_NOTEQUAL,
	Always = GL_ALWAYS,
	Never = GL_NEVER
};

} // namespace oglplus

#endif // include guard
