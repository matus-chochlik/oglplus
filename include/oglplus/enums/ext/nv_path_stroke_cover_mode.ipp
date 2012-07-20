/*
 *  .file oglplus/enums/ext/nv_path_stroke_cover_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_stroke_cover_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// CONVEX_HULL_NV
ConvexHull,
/// BOUNDING_BOX_NV
BoundingBox,
/// BOUNDING_BOX_OF_BOUNDING_BOXES_NV
BoundingBoxOfBoundingBoxes,
/// PATH_STROKE_COVER_MODE_NV
StrokeCover

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_CONVEX_HULL_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ConvexHull)
#  pragma push_macro("ConvexHull")
#  undef ConvexHull
   OGLPLUS_ENUM_CLASS_VALUE(ConvexHull, GL_CONVEX_HULL_NV)
#  pragma pop_macro("ConvexHull")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ConvexHull, GL_CONVEX_HULL_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BOUNDING_BOX_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(BoundingBox)
#  pragma push_macro("BoundingBox")
#  undef BoundingBox
   OGLPLUS_ENUM_CLASS_VALUE(BoundingBox, GL_BOUNDING_BOX_NV)
#  pragma pop_macro("BoundingBox")
# else
   OGLPLUS_ENUM_CLASS_VALUE(BoundingBox, GL_BOUNDING_BOX_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(BoundingBoxOfBoundingBoxes)
#  pragma push_macro("BoundingBoxOfBoundingBoxes")
#  undef BoundingBoxOfBoundingBoxes
   OGLPLUS_ENUM_CLASS_VALUE(BoundingBoxOfBoundingBoxes, GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV)
#  pragma pop_macro("BoundingBoxOfBoundingBoxes")
# else
   OGLPLUS_ENUM_CLASS_VALUE(BoundingBoxOfBoundingBoxes, GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PATH_STROKE_COVER_MODE_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StrokeCover)
#  pragma push_macro("StrokeCover")
#  undef StrokeCover
   OGLPLUS_ENUM_CLASS_VALUE(StrokeCover, GL_PATH_STROKE_COVER_MODE_NV)
#  pragma pop_macro("StrokeCover")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StrokeCover, GL_PATH_STROKE_COVER_MODE_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

