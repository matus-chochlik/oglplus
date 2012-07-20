/*
 *  .file oglplus/enums/ext/nv_path_gen_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_gen_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// NONE
None,
/// EYE_LINEAR
EyeLinear,
/// OBJECT_LINEAR
ObjectLinear,
/// PATH_OBJECT_BOUNDING_BOX_NV
ObjectBoundingBox

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_NONE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(None)
#  pragma push_macro("None")
#  undef None
   OGLPLUS_ENUM_CLASS_VALUE(None, GL_NONE)
#  pragma pop_macro("None")
# else
   OGLPLUS_ENUM_CLASS_VALUE(None, GL_NONE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_EYE_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(EyeLinear)
#  pragma push_macro("EyeLinear")
#  undef EyeLinear
   OGLPLUS_ENUM_CLASS_VALUE(EyeLinear, GL_EYE_LINEAR)
#  pragma pop_macro("EyeLinear")
# else
   OGLPLUS_ENUM_CLASS_VALUE(EyeLinear, GL_EYE_LINEAR)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_OBJECT_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ObjectLinear)
#  pragma push_macro("ObjectLinear")
#  undef ObjectLinear
   OGLPLUS_ENUM_CLASS_VALUE(ObjectLinear, GL_OBJECT_LINEAR)
#  pragma pop_macro("ObjectLinear")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ObjectLinear, GL_OBJECT_LINEAR)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PATH_OBJECT_BOUNDING_BOX_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ObjectBoundingBox)
#  pragma push_macro("ObjectBoundingBox")
#  undef ObjectBoundingBox
   OGLPLUS_ENUM_CLASS_VALUE(ObjectBoundingBox, GL_PATH_OBJECT_BOUNDING_BOX_NV)
#  pragma pop_macro("ObjectBoundingBox")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ObjectBoundingBox, GL_PATH_OBJECT_BOUNDING_BOX_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

