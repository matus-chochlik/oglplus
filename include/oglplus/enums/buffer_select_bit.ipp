/*
 *  .file oglplus/enums/buffer_select_bit.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/buffer_select_bit.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// COLOR_BUFFER_BIT: Clear the color buffer
ColorBuffer,
/// DEPTH_BUFFER_BIT: Clear the depth buffer
DepthBuffer,
/// STENCIL_BUFFER_BIT: Clear the stencil buffer
StencilBuffer

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_COLOR_BUFFER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ColorBuffer)
#  pragma push_macro("ColorBuffer")
#  undef ColorBuffer
   OGLPLUS_ENUM_CLASS_VALUE(ColorBuffer, GL_COLOR_BUFFER_BIT)
#  pragma pop_macro("ColorBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ColorBuffer, GL_COLOR_BUFFER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEPTH_BUFFER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DepthBuffer)
#  pragma push_macro("DepthBuffer")
#  undef DepthBuffer
   OGLPLUS_ENUM_CLASS_VALUE(DepthBuffer, GL_DEPTH_BUFFER_BIT)
#  pragma pop_macro("DepthBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DepthBuffer, GL_DEPTH_BUFFER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STENCIL_BUFFER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StencilBuffer)
#  pragma push_macro("StencilBuffer")
#  undef StencilBuffer
   OGLPLUS_ENUM_CLASS_VALUE(StencilBuffer, GL_STENCIL_BUFFER_BIT)
#  pragma pop_macro("StencilBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StencilBuffer, GL_STENCIL_BUFFER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

