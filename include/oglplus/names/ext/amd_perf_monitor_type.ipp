/*
 *  .file oglplus/names/ext/amd_perf_monitor_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/amd_perf_monitor_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(value)
{
#if defined GL_UNSIGNED_INT
	case GL_UNSIGNED_INT: return StrLit("UNSIGNED_INT");
#endif
#if defined GL_FLOAT
	case GL_FLOAT: return StrLit("FLOAT");
#endif
#if defined GL_UNSIGNED_INT64_AMD
	case GL_UNSIGNED_INT64_AMD: return StrLit("UNSIGNED_INT64_AMD");
#endif
#if defined GL_PERCENTAGE_AMD
	case GL_PERCENTAGE_AMD: return StrLit("PERCENTAGE_AMD");
#endif
	default:;
}

