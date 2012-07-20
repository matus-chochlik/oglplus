/*
 *  .file oglplus/enums/sync_status_ese.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/sync_status.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined GL_SIGNALED
# if defined Signaled
#  pragma push_macro("Signaled")
#  undef Signaled
   OGLPLUS_ENUM_CLASS_VALUE(Signaled, GL_SIGNALED)
#  pragma pop_macro("Signaled")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Signaled, GL_SIGNALED)
# endif
#endif
#if defined GL_UNSIGNALED
# if defined Unsignaled
#  pragma push_macro("Unsignaled")
#  undef Unsignaled
   OGLPLUS_ENUM_CLASS_VALUE(Unsignaled, GL_UNSIGNALED)
#  pragma pop_macro("Unsignaled")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Unsignaled, GL_UNSIGNALED)
# endif
#endif
