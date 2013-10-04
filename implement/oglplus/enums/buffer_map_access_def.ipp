/*
 *  .file oglplus/enums/buffer_map_access_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/buffer_map_access.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_MAP_READ_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Read
#  pragma push_macro("Read")
#  undef Read
   OGLPLUS_ENUM_CLASS_VALUE(Read, GL_MAP_READ_BIT)
#  pragma pop_macro("Read")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Read, GL_MAP_READ_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MAP_WRITE_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Write
#  pragma push_macro("Write")
#  undef Write
   OGLPLUS_ENUM_CLASS_VALUE(Write, GL_MAP_WRITE_BIT)
#  pragma pop_macro("Write")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Write, GL_MAP_WRITE_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MAP_PERSISTENT_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Persistent
#  pragma push_macro("Persistent")
#  undef Persistent
   OGLPLUS_ENUM_CLASS_VALUE(Persistent, GL_MAP_PERSISTENT_BIT)
#  pragma pop_macro("Persistent")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Persistent, GL_MAP_PERSISTENT_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MAP_COHERENT_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Coherent
#  pragma push_macro("Coherent")
#  undef Coherent
   OGLPLUS_ENUM_CLASS_VALUE(Coherent, GL_MAP_COHERENT_BIT)
#  pragma pop_macro("Coherent")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Coherent, GL_MAP_COHERENT_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

