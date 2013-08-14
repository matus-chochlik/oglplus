/**
 *  @file oglplus/images/checker.hpp
 *  @brief Checker image generator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_CHECKER_1107121519_HPP
#define OGLPLUS_IMAGES_CHECKER_1107121519_HPP

#include <oglplus/images/image.hpp>

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <cassert>
#include <cmath>
#endif

namespace oglplus {
namespace images {

class CheckerRedBlack
 : public Image
{
public:
	CheckerRedBlack(
		GLsizei width,
		GLsizei height,
		GLsizei xrep = 4,
		GLsizei yrep = 4
	);
};

// Implementation
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
CheckerRedBlack::CheckerRedBlack(
	GLsizei width,
	GLsizei height,
	GLsizei xrep,
	GLsizei yrep
): Image(
	width,
	height,
	1,
	1,
	(GLubyte*)0,
	PixelDataFormat::Red,
	PixelDataInternalFormat::Red
)
{
	assert(width != 0 && height != 0);
	assert(xrep != 0 && yrep != 0);

	GLsizei xdiv = width / xrep;
	GLsizei ydiv = height/ yrep;

	auto p = this->_begin<GLubyte>();
	for(GLsizei j=0; j!=height; ++j)
	{
		GLsizei y = j / ydiv;
		for(GLsizei i=0; i!=width; ++i)
		{
			GLsizei x = i / xdiv;
			GLubyte c = ((x+y)%2==0)?0x00:0xFF;
			assert(p != this->_end<GLubyte>());
			*p = c; ++p;
		}
	}
	assert(p == this->_end<GLubyte>());
}
#endif

} // images
} // oglplus

#endif // include guard
