/**
 *  @file oglplus/renderbuffer.ipp
 *  @brief Implementation of Renderbuffer functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
GLenum RenderbufferOps::_binding_query(Target target)
{
	switch(GLenum(target))
	{
#include <oglplus/enums/renderbuffer_target_bq.ipp>
		default:;
	}
	return 0;
}

} // namespace oglplus

