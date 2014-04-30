/**
 *  @file oglplus/framebuffer.ipp
 *  @brief Implementation of Framebuffer functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
GLuint FramebufferOps::_binding(Target target)
{
	return BindingQuery<FramebufferOps>::QueryBinding(target);
}

OGLPLUS_LIB_FUNC
GLenum FramebufferOps::_binding_query(Target target)
{
	switch(GLenum(target))
	{
#include <oglplus/enums/framebuffer_target_bq.ipp>
		default:;
	}
	return 0;
}

OGLPLUS_LIB_FUNC
void FramebufferOps::HandleIncompleteError(
	Target target,
	FramebufferStatus status
)
{
	OGLPLUS_FAKE_USE(target);
	HandleIncompleteFramebuffer<IncompleteFramebuffer>(
		status,
		OGLPLUS_OBJECT_ERROR_INFO(
			CheckFramebufferStatus,
			Framebuffer,
			EnumValueName(target),
			BindingQuery<FramebufferOps>::
			QueryBinding(target)
		)
	);
}

} // namespace oglplus

