/**
 *  @file oglplus/images/voronoi.hpp
 *  @brief Voronoi diagram image generators
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_VORONOI_1107121519_HPP
#define OGLPLUS_IMAGES_VORONOI_1107121519_HPP

#include <oglplus/images/image.hpp>

namespace oglplus {
namespace images {

class VoronoiDiagram
 : public Image
{
public:
	VoronoiDiagram(
		GLsizei cell_w,
		GLsizei cell_h,
		GLsizei cell_d,
		const Image& input
	);
};

class VoronoiCells
 : public Image
{
public:
	VoronoiCells(
		GLsizei cell_w,
		GLsizei cell_h,
		GLsizei cell_d,
		const Image& input
	);
};

} // images
} // oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/images/voronoi.ipp>
#endif

#endif // include guard
