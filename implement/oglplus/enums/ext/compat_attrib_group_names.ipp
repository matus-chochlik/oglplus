//  File implement/oglplus/enums/ext/compat_attrib_group_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/compat_attrib_group.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	CompatibilityAttributeGroup*,
	GLbitfield value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_COMPATIBILITYATTRIBUTEGROUP)
#define OGLPLUS_IMPL_EVN_COMPATIBILITYATTRIBUTEGROUP
{
switch(value)
{
#if defined GL_ACCUM_BUFFER_BIT
	case GL_ACCUM_BUFFER_BIT: return CStrRef("ACCUM_BUFFER_BIT");
#endif
#if defined GL_COLOR_BUFFER_BIT
	case GL_COLOR_BUFFER_BIT: return CStrRef("COLOR_BUFFER_BIT");
#endif
#if defined GL_CURRENT_BIT
	case GL_CURRENT_BIT: return CStrRef("CURRENT_BIT");
#endif
#if defined GL_DEPTH_BUFFER_BIT
	case GL_DEPTH_BUFFER_BIT: return CStrRef("DEPTH_BUFFER_BIT");
#endif
#if defined GL_ENABLE_BIT
	case GL_ENABLE_BIT: return CStrRef("ENABLE_BIT");
#endif
#if defined GL_EVAL_BIT
	case GL_EVAL_BIT: return CStrRef("EVAL_BIT");
#endif
#if defined GL_FOG_BIT
	case GL_FOG_BIT: return CStrRef("FOG_BIT");
#endif
#if defined GL_HINT_BIT
	case GL_HINT_BIT: return CStrRef("HINT_BIT");
#endif
#if defined GL_LIGHTING_BIT
	case GL_LIGHTING_BIT: return CStrRef("LIGHTING_BIT");
#endif
#if defined GL_LINE_BIT
	case GL_LINE_BIT: return CStrRef("LINE_BIT");
#endif
#if defined GL_LIST_BIT
	case GL_LIST_BIT: return CStrRef("LIST_BIT");
#endif
#if defined GL_MULTISAMPLE_BIT
	case GL_MULTISAMPLE_BIT: return CStrRef("MULTISAMPLE_BIT");
#endif
#if defined GL_PIXEL_MODE_BIT
	case GL_PIXEL_MODE_BIT: return CStrRef("PIXEL_MODE_BIT");
#endif
#if defined GL_POINT_BIT
	case GL_POINT_BIT: return CStrRef("POINT_BIT");
#endif
#if defined GL_POLYGON_BIT
	case GL_POLYGON_BIT: return CStrRef("POLYGON_BIT");
#endif
#if defined GL_POLYGON_STIPPLE_BIT
	case GL_POLYGON_STIPPLE_BIT: return CStrRef("POLYGON_STIPPLE_BIT");
#endif
#if defined GL_SCISSOR_BIT
	case GL_SCISSOR_BIT: return CStrRef("SCISSOR_BIT");
#endif
#if defined GL_STENCIL_BUFFER_BIT
	case GL_STENCIL_BUFFER_BIT: return CStrRef("STENCIL_BUFFER_BIT");
#endif
#if defined GL_TEXTURE_BIT
	case GL_TEXTURE_BIT: return CStrRef("TEXTURE_BIT");
#endif
#if defined GL_TRANSFORM_BIT
	case GL_TRANSFORM_BIT: return CStrRef("TRANSFORM_BIT");
#endif
#if defined GL_VIEWPORT_BIT
	case GL_VIEWPORT_BIT: return CStrRef("VIEWPORT_BIT");
#endif
#if defined GL_ALL_ATTRIB_BITS
	case GL_ALL_ATTRIB_BITS: return CStrRef("ALL_ATTRIB_BITS");
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

