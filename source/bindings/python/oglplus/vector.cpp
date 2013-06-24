/*
 *  .file oglplus/vector.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/vector.hpp>

#include <boost/python.hpp>

#include "./vector.hpp"

void oglplus_py_Vector(void)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	oglplus_py_export_Vector((Vec1f*)0, "Vec1f");
	oglplus_py_export_Vector((Vec2f*)0, "Vec2f");
	oglplus_py_export_Vector((Vec3f*)0, "Vec3f");
	oglplus_py_export_Vector((Vec4f*)0, "Vec4f");

	oglplus_py_export_Vector((Vec1d*)0, "Vec1d");
	oglplus_py_export_Vector((Vec2d*)0, "Vec2d");
	oglplus_py_export_Vector((Vec3d*)0, "Vec3d");
	oglplus_py_export_Vector((Vec4d*)0, "Vec4d");

}

