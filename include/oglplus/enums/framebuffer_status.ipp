/*
 *  .file oglplus/enums/framebuffer_status.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/framebuffer_status.txt' instead.
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// FRAMEBUFFER_COMPLETE
Complete,
/// FRAMEBUFFER_UNDEFINED
Undefined,
/// FRAMEBUFFER_INCOMPLETE_ATTACHMENT
IncompleteAttachment,
/// FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
IncompleteMissingAttachment,
/// FRAMEBUFFER_UNSUPPORTED
Unsupported,
/// FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
IncompleteMultisample,
/// FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
IncompleteLayerTargets

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FRAMEBUFFER_COMPLETE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Complete = GL_FRAMEBUFFER_COMPLETE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_UNDEFINED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Undefined = GL_FRAMEBUFFER_UNDEFINED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
IncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_UNSUPPORTED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Unsupported = GL_FRAMEBUFFER_UNSUPPORTED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
IncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
IncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

