/**
 *  @file oglplus/images/newton.hpp
 *  @brief Newton fractal image generator
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_NEWTON_1107121519_HPP
#define OGLPLUS_IMAGES_NEWTON_1107121519_HPP

#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/vector.hpp>

#include <cassert>

namespace oglplus {
namespace images {

class NewtonFractal
 : public Image<GLfloat>
{
private:
	// complex number division
	static Vec2f _cdiv(Vec2f a, Vec2f b)
	{
		float d = Dot(b, b);
		if(d == 0.0f) return a;
		else return Vec2f(
			(a.x()*b.x() + a.y()*b.y()) / d,
			(a.y()*b.x() - a.x()*b.y()) / d
		);
	}

	template <typename T>
	static T _mix(T a, T b, float coef)
	{
		return a*(1.0f - coef) + b*coef;
	}

	template <typename Function, size_t N>
	void _make(
		GLsizei width,
		GLsizei height,
		Function,
		Vec2f lb,
		Vec2f rt,
		Vector<float, N> c1,
		Vector<float, N> c2
	)
	{
		_data.resize(width*height*N);
		auto p = _data.begin(), e = _data.end();

		for(GLsizei i=0; i!=width; ++i)
		for(GLsizei j=0; j!=height; ++j)
		{
			Vec2f z(
				_mix(lb.x(), rt.x(), float(i)/float(width)),
				_mix(lb.y(), rt.y(), float(j)/float(height))
			);
			size_t n, max = 256;
			for(n = 0; n != max; ++n)
			{
				Vec2f zn = z - _cdiv(
					Function::f(z),
					Function::df(z)
				);
				if(Distance(zn, z) < 0.00001f) break;
				z = zn;
			}
			Vector<float, N> c = _mix(c1, c2, (float(n) / float(max)));
			for(n=0; n!=N; ++n)
			{
				assert(p != e);
				*p = c.At(n);
				++p;
			}
		}
		assert(p == e);
	}
public:
	/// The X^3-1 function and its derivation
	struct X3Minus1
	{
		static Vec2f f(Vec2f n)
		{
			return Vec2f(
				n.x()*n.x()*n.x() - 3.f*n.x()*n.y()*n.y() - 1.f,
				-n.y()*n.y()*n.y() + 3.f*n.x()*n.x()*n.y()
			);
		}

		static Vec2f df(Vec2f n)
		{
			return 3.0f * Vec2f(
				n.x()*n.x() - n.y()*n.y(),
				2.0 * n.x() * n.y()
			);
		}
	};

	/// Creates a RGB texture using c1 and c2 for colorizing of the fractal
	template <typename Function = X3Minus1>
	NewtonFractal(
		GLsizei width,
		GLsizei height,
		Vec3f c1,
		Vec3f c2,
		Vec2f lb = Vec2f(-1.0f, -1.0f),
		Vec2f rt = Vec2f( 1.0f,  1.0f),
		Function func = Function()
	): Image<GLfloat>(width, height, 1)
	{
		_make(width, height, func, lb, rt, c1, c2);
		_type = PixelDataType::Float;
		_format = PixelDataFormat::RGB;
		_internal = PixelDataInternalFormat::RGB;
	}

	/// Creates a Red texture colorized from black to red
	template <typename Function = X3Minus1>
	NewtonFractal(
		GLsizei width,
		GLsizei height,
		Function func = Function()
	): Image<GLfloat>(width, height, 1)
	{
		_make(
			width, height,
			func,
			Vec2f(-1.0f, -1.0f), Vec2f(1.0f, 1.0f),
			Vec1f(0.0f), Vec1f(1.0f)
		);
		_type = PixelDataType::Float;
		_format = PixelDataFormat::Red;
		_internal = PixelDataInternalFormat::Red;
	}
};

} // images
} // oglplus

#endif // include guard
