/*
 *  .file oglplus/enums/sync_type_ese.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/sync_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined GL_SYNC_FENCE
# if defined Fence
#  pragma push_macro("Fence")
#  undef Fence
   OGLPLUS_ENUM_CLASS_VALUE(Fence, GL_SYNC_FENCE)
#  pragma pop_macro("Fence")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Fence, GL_SYNC_FENCE)
# endif
#endif
