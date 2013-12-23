/**
 *  @file oglplus/images/normal_map.hpp
 *  @brief Filter creating a normal+height map out of a height map
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
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
	struct _filter
	{
		template <typename Extractor, typename Sampler>
		Vector<GLfloat, 4> operator()(
			const Extractor& extractor,
			const Sampler& sampler,
			GLfloat one
		) const
		{
			typedef GLdouble number;
			number s = 0.05;

			number sc  = extractor(sampler( 0, 0, 0));
			number spx = extractor(sampler(+1, 0, 0));
			number spy = extractor(sampler( 0,+1, 0));
			number snx = extractor(sampler(-1, 0, 0));
			number sny = extractor(sampler( 0,-1, 0));
			Vector<number, 3> vpx(+s, 0, (spx-sc));
			Vector<number, 3> vpy(0, +s, (spy-sc));
			Vector<number, 3> vnx(-s, 0, (snx-sc));
			Vector<number, 3> vny(0, -s, (sny-sc));
			return Vector<number, 4>(
				Normalized(
					Cross(vpx, vpy) +
					Cross(vpy, vnx) +
					Cross(vnx, vny) +
					Cross(vny, vpx)
				),
				sc
			) * one;
		}
	};
public:
	typedef FilteredImage<GLfloat, 4> Filtered;

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Creates a normal-map from the @p input height-map image
	/**
	 *  @param input the height-map image to be filtered
	 *  @param extractor the height map color component extractor (by
	 *    default the RED component of the image is used as the height-map
	 *    value used in normal-map calculation).
	 */
	template <typename Extractor = typename Filtered::FromRed>
	NormalMap(const Image& input, Extractor extractor = Extractor());
#endif

#if !OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
	template <typename Extractor = typename Filtered::FromRed>
	NormalMap(const Image& input, Extractor extractor = Extractor())
#else
	template <typename Extractor>
	NormalMap(const Image& input, Extractor extractor)
#endif
	 : Filtered(
		input,
		_filter(),
		Filtered::DefaultSampler(),
		extractor
	)
	{
		this->_format = PixelDataFormat::RGBA;
		this->_internal = PixelDataInternalFormat::RGBA16F;
	}
};

} // images
} // oglplus

#endif // include guard
