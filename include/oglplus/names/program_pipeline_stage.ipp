/*
 *  .file oglplus/names/program_pipeline_stage.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/program_pipeline_stage.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_VERTEX_SHADER_BIT
	case GL_VERTEX_SHADER_BIT: return "VERTEX_SHADER_BIT";
#endif
#if defined GL_TESS_CONTROL_SHADER_BIT
	case GL_TESS_CONTROL_SHADER_BIT: return "TESS_CONTROL_SHADER_BIT";
#endif
#if defined GL_TESS_EVALUATION_SHADER_BIT
	case GL_TESS_EVALUATION_SHADER_BIT: return "TESS_EVALUATION_SHADER_BIT";
#endif
#if defined GL_GEOMETRY_SHADER_BIT
	case GL_GEOMETRY_SHADER_BIT: return "GEOMETRY_SHADER_BIT";
#endif
#if defined GL_FRAGMENT_SHADER_BIT
	case GL_FRAGMENT_SHADER_BIT: return "FRAGMENT_SHADER_BIT";
#endif
#if defined GL_ALL_SHADER_BITS
	case GL_ALL_SHADER_BITS: return "ALL_SHADER_BITS";
#endif
	default:;
}

