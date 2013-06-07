/*
 *  .file oglplus/enums/tess_gen_primitive_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/tess_gen_primitive_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/primitive_type.hpp>

#include <boost/python.hpp>

void oglplus_py_tess_gen_primitive_type(void)
{
	boost::python::enum_<oglplus::TessGenPrimitiveType>("TessGenPrimitiveType")
#if defined GL_QUADS
# if defined Quads
#  pragma push_macro("Quads")
#  undef Quads
	.value("Quads", oglplus::TessGenPrimitiveType::Quads)
#  pragma pop_macro("Quads")
# else
	.value("Quads", oglplus::TessGenPrimitiveType::Quads)
# endif
#endif
#if defined GL_TRIANGLES
# if defined Triangles
#  pragma push_macro("Triangles")
#  undef Triangles
	.value("Triangles", oglplus::TessGenPrimitiveType::Triangles)
#  pragma pop_macro("Triangles")
# else
	.value("Triangles", oglplus::TessGenPrimitiveType::Triangles)
# endif
#endif
#if defined GL_ISOLINES
# if defined Isolines
#  pragma push_macro("Isolines")
#  undef Isolines
	.value("Isolines", oglplus::TessGenPrimitiveType::Isolines)
#  pragma pop_macro("Isolines")
# else
	.value("Isolines", oglplus::TessGenPrimitiveType::Isolines)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TessGenPrimitiveType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
