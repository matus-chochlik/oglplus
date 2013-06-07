/*
 *  .file oglplus/enums/stencil_operation.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/stencil_operation.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/stencil_op.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_stencil_operation(void)
{
	boost::python::enum_<oglplus::StencilOperation>("StencilOperation")
#if defined GL_KEEP
# if defined Keep
#  pragma push_macro("Keep")
#  undef Keep
	.value("Keep", oglplus::StencilOperation::Keep)
#  pragma pop_macro("Keep")
# else
	.value("Keep", oglplus::StencilOperation::Keep)
# endif
#endif
#if defined GL_ZERO
# if defined Zero
#  pragma push_macro("Zero")
#  undef Zero
	.value("Zero", oglplus::StencilOperation::Zero)
#  pragma pop_macro("Zero")
# else
	.value("Zero", oglplus::StencilOperation::Zero)
# endif
#endif
#if defined GL_REPLACE
# if defined Replace
#  pragma push_macro("Replace")
#  undef Replace
	.value("Replace", oglplus::StencilOperation::Replace)
#  pragma pop_macro("Replace")
# else
	.value("Replace", oglplus::StencilOperation::Replace)
# endif
#endif
#if defined GL_INCR
# if defined Incr
#  pragma push_macro("Incr")
#  undef Incr
	.value("Incr", oglplus::StencilOperation::Incr)
#  pragma pop_macro("Incr")
# else
	.value("Incr", oglplus::StencilOperation::Incr)
# endif
#endif
#if defined GL_DECR
# if defined Decr
#  pragma push_macro("Decr")
#  undef Decr
	.value("Decr", oglplus::StencilOperation::Decr)
#  pragma pop_macro("Decr")
# else
	.value("Decr", oglplus::StencilOperation::Decr)
# endif
#endif
#if defined GL_INVERT
# if defined Invert
#  pragma push_macro("Invert")
#  undef Invert
	.value("Invert", oglplus::StencilOperation::Invert)
#  pragma pop_macro("Invert")
# else
	.value("Invert", oglplus::StencilOperation::Invert)
# endif
#endif
#if defined GL_INCR_WRAP
# if defined IncrWrap
#  pragma push_macro("IncrWrap")
#  undef IncrWrap
	.value("IncrWrap", oglplus::StencilOperation::IncrWrap)
#  pragma pop_macro("IncrWrap")
# else
	.value("IncrWrap", oglplus::StencilOperation::IncrWrap)
# endif
#endif
#if defined GL_DECR_WRAP
# if defined DecrWrap
#  pragma push_macro("DecrWrap")
#  undef DecrWrap
	.value("DecrWrap", oglplus::StencilOperation::DecrWrap)
#  pragma pop_macro("DecrWrap")
# else
	.value("DecrWrap", oglplus::StencilOperation::DecrWrap)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::StencilOperation) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::StencilOperation
		>
	>("aux_CastIterRange_StencilOperation");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::StencilOperation
	> (*PEnumValueRange)(oglplus::StencilOperation) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
