/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_config_error
namespace oglplus {

#ifndef OGLPLUS_ERROR_NO_GL_LIB /*<
	Disables the GLLib() attribute of __Error.
>*/
# define OGLPLUS_ERROR_NO_GL_LIB 0
#endif

#ifndef OGLPLUS_ERROR_NO_GL_FUNC /*<
	Disables the GLFunc() attribute of __Error.
>*/
# define OGLPLUS_ERROR_NO_GL_FUNC 0
#endif

} // namespace oglplus
//]

