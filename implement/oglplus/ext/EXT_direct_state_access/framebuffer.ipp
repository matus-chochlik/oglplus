/**
 *  @file oglplus/ext/EXT_direct_state_access/framebuffer.ipp
 *  @brief Implementation of DSA Framebuffer functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

#if GL_EXT_direct_state_access

OGLPLUS_LIB_FUNC
void DSAFramebufferEXTOps::HandleIncompleteError(
	FramebufferStatus status
) const
{
	HandleIncompleteFramebuffer<IncompleteFramebuffer>(
		status,
		OGLPLUS_OBJECT_ERROR_INFO(
			CheckFramebufferStatus,
			Framebuffer,
			EnumValueName(target),
			_name
		)
	);
}

#endif // GL_EXT_direct_state_access

} // namespace oglplus

