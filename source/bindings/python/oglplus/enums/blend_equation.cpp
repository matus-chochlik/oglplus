/*
 *  .file oglplus/enums/blend_equation.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/blend_equation.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/blend_func.hpp>

#include <boost/python.hpp>

void oglplus_py_blend_equation(void)
{
	boost::python::enum_<oglplus::BlendEquation>("BlendEquation")
#if defined GL_FUNC_ADD
# if defined Add
#  pragma push_macro("Add")
#  undef Add
	.value("Add", oglplus::BlendEquation::Add)
#  pragma pop_macro("Add")
# else
	.value("Add", oglplus::BlendEquation::Add)
# endif
#endif
#if defined GL_FUNC_SUBTRACT
# if defined Subtract
#  pragma push_macro("Subtract")
#  undef Subtract
	.value("Subtract", oglplus::BlendEquation::Subtract)
#  pragma pop_macro("Subtract")
# else
	.value("Subtract", oglplus::BlendEquation::Subtract)
# endif
#endif
#if defined GL_FUNC_REVERSE_SUBTRACT
# if defined ReverseSubtract
#  pragma push_macro("ReverseSubtract")
#  undef ReverseSubtract
	.value("ReverseSubtract", oglplus::BlendEquation::ReverseSubtract)
#  pragma pop_macro("ReverseSubtract")
# else
	.value("ReverseSubtract", oglplus::BlendEquation::ReverseSubtract)
# endif
#endif
#if defined GL_MIN
# if defined Min
#  pragma push_macro("Min")
#  undef Min
	.value("Min", oglplus::BlendEquation::Min)
#  pragma pop_macro("Min")
# else
	.value("Min", oglplus::BlendEquation::Min)
# endif
#endif
#if defined GL_MAX
# if defined Max
#  pragma push_macro("Max")
#  undef Max
	.value("Max", oglplus::BlendEquation::Max)
#  pragma pop_macro("Max")
# else
	.value("Max", oglplus::BlendEquation::Max)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::BlendEquation) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
