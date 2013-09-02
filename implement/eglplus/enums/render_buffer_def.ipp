/*
 *  .file eglplus/enums/render_buffer_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/render_buffer.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef EGLPLUS_LIST_NEEDS_COMMA
# undef EGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined EGL_SINGLE_BUFFER
# if EGLPLUS_LIST_NEEDS_COMMA
   EGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined SingleBuffer
#  pragma push_macro("SingleBuffer")
#  undef SingleBuffer
   EGLPLUS_ENUM_CLASS_VALUE(SingleBuffer, EGL_SINGLE_BUFFER)
#  pragma pop_macro("SingleBuffer")
# else
   EGLPLUS_ENUM_CLASS_VALUE(SingleBuffer, EGL_SINGLE_BUFFER)
# endif
# ifndef EGLPLUS_LIST_NEEDS_COMMA
#  define EGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined EGL_BACK_BUFFER
# if EGLPLUS_LIST_NEEDS_COMMA
   EGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined BackBuffer
#  pragma push_macro("BackBuffer")
#  undef BackBuffer
   EGLPLUS_ENUM_CLASS_VALUE(BackBuffer, EGL_BACK_BUFFER)
#  pragma pop_macro("BackBuffer")
# else
   EGLPLUS_ENUM_CLASS_VALUE(BackBuffer, EGL_BACK_BUFFER)
# endif
# ifndef EGLPLUS_LIST_NEEDS_COMMA
#  define EGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef EGLPLUS_LIST_NEEDS_COMMA
# undef EGLPLUS_LIST_NEEDS_COMMA
#endif

