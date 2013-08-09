/**
 *  @file oglplus/images/random.hpp
 *  @brief Random image generator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_RANDOM_1107121519_HPP
#define OGLPLUS_IMAGES_RANDOM_1107121519_HPP

#include <oglplus/images/image.hpp>

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <cassert>
#include <cstdlib>
#endif

namespace oglplus {
namespace images {

/// Creates a RED (one component per pixel) white noise image
/**
 *  @ingroup image_load_gen
 */
class RandomRedUByte
 : public Image
{
public:
	RandomRedUByte(GLsizei width, GLsizei height = 1, GLsizei depth = 1);
};


/// Creates a RGB (three components per pixel) white noise image
/**
 *  @ingroup image_load_gen
 */
class RandomRGBUByte
 : public Image
{
public:
	RandomRGBUByte(GLsizei width, GLsizei height = 1, GLsizei depth = 1);
};

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)

OGLPLUS_LIB_FUNC
RandomRedUByte::RandomRedUByte(GLsizei width, GLsizei height, GLsizei depth)
 : Image(width, height, depth, 1, (GLubyte*)0)
{
	auto p = this->_begin_ub(), e = this->_end_ub();
	for(GLsizei k=0; k!=depth; ++k)
	for(GLsizei j=0; j!=height; ++j)
	for(GLsizei i=0; i!=width; ++i)
	{
		assert(p != e);
		*p = ::std::rand() % 0x100;
		++p;
	}
	OGLPLUS_FAKE_USE(e);
	assert(p == e);
}

OGLPLUS_LIB_FUNC
RandomRGBUByte::RandomRGBUByte(GLsizei width, GLsizei height, GLsizei depth)
 : Image(width, height, depth, 3, (GLubyte*)0)
{
	auto p = this->_begin_ub(), e = this->_end_ub();
	for(GLsizei k=0; k!=depth; ++k)
	for(GLsizei j=0; j!=height; ++j)
	for(GLsizei i=0; i!=width; ++i)
	for(GLsizei c=0; c!=3; ++c)
	{
		assert(p != e);
		*p = ::std::rand() % 0x100;
		++p;
	}
	OGLPLUS_FAKE_USE(e);
	assert(p == e);
}

#endif // OGLPLUS_LINK_LIBRARY

} // images
} // oglplus

#endif // include guard
