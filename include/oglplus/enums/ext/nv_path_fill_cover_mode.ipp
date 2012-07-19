/*
 *  .file oglplus/enums/ext/nv_path_fill_cover_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_fill_cover_mode.txt' instead.
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
/// PATH_FILL_COVER_MODE_NV
FillCover

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_CONVEX_HULL_NV
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(ConvexHull, GL_CONVEX_HULL_NV)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BOUNDING_BOX_NV
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(BoundingBox, GL_BOUNDING_BOX_NV)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(BoundingBoxOfBoundingBoxes, GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PATH_FILL_COVER_MODE_NV
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(FillCover, GL_PATH_FILL_COVER_MODE_NV)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

