/*
 *  .file eglplus/swap_behavior.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/swap_behavior.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/swap_behavior.hpp>

#include <boost/python.hpp>

void eglplus_py_swap_behavior(void)
{
	boost::python::enum_<eglplus::SwapBehavior>("SwapBehavior")
#if defined EGL_BUFFER_PRESERVED
# if defined BufferPreserved
#  pragma push_macro("BufferPreserved")
#  undef BufferPreserved
	.value("BufferPreserved", eglplus::SwapBehavior::BufferPreserved)
#  pragma pop_macro("BufferPreserved")
# else
	.value("BufferPreserved", eglplus::SwapBehavior::BufferPreserved)
# endif
#endif
#if defined EGL_BUFFER_DESTROYED
# if defined BufferDestroyed
#  pragma push_macro("BufferDestroyed")
#  undef BufferDestroyed
	.value("BufferDestroyed", eglplus::SwapBehavior::BufferDestroyed)
#  pragma pop_macro("BufferDestroyed")
# else
	.value("BufferDestroyed", eglplus::SwapBehavior::BufferDestroyed)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::SwapBehavior) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
