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

BOOST_PYTHON_MODULE(oglplus)
{
#include "oglplus/_enums_call.ipp"

	oglplus_py_Auxiliary();
	oglplus_py_String();
	oglplus_py_Angle();
}
