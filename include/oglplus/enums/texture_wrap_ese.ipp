/*
 *  .file oglplus/enums/texture_wrap_ese.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_wrap.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined GL_CLAMP_TO_EDGE
# if defined ClampToEdge
#  pragma push_macro("ClampToEdge")
#  undef ClampToEdge
   OGLPLUS_ENUM_CLASS_VALUE(ClampToEdge, GL_CLAMP_TO_EDGE)
#  pragma pop_macro("ClampToEdge")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ClampToEdge, GL_CLAMP_TO_EDGE)
# endif
#endif
#if defined GL_REPEAT
# if defined Repeat
#  pragma push_macro("Repeat")
#  undef Repeat
   OGLPLUS_ENUM_CLASS_VALUE(Repeat, GL_REPEAT)
#  pragma pop_macro("Repeat")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Repeat, GL_REPEAT)
# endif
#endif
#if defined GL_CLAMP_TO_BORDER
# if defined ClampToBorder
#  pragma push_macro("ClampToBorder")
#  undef ClampToBorder
   OGLPLUS_ENUM_CLASS_VALUE(ClampToBorder, GL_CLAMP_TO_BORDER)
#  pragma pop_macro("ClampToBorder")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ClampToBorder, GL_CLAMP_TO_BORDER)
# endif
#endif
#if defined GL_MIRRORED_REPEAT
# if defined MirroredRepeat
#  pragma push_macro("MirroredRepeat")
#  undef MirroredRepeat
   OGLPLUS_ENUM_CLASS_VALUE(MirroredRepeat, GL_MIRRORED_REPEAT)
#  pragma pop_macro("MirroredRepeat")
# else
   OGLPLUS_ENUM_CLASS_VALUE(MirroredRepeat, GL_MIRRORED_REPEAT)
# endif
#endif
