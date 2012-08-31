/*
 *  .file oglplus/names/framebuffer_status.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/framebuffer_status.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(value)
{
#if defined GL_FRAMEBUFFER_COMPLETE
	case GL_FRAMEBUFFER_COMPLETE: return StrLit("FRAMEBUFFER_COMPLETE");
#endif
#if defined GL_FRAMEBUFFER_UNDEFINED
	case GL_FRAMEBUFFER_UNDEFINED: return StrLit("FRAMEBUFFER_UNDEFINED");
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: return StrLit("FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return StrLit("FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
#endif
#if defined GL_FRAMEBUFFER_UNSUPPORTED
	case GL_FRAMEBUFFER_UNSUPPORTED: return StrLit("FRAMEBUFFER_UNSUPPORTED");
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: return StrLit("FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
	case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: return StrLit("FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
#endif
	default:;
}

