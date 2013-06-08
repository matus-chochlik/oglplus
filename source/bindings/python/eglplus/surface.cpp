/*
 *  .file eglplus/surface.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/surface.hpp>

#include <boost/python.hpp>

#include "_py_range_adapt.hpp"
#include "attrib_list.hpp"

void eglplus_py_Surface(void)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	eglplus_py_export_AttributeList<eglplus::SurfaceAttribs>("SurfaceAttribs");

	EGLint (Surface::*GetWidth)(void) const = &Surface::Width;
	EGLint (Surface::*GetHeight)(void) const = &Surface::Height;
	RenderBuffer (Surface::*GetRenderBuffer)(void) const = &Surface::RenderBuffer;
	void (Surface::*SetRenderBuffer)(RenderBuffer) = &Surface::RenderBuffer;

	bpy::class_<Surface, boost::noncopyable>("Surface", bpy::no_init)
		.def("Pbuffer", &Surface::Pbuffer).staticmethod("Pbuffer")
		.def("Pixmap", &Surface::Pixmap).staticmethod("Pixmap")
		.def("Window", &Surface::Window).staticmethod("Window")
		.def("SwapBuffers", &Surface::SwapBuffers)
		.def("CopyBuffers", &Surface::CopyBuffers)
		.def("Attrib", &Surface::Attrib)
		.def("GetAttrib", &Surface::GetAttrib)
		.def("Width", GetWidth)
		.def("Height", GetHeight)
		.def("RenderBuffer", GetRenderBuffer)
		.def("RenderBuffer", SetRenderBuffer)
	;
}

