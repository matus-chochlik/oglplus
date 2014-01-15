/**
 *  @file oglplus/framebuffer_attachment.hpp
 *  @brief OpenGL Framebuffer attachment enumerations.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRAMEBUFFER_ATTACHMENT_1312081013_HPP
#define OGLPLUS_FRAMEBUFFER_ATTACHMENT_1312081013_HPP

#include <oglplus/enumerations.hpp>
#include <oglplus/limited_value.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY
/// Type for the framebuffer color attachment (implementation-dependent) number
class FramebufferColorAttachmentNumber
 : public LimitedCount
{
public:
	FramebufferColorAttachmentNumber(GLuint count);
};
#else
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	FramebufferColorAttachmentNumber,
	MAX_COLOR_ATTACHMENTS
)
#endif

/// Default framebuffer buffers
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferBuffer, GLenum)
#include <oglplus/enums/framebuffer_buffer.ipp>
OGLPLUS_ENUM_CLASS_END(FramebufferBuffer)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/framebuffer_buffer_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/framebuffer_buffer_range.ipp>
#endif

/// Framebuffer object attachment points
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferAttachment, GLenum)
#include <oglplus/enums/framebuffer_attachment.ipp>
OGLPLUS_ENUM_CLASS_END(FramebufferAttachment)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/framebuffer_attachment_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/framebuffer_attachment_range.ipp>
#endif

/// Framebuffer color attachment points
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferColorAttachment, GLenum)
#include <oglplus/enums/framebuffer_color_attachment.ipp>
OGLPLUS_ENUM_CLASS_END(FramebufferColorAttachment)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/framebuffer_color_attachment_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/framebuffer_color_attachment_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
