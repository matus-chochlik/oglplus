/*
 *  .file oglplus/vector_swizzle.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/vector.hpp>

#include <boost/python.hpp>

#include "./vector_swizzle.ipp"

void oglplus_py_Vector_Swizzle(void)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	oglplus_py_export_Vector_Swizzle_xyzw((Vec1f*)0, "SwizzleVec1f_xyzw");
	oglplus_py_export_Vector_Swizzle_xyzw((Vec2f*)0, "SwizzleVec2f_xyzw");
	oglplus_py_export_Vector_Swizzle_xyzw((Vec3f*)0, "SwizzleVec3f_xyzw");
	oglplus_py_export_Vector_Swizzle_xyzw((Vec4f*)0, "SwizzleVec4f_xyzw");
}

