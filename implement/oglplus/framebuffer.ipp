/**
 *  @file oglplus/framebuffer.ipp
 *  @brief Implementation of Framebuffer functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

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

