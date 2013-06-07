/*
 *  .file oglplus/enums/hint_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/hint_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/hint.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_hint_target(void)
{
	boost::python::enum_<oglplus::HintTarget>("HintTarget")
#if defined GL_LINE_SMOOTH_HINT
# if defined LineSmooth
#  pragma push_macro("LineSmooth")
#  undef LineSmooth
	.value("LineSmooth", oglplus::HintTarget::LineSmooth)
#  pragma pop_macro("LineSmooth")
# else
	.value("LineSmooth", oglplus::HintTarget::LineSmooth)
# endif
#endif
#if defined GL_POLYGON_SMOOTH_HINT
# if defined PolygonSmooth
#  pragma push_macro("PolygonSmooth")
#  undef PolygonSmooth
	.value("PolygonSmooth", oglplus::HintTarget::PolygonSmooth)
#  pragma pop_macro("PolygonSmooth")
# else
	.value("PolygonSmooth", oglplus::HintTarget::PolygonSmooth)
# endif
#endif
#if defined GL_TEXTURE_COMPRESSION_HINT
# if defined TextureCompression
#  pragma push_macro("TextureCompression")
#  undef TextureCompression
	.value("TextureCompression", oglplus::HintTarget::TextureCompression)
#  pragma pop_macro("TextureCompression")
# else
	.value("TextureCompression", oglplus::HintTarget::TextureCompression)
# endif
#endif
#if defined GL_FRAGMENT_SHADER_DERIVATIVE_HINT
# if defined FragmentShaderDerivative
#  pragma push_macro("FragmentShaderDerivative")
#  undef FragmentShaderDerivative
	.value("FragmentShaderDerivative", oglplus::HintTarget::FragmentShaderDerivative)
#  pragma pop_macro("FragmentShaderDerivative")
# else
	.value("FragmentShaderDerivative", oglplus::HintTarget::FragmentShaderDerivative)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::HintTarget) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::HintTarget
		>
	>("aux_CastIterRange_HintTarget");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::HintTarget
	> (*PEnumValueRange)(oglplus::HintTarget) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
