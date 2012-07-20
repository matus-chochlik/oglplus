/*
 *  .file oglplus/enums/framebuffer_status.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/framebuffer_status.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
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

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FRAMEBUFFER_COMPLETE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Complete)
#  pragma push_macro("Complete")
#  undef Complete
   OGLPLUS_ENUM_CLASS_VALUE(Complete, GL_FRAMEBUFFER_COMPLETE)
#  pragma pop_macro("Complete")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Complete, GL_FRAMEBUFFER_COMPLETE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_UNDEFINED
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Undefined)
#  pragma push_macro("Undefined")
#  undef Undefined
   OGLPLUS_ENUM_CLASS_VALUE(Undefined, GL_FRAMEBUFFER_UNDEFINED)
#  pragma pop_macro("Undefined")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Undefined, GL_FRAMEBUFFER_UNDEFINED)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IncompleteAttachment)
#  pragma push_macro("IncompleteAttachment")
#  undef IncompleteAttachment
   OGLPLUS_ENUM_CLASS_VALUE(IncompleteAttachment, GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
#  pragma pop_macro("IncompleteAttachment")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IncompleteAttachment, GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IncompleteMissingAttachment)
#  pragma push_macro("IncompleteMissingAttachment")
#  undef IncompleteMissingAttachment
   OGLPLUS_ENUM_CLASS_VALUE(IncompleteMissingAttachment, GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
#  pragma pop_macro("IncompleteMissingAttachment")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IncompleteMissingAttachment, GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_UNSUPPORTED
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Unsupported)
#  pragma push_macro("Unsupported")
#  undef Unsupported
   OGLPLUS_ENUM_CLASS_VALUE(Unsupported, GL_FRAMEBUFFER_UNSUPPORTED)
#  pragma pop_macro("Unsupported")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Unsupported, GL_FRAMEBUFFER_UNSUPPORTED)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IncompleteMultisample)
#  pragma push_macro("IncompleteMultisample")
#  undef IncompleteMultisample
   OGLPLUS_ENUM_CLASS_VALUE(IncompleteMultisample, GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
#  pragma pop_macro("IncompleteMultisample")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IncompleteMultisample, GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IncompleteLayerTargets)
#  pragma push_macro("IncompleteLayerTargets")
#  undef IncompleteLayerTargets
   OGLPLUS_ENUM_CLASS_VALUE(IncompleteLayerTargets, GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
#  pragma pop_macro("IncompleteLayerTargets")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IncompleteLayerTargets, GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

