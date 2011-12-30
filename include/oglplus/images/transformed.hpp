/**
 *  @file oglplus/images/transformed.hpp
 *  @brief Filter transforming image RGB components by a 4x4 matrix
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_TRANSFORMED_1107121519_HPP
#define OGLPLUS_IMAGES_TRANSFORMED_1107121519_HPP

#include <oglplus/images/filtered.hpp>
#include <oglplus/matrix.hpp>

namespace oglplus {
namespace images {

/// A filter transforming image RGB components by a 4x4 matrix
/**
 *  @ingroup image_load_gen
 */
template <typename T>
class Transformed
 : public FilteredImage<T, 3>
{
private:
	struct _filter
	{
		Matrix4f _matrix;

		_filter(const Matrix4f& matrix)
		 : _matrix(matrix)
		{ }

		template <typename Extractor, typename Sampler, typename IT>
		Vector<T, 3> operator()(
			const Extractor& extractor,
			const Sampler& sampler,
			T one,
			IT ione
		) const
		{
			const Vector<T, 4> c(
				extractor(sampler.get(0,0)),
				1.0
			);
			return (_matrix*c).xyz();
		}
	};
public:
	typedef FilteredImage<T, 3> Filter;

	/// Created a normal-map from the @p input height-map image
	/**
	 */
	template <typename IT>
	Transformed(const Image<IT>& input, const Matrix4f& matrix)
	 : Filter(input, _filter(matrix), typename Filter::FromRGB())
	{
		this->_format = PixelDataFormat::RGB;
		this->_internal = PixelDataInternalFormat::RGB;
	}
};

} // images
} // oglplus

#endif // include guard
