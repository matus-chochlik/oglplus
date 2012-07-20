/*
 *  .file oglplus/enums/ext/debug_output_source.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/debug_output_source.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// DEBUG_SOURCE_API_ARB
API,
/// DEBUG_SOURCE_WINDOW_SYSTEM_ARB
WindowSystem,
/// DEBUG_SOURCE_SHADER_COMPILER_ARB
ShaderCompiler,
/// DEBUG_SOURCE_THIRD_PARTY_ARB
ThirdParty,
/// DEBUG_SOURCE_APPLICATION_ARB
Application,
/// DEBUG_SOURCE_OTHER_ARB
Other,
/// DONT_CARE
DontCare

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_DEBUG_SOURCE_API_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(API)
#  pragma push_macro("API")
#  undef API
   OGLPLUS_ENUM_CLASS_VALUE(API, GL_DEBUG_SOURCE_API_ARB)
#  pragma pop_macro("API")
# else
   OGLPLUS_ENUM_CLASS_VALUE(API, GL_DEBUG_SOURCE_API_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(WindowSystem)
#  pragma push_macro("WindowSystem")
#  undef WindowSystem
   OGLPLUS_ENUM_CLASS_VALUE(WindowSystem, GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
#  pragma pop_macro("WindowSystem")
# else
   OGLPLUS_ENUM_CLASS_VALUE(WindowSystem, GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SOURCE_SHADER_COMPILER_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ShaderCompiler)
#  pragma push_macro("ShaderCompiler")
#  undef ShaderCompiler
   OGLPLUS_ENUM_CLASS_VALUE(ShaderCompiler, GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
#  pragma pop_macro("ShaderCompiler")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ShaderCompiler, GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SOURCE_THIRD_PARTY_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ThirdParty)
#  pragma push_macro("ThirdParty")
#  undef ThirdParty
   OGLPLUS_ENUM_CLASS_VALUE(ThirdParty, GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
#  pragma pop_macro("ThirdParty")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ThirdParty, GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SOURCE_APPLICATION_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Application)
#  pragma push_macro("Application")
#  undef Application
   OGLPLUS_ENUM_CLASS_VALUE(Application, GL_DEBUG_SOURCE_APPLICATION_ARB)
#  pragma pop_macro("Application")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Application, GL_DEBUG_SOURCE_APPLICATION_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SOURCE_OTHER_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Other)
#  pragma push_macro("Other")
#  undef Other
   OGLPLUS_ENUM_CLASS_VALUE(Other, GL_DEBUG_SOURCE_OTHER_ARB)
#  pragma pop_macro("Other")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Other, GL_DEBUG_SOURCE_OTHER_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DONT_CARE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DontCare)
#  pragma push_macro("DontCare")
#  undef DontCare
   OGLPLUS_ENUM_CLASS_VALUE(DontCare, GL_DONT_CARE)
#  pragma pop_macro("DontCare")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DontCare, GL_DONT_CARE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

