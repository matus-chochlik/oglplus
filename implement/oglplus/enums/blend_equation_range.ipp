/*
 *  .file oglplus/enums/blend_equation_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/blend_equation.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	BlendEquation
> ValueRange_(BlendEquation*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_BLENDEQUATION)
#define OGLPLUS_IMPL_EVR_BLENDEQUATION
{
static const GLenum _values[] = {
#if defined GL_FUNC_ADD
GL_FUNC_ADD,
#endif
#if defined GL_FUNC_SUBTRACT
GL_FUNC_SUBTRACT,
#endif
#if defined GL_FUNC_REVERSE_SUBTRACT
GL_FUNC_REVERSE_SUBTRACT,
#endif
#if defined GL_MIN
GL_MIN,
#endif
#if defined GL_MAX
GL_MAX,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	BlendEquation
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

