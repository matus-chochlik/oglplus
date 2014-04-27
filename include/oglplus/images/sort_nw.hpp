/**
 *  @file oglplus/images/sort_nw.hpp
 *  @brief Generator of an image that encodes a sorting network
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_SORT_NW_1404252143_HPP
#define OGLPLUS_IMAGES_SORT_NW_1404252143_HPP

#include <oglplus/images/image.hpp>

namespace oglplus {
namespace images {

/// Generator of an Image encoding a sorting network of specified size
/**
 *  @ingroup image_load_gen
 */
class SortNWMap
 : public Image
{
private:
	typedef GLushort T;
	static unsigned _pot(unsigned n);
	static unsigned _next_log(unsigned n);
	static unsigned _num_steps(unsigned size);
public:
	/// Generates the sorting network encoding
	SortNWMap(unsigned size);
};

} // images
} // oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/images/sort_nw.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
