/*
 *  .file eglplus/enums/rendering_api.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/rendering_api.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/rendering_api.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void eglplus_py_rendering_api(void)
{
	boost::python::enum_<eglplus::RenderingAPI>("RenderingAPI")
#if defined EGL_OPENGL_API
# if defined OpenGL
#  pragma push_macro("OpenGL")
#  undef OpenGL
	.value("OpenGL", eglplus::RenderingAPI::OpenGL)
#  pragma pop_macro("OpenGL")
# else
	.value("OpenGL", eglplus::RenderingAPI::OpenGL)
# endif
#endif
#if defined EGL_OPENGL_ES_API
# if defined OpenGL_ES
#  pragma push_macro("OpenGL_ES")
#  undef OpenGL_ES
	.value("OpenGL_ES", eglplus::RenderingAPI::OpenGL_ES)
#  pragma pop_macro("OpenGL_ES")
# else
	.value("OpenGL_ES", eglplus::RenderingAPI::OpenGL_ES)
# endif
#endif
#if defined EGL_OPENVG_API
# if defined OpenVG
#  pragma push_macro("OpenVG")
#  undef OpenVG
	.value("OpenVG", eglplus::RenderingAPI::OpenVG)
#  pragma pop_macro("OpenVG")
# else
	.value("OpenVG", eglplus::RenderingAPI::OpenVG)
# endif
#endif
#if defined EGL_NONE
# if defined None
#  pragma push_macro("None")
#  undef None
	.value("None", eglplus::RenderingAPI::None)
#  pragma pop_macro("None")
# else
	.value("None", eglplus::RenderingAPI::None)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::RenderingAPI) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::RenderingAPI
		>
	>("aux_CastIterRange_RenderingAPI");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::RenderingAPI
	> (*PEnumValueRange)(eglplus::RenderingAPI) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
