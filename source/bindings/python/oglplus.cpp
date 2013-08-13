/*
 *  .file oglplus.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/lib.hpp>
#include <boost/python.hpp>

#include "oglplus/_enums_decl.ipp"

void oglplus_py_Auxiliary(void);
void oglplus_py_String(void);
void oglplus_py_Angle(void);
void oglplus_py_Vector(void);
void oglplus_py_Vector_Swizzle(void);
void oglplus_py_Plane(void);

void oglplus_py_Buffer(void);

BOOST_PYTHON_MODULE(oglplus)
{
#include "oglplus/_enums_call.ipp"

	oglplus_py_Auxiliary();
	oglplus_py_String();
	oglplus_py_Angle();
	oglplus_py_Vector();
	oglplus_py_Vector_Swizzle();
	oglplus_py_Plane();

	oglplus_py_Buffer();
}
