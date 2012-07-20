/*
 *  .file oglplus/enums/texture_compare_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_compare_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// NONE
None,
/// COMPARE_REF_TO_TEXTURE
CompareRefToTexture

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
#if defined GL_COMPARE_REF_TO_TEXTURE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(CompareRefToTexture)
#  pragma push_macro("CompareRefToTexture")
#  undef CompareRefToTexture
   OGLPLUS_ENUM_CLASS_VALUE(CompareRefToTexture, GL_COMPARE_REF_TO_TEXTURE)
#  pragma pop_macro("CompareRefToTexture")
# else
   OGLPLUS_ENUM_CLASS_VALUE(CompareRefToTexture, GL_COMPARE_REF_TO_TEXTURE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

