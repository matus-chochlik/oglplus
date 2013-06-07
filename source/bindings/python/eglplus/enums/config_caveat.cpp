/*
 *  .file eglplus/enums/config_caveat.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/config_caveat.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/config_caveat.hpp>

#include <boost/python.hpp>

void eglplus_py_config_caveat(void)
{
	boost::python::enum_<eglplus::ConfigCaveat>("ConfigCaveat")
#if defined EGL_NONE
# if defined None
#  pragma push_macro("None")
#  undef None
	.value("None", eglplus::ConfigCaveat::None)
#  pragma pop_macro("None")
# else
	.value("None", eglplus::ConfigCaveat::None)
# endif
#endif
#if defined EGL_SLOW_CONFIG
# if defined SlowConfig
#  pragma push_macro("SlowConfig")
#  undef SlowConfig
	.value("SlowConfig", eglplus::ConfigCaveat::SlowConfig)
#  pragma pop_macro("SlowConfig")
# else
	.value("SlowConfig", eglplus::ConfigCaveat::SlowConfig)
# endif
#endif
#if defined EGL_NON_CONFORMANT_CONFIG
# if defined NonConformantConfig
#  pragma push_macro("NonConformantConfig")
#  undef NonConformantConfig
	.value("NonConformantConfig", eglplus::ConfigCaveat::NonConformantConfig)
#  pragma pop_macro("NonConformantConfig")
# else
	.value("NonConformantConfig", eglplus::ConfigCaveat::NonConformantConfig)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::ConfigCaveat) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
