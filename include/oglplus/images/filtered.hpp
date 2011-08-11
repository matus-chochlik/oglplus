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
		size_t _width, _height, _iepp, _n;
		const IT* _data;
	public:
		_sampler(
			size_t width,
			size_t height,
			size_t iepp,
			size_t n,
			const IT* data
		): _width(width)
		 , _height(height)
		 , _iepp(iepp)
		 , _n(n)
		 , _data(data)
		{
			assert(_iepp > 0 && _iepp <= 4);
		}

		template <int Xoffs, int Yoffs>
		Vector<IT, 4> get(void) const
		{
			assert(Xoffs > int(-_width));
			assert(Yoffs > int(-_height));
			assert(Xoffs < int( _width));
			assert(Yoffs < int( _height));

			size_t xoffs = (Xoffs < 0)?
				(Xoffs+_width) % _width :
				Xoffs;
			size_t yoffs = (Yoffs < 0)?
				(Yoffs+_height) % _height:
				Yoffs;
			size_t offs = _n + yoffs*_width + xoffs;
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
		size_t n = 0;
		for(size_t k=0,d=input.Depth();  k!=d; ++k)
		for(size_t j=0,h=input.Height(); j!=h; ++j)
		for(size_t i=0,w=input.Width();  i!=w; ++i)
		{
			_sampler<IT> sampler(w,h,iepp,n++,input.Data());
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

	template <typename IT>
	static IT _one(void)
	{
		return _one((IT*)0);
	}
public:
	template <size_t I>
	struct FromComponentI
	{
		template <typename IT>
		IT operator()(const Vector<IT, 4>& v) const
		{
			return v.template At<I>();
		}
	};

	typedef FromComponentI<0> FromRed;
	typedef FromComponentI<1> FromGreen;
	typedef FromComponentI<2> FromBlue;
	typedef FromComponentI<3> FromAlpha;

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
