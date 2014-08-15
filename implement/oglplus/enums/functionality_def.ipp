/*
 *  .file oglplus/enums/functionality_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/functionality.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_CLIP_DISTANCE0
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined ClipDistance
#  pragma push_macro("ClipDistance")
#  undef ClipDistance
   OGLPLUS_ENUM_CLASS_VALUE(ClipDistance, GL_CLIP_DISTANCE0)
#  pragma pop_macro("ClipDistance")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ClipDistance, GL_CLIP_DISTANCE0)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

