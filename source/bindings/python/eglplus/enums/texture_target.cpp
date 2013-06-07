/*
 *  .file eglplus/enums/texture_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/texture_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/texture_target.hpp>

#include <boost/python.hpp>

void eglplus_py_texture_target(void)
{
	boost::python::enum_<eglplus::TextureTarget>("TextureTarget")
#if defined EGL_NO_TEXTURE
# if defined NoTexture
#  pragma push_macro("NoTexture")
#  undef NoTexture
	.value("NoTexture", eglplus::TextureTarget::NoTexture)
#  pragma pop_macro("NoTexture")
# else
	.value("NoTexture", eglplus::TextureTarget::NoTexture)
# endif
#endif
#if defined EGL_TEXTURE_2D
# if defined Texture2D
#  pragma push_macro("Texture2D")
#  undef Texture2D
	.value("Texture2D", eglplus::TextureTarget::Texture2D)
#  pragma pop_macro("Texture2D")
# else
	.value("Texture2D", eglplus::TextureTarget::Texture2D)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::TextureTarget) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
