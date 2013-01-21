/*
 *  .file oglplus/enums/face_orientation_ese.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/face_orientation.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined GL_CW
# if defined CW
#  pragma push_macro("CW")
#  undef CW
   OGLPLUS_ENUM_CLASS_VALUE(CW, GL_CW)
#  pragma pop_macro("CW")
# else
   OGLPLUS_ENUM_CLASS_VALUE(CW, GL_CW)
# endif
#endif
#if defined GL_CCW
# if defined CCW
#  pragma push_macro("CCW")
#  undef CCW
   OGLPLUS_ENUM_CLASS_VALUE(CCW, GL_CCW)
#  pragma pop_macro("CCW")
# else
   OGLPLUS_ENUM_CLASS_VALUE(CCW, GL_CCW)
# endif
#endif
