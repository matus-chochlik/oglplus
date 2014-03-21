/*
 *  .file eglplus/enums/opengl_profile_bit_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/opengl_profile_bit.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef EGLPLUS_LIST_NEEDS_COMMA
# undef EGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT
# if EGLPLUS_LIST_NEEDS_COMMA
   EGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Core
#  pragma push_macro("Core")
#  undef Core
   EGLPLUS_ENUM_CLASS_VALUE(Core, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT)
#  pragma pop_macro("Core")
# else
   EGLPLUS_ENUM_CLASS_VALUE(Core, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT)
# endif
# ifndef EGLPLUS_LIST_NEEDS_COMMA
#  define EGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT
# if EGLPLUS_LIST_NEEDS_COMMA
   EGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Compatibility
#  pragma push_macro("Compatibility")
#  undef Compatibility
   EGLPLUS_ENUM_CLASS_VALUE(Compatibility, EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT)
#  pragma pop_macro("Compatibility")
# else
   EGLPLUS_ENUM_CLASS_VALUE(Compatibility, EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT)
# endif
# ifndef EGLPLUS_LIST_NEEDS_COMMA
#  define EGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef EGLPLUS_LIST_NEEDS_COMMA
# undef EGLPLUS_LIST_NEEDS_COMMA
#endif

