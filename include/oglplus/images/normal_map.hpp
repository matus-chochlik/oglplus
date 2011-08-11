/**
 *  @file oglplus/images/normal_map.hpp
 *  @brief Filter creating a normal+height map out of a height map
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_NORMAL_MAP_1107121519_HPP
#define OGLPLUS_IMAGES_NORMAL_MAP_1107121519_HPP

#include <oglplus/images/filtered.hpp>

namespace oglplus {
namespace images {

template <typename T>
class NormalMap
 : public FilteredImage<T, 4>
{
private:

	struct _filter
	{
		template <typename Extractor, typename Sampler, typename IT>
		Vector<T, 4> operator()(
			const Extractor& extractor,
			const Sampler& sampler,
			T one,
			IT ione
		) const
		{
			float sc = extractor(sampler.template get< 0,  0>());
			float sx = extractor(sampler.template get< 1,  0>());
			float sy = extractor(sampler.template get< 0,  1>());
			Vector<float, 3> vx(0.5f, 0, (sc-sx)/ione);
			Vector<float, 3> vy(0, 0.5f, (sc-sy)/ione);
			return Vector<float, 4>(
				Normalized(Cross(vx, vy)) * one,
				T((1.0f - sc/ione)*one)
			);
		}
	};
public:
	typedef FilteredImage<T, 4> Filter;

	template <typename IT,  typename Extractor = typename Filter::FromRed>
	NormalMap(const Image<IT>& input, Extractor extractor = Extractor())
	 : Filter(input, _filter(), extractor)
	{
		this->_format = PixelDataFormat::RGBA;
		this->_internal = PixelDataInternalFormat::RGBA;
	}
};

} // images
} // oglplus

#endif // include guard
