/**
 *  @file oglplus/images/squares.hpp
 *  @brief Generator of a image covered with reqular squares
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_SQUARES_1107121519_HPP
#define OGLPLUS_IMAGES_SQUARES_1107121519_HPP

#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>

#include <cassert>
#include <cmath>

namespace oglplus {
namespace images {

class Squares
 : public Image<GLubyte>
{
public:
	Squares(
		GLsizei width,
		GLsizei height,
		GLfloat ratio = 0.8f,
		GLsizei xrep = 2,
		GLsizei yrep = 2
	): Image<GLubyte>(width, height, 1)
	{
		assert(width != 0 && height != 0);
		assert(ratio > 0.0f && ratio <= 1.0f);
		assert(xrep != 0 && yrep != 0);
		_data.resize(width*height);

		float rmin = (1.0f - ratio) * 0.5f;
		float rmax = rmin + ratio;

		unsigned n = 0;

		for(GLsizei y=0; y!=height; ++y)
		for(GLsizei x=0; x!=width;  ++x)
		{
			float vx = float((x * xrep)% width)/width;
			float vy = float((y * yrep)%height)/height;
			bool outside =
				((vx < rmin) || (vx > rmax)) ||
				((vy < rmin) || (vy > rmax));
			_data[n++] = outside?0x00:0xFF;
		}

		assert(n == _data.size());

		_type = PixelDataType::UnsignedByte;
		_format = PixelDataFormat::Red;
		_internal = PixelDataInternalFormat::Red;
	}
};

} // images
} // oglplus

#endif // include guard
