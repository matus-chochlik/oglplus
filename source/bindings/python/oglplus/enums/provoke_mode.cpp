/*
 *  .file oglplus/enums/provoke_mode.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/provoke_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/provoke_mode.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_provoke_mode(void)
{
	boost::python::enum_<oglplus::ProvokeMode>("ProvokeMode")
#if defined GL_FIRST_VERTEX_CONVENTION
# if defined FirstVertexConvention
#  pragma push_macro("FirstVertexConvention")
#  undef FirstVertexConvention
	.value("FirstVertexConvention", oglplus::ProvokeMode::FirstVertexConvention)
#  pragma pop_macro("FirstVertexConvention")
# else
	.value("FirstVertexConvention", oglplus::ProvokeMode::FirstVertexConvention)
# endif
#endif
#if defined GL_LAST_VERTEX_CONVENTION
# if defined LastVertexConvention
#  pragma push_macro("LastVertexConvention")
#  undef LastVertexConvention
	.value("LastVertexConvention", oglplus::ProvokeMode::LastVertexConvention)
#  pragma pop_macro("LastVertexConvention")
# else
	.value("LastVertexConvention", oglplus::ProvokeMode::LastVertexConvention)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ProvokeMode) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::ProvokeMode
		>
	>("aux_CastIterRange_ProvokeMode");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::ProvokeMode
	> (*PEnumValueRange)(oglplus::ProvokeMode) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
