/*
 *  .file eglplus/enums/texture_format.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/texture_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/texture_format.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void eglplus_py_texture_format(void)
{
	boost::python::enum_<eglplus::TextureFormat>("TextureFormat")
#if defined EGL_TEXTURE_RGB
# if defined RGB
#  pragma push_macro("RGB")
#  undef RGB
	.value("RGB", eglplus::TextureFormat::RGB)
#  pragma pop_macro("RGB")
# else
	.value("RGB", eglplus::TextureFormat::RGB)
# endif
#endif
#if defined EGL_TEXTURE_RGBA
# if defined RGBA
#  pragma push_macro("RGBA")
#  undef RGBA
	.value("RGBA", eglplus::TextureFormat::RGBA)
#  pragma pop_macro("RGBA")
# else
	.value("RGBA", eglplus::TextureFormat::RGBA)
# endif
#endif
#if defined EGL_NO_TEXTURE
# if defined NoTexture
#  pragma push_macro("NoTexture")
#  undef NoTexture
	.value("NoTexture", eglplus::TextureFormat::NoTexture)
#  pragma pop_macro("NoTexture")
# else
	.value("NoTexture", eglplus::TextureFormat::NoTexture)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::TextureFormat) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::TextureFormat
		>
	>("aux_CastIterRange_TextureFormat");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::TextureFormat
	> (*PEnumValueRange)(eglplus::TextureFormat) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
