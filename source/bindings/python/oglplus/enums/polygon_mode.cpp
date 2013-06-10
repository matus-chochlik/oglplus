/*
 *  .file oglplus/enums/polygon_mode.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/polygon_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/polygon_mode.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_polygon_mode(void)
{
	boost::python::enum_<oglplus::PolygonMode>("PolygonMode")
#if defined GL_POINT
# if defined Point
#  pragma push_macro("Point")
#  undef Point
	.value("Point", oglplus::PolygonMode::Point)
#  pragma pop_macro("Point")
# else
	.value("Point", oglplus::PolygonMode::Point)
# endif
#endif
#if defined GL_LINE
# if defined Line
#  pragma push_macro("Line")
#  undef Line
	.value("Line", oglplus::PolygonMode::Line)
#  pragma pop_macro("Line")
# else
	.value("Line", oglplus::PolygonMode::Line)
# endif
#endif
#if defined GL_FILL
# if defined Fill
#  pragma push_macro("Fill")
#  undef Fill
	.value("Fill", oglplus::PolygonMode::Fill)
#  pragma pop_macro("Fill")
# else
	.value("Fill", oglplus::PolygonMode::Fill)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::PolygonMode) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::PolygonMode
		>
	>("aux_CastIterRange_PolygonMode");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::PolygonMode
	> (*PEnumValueRange)(oglplus::PolygonMode) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
