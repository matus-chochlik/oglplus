/*
 *  .file eglplus/bitfield.hpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_PYTHON_EGLPLUS_BITFIELD_0306061605_HPP
#define OGLPLUS_PYTHON_EGLPLUS_BITFIELD_0306061605_HPP

#include <eglplus/egl.hpp>
#include <eglplus/bitfield.hpp>

#include "../oglplus/bitfield.hpp"

template <typename Bitfield>
inline void eglplus_py_export_Bitfield(const char* name)
{
	oglplus_py_export_Bitfield<Bitfield>(name);
}

#endif
