/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_framebuffer_color_attachment_number
namespace oglplus {

class FramebufferColorAttachmentNumber
 : public __LimitedCount
{
public:
	FramebufferColorAttachmentNumber(GLuint number); /*<
	Throws __LimitError if [^number] is greater than
	the implementation-dependent maximum number of framebuffer
	color attachments.
	See [glconst MAX_COLOR_ATTACHMENTS].
	>*/
};

} // namespace oglplus
//]

