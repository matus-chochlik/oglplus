/*
 *  .file oglplus/enums/patch_parameter.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/patch_parameter.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/patch_parameter.hpp>

#include <boost/python.hpp>

void oglplus_py_patch_parameter(void)
{
	boost::python::enum_<oglplus::PatchParameter>("PatchParameter")
#if defined GL_PATCH_VERTICES
# if defined PatchVertices
#  pragma push_macro("PatchVertices")
#  undef PatchVertices
	.value("PatchVertices", oglplus::PatchParameter::PatchVertices)
#  pragma pop_macro("PatchVertices")
# else
	.value("PatchVertices", oglplus::PatchParameter::PatchVertices)
# endif
#endif
#if defined GL_PATCH_DEFAULT_OUTER_LEVEL
# if defined PatchDefaultOuterLevel
#  pragma push_macro("PatchDefaultOuterLevel")
#  undef PatchDefaultOuterLevel
	.value("PatchDefaultOuterLevel", oglplus::PatchParameter::PatchDefaultOuterLevel)
#  pragma pop_macro("PatchDefaultOuterLevel")
# else
	.value("PatchDefaultOuterLevel", oglplus::PatchParameter::PatchDefaultOuterLevel)
# endif
#endif
#if defined GL_PATCH_DEFAULT_INNER_LEVEL
# if defined PatchDefaultInnerLevel
#  pragma push_macro("PatchDefaultInnerLevel")
#  undef PatchDefaultInnerLevel
	.value("PatchDefaultInnerLevel", oglplus::PatchParameter::PatchDefaultInnerLevel)
#  pragma pop_macro("PatchDefaultInnerLevel")
# else
	.value("PatchDefaultInnerLevel", oglplus::PatchParameter::PatchDefaultInnerLevel)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::PatchParameter) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
