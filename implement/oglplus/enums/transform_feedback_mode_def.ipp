/*
 *  .file oglplus/enums/transform_feedback_mode_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/transform_feedback_mode.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_INTERLEAVED_ATTRIBS
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined InterleavedAttribs
#  pragma push_macro("InterleavedAttribs")
#  undef InterleavedAttribs
   OGLPLUS_ENUM_CLASS_VALUE(InterleavedAttribs, GL_INTERLEAVED_ATTRIBS)
#  pragma pop_macro("InterleavedAttribs")
# else
   OGLPLUS_ENUM_CLASS_VALUE(InterleavedAttribs, GL_INTERLEAVED_ATTRIBS)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SEPARATE_ATTRIBS
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined SeparateAttribs
#  pragma push_macro("SeparateAttribs")
#  undef SeparateAttribs
   OGLPLUS_ENUM_CLASS_VALUE(SeparateAttribs, GL_SEPARATE_ATTRIBS)
#  pragma pop_macro("SeparateAttribs")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SeparateAttribs, GL_SEPARATE_ATTRIBS)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

