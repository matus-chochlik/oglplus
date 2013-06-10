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

#include "range.hpp"
#include "attrib_list.hpp"

void eglplus_py_Surface(void)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	eglplus_py_export_AttributeList<eglplus::SurfaceAttribs>("SurfaceAttribs");

	bpy::class_<Surface, boost::noncopyable>("Surface", bpy::no_init)
		.def("Pbuffer", &Surface::Pbuffer).staticmethod("Pbuffer")
		.def("Pixmap", &Surface::Pixmap).staticmethod("Pixmap")
		.def("Window", &Surface::Window).staticmethod("Window")
		.def("SwapBuffers", &Surface::SwapBuffers)
		.def("CopyBuffers", &Surface::CopyBuffers)
		.def("Attrib", &Surface::Attrib)
		.def("GetAttrib", &Surface::GetAttrib)
		.def("Width",  (EGLint (Surface::*)(void) const)&Surface::Width)
		.def("Height", (EGLint (Surface::*)(void) const)&Surface::Height)
		.def("RenderBuffer", (RenderBuffer(Surface::*)(void) const)&Surface::RenderBuffer)
		.def("RenderBuffer", (void (Surface::*)(RenderBuffer))&Surface::RenderBuffer)
		.def("MultisampleResolve", (MultisampleResolve(Surface::*)(void) const)&Surface::MultisampleResolve)
		.def("MultisampleResolve", (void (Surface::*)(MultisampleResolve))&Surface::MultisampleResolve)
		.def("SwapBehavior", (SwapBehavior(Surface::*)(void) const)&Surface::SwapBehavior)
		.def("SwapBehavior", (void (Surface::*)(SwapBehavior))&Surface::SwapBehavior)
		.def("TextureTarget", (TextureTarget(Surface::*)(void) const)&Surface::TextureTarget)
		.def("TextureFormat", (TextureFormat(Surface::*)(void) const)&Surface::TextureFormat)
		.def("VGColorspace", (VGColorspace(Surface::*)(void) const)&Surface::VGColorspace)
		.def("VGAlphaFormat", (VGAlphaFormat(Surface::*)(void) const)&Surface::VGAlphaFormat)
	;
}

