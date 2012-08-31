/*
 *  .file oglplus/enums/buffer_usage_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/buffer_usage.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	BufferUsage
> EnumValueRange(BufferUsage*)
OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
static const GLenum _values[] = {
#if defined GL_STREAM_DRAW
GL_STREAM_DRAW,
#endif
#if defined GL_STREAM_READ
GL_STREAM_READ,
#endif
#if defined GL_STREAM_COPY
GL_STREAM_COPY,
#endif
#if defined GL_STATIC_DRAW
GL_STATIC_DRAW,
#endif
#if defined GL_STATIC_READ
GL_STATIC_READ,
#endif
#if defined GL_STATIC_COPY
GL_STATIC_COPY,
#endif
#if defined GL_DYNAMIC_DRAW
GL_DYNAMIC_DRAW,
#endif
#if defined GL_DYNAMIC_READ
GL_DYNAMIC_READ,
#endif
#if defined GL_DYNAMIC_COPY
GL_DYNAMIC_COPY,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	BufferUsage
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#endif

