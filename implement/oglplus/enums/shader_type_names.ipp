/*
 *  .file oglplus/enums/shader_type_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/shader_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	ShaderType*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_SHADERTYPE)
#define OGLPLUS_IMPL_EVN_SHADERTYPE
{
switch(value)
{
#if defined GL_VERTEX_SHADER
	case GL_VERTEX_SHADER: return StrLit("VERTEX_SHADER");
#endif
#if defined GL_TESS_CONTROL_SHADER
	case GL_TESS_CONTROL_SHADER: return StrLit("TESS_CONTROL_SHADER");
#endif
#if defined GL_TESS_EVALUATION_SHADER
	case GL_TESS_EVALUATION_SHADER: return StrLit("TESS_EVALUATION_SHADER");
#endif
#if defined GL_GEOMETRY_SHADER
	case GL_GEOMETRY_SHADER: return StrLit("GEOMETRY_SHADER");
#endif
#if defined GL_FRAGMENT_SHADER
	case GL_FRAGMENT_SHADER: return StrLit("FRAGMENT_SHADER");
#endif
#if defined GL_COMPUTE_SHADER
	case GL_COMPUTE_SHADER: return StrLit("COMPUTE_SHADER");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

