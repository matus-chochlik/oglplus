/**
 *  @file oglplus/images/filtered.hpp
 *  @brief Base class for image filters
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_FILTERED_1107121519_HPP
#define OGLPLUS_IMAGES_FILTERED_1107121519_HPP

#include <oglplus/image.hpp>
#include <oglplus/vector.hpp>

#include <cassert>

namespace oglplus {
namespace images {

/// Base class for various image filters
/**
 *  @note Do not use this class directly, use the derived filters instead.
 *  @ingroup image_load_gen
 */
template <typename T, unsigned CH>
class FilteredImage
 : public Image
{
private:
	static_assert(
		CH > 0 && CH <= 4,
		"Number of channels must be between 1 and 4"
	);
protected:
	struct _sampler
	{
	private:
		unsigned _width, _height, _channels, _x, _y, _z;
		const Image& _image;
	public:
		_sampler(
			unsigned width,
			unsigned height,
			unsigned /*depth*/,
			unsigned channels,
			unsigned x,
			unsigned y,
			unsigned z,
			const Image& image
		): _width(width)
		 , _height(height)
		 , _channels(channels)
		 , _x(x)
		 , _y(y)
		 , _z(z)
		 , _image(image)
		{
			assert(channels >= 1 && channels <= 4);
		}

		Vector<GLdouble, 4> get(int xoffs, int yoffs) const
		{
			assert(xoffs > int(-_width));
			assert(yoffs > int(-_height));
			assert(xoffs < int( _width));
			assert(yoffs < int( _height));

			int xpos = _x + xoffs;
			if(xpos >= int(_width)) xpos %= _width;
			if(xpos < 0) xpos = (xpos+_width)%_width;

			int ypos = _y + yoffs;
			if(ypos >= int(_height)) ypos %= _height;
			if(ypos < 0) ypos = (ypos+_height)%_height;

			return _image.Pixel(xpos, ypos, _z);
		}
	};
private:
	template <typename Filter, typename Extractor>
	void _calculate(
		const Image& input,
		Filter filter,
		Extractor extractor,
		T one
	)
	{
		unsigned c = input.Channels();
		auto p = this->_begin<T>(), e = this->_end<T>();
		unsigned w = input.Width(), h = input.Height(), d = input.Depth();
		for(unsigned k=0; k!=d; ++k)
		for(unsigned j=0; j!=h; ++j)
		for(unsigned i=0; i!=w; ++i)
		{
			_sampler sampler(w, h, d, c, i, j, k, input);
			Vector<T, CH> outv = filter(extractor, sampler, one);

			for(unsigned c=0; c!=CH; ++c)
			{
				assert(p != e);
				*p = outv.At(c);
				++p;
			}
		}
		OGLPLUS_FAKE_USE(e);
		assert(p == e);
	}
public:
	/// Extractor that allows to specify which component to use as input
	template <unsigned I>
	struct FromComponentI
	{
		template <typename IT>
		IT operator()(const Vector<IT, 4>& v) const
		{
			return v.At(I);
		}
	};

	/// Extractor selecting the Red component of the input image
	typedef FromComponentI<0> FromRed;
	/// Extractor selecting the Green component of the input image
	typedef FromComponentI<1> FromGreen;
	/// Extractor selecting the Blue component of the input image
	typedef FromComponentI<2> FromBlue;
	/// Extractor selecting the Alpha component of the input image
	typedef FromComponentI<3> FromAlpha;

	struct FromRGB
	{
		template <typename IT>
		Vector<IT, 3> operator()(const Vector<IT, 4>& v) const
		{
			return v.xyz();
		}
	};

	template <typename Filter, typename Extractor>
	FilteredImage(
		const Image& input,
		Filter filter,
		Extractor extractor
	): Image(input.Width(), input.Height(), input.Depth(), CH, (T*)0)
	{
		_calculate(input, filter, extractor, this->_one((T*)0));
	}
};

} // images
} // oglplus

#endif // include guard
