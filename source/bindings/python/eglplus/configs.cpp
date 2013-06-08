/*
 *  .file eglplus/configs.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/configs.hpp>

#include <boost/python.hpp>

#include "_py_range_adapt.hpp"
#include "attrib_list.hpp"

void eglplus_py_Configs(void)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	eglplus_py_export_AttributeList<eglplus::ConfigAttribs>("ConfigAttribs");

	bpy::class_<Config>("Config", bpy::no_init)
		.def("GetAttrib", &Config::GetAttrib)
		.def("ConfigId", &Config::ConfigId)
		.def("BufferSize", &Config::BufferSize)
		.def("RedSize", &Config::RedSize)
		.def("GreenSize", &Config::GreenSize)
		.def("BlueSize", &Config::BlueSize)
		.def("AlphaSize", &Config::AlphaSize)
		.def("DepthSize", &Config::DepthSize)
		.def("LuminanceSize", &Config::LuminanceSize)
		.def("MaxPbufferWidth", &Config::MaxPbufferWidth)
		.def("MaxPbufferHeight", &Config::MaxPbufferHeight)
		.def("MaxPbufferPixels", &Config::MaxPbufferPixels)
		.def("ConfigCaveat", &Config::ConfigCaveat)
		.def("ColorBufferType", &Config::ColorBufferType)
		.def("TransparentType", &Config::TransparentType)
		.def("RenderableTypes", &Config::RenderableTypes)
		.def("SurfaceTypes", &Config::SurfaceTypes)
		.def("Conformant", &Config::Conformant)
	;

	eglplus_py_export_range<Configs::ConfigRange>("ConfigRange");

	bpy::class_<Configs>("Configs", bpy::no_init)
		.def(bpy::init<const eglplus::Display&>())
		.def(bpy::init<const eglplus::Display&, const FinishedConfigAttribs&>())
		.def("Empty", &Configs::Empty)
		.def("First", &Configs::First)
		.def("All", &Configs::All)
	;
}

