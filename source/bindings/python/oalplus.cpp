/*
 *  .file oalplus.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/alut.hpp>
#include <oalplus/lib.hpp>
#include <boost/python.hpp>

#include "oalplus/_enums_decl.ipp"

void oalplus_py_Auxiliary(void);
void oalplus_py_Device(void);
void oalplus_py_Context(void);
void oalplus_py_Angle(void);
void oalplus_py_Vector(void);
void oalplus_py_Buffer(void);
void oalplus_py_Listener(void);

BOOST_PYTHON_MODULE(oalplus)
{
#include "oalplus/_enums_call.ipp"

	oalplus_py_Auxiliary();
	oalplus_py_Device();
	oalplus_py_Context();
	oalplus_py_Angle();
	oalplus_py_Vector();
	oalplus_py_Buffer();
	oalplus_py_Listener();
}
