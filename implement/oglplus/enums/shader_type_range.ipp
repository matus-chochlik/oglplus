/*
 *  .file oglplus/enums/shader_type_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/shader_type.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	ShaderType
> ValueRange_(ShaderType*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_SHADERTYPE)
#define OGLPLUS_IMPL_EVR_SHADERTYPE
{
static const GLenum _values[] = {
#if defined GL_VERTEX_SHADER
GL_VERTEX_SHADER,
#endif
#if defined GL_TESS_CONTROL_SHADER
GL_TESS_CONTROL_SHADER,
#endif
#if defined GL_TESS_EVALUATION_SHADER
GL_TESS_EVALUATION_SHADER,
#endif
#if defined GL_GEOMETRY_SHADER
GL_GEOMETRY_SHADER,
#endif
#if defined GL_FRAGMENT_SHADER
GL_FRAGMENT_SHADER,
#endif
#if defined GL_COMPUTE_SHADER
GL_COMPUTE_SHADER,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	ShaderType
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

