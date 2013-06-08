/*
 *  .file eglplus/bitfields.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/context_flag.hpp>
#include <eglplus/opengl_profile_bit.hpp>
#include <eglplus/surface_type_bit.hpp>
#include <eglplus/renderable_type_bit.hpp>

#include <boost/python.hpp>

#include "bitfield.hpp"

void eglplus_py_Bitfields(void)
{
	using namespace eglplus;

	eglplus_py_export_Bitfield<Bitfield<ContextFlag> >("Bitfield_ContextFlag");
	eglplus_py_export_Bitfield<Bitfield<OpenGLProfileBit> >("Bitfield_OpenGLProfileBit");
	eglplus_py_export_Bitfield<Bitfield<SurfaceTypeBit> >("Bitfield_SurfaceTypeBit");
	eglplus_py_export_Bitfield<Bitfield<RenderableTypeBit> >("Bitfield_RenderableTypeBit");
}

