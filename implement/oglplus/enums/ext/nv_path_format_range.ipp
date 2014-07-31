/*
 *  .file oglplus/enums/ext/nv_path_format_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_format.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	PathNVFormat
> ValueRange_(PathNVFormat*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_PATHNVFORMAT)
#define OGLPLUS_IMPL_EVR_PATHNVFORMAT
{
static const GLenum _values[] = {
#if defined GL_PATH_FORMAT_SVG_NV
GL_PATH_FORMAT_SVG_NV,
#endif
#if defined GL_PATH_FORMAT_PS_NV
GL_PATH_FORMAT_PS_NV,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	PathNVFormat
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

