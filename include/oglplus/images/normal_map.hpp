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

class NormalMap
 : public FilteredImage<GLfloat, 3>
{
private:
	typedef GLfloat T;

	struct _filter
	{
		template <typename Extractor, typename Sampler, typename IT>
		Vector<T, 3> operator()(
			const Extractor& extractor,
			const Sampler& sampler,
			T one,
			IT ione
		) const
		{
			typedef float number;
			number s = 0.05;

			number sc  = extractor(sampler.get( 0, 0));
			number spx = extractor(sampler.get(+1, 0));
			number spy = extractor(sampler.get( 0,+1));
			number snx = extractor(sampler.get(-1, 0));
			number sny = extractor(sampler.get( 0,-1));
			Vector<number, 3> vpx(+s, 0, (spx-sc)/ione);
			Vector<number, 3> vpy(0, +s, (spy-sc)/ione);
			Vector<number, 3> vnx(-s, 0, (snx-sc)/ione);
			Vector<number, 3> vny(0, -s, (sny-sc)/ione);
			return Normalized(
				Cross(vpx, vpy) +
				Cross(vpy, vnx) +
				Cross(vnx, vny) +
				Cross(vny, vpx)
			) * one;
		}
	};
public:
	typedef FilteredImage<T, 3> Filter;

	template <typename IT,  typename Extractor = typename Filter::FromRed>
	NormalMap(const Image<IT>& input, Extractor extractor = Extractor())
	 : Filter(input, _filter(), extractor)
	{
		this->_format = PixelDataFormat::RGB;
		this->_internal = PixelDataInternalFormat::RGB16F;
	}
};

} // images
} // oglplus

#endif // include guard
