/**
 *  @file oglplus/images/brushed_metal.hpp
 *  @brief Brushed metal texture generator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_BRUSHED_METAL_1107121519_HPP
#define OGLPLUS_IMAGES_BRUSHED_METAL_1107121519_HPP

#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>

#include <cassert>
#include <cstdlib>

namespace oglplus {
namespace images {

/// Creates a RGB (three components per pixel) image used for brushed metal effect
/**
 *  @ingroup image_load_gen
 */
class BrushedMetalUByte
 : public Image<GLubyte>
{
private:
	static void _make_pixel(
		GLubyte* b,
		GLubyte *e,
		GLsizei w,
		GLsizei h,
		GLint x,
		GLint y,
		GLdouble /*c*/,
		GLubyte r,
		GLubyte g
	)
	{
		while(x < 0) x += w;
		while(y < 0) y += h;
		if(x >= w) x %= w;
		if(y >= h) y %= h;
		GLubyte* p = b + (y*w + x)*3;
		GLubyte* pr = p;
		GLubyte* pg = p+1;
		GLubyte* pb = p+2;
		assert((pr < e) && (pg < e) && (pb < e));
		*pr = r;
		*pg = g;
		*pb = (*pb + 8) % 0x100;
	}

	static void _make_scratch(
		GLubyte* b,
		GLubyte *e,
		GLsizei w,
		GLsizei h,
		GLint x,
		GLint y,
		GLdouble dx,
		GLdouble dy
	)
	{
		if((dx == 0) && (dy == 0)) return;
		GLubyte r = dy/std::sqrt(dx*dx + dy*dy)*0xFF;
		GLubyte g = dx/std::sqrt(dx*dx + dy*dy)*0xFF;

		if(dx > dy)
		{
			if(dx >= 0)
			{
				for(GLint i=0; i!=dx; ++i)
				{
					GLdouble c = GLdouble(i)/dx;
					GLint j = dy*c;
					_make_pixel(b,e,w,h,x+i,y+j,c,r,g);
				}
			}
			else
			{
				for(GLint i=0; i!=dx; --i)
				{
					GLdouble c = GLdouble(i)/dx;
					GLint j = dy*c;
					_make_pixel(b,e,w,h,x+i,y+j,c,r,g);
				}
			}
		}
		else
		{
			if(dy >= 0)
			{
				for(GLint j=0; j!=dy; ++j)
				{
					GLdouble c = GLdouble(j)/dy;
					GLint i = dx*c;
					_make_pixel(b,e,w,h,x+i,y+j,c,r,g);
				}
			}
			else
			{
				for(GLint j=0; j!=dy; --j)
				{
					GLdouble c = GLdouble(j)/dy;
					GLint i = dx*c;
					_make_pixel(b,e,w,h,x+i,y+j,c,r,g);
				}
			}
		}

	}
public:
	BrushedMetalUByte(
		GLsizei width,
		GLsizei height,
		size_t n_scratches,
		int s_disp_min,
		int s_disp_max,
		int t_disp_min,
		int t_disp_max
	): Image<GLubyte>(width, height, 1)
	{
		_data.resize(width*height*3, GLubyte(0));
		GLubyte *p = _data.data(), *e = _data.data() + _data.size();
		while(n_scratches--)
		{
			const GLuint n_segments = 1 + std::rand() % 4;
			GLint x = std::rand() % width;
			GLint y = std::rand() % height;
			for(GLuint seg=0; seg!=n_segments; ++seg)
			{
				GLint dx = s_disp_min +
					std::rand()%(s_disp_max-s_disp_min+1);
				GLint dy = t_disp_min +
					std::rand()%(t_disp_max-t_disp_min+1);

				_make_scratch(
					p, e,
					width,
					height,
					x, y,
					dx, dy
				);
				x += dx;
				y += dy;
			}
		}
		_type = PixelDataType::UnsignedByte;
		_format = PixelDataFormat::RGB;
		_internal = PixelDataInternalFormat::RGB;
	}
};

} // images
} // oglplus

#endif // include guard
