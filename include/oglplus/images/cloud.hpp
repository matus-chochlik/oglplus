/**
 *  @file oglplus/images/cloud.hpp
 *  @brief Cloud 3d texture generator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_CLOUD_1107121519_HPP
#define OGLPLUS_IMAGES_CLOUD_1107121519_HPP

#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/angle.hpp>

#include <cassert>
#include <cstdlib>
#include <cmath>

#include <iostream>

namespace oglplus {
namespace images {

class Cloud
 : public Image<GLubyte>
{
private:
	GLfloat _sub_scale;
	GLfloat _sub_variance;
	GLfloat _min_radius;

	void _adjust_sphere(Vec3f& center, GLfloat& radius) const
	{
		GLfloat c[3] = {center.x(), center.y(), center.z()};
		for(size_t i=0; i!=3; ++i)
		{
			if(c[i] < -1.0f)
			{
				radius *= 0.5f;
				c[i] = -1.0f + radius;
			}
			if(c[i] > 1.0f)
			{
				radius *= 0.5f;
				c[i] = 1.0f - radius;
			}
			if((c[i] - radius) < -1.0f)
			{
				GLfloat d = (-1.0f - c[i] + radius)*0.51f;
				assert(d >= 0.0f);
				radius -= d;
				c[i] += d;
			}
			if((c[i] + radius) > 1.0f)
			{
				GLfloat d = (c[i] + radius - 1.0f)*0.51f;
				assert(d >= 0.0f);
				radius -= d;
				c[i] -= d;
			}
		}
		center = Vec3f(c[0], c[1], c[2]);
	}

	bool _apply_sphere(const Vec3f& center, GLfloat radius)
	{
		assert(radius > 0.0f);
		bool something_updated = false;
		Vec3f c = center*0.5f + Vec3f(0.5f, 0.5f, 0.5f);
		GLfloat r = radius*0.5f;
		GLsizei w = Width(), h = Height(), d = Depth();
		for(GLsizei k=(c.z()-r)*d, ke=(c.z()+r)*d; k!=ke; ++k)
		for(GLsizei j=(c.y()-r)*h, je=(c.y()+r)*h; j!=je; ++j)
		for(GLsizei i=(c.x()-r)*w, ie=(c.x()+r)*w; i!=ie; ++i)
		{
			assert(k >= 0 && k < d);
			assert(j >= 0 && j < h);
			assert(i >= 0 && i < w);
			GLsizei n = k*w*h + j*w + i;
			GLubyte b = _data[n];
			if(b != 0xFF)
			{
				GLfloat cd = GLfloat(b)/GLfloat(0xFF);
				Vec3f p(GLfloat(i)/w, GLfloat(j)/h, GLfloat(k)/d);
				GLfloat nd = (r - Distance(c, p))/r;
				if(nd < 0.0f) nd = 0.0f;
				nd += cd;
				if(nd > 1.0f) nd = 1.0f;
				_data[n] = GLubyte(0xFF * nd);
				something_updated = true;
			}
		}
		return something_updated;
	}

	static GLfloat _rand_u(void)
	{
		return GLfloat(std::rand())/RAND_MAX;
	}

	static GLfloat _rand_s(void)
	{
		return (_rand_u() - 0.5f)*2.0f;
	}

	void _make_spheres(Vec3f center, GLfloat radius)
	{
		_adjust_sphere(center, radius);
		if(radius < _min_radius) return;
		if(!_apply_sphere(center, radius)) return;
		GLfloat sub_radius = radius * _sub_scale;
		GLsizei i = 0, n = (8.0f*radius*radius)/(sub_radius*sub_radius);
		while(i != n)
		{
			auto rad = radius*(1.0f + _rand_s()*_sub_variance*0.5f);
			auto rho = FullCircles(_rand_u());
			auto phi = RightAngles(_rand_s());
			_make_spheres(
				center + Vec3f(
					rad*Cos(phi)*Cos(rho),
					rad*Sin(phi),
					rad*Cos(phi)*Sin(rho)
				),
				sub_radius*(1.0f + _rand_s()*_sub_variance)
			);
			++i;
		}
	}
public:
	Cloud(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		const Vec3f& origin = Vec3f(0.0f, -0.3f, 0.0f),
		GLfloat init_radius = 0.7f
	): Image<GLubyte>(width, height, depth)
	 , _sub_scale(0.333f)
	 , _sub_variance(0.3f)
	 , _min_radius(0.05f)
	{
		_data.resize(width*height*depth);
		auto p = _data.begin(), e = _data.end();
		for(GLsizei k=0; k!=depth; ++k)
		for(GLsizei j=0; j!=height; ++j)
		for(GLsizei i=0; i!=width; ++i)
		{
			assert(p != e);
			*p = GLubyte(0);
			++p;
		}
		assert(p == e);
		_make_spheres(origin, init_radius);
		_type = PixelDataType::UnsignedByte;
		_format = PixelDataFormat::Red;
		_internal = PixelDataInternalFormat::Red;
	}
};


} // images
} // oglplus

#endif // include guard
