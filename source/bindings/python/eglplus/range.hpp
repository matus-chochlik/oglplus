/*
 *  .file eglplus/range.hpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_PYTHON_EGLPLUS_RANGE_0306061605_HPP
#define OGLPLUS_PYTHON_EGLPLUS_RANGE_0306061605_HPP

#include "../oglplus/range.hpp"
template <typename Range>
inline void eglplus_py_export_range(const char* name)
{
	oglplus_py_export_range<Range>(name);
}

#endif
