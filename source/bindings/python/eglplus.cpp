/*
 *  .file eglplus.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/lib.hpp>
#include <boost/python.hpp>

#include "eglplus/_enums_decl.ipp"

void eglplus_py_Auxiliary(void);
void eglplus_py_String(void);
void eglplus_py_Bitfields(void);
void eglplus_py_Display(void);
void eglplus_py_Initializer(void);
void eglplus_py_Configs(void);
void eglplus_py_Surface(void);
void eglplus_py_Context(void);

BOOST_PYTHON_MODULE(eglplus)
{
#include "eglplus/_enums_call.ipp"

	eglplus_py_Auxiliary();
	eglplus_py_String();
	eglplus_py_Bitfields();
	eglplus_py_Display();
	eglplus_py_Initializer();
	eglplus_py_Configs();
	eglplus_py_Surface();
	eglplus_py_Context();
}
