/*
 *  .file oglplus/enums/ext/nv_path_font_style.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_font_style.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// BOLD_BIT_NV
Bold,
/// ITALIC_BIT_NV
Italic

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_BOLD_BIT_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Bold)
#  pragma push_macro("Bold")
#  undef Bold
   OGLPLUS_ENUM_CLASS_VALUE(Bold, GL_BOLD_BIT_NV)
#  pragma pop_macro("Bold")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Bold, GL_BOLD_BIT_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ITALIC_BIT_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Italic)
#  pragma push_macro("Italic")
#  undef Italic
   OGLPLUS_ENUM_CLASS_VALUE(Italic, GL_ITALIC_BIT_NV)
#  pragma pop_macro("Italic")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Italic, GL_ITALIC_BIT_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

