/*
 *  .file oglplus/enums/patch_parameter_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/patch_parameter.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	PatchParameter
> ValueRange_(PatchParameter*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_PATCHPARAMETER)
#define OGLPLUS_IMPL_EVR_PATCHPARAMETER
{
static const GLenum _values[] = {
#if defined GL_PATCH_VERTICES
GL_PATCH_VERTICES,
#endif
#if defined GL_PATCH_DEFAULT_OUTER_LEVEL
GL_PATCH_DEFAULT_OUTER_LEVEL,
#endif
#if defined GL_PATCH_DEFAULT_INNER_LEVEL
GL_PATCH_DEFAULT_INNER_LEVEL,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	PatchParameter
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

