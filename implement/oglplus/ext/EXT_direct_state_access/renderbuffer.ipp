/**
 *  @file oglplus/ext/EXT_direct_state_access/renderbuffer.ipp
 *  @brief Implementation of DSA Renderbuffer functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/images/image_spec.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {

#if GL_EXT_direct_state_access

OGLPLUS_LIB_FUNC
void DSARenderbufferEXTOps::Storage(const images::ImageSpec& image_spec)
{
	Storage(
		image_spec.internal_format,
		image_spec.width,
		image_spec.height
	);
}

#endif // GL_EXT_direct_state_access

} // namespace oglplus

