/**
 *  .file lib/oglplus/debug_output.cpp
 *  .brief ARB_debug_output and KHR_debug functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "prologue.ipp"
#include <oglplus/extension.hpp>
#include <oglplus/ext/ARB_debug_output/severity.hpp>
#include <oglplus/ext/ARB_debug_output/source.hpp>
#include <oglplus/ext/ARB_debug_output/type.hpp>
#include <oglplus/ext/KHR_debug/severity.hpp>
#include <oglplus/ext/KHR_debug/source.hpp>
#include <oglplus/ext/KHR_debug/type.hpp>

#include "implement.ipp"

#include <oglplus/ext/ARB_debug_output.hpp>
//TODO: this causes problems with certain versions of GLEW
//#include <oglplus/ext/KHR_debug.hpp>
#include "epilogue.ipp"
