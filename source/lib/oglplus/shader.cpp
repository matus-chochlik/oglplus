/**
 *  .file lib/oglplus/shader.cpp
 *  .brief GLSL and Shader and shader variable-related functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "prologue.ipp"
#include <oglplus/auxiliary/glsl_source.hpp>
#include <oglplus/auxiliary/shader_data.hpp>
#include <oglplus/auxiliary/uniform_init.hpp>
#include <oglplus/auxiliary/uniform_typecheck.hpp>
#include <oglplus/auxiliary/info_log.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/uniform_block.hpp>
#include <oglplus/uniform_subroutines.hpp>
#include <oglplus/vertex_attrib.hpp>
#include "epilogue.ipp"
