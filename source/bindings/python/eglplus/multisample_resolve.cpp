/*
 *  .file eglplus/multisample_resolve.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/multisample_resolve.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/multisample_resolve.hpp>

#include <boost/python.hpp>

void eglplus_py_multisample_resolve(void)
{
	boost::python::enum_<eglplus::MultisampleResolve>("MultisampleResolve")
#if defined EGL_MULTISAMPLE_RESOLVE_DEFAULT
# if defined Default
#  pragma push_macro("Default")
#  undef Default
	.value("Default", eglplus::MultisampleResolve::Default)
#  pragma pop_macro("Default")
# else
	.value("Default", eglplus::MultisampleResolve::Default)
# endif
#endif
#if defined EGL_MULTISAMPLE_RESOLVE_BOX
# if defined Box
#  pragma push_macro("Box")
#  undef Box
	.value("Box", eglplus::MultisampleResolve::Box)
#  pragma pop_macro("Box")
# else
	.value("Box", eglplus::MultisampleResolve::Box)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::MultisampleResolve) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
