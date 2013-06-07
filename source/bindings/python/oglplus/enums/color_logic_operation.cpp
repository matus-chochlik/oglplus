/*
 *  .file oglplus/enums/color_logic_operation.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/color_logic_operation.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/color_log_op.hpp>

#include <boost/python.hpp>

void oglplus_py_color_logic_operation(void)
{
	boost::python::enum_<oglplus::ColorLogicOperation>("ColorLogicOperation")
#if defined GL_CLEAR
# if defined Clear
#  pragma push_macro("Clear")
#  undef Clear
	.value("Clear", oglplus::ColorLogicOperation::Clear)
#  pragma pop_macro("Clear")
# else
	.value("Clear", oglplus::ColorLogicOperation::Clear)
# endif
#endif
#if defined GL_AND
# if defined And
#  pragma push_macro("And")
#  undef And
	.value("And", oglplus::ColorLogicOperation::And)
#  pragma pop_macro("And")
# else
	.value("And", oglplus::ColorLogicOperation::And)
# endif
#endif
#if defined GL_AND_REVERSE
# if defined AndReverse
#  pragma push_macro("AndReverse")
#  undef AndReverse
	.value("AndReverse", oglplus::ColorLogicOperation::AndReverse)
#  pragma pop_macro("AndReverse")
# else
	.value("AndReverse", oglplus::ColorLogicOperation::AndReverse)
# endif
#endif
#if defined GL_COPY
# if defined Copy
#  pragma push_macro("Copy")
#  undef Copy
	.value("Copy", oglplus::ColorLogicOperation::Copy)
#  pragma pop_macro("Copy")
# else
	.value("Copy", oglplus::ColorLogicOperation::Copy)
# endif
#endif
#if defined GL_AND_INVERTED
# if defined AndInverted
#  pragma push_macro("AndInverted")
#  undef AndInverted
	.value("AndInverted", oglplus::ColorLogicOperation::AndInverted)
#  pragma pop_macro("AndInverted")
# else
	.value("AndInverted", oglplus::ColorLogicOperation::AndInverted)
# endif
#endif
#if defined GL_NOOP
# if defined Noop
#  pragma push_macro("Noop")
#  undef Noop
	.value("Noop", oglplus::ColorLogicOperation::Noop)
#  pragma pop_macro("Noop")
# else
	.value("Noop", oglplus::ColorLogicOperation::Noop)
# endif
#endif
#if defined GL_XOR
# if defined Xor
#  pragma push_macro("Xor")
#  undef Xor
	.value("Xor", oglplus::ColorLogicOperation::Xor)
#  pragma pop_macro("Xor")
# else
	.value("Xor", oglplus::ColorLogicOperation::Xor)
# endif
#endif
#if defined GL_OR
# if defined Or
#  pragma push_macro("Or")
#  undef Or
	.value("Or", oglplus::ColorLogicOperation::Or)
#  pragma pop_macro("Or")
# else
	.value("Or", oglplus::ColorLogicOperation::Or)
# endif
#endif
#if defined GL_NOR
# if defined Nor
#  pragma push_macro("Nor")
#  undef Nor
	.value("Nor", oglplus::ColorLogicOperation::Nor)
#  pragma pop_macro("Nor")
# else
	.value("Nor", oglplus::ColorLogicOperation::Nor)
# endif
#endif
#if defined GL_EQUIV
# if defined Equiv
#  pragma push_macro("Equiv")
#  undef Equiv
	.value("Equiv", oglplus::ColorLogicOperation::Equiv)
#  pragma pop_macro("Equiv")
# else
	.value("Equiv", oglplus::ColorLogicOperation::Equiv)
# endif
#endif
#if defined GL_INVERT
# if defined Invert
#  pragma push_macro("Invert")
#  undef Invert
	.value("Invert", oglplus::ColorLogicOperation::Invert)
#  pragma pop_macro("Invert")
# else
	.value("Invert", oglplus::ColorLogicOperation::Invert)
# endif
#endif
#if defined GL_OR_REVERSE
# if defined OrReverse
#  pragma push_macro("OrReverse")
#  undef OrReverse
	.value("OrReverse", oglplus::ColorLogicOperation::OrReverse)
#  pragma pop_macro("OrReverse")
# else
	.value("OrReverse", oglplus::ColorLogicOperation::OrReverse)
# endif
#endif
#if defined GL_COPY_INVERTED
# if defined CopyInverted
#  pragma push_macro("CopyInverted")
#  undef CopyInverted
	.value("CopyInverted", oglplus::ColorLogicOperation::CopyInverted)
#  pragma pop_macro("CopyInverted")
# else
	.value("CopyInverted", oglplus::ColorLogicOperation::CopyInverted)
# endif
#endif
#if defined GL_OR_INVERTED
# if defined OrInverted
#  pragma push_macro("OrInverted")
#  undef OrInverted
	.value("OrInverted", oglplus::ColorLogicOperation::OrInverted)
#  pragma pop_macro("OrInverted")
# else
	.value("OrInverted", oglplus::ColorLogicOperation::OrInverted)
# endif
#endif
#if defined GL_NAND
# if defined Nand
#  pragma push_macro("Nand")
#  undef Nand
	.value("Nand", oglplus::ColorLogicOperation::Nand)
#  pragma pop_macro("Nand")
# else
	.value("Nand", oglplus::ColorLogicOperation::Nand)
# endif
#endif
#if defined GL_SET
# if defined Set
#  pragma push_macro("Set")
#  undef Set
	.value("Set", oglplus::ColorLogicOperation::Set)
#  pragma pop_macro("Set")
# else
	.value("Set", oglplus::ColorLogicOperation::Set)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ColorLogicOperation) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
