/*
 *  .file eglplus/error_code.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/error_code.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/error_code.hpp>

#include <boost/python.hpp>

void eglplus_py_error_code(void)
{
	boost::python::enum_<eglplus::ErrorCode>("ErrorCode")
#if defined EGL_NOT_INITIALIZED
# if defined NotInitialized
#  pragma push_macro("NotInitialized")
#  undef NotInitialized
	.value("NotInitialized", eglplus::ErrorCode::NotInitialized)
#  pragma pop_macro("NotInitialized")
# else
	.value("NotInitialized", eglplus::ErrorCode::NotInitialized)
# endif
#endif
#if defined EGL_BAD_ACCESS
# if defined BadAccess
#  pragma push_macro("BadAccess")
#  undef BadAccess
	.value("BadAccess", eglplus::ErrorCode::BadAccess)
#  pragma pop_macro("BadAccess")
# else
	.value("BadAccess", eglplus::ErrorCode::BadAccess)
# endif
#endif
#if defined EGL_BAD_ALLOC
# if defined BadAlloc
#  pragma push_macro("BadAlloc")
#  undef BadAlloc
	.value("BadAlloc", eglplus::ErrorCode::BadAlloc)
#  pragma pop_macro("BadAlloc")
# else
	.value("BadAlloc", eglplus::ErrorCode::BadAlloc)
# endif
#endif
#if defined EGL_BAD_ATTRIBUTE
# if defined BadAttribute
#  pragma push_macro("BadAttribute")
#  undef BadAttribute
	.value("BadAttribute", eglplus::ErrorCode::BadAttribute)
#  pragma pop_macro("BadAttribute")
# else
	.value("BadAttribute", eglplus::ErrorCode::BadAttribute)
# endif
#endif
#if defined EGL_BAD_CONTEXT
# if defined BadContext
#  pragma push_macro("BadContext")
#  undef BadContext
	.value("BadContext", eglplus::ErrorCode::BadContext)
#  pragma pop_macro("BadContext")
# else
	.value("BadContext", eglplus::ErrorCode::BadContext)
# endif
#endif
#if defined EGL_BAD_CONFIG
# if defined BadConfig
#  pragma push_macro("BadConfig")
#  undef BadConfig
	.value("BadConfig", eglplus::ErrorCode::BadConfig)
#  pragma pop_macro("BadConfig")
# else
	.value("BadConfig", eglplus::ErrorCode::BadConfig)
# endif
#endif
#if defined EGL_BAD_CURRENT_SURFACE
# if defined BadCurrentSurface
#  pragma push_macro("BadCurrentSurface")
#  undef BadCurrentSurface
	.value("BadCurrentSurface", eglplus::ErrorCode::BadCurrentSurface)
#  pragma pop_macro("BadCurrentSurface")
# else
	.value("BadCurrentSurface", eglplus::ErrorCode::BadCurrentSurface)
# endif
#endif
#if defined EGL_BAD_DISPLAY
# if defined BadDisplay
#  pragma push_macro("BadDisplay")
#  undef BadDisplay
	.value("BadDisplay", eglplus::ErrorCode::BadDisplay)
#  pragma pop_macro("BadDisplay")
# else
	.value("BadDisplay", eglplus::ErrorCode::BadDisplay)
# endif
#endif
#if defined EGL_BAD_SURFACE
# if defined BadSurface
#  pragma push_macro("BadSurface")
#  undef BadSurface
	.value("BadSurface", eglplus::ErrorCode::BadSurface)
#  pragma pop_macro("BadSurface")
# else
	.value("BadSurface", eglplus::ErrorCode::BadSurface)
# endif
#endif
#if defined EGL_BAD_MATCH
# if defined BadMatch
#  pragma push_macro("BadMatch")
#  undef BadMatch
	.value("BadMatch", eglplus::ErrorCode::BadMatch)
#  pragma pop_macro("BadMatch")
# else
	.value("BadMatch", eglplus::ErrorCode::BadMatch)
# endif
#endif
#if defined EGL_BAD_PARAMETER
# if defined BadParameter
#  pragma push_macro("BadParameter")
#  undef BadParameter
	.value("BadParameter", eglplus::ErrorCode::BadParameter)
#  pragma pop_macro("BadParameter")
# else
	.value("BadParameter", eglplus::ErrorCode::BadParameter)
# endif
#endif
#if defined EGL_BAD_NATIVE_PIXMAP
# if defined BadNativePixmap
#  pragma push_macro("BadNativePixmap")
#  undef BadNativePixmap
	.value("BadNativePixmap", eglplus::ErrorCode::BadNativePixmap)
#  pragma pop_macro("BadNativePixmap")
# else
	.value("BadNativePixmap", eglplus::ErrorCode::BadNativePixmap)
# endif
#endif
#if defined EGL_BAD_NATIVE_WINDOW
# if defined BadNativeWindow
#  pragma push_macro("BadNativeWindow")
#  undef BadNativeWindow
	.value("BadNativeWindow", eglplus::ErrorCode::BadNativeWindow)
#  pragma pop_macro("BadNativeWindow")
# else
	.value("BadNativeWindow", eglplus::ErrorCode::BadNativeWindow)
# endif
#endif
#if defined EGL_CONTEXT_LOST
# if defined ContextLost
#  pragma push_macro("ContextLost")
#  undef ContextLost
	.value("ContextLost", eglplus::ErrorCode::ContextLost)
#  pragma pop_macro("ContextLost")
# else
	.value("ContextLost", eglplus::ErrorCode::ContextLost)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::ErrorCode) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
