/*
 *  .file oglplus/enums/image_unit_format.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/image_unit_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/pixel_data.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_image_unit_format(void)
{
	boost::python::enum_<oglplus::ImageUnitFormat>("ImageUnitFormat")
#if defined GL_RGBA32F
# if defined RGBA32F
#  pragma push_macro("RGBA32F")
#  undef RGBA32F
	.value("RGBA32F", oglplus::ImageUnitFormat::RGBA32F)
#  pragma pop_macro("RGBA32F")
# else
	.value("RGBA32F", oglplus::ImageUnitFormat::RGBA32F)
# endif
#endif
#if defined GL_RGBA16F
# if defined RGBA16F
#  pragma push_macro("RGBA16F")
#  undef RGBA16F
	.value("RGBA16F", oglplus::ImageUnitFormat::RGBA16F)
#  pragma pop_macro("RGBA16F")
# else
	.value("RGBA16F", oglplus::ImageUnitFormat::RGBA16F)
# endif
#endif
#if defined GL_RG32F
# if defined RG32F
#  pragma push_macro("RG32F")
#  undef RG32F
	.value("RG32F", oglplus::ImageUnitFormat::RG32F)
#  pragma pop_macro("RG32F")
# else
	.value("RG32F", oglplus::ImageUnitFormat::RG32F)
# endif
#endif
#if defined GL_RG16F
# if defined RG16F
#  pragma push_macro("RG16F")
#  undef RG16F
	.value("RG16F", oglplus::ImageUnitFormat::RG16F)
#  pragma pop_macro("RG16F")
# else
	.value("RG16F", oglplus::ImageUnitFormat::RG16F)
# endif
#endif
#if defined GL_R11F_G11F_B10F
# if defined R11FG11FB10F
#  pragma push_macro("R11FG11FB10F")
#  undef R11FG11FB10F
	.value("R11FG11FB10F", oglplus::ImageUnitFormat::R11FG11FB10F)
#  pragma pop_macro("R11FG11FB10F")
# else
	.value("R11FG11FB10F", oglplus::ImageUnitFormat::R11FG11FB10F)
# endif
#endif
#if defined GL_R32F
# if defined R32F
#  pragma push_macro("R32F")
#  undef R32F
	.value("R32F", oglplus::ImageUnitFormat::R32F)
#  pragma pop_macro("R32F")
# else
	.value("R32F", oglplus::ImageUnitFormat::R32F)
# endif
#endif
#if defined GL_R16F
# if defined R16F
#  pragma push_macro("R16F")
#  undef R16F
	.value("R16F", oglplus::ImageUnitFormat::R16F)
#  pragma pop_macro("R16F")
# else
	.value("R16F", oglplus::ImageUnitFormat::R16F)
# endif
#endif
#if defined GL_RGBA32UI
# if defined RGBA32UI
#  pragma push_macro("RGBA32UI")
#  undef RGBA32UI
	.value("RGBA32UI", oglplus::ImageUnitFormat::RGBA32UI)
#  pragma pop_macro("RGBA32UI")
# else
	.value("RGBA32UI", oglplus::ImageUnitFormat::RGBA32UI)
# endif
#endif
#if defined GL_RGBA16UI
# if defined RGBA16UI
#  pragma push_macro("RGBA16UI")
#  undef RGBA16UI
	.value("RGBA16UI", oglplus::ImageUnitFormat::RGBA16UI)
#  pragma pop_macro("RGBA16UI")
# else
	.value("RGBA16UI", oglplus::ImageUnitFormat::RGBA16UI)
# endif
#endif
#if defined GL_RGB10_A2UI
# if defined RGB10_A2UI
#  pragma push_macro("RGB10_A2UI")
#  undef RGB10_A2UI
	.value("RGB10_A2UI", oglplus::ImageUnitFormat::RGB10_A2UI)
#  pragma pop_macro("RGB10_A2UI")
# else
	.value("RGB10_A2UI", oglplus::ImageUnitFormat::RGB10_A2UI)
# endif
#endif
#if defined GL_RGBA8UI
# if defined RGBA8UI
#  pragma push_macro("RGBA8UI")
#  undef RGBA8UI
	.value("RGBA8UI", oglplus::ImageUnitFormat::RGBA8UI)
#  pragma pop_macro("RGBA8UI")
# else
	.value("RGBA8UI", oglplus::ImageUnitFormat::RGBA8UI)
# endif
#endif
#if defined GL_RG32UI
# if defined RG32UI
#  pragma push_macro("RG32UI")
#  undef RG32UI
	.value("RG32UI", oglplus::ImageUnitFormat::RG32UI)
#  pragma pop_macro("RG32UI")
# else
	.value("RG32UI", oglplus::ImageUnitFormat::RG32UI)
# endif
#endif
#if defined GL_RG16UI
# if defined RG16UI
#  pragma push_macro("RG16UI")
#  undef RG16UI
	.value("RG16UI", oglplus::ImageUnitFormat::RG16UI)
#  pragma pop_macro("RG16UI")
# else
	.value("RG16UI", oglplus::ImageUnitFormat::RG16UI)
# endif
#endif
#if defined GL_RG8UI
# if defined RG8UI
#  pragma push_macro("RG8UI")
#  undef RG8UI
	.value("RG8UI", oglplus::ImageUnitFormat::RG8UI)
#  pragma pop_macro("RG8UI")
# else
	.value("RG8UI", oglplus::ImageUnitFormat::RG8UI)
# endif
#endif
#if defined GL_R32UI
# if defined R32UI
#  pragma push_macro("R32UI")
#  undef R32UI
	.value("R32UI", oglplus::ImageUnitFormat::R32UI)
#  pragma pop_macro("R32UI")
# else
	.value("R32UI", oglplus::ImageUnitFormat::R32UI)
# endif
#endif
#if defined GL_R16UI
# if defined R16UI
#  pragma push_macro("R16UI")
#  undef R16UI
	.value("R16UI", oglplus::ImageUnitFormat::R16UI)
#  pragma pop_macro("R16UI")
# else
	.value("R16UI", oglplus::ImageUnitFormat::R16UI)
# endif
#endif
#if defined GL_R8UI
# if defined R8UI
#  pragma push_macro("R8UI")
#  undef R8UI
	.value("R8UI", oglplus::ImageUnitFormat::R8UI)
#  pragma pop_macro("R8UI")
# else
	.value("R8UI", oglplus::ImageUnitFormat::R8UI)
# endif
#endif
#if defined GL_RGBA32I
# if defined RGBA32I
#  pragma push_macro("RGBA32I")
#  undef RGBA32I
	.value("RGBA32I", oglplus::ImageUnitFormat::RGBA32I)
#  pragma pop_macro("RGBA32I")
# else
	.value("RGBA32I", oglplus::ImageUnitFormat::RGBA32I)
# endif
#endif
#if defined GL_RGBA16I
# if defined RGBA16I
#  pragma push_macro("RGBA16I")
#  undef RGBA16I
	.value("RGBA16I", oglplus::ImageUnitFormat::RGBA16I)
#  pragma pop_macro("RGBA16I")
# else
	.value("RGBA16I", oglplus::ImageUnitFormat::RGBA16I)
# endif
#endif
#if defined GL_RGBA8I
# if defined RGBA8I
#  pragma push_macro("RGBA8I")
#  undef RGBA8I
	.value("RGBA8I", oglplus::ImageUnitFormat::RGBA8I)
#  pragma pop_macro("RGBA8I")
# else
	.value("RGBA8I", oglplus::ImageUnitFormat::RGBA8I)
# endif
#endif
#if defined GL_RG32I
# if defined RG32I
#  pragma push_macro("RG32I")
#  undef RG32I
	.value("RG32I", oglplus::ImageUnitFormat::RG32I)
#  pragma pop_macro("RG32I")
# else
	.value("RG32I", oglplus::ImageUnitFormat::RG32I)
# endif
#endif
#if defined GL_RG16I
# if defined RG16I
#  pragma push_macro("RG16I")
#  undef RG16I
	.value("RG16I", oglplus::ImageUnitFormat::RG16I)
#  pragma pop_macro("RG16I")
# else
	.value("RG16I", oglplus::ImageUnitFormat::RG16I)
# endif
#endif
#if defined GL_RG8I
# if defined RG8I
#  pragma push_macro("RG8I")
#  undef RG8I
	.value("RG8I", oglplus::ImageUnitFormat::RG8I)
#  pragma pop_macro("RG8I")
# else
	.value("RG8I", oglplus::ImageUnitFormat::RG8I)
# endif
#endif
#if defined GL_R32I
# if defined R32I
#  pragma push_macro("R32I")
#  undef R32I
	.value("R32I", oglplus::ImageUnitFormat::R32I)
#  pragma pop_macro("R32I")
# else
	.value("R32I", oglplus::ImageUnitFormat::R32I)
# endif
#endif
#if defined GL_R16I
# if defined R16I
#  pragma push_macro("R16I")
#  undef R16I
	.value("R16I", oglplus::ImageUnitFormat::R16I)
#  pragma pop_macro("R16I")
# else
	.value("R16I", oglplus::ImageUnitFormat::R16I)
# endif
#endif
#if defined GL_R8I
# if defined R8I
#  pragma push_macro("R8I")
#  undef R8I
	.value("R8I", oglplus::ImageUnitFormat::R8I)
#  pragma pop_macro("R8I")
# else
	.value("R8I", oglplus::ImageUnitFormat::R8I)
# endif
#endif
#if defined GL_RGBA16
# if defined RGBA16
#  pragma push_macro("RGBA16")
#  undef RGBA16
	.value("RGBA16", oglplus::ImageUnitFormat::RGBA16)
#  pragma pop_macro("RGBA16")
# else
	.value("RGBA16", oglplus::ImageUnitFormat::RGBA16)
# endif
#endif
#if defined GL_RGB10_A2
# if defined RGB10A2
#  pragma push_macro("RGB10A2")
#  undef RGB10A2
	.value("RGB10A2", oglplus::ImageUnitFormat::RGB10A2)
#  pragma pop_macro("RGB10A2")
# else
	.value("RGB10A2", oglplus::ImageUnitFormat::RGB10A2)
# endif
#endif
#if defined GL_RGBA8
# if defined RGBA8
#  pragma push_macro("RGBA8")
#  undef RGBA8
	.value("RGBA8", oglplus::ImageUnitFormat::RGBA8)
#  pragma pop_macro("RGBA8")
# else
	.value("RGBA8", oglplus::ImageUnitFormat::RGBA8)
# endif
#endif
#if defined GL_RG16
# if defined RG16
#  pragma push_macro("RG16")
#  undef RG16
	.value("RG16", oglplus::ImageUnitFormat::RG16)
#  pragma pop_macro("RG16")
# else
	.value("RG16", oglplus::ImageUnitFormat::RG16)
# endif
#endif
#if defined GL_RG8
# if defined RG8
#  pragma push_macro("RG8")
#  undef RG8
	.value("RG8", oglplus::ImageUnitFormat::RG8)
#  pragma pop_macro("RG8")
# else
	.value("RG8", oglplus::ImageUnitFormat::RG8)
# endif
#endif
#if defined GL_R16
# if defined R16
#  pragma push_macro("R16")
#  undef R16
	.value("R16", oglplus::ImageUnitFormat::R16)
#  pragma pop_macro("R16")
# else
	.value("R16", oglplus::ImageUnitFormat::R16)
# endif
#endif
#if defined GL_R8
# if defined R8
#  pragma push_macro("R8")
#  undef R8
	.value("R8", oglplus::ImageUnitFormat::R8)
#  pragma pop_macro("R8")
# else
	.value("R8", oglplus::ImageUnitFormat::R8)
# endif
#endif
#if defined GL_RGBA16_SNORM
# if defined RGBA16SNorm
#  pragma push_macro("RGBA16SNorm")
#  undef RGBA16SNorm
	.value("RGBA16SNorm", oglplus::ImageUnitFormat::RGBA16SNorm)
#  pragma pop_macro("RGBA16SNorm")
# else
	.value("RGBA16SNorm", oglplus::ImageUnitFormat::RGBA16SNorm)
# endif
#endif
#if defined GL_RGBA8_SNORM
# if defined RGBA8SNorm
#  pragma push_macro("RGBA8SNorm")
#  undef RGBA8SNorm
	.value("RGBA8SNorm", oglplus::ImageUnitFormat::RGBA8SNorm)
#  pragma pop_macro("RGBA8SNorm")
# else
	.value("RGBA8SNorm", oglplus::ImageUnitFormat::RGBA8SNorm)
# endif
#endif
#if defined GL_RG16_SNORM
# if defined RG16SNorm
#  pragma push_macro("RG16SNorm")
#  undef RG16SNorm
	.value("RG16SNorm", oglplus::ImageUnitFormat::RG16SNorm)
#  pragma pop_macro("RG16SNorm")
# else
	.value("RG16SNorm", oglplus::ImageUnitFormat::RG16SNorm)
# endif
#endif
#if defined GL_RG8_SNORM
# if defined RG8SNorm
#  pragma push_macro("RG8SNorm")
#  undef RG8SNorm
	.value("RG8SNorm", oglplus::ImageUnitFormat::RG8SNorm)
#  pragma pop_macro("RG8SNorm")
# else
	.value("RG8SNorm", oglplus::ImageUnitFormat::RG8SNorm)
# endif
#endif
#if defined GL_R16_SNORM
# if defined R16SNorm
#  pragma push_macro("R16SNorm")
#  undef R16SNorm
	.value("R16SNorm", oglplus::ImageUnitFormat::R16SNorm)
#  pragma pop_macro("R16SNorm")
# else
	.value("R16SNorm", oglplus::ImageUnitFormat::R16SNorm)
# endif
#endif
#if defined GL_R8_SNORM
# if defined R8SNorm
#  pragma push_macro("R8SNorm")
#  undef R8SNorm
	.value("R8SNorm", oglplus::ImageUnitFormat::R8SNorm)
#  pragma pop_macro("R8SNorm")
# else
	.value("R8SNorm", oglplus::ImageUnitFormat::R8SNorm)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ImageUnitFormat) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::ImageUnitFormat
		>
	>("aux_CastIterRange_ImageUnitFormat");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::ImageUnitFormat
	> (*PEnumValueRange)(oglplus::ImageUnitFormat) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
