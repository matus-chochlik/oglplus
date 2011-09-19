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

/// Comparison function type enumeration
enum class CompareFunction : GLenum
{
	/// Less-than or equal (LEQUAL)
	LEqual = GL_LEQUAL,
	/// Greater-than or equal (GEQUAL)
	GEqual = GL_GEQUAL,
	/// Less-than (LESS)
	Less  = GL_LESS,
	/// Greater-than (GREATER)
	Greater = GL_GREATER,
	/// Equal (EQUAL)
	Equal = GL_EQUAL,
	/// Not equal (NOTEQUAL)
	NotEqual = GL_NOTEQUAL,
	/// Always true (ALWAYS)
	Always = GL_ALWAYS,
	/// Always false (NEVER)
	Never = GL_NEVER
};

/// Alternate name for the CompareFunction enumeration
typedef CompareFunction CompareFn;

} // namespace oglplus

#endif // include guard
