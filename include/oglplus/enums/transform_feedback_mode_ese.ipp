/*
 *  .file oglplus/enums/transform_feedback_mode_ese.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/transform_feedback_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined GL_INTERLEAVED_ATTRIBS
# if defined InterleavedAttribs
#  pragma push_macro("InterleavedAttribs")
#  undef InterleavedAttribs
   OGLPLUS_ENUM_CLASS_VALUE(InterleavedAttribs, GL_INTERLEAVED_ATTRIBS)
#  pragma pop_macro("InterleavedAttribs")
# else
   OGLPLUS_ENUM_CLASS_VALUE(InterleavedAttribs, GL_INTERLEAVED_ATTRIBS)
# endif
#endif
#if defined GL_SEPARATE_ATTRIBS
# if defined SeparateAttribs
#  pragma push_macro("SeparateAttribs")
#  undef SeparateAttribs
   OGLPLUS_ENUM_CLASS_VALUE(SeparateAttribs, GL_SEPARATE_ATTRIBS)
#  pragma pop_macro("SeparateAttribs")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SeparateAttribs, GL_SEPARATE_ATTRIBS)
# endif
#endif
