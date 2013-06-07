/*
 *  .file oglplus/enums/compare_function.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/compare_function.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/compare_func.hpp>

#include <boost/python.hpp>

void oglplus_py_compare_function(void)
{
	boost::python::enum_<oglplus::CompareFunction>("CompareFunction")
#if defined GL_LEQUAL
# if defined LEqual
#  pragma push_macro("LEqual")
#  undef LEqual
	.value("LEqual", oglplus::CompareFunction::LEqual)
#  pragma pop_macro("LEqual")
# else
	.value("LEqual", oglplus::CompareFunction::LEqual)
# endif
#endif
#if defined GL_GEQUAL
# if defined GEqual
#  pragma push_macro("GEqual")
#  undef GEqual
	.value("GEqual", oglplus::CompareFunction::GEqual)
#  pragma pop_macro("GEqual")
# else
	.value("GEqual", oglplus::CompareFunction::GEqual)
# endif
#endif
#if defined GL_LESS
# if defined Less
#  pragma push_macro("Less")
#  undef Less
	.value("Less", oglplus::CompareFunction::Less)
#  pragma pop_macro("Less")
# else
	.value("Less", oglplus::CompareFunction::Less)
# endif
#endif
#if defined GL_GREATER
# if defined Greater
#  pragma push_macro("Greater")
#  undef Greater
	.value("Greater", oglplus::CompareFunction::Greater)
#  pragma pop_macro("Greater")
# else
	.value("Greater", oglplus::CompareFunction::Greater)
# endif
#endif
#if defined GL_EQUAL
# if defined Equal
#  pragma push_macro("Equal")
#  undef Equal
	.value("Equal", oglplus::CompareFunction::Equal)
#  pragma pop_macro("Equal")
# else
	.value("Equal", oglplus::CompareFunction::Equal)
# endif
#endif
#if defined GL_NOTEQUAL
# if defined NotEqual
#  pragma push_macro("NotEqual")
#  undef NotEqual
	.value("NotEqual", oglplus::CompareFunction::NotEqual)
#  pragma pop_macro("NotEqual")
# else
	.value("NotEqual", oglplus::CompareFunction::NotEqual)
# endif
#endif
#if defined GL_ALWAYS
# if defined Always
#  pragma push_macro("Always")
#  undef Always
	.value("Always", oglplus::CompareFunction::Always)
#  pragma pop_macro("Always")
# else
	.value("Always", oglplus::CompareFunction::Always)
# endif
#endif
#if defined GL_NEVER
# if defined Never
#  pragma push_macro("Never")
#  undef Never
	.value("Never", oglplus::CompareFunction::Never)
#  pragma pop_macro("Never")
# else
	.value("Never", oglplus::CompareFunction::Never)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::CompareFunction) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
