/*
 *  .file oglplus/enums/texture_min_filter.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_min_filter.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/texture.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_texture_min_filter(void)
{
	boost::python::enum_<oglplus::TextureMinFilter>("TextureMinFilter")
#if defined GL_NEAREST
# if defined Nearest
#  pragma push_macro("Nearest")
#  undef Nearest
	.value("Nearest", oglplus::TextureMinFilter::Nearest)
#  pragma pop_macro("Nearest")
# else
	.value("Nearest", oglplus::TextureMinFilter::Nearest)
# endif
#endif
#if defined GL_LINEAR
# if defined Linear
#  pragma push_macro("Linear")
#  undef Linear
	.value("Linear", oglplus::TextureMinFilter::Linear)
#  pragma pop_macro("Linear")
# else
	.value("Linear", oglplus::TextureMinFilter::Linear)
# endif
#endif
#if defined GL_NEAREST_MIPMAP_NEAREST
# if defined NearestMipmapNearest
#  pragma push_macro("NearestMipmapNearest")
#  undef NearestMipmapNearest
	.value("NearestMipmapNearest", oglplus::TextureMinFilter::NearestMipmapNearest)
#  pragma pop_macro("NearestMipmapNearest")
# else
	.value("NearestMipmapNearest", oglplus::TextureMinFilter::NearestMipmapNearest)
# endif
#endif
#if defined GL_NEAREST_MIPMAP_LINEAR
# if defined NearestMipmapLinear
#  pragma push_macro("NearestMipmapLinear")
#  undef NearestMipmapLinear
	.value("NearestMipmapLinear", oglplus::TextureMinFilter::NearestMipmapLinear)
#  pragma pop_macro("NearestMipmapLinear")
# else
	.value("NearestMipmapLinear", oglplus::TextureMinFilter::NearestMipmapLinear)
# endif
#endif
#if defined GL_LINEAR_MIPMAP_NEAREST
# if defined LinearMipmapNearest
#  pragma push_macro("LinearMipmapNearest")
#  undef LinearMipmapNearest
	.value("LinearMipmapNearest", oglplus::TextureMinFilter::LinearMipmapNearest)
#  pragma pop_macro("LinearMipmapNearest")
# else
	.value("LinearMipmapNearest", oglplus::TextureMinFilter::LinearMipmapNearest)
# endif
#endif
#if defined GL_LINEAR_MIPMAP_LINEAR
# if defined LinearMipmapLinear
#  pragma push_macro("LinearMipmapLinear")
#  undef LinearMipmapLinear
	.value("LinearMipmapLinear", oglplus::TextureMinFilter::LinearMipmapLinear)
#  pragma pop_macro("LinearMipmapLinear")
# else
	.value("LinearMipmapLinear", oglplus::TextureMinFilter::LinearMipmapLinear)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TextureMinFilter) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TextureMinFilter
		>
	>("aux_CastIterRange_TextureMinFilter");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TextureMinFilter
	> (*PEnumValueRange)(oglplus::TextureMinFilter) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
