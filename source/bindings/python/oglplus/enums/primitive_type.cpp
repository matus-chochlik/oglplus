/*
 *  .file oglplus/enums/primitive_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/primitive_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/primitive_type.hpp>

#include <boost/python.hpp>

void oglplus_py_primitive_type(void)
{
	boost::python::enum_<oglplus::PrimitiveType>("PrimitiveType")
#if defined GL_POINTS
# if defined Points
#  pragma push_macro("Points")
#  undef Points
	.value("Points", oglplus::PrimitiveType::Points)
#  pragma pop_macro("Points")
# else
	.value("Points", oglplus::PrimitiveType::Points)
# endif
#endif
#if defined GL_LINE_STRIP
# if defined LineStrip
#  pragma push_macro("LineStrip")
#  undef LineStrip
	.value("LineStrip", oglplus::PrimitiveType::LineStrip)
#  pragma pop_macro("LineStrip")
# else
	.value("LineStrip", oglplus::PrimitiveType::LineStrip)
# endif
#endif
#if defined GL_LINE_LOOP
# if defined LineLoop
#  pragma push_macro("LineLoop")
#  undef LineLoop
	.value("LineLoop", oglplus::PrimitiveType::LineLoop)
#  pragma pop_macro("LineLoop")
# else
	.value("LineLoop", oglplus::PrimitiveType::LineLoop)
# endif
#endif
#if defined GL_LINES
# if defined Lines
#  pragma push_macro("Lines")
#  undef Lines
	.value("Lines", oglplus::PrimitiveType::Lines)
#  pragma pop_macro("Lines")
# else
	.value("Lines", oglplus::PrimitiveType::Lines)
# endif
#endif
#if defined GL_TRIANGLE_STRIP
# if defined TriangleStrip
#  pragma push_macro("TriangleStrip")
#  undef TriangleStrip
	.value("TriangleStrip", oglplus::PrimitiveType::TriangleStrip)
#  pragma pop_macro("TriangleStrip")
# else
	.value("TriangleStrip", oglplus::PrimitiveType::TriangleStrip)
# endif
#endif
#if defined GL_TRIANGLE_FAN
# if defined TriangleFan
#  pragma push_macro("TriangleFan")
#  undef TriangleFan
	.value("TriangleFan", oglplus::PrimitiveType::TriangleFan)
#  pragma pop_macro("TriangleFan")
# else
	.value("TriangleFan", oglplus::PrimitiveType::TriangleFan)
# endif
#endif
#if defined GL_TRIANGLES
# if defined Triangles
#  pragma push_macro("Triangles")
#  undef Triangles
	.value("Triangles", oglplus::PrimitiveType::Triangles)
#  pragma pop_macro("Triangles")
# else
	.value("Triangles", oglplus::PrimitiveType::Triangles)
# endif
#endif
#if defined GL_LINES_ADJACENCY
# if defined LinesAdjacency
#  pragma push_macro("LinesAdjacency")
#  undef LinesAdjacency
	.value("LinesAdjacency", oglplus::PrimitiveType::LinesAdjacency)
#  pragma pop_macro("LinesAdjacency")
# else
	.value("LinesAdjacency", oglplus::PrimitiveType::LinesAdjacency)
# endif
#endif
#if defined GL_LINE_STRIP_ADJACENCY
# if defined LineStripAdjacency
#  pragma push_macro("LineStripAdjacency")
#  undef LineStripAdjacency
	.value("LineStripAdjacency", oglplus::PrimitiveType::LineStripAdjacency)
#  pragma pop_macro("LineStripAdjacency")
# else
	.value("LineStripAdjacency", oglplus::PrimitiveType::LineStripAdjacency)
# endif
#endif
#if defined GL_TRIANGLES_ADJACENCY
# if defined TrianglesAdjacency
#  pragma push_macro("TrianglesAdjacency")
#  undef TrianglesAdjacency
	.value("TrianglesAdjacency", oglplus::PrimitiveType::TrianglesAdjacency)
#  pragma pop_macro("TrianglesAdjacency")
# else
	.value("TrianglesAdjacency", oglplus::PrimitiveType::TrianglesAdjacency)
# endif
#endif
#if defined GL_TRIANGLE_STRIP_ADJACENCY
# if defined TriangleStripAdjacency
#  pragma push_macro("TriangleStripAdjacency")
#  undef TriangleStripAdjacency
	.value("TriangleStripAdjacency", oglplus::PrimitiveType::TriangleStripAdjacency)
#  pragma pop_macro("TriangleStripAdjacency")
# else
	.value("TriangleStripAdjacency", oglplus::PrimitiveType::TriangleStripAdjacency)
# endif
#endif
#if defined GL_PATCHES
# if defined Patches
#  pragma push_macro("Patches")
#  undef Patches
	.value("Patches", oglplus::PrimitiveType::Patches)
#  pragma pop_macro("Patches")
# else
	.value("Patches", oglplus::PrimitiveType::Patches)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::PrimitiveType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
