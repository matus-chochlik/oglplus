/*
 *  .file oglplus/enums/ext/nv_path_fill_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_fill_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// INVERT
Invert,
/// COUNT_UP_NV
CountUp,
/// COUNT_DOWN_NV
CountDown,
/// PATH_FILL_MODE_NV
FillMode

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_INVERT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Invert)
#  pragma push_macro("Invert")
#  undef Invert
   OGLPLUS_ENUM_CLASS_VALUE(Invert, GL_INVERT)
#  pragma pop_macro("Invert")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Invert, GL_INVERT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COUNT_UP_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(CountUp)
#  pragma push_macro("CountUp")
#  undef CountUp
   OGLPLUS_ENUM_CLASS_VALUE(CountUp, GL_COUNT_UP_NV)
#  pragma pop_macro("CountUp")
# else
   OGLPLUS_ENUM_CLASS_VALUE(CountUp, GL_COUNT_UP_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COUNT_DOWN_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(CountDown)
#  pragma push_macro("CountDown")
#  undef CountDown
   OGLPLUS_ENUM_CLASS_VALUE(CountDown, GL_COUNT_DOWN_NV)
#  pragma pop_macro("CountDown")
# else
   OGLPLUS_ENUM_CLASS_VALUE(CountDown, GL_COUNT_DOWN_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PATH_FILL_MODE_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FillMode)
#  pragma push_macro("FillMode")
#  undef FillMode
   OGLPLUS_ENUM_CLASS_VALUE(FillMode, GL_PATH_FILL_MODE_NV)
#  pragma pop_macro("FillMode")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FillMode, GL_PATH_FILL_MODE_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

