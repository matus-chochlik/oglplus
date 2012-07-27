/**
 *  @file oglplus/images/filtered.hpp
 *  @brief Base class for image filters
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

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
template <typename T, size_t EPP>
class FilteredImage
 : public Image<T>
{
private:
	static_assert(
		EPP > 0 && EPP <= 4,
		"Number of Elements Per Pixel must be between 1 and 4"
	);
protected:
	template <typename IT>
	struct _sampler
	{
	private:
		size_t _width, _height, _iepp, _x, _y, _n;
		const IT* _data;
	public:
		_sampler(
			size_t width,
			size_t height,
			size_t iepp,
			size_t x,
			size_t y,
			size_t z,
			const IT* data
		): _width(width)
		 , _height(height)
		 , _iepp(iepp)
		 , _x(x)
		 , _y(y)
		 , _n(z*width*height)
		 , _data(data)
		{
			assert(_iepp > 0 && _iepp <= 4);
		}

		Vector<IT, 4> get(int xoffs, int yoffs) const
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

			size_t offs = _n + ypos*_width + xpos;
			const IT* p = _data + _iepp*offs;
			return Vector<IT, 4>(
				*p,
				(_iepp > 1) ? *(p+1) : T(0),
				(_iepp > 2) ? *(p+2) : T(0),
				(_iepp > 3) ? *(p+3) : T(0)
			);
		}
	};
private:
	template <typename IT, typename Filter, typename Extractor>
	void _calculate(
		const Image<IT>& input,
		Filter filter,
		Extractor extractor,
		T one,
		IT ione
	)
	{
		size_t iepp = input.ElementsPerPixel();
		auto p = this->_data.begin(), e = this->_data.end();
		size_t w = input.Width(), h = input.Height(), d = input.Depth();
		const IT* data = input.Data();
		for(size_t k=0; k!=d; ++k)
		for(size_t j=0; j!=h; ++j)
		for(size_t i=0; i!=w; ++i)
		{
			_sampler<IT> sampler(w,h,iepp,i,j,k,data);
			Vector<T, EPP> outv = filter(
				extractor,
				sampler,
				one,
				ione
			);
			for(size_t c=0; c!= EPP; ++c)
			{
				assert(p != e);
				*p = outv.At(c);
				++p;
			}
		}
		assert(p == e);
	}

	static GLubyte _one(GLubyte*)
	{
		return 0xFF;
	}

	static GLfloat _one(GLfloat*)
	{
		return 1.0f;
	}

	template <typename _T>
	static _T _one(void)
	{
		return _one((_T*)0);
	}
public:
	/// Extractor that allows to specify which component to use as input
	template <size_t I>
	struct FromComponentI
	{
		template <typename IT>
		IT operator()(const Vector<IT, 4>& v) const
		{
			return v.template At<I>();
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

	template <typename IT, typename Filter, typename Extractor>
	FilteredImage(
		const Image<IT>& input,
		Filter filter,
		Extractor extractor
	): Image<T>(input.Width(), input.Height(), input.Depth())
	{
		this->_data.resize(
			input.Width()*
			input.Height()*
			input.Depth()*
			EPP
		);
		assert(this->ElementsPerPixel() == EPP);
		_calculate(input, filter, extractor, _one<T>(), _one<IT>());

		this->_type = PixelDataType(oglplus::GetDataType((T*)0));
	}
};

} // images
} // oglplus

#endif // include guard
