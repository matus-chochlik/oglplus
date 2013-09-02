/**
 *  @file oglplus/images/sphere_bmap.hpp
 *  @brief Generator of a normal/depth map with "imprinted" sphere
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_SPHERE_BMAP_1107121519_HPP
#define OGLPLUS_IMAGES_SPHERE_BMAP_1107121519_HPP

#include <oglplus/images/image.hpp>

namespace oglplus {
namespace images {

class SphereBumpMap
 : public Image
{
public:
	SphereBumpMap(
		GLsizei width,
		GLsizei height,
		GLsizei xrep = 1,
		GLsizei yrep = 1
	);
};

} // images
} // oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/images/sphere_bmap.ipp>
#endif

#endif // include guard
