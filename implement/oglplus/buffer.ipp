/**
 *  @file oglplus/buffer.ipp
 *  @brief Implementation of Buffer functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
GLuint BufferOps::_binding(Target target)
{
	return BindingQuery<BufferOps>::QueryBinding(target);
}

OGLPLUS_LIB_FUNC
GLenum BufferOps::_binding_query(Target target)
{
	switch(GLenum(target))
	{
#include <oglplus/enums/buffer_target_bq.ipp>
		default:;
	}
	return 0;
}

OGLPLUS_LIB_FUNC
GLenum BufferOps::_binding_query(IndexedTarget target)
{
	switch(GLenum(target))
	{
#include <oglplus/enums/buffer_indexed_target_bq.ipp>
		default:;
	}
	return 0;
}

} // namespace oglplus

