/*
 *  .file oglplus/enums/ext/nv_path_format.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_format.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// PATH_FORMAT_SVG_NV
SVG,
/// PATH_FORMAT_PS_NV
PS

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_PATH_FORMAT_SVG_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SVG)
#  pragma push_macro("SVG")
#  undef SVG
   OGLPLUS_ENUM_CLASS_VALUE(SVG, GL_PATH_FORMAT_SVG_NV)
#  pragma pop_macro("SVG")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SVG, GL_PATH_FORMAT_SVG_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PATH_FORMAT_PS_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PS)
#  pragma push_macro("PS")
#  undef PS
   OGLPLUS_ENUM_CLASS_VALUE(PS, GL_PATH_FORMAT_PS_NV)
#  pragma pop_macro("PS")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PS, GL_PATH_FORMAT_PS_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

