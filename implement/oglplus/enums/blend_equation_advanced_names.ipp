//  File implement/oglplus/enums/blend_equation_advanced_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/blend_equation_advanced.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	BlendEquationAdvanced*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_BLENDEQUATIONADVANCED)
#define OGLPLUS_IMPL_EVN_BLENDEQUATIONADVANCED
{
switch(value)
{
#if defined GL_MULTIPLY_KHR
	case GL_MULTIPLY_KHR: return CStrRef("MULTIPLY_KHR");
#endif
#if defined GL_SCREEN_KHR
	case GL_SCREEN_KHR: return CStrRef("SCREEN_KHR");
#endif
#if defined GL_OVERLAY_KHR
	case GL_OVERLAY_KHR: return CStrRef("OVERLAY_KHR");
#endif
#if defined GL_DARKEN_KHR
	case GL_DARKEN_KHR: return CStrRef("DARKEN_KHR");
#endif
#if defined GL_LIGHTEN_KHR
	case GL_LIGHTEN_KHR: return CStrRef("LIGHTEN_KHR");
#endif
#if defined GL_COLORDODGE_KHR
	case GL_COLORDODGE_KHR: return CStrRef("COLORDODGE_KHR");
#endif
#if defined GL_COLORBURN_KHR
	case GL_COLORBURN_KHR: return CStrRef("COLORBURN_KHR");
#endif
#if defined GL_HARDLIGHT_KHR
	case GL_HARDLIGHT_KHR: return CStrRef("HARDLIGHT_KHR");
#endif
#if defined GL_SOFTLIGHT_KHR
	case GL_SOFTLIGHT_KHR: return CStrRef("SOFTLIGHT_KHR");
#endif
#if defined GL_DIFFERENCE_KHR
	case GL_DIFFERENCE_KHR: return CStrRef("DIFFERENCE_KHR");
#endif
#if defined GL_EXCLUSION_KHR
	case GL_EXCLUSION_KHR: return CStrRef("EXCLUSION_KHR");
#endif
#if defined GL_HSL_HUE_KHR
	case GL_HSL_HUE_KHR: return CStrRef("HSL_HUE_KHR");
#endif
#if defined GL_HSL_SATURATION_KHR
	case GL_HSL_SATURATION_KHR: return CStrRef("HSL_SATURATION_KHR");
#endif
#if defined GL_HSL_COLOR_KHR
	case GL_HSL_COLOR_KHR: return CStrRef("HSL_COLOR_KHR");
#endif
#if defined GL_HSL_LUMINOSITY_KHR
	case GL_HSL_LUMINOSITY_KHR: return CStrRef("HSL_LUMINOSITY_KHR");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

