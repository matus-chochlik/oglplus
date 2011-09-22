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

/// A filter creating a normal-map/height-map from a height map image
/**
 *  @ingroup image_load_gen
 */
class NormalMap
 : public FilteredImage<GLfloat, 4>
{
private:
	typedef GLfloat T;

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
			return Vector<number, 4>(
				Normalized(
					Cross(vpx, vpy) +
					Cross(vpy, vnx) +
					Cross(vnx, vny) +
					Cross(vny, vpx)
				),
				(1.0 - sc/ione)
			) * one;
		}
	};
public:
	typedef FilteredImage<T, 4> Filter;

	/// Created a normal-map from the @p input height-map image
	/**
	 *  @param input the height-map image to be filtered
	 *  @param extractor the height map color component extractor (by
	 *    default the RED component of the image is used as the height-map
	 *    value used in normal-map calculation).
	 */
	template <typename IT,  typename Extractor = typename Filter::FromRed>
	NormalMap(const Image<IT>& input, Extractor extractor = Extractor())
	 : Filter(input, _filter(), extractor)
	{
		this->_format = PixelDataFormat::RGBA;
		this->_internal = PixelDataInternalFormat::RGBA16F;
	}
};

} // images
} // oglplus

#endif // include guard
