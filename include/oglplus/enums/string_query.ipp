/*
 *  .file oglplus/enums/string_query.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/string_query.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// RENDERER
Renderer,
/// VENDOR
Vendor,
/// VERSION
Version,
/// SHADING_LANGUAGE_VERSION
ShadingLanguageVersion

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_RENDERER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Renderer)
#  pragma push_macro("Renderer")
#  undef Renderer
   OGLPLUS_ENUM_CLASS_VALUE(Renderer, GL_RENDERER)
#  pragma pop_macro("Renderer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Renderer, GL_RENDERER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_VENDOR
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Vendor)
#  pragma push_macro("Vendor")
#  undef Vendor
   OGLPLUS_ENUM_CLASS_VALUE(Vendor, GL_VENDOR)
#  pragma pop_macro("Vendor")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Vendor, GL_VENDOR)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_VERSION
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Version)
#  pragma push_macro("Version")
#  undef Version
   OGLPLUS_ENUM_CLASS_VALUE(Version, GL_VERSION)
#  pragma pop_macro("Version")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Version, GL_VERSION)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SHADING_LANGUAGE_VERSION
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ShadingLanguageVersion)
#  pragma push_macro("ShadingLanguageVersion")
#  undef ShadingLanguageVersion
   OGLPLUS_ENUM_CLASS_VALUE(ShadingLanguageVersion, GL_SHADING_LANGUAGE_VERSION)
#  pragma pop_macro("ShadingLanguageVersion")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ShadingLanguageVersion, GL_SHADING_LANGUAGE_VERSION)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

