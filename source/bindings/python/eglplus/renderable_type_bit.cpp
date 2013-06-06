/*
 *  .file eglplus/renderable_type_bit.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/renderable_type_bit.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/renderable_type_bit.hpp>

#include <boost/python.hpp>

void eglplus_py_renderable_type_bit(void)
{
	boost::python::enum_<eglplus::RenderableTypeBit>("RenderableTypeBit")
#if defined EGL_OPENGL_BIT
# if defined OpenGL
#  pragma push_macro("OpenGL")
#  undef OpenGL
	.value("OpenGL", eglplus::RenderableTypeBit::OpenGL)
#  pragma pop_macro("OpenGL")
# else
	.value("OpenGL", eglplus::RenderableTypeBit::OpenGL)
# endif
#endif
#if defined EGL_OPENGL_ES_BIT
# if defined OpenGL_ES
#  pragma push_macro("OpenGL_ES")
#  undef OpenGL_ES
	.value("OpenGL_ES", eglplus::RenderableTypeBit::OpenGL_ES)
#  pragma pop_macro("OpenGL_ES")
# else
	.value("OpenGL_ES", eglplus::RenderableTypeBit::OpenGL_ES)
# endif
#endif
#if defined EGL_OPENGL_ES2_BIT
# if defined OpenGL_ES2
#  pragma push_macro("OpenGL_ES2")
#  undef OpenGL_ES2
	.value("OpenGL_ES2", eglplus::RenderableTypeBit::OpenGL_ES2)
#  pragma pop_macro("OpenGL_ES2")
# else
	.value("OpenGL_ES2", eglplus::RenderableTypeBit::OpenGL_ES2)
# endif
#endif
#if defined EGL_OPENGL_ES3_BIT_KHR
# if defined OpenGL_ES3
#  pragma push_macro("OpenGL_ES3")
#  undef OpenGL_ES3
	.value("OpenGL_ES3", eglplus::RenderableTypeBit::OpenGL_ES3)
#  pragma pop_macro("OpenGL_ES3")
# else
	.value("OpenGL_ES3", eglplus::RenderableTypeBit::OpenGL_ES3)
# endif
#endif
#if defined EGL_OPENVG_BIT
# if defined OpenVG
#  pragma push_macro("OpenVG")
#  undef OpenVG
	.value("OpenVG", eglplus::RenderableTypeBit::OpenVG)
#  pragma pop_macro("OpenVG")
# else
	.value("OpenVG", eglplus::RenderableTypeBit::OpenVG)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::RenderableTypeBit) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
