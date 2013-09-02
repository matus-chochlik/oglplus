/*
 *  .file oglplus/enums/framebuffer_target_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/framebuffer_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_DRAW_FRAMEBUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Draw
#  pragma push_macro("Draw")
#  undef Draw
   OGLPLUS_ENUM_CLASS_VALUE(Draw, GL_DRAW_FRAMEBUFFER)
#  pragma pop_macro("Draw")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Draw, GL_DRAW_FRAMEBUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_READ_FRAMEBUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Read
#  pragma push_macro("Read")
#  undef Read
   OGLPLUS_ENUM_CLASS_VALUE(Read, GL_READ_FRAMEBUFFER)
#  pragma pop_macro("Read")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Read, GL_READ_FRAMEBUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

