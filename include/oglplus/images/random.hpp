/**
 *  @file oglplus/images/random.hpp
 *  @brief Random image generator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_RANDOM_1107121519_HPP
#define OGLPLUS_IMAGES_RANDOM_1107121519_HPP

#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>

#include <cassert>
#include <cstdlib>

namespace oglplus {
namespace images {

/// Creates a RED (one component per pixel) white noise image
/** 
 *  @ingroup image_load_gen
 */
class RandomRedUByte
 : public Image<GLubyte>
{
public:
	RandomRedUByte(GLsizei width, GLsizei height = 1, GLsizei depth = 1)
	 : Image<GLubyte>(width, height, depth)
	{
		_data.resize(width*height*depth);
		auto p = _data.begin(), e = _data.end();
		for(GLsizei k=0; k!=depth; ++k)
		for(GLsizei j=0; j!=height; ++j)
		for(GLsizei i=0; i!=width; ++i)
		{
			assert(p != e);
			*p = ::std::rand() % 0x100;
			++p;
		}
		assert(p == e);
		_type = PixelDataType::UnsignedByte;
		_format = PixelDataFormat::Red;
		_internal = PixelDataInternalFormat::Red;
	}
};


/// Creates a RGB (three components per pixel) white noise image
/** 
 *  @ingroup image_load_gen
 */
class RandomRGBUByte
 : public Image<GLubyte>
{
public:
	RandomRGBUByte(GLsizei width, GLsizei height = 1, GLsizei depth = 1)
	 : Image<GLubyte>(width, height, depth)
	{
		_data.resize(width*height*depth*3);
		auto p = _data.begin(), e = _data.end();
		for(GLsizei k=0; k!=depth; ++k)
		for(GLsizei j=0; j!=height; ++j)
		for(GLsizei i=0; i!=width; ++i)
		for(GLsizei c=0; c!=3; ++c)
		{
			assert(p != e);
			*p = ::std::rand() % 0x100;
			++p;
		}
		assert(p == e);
		_type = PixelDataType::UnsignedByte;
		_format = PixelDataFormat::RGB;
		_internal = PixelDataInternalFormat::RGB;
	}
};

} // images
} // oglplus

#endif // include guard
