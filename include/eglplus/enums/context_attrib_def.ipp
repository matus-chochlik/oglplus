/*
 *  .file eglplus/enums/context_attrib_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/context_attrib.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef EGLPLUS_LIST_NEEDS_COMMA
# undef EGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined EGL_CONTEXT_CLIENT_VERSION
# if EGLPLUS_LIST_NEEDS_COMMA
   EGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined ContextClientVersion
#  pragma push_macro("ContextClientVersion")
#  undef ContextClientVersion
   EGLPLUS_ENUM_CLASS_VALUE(ContextClientVersion, EGL_CONTEXT_CLIENT_VERSION)
#  pragma pop_macro("ContextClientVersion")
# else
   EGLPLUS_ENUM_CLASS_VALUE(ContextClientVersion, EGL_CONTEXT_CLIENT_VERSION)
# endif
# ifndef EGLPLUS_LIST_NEEDS_COMMA
#  define EGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef EGLPLUS_LIST_NEEDS_COMMA
# undef EGLPLUS_LIST_NEEDS_COMMA
#endif

