/**
 *  .file oglplus/auxiliary/glsl_to_cpp.hpp
 *  .brief Mapping of GLSL types to CPP types
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2011-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef __OGLPLUS_AUX_GLSL_TO_CPP_1102101236_HPP
#define __OGLPLUS_AUX_GLSL_TO_CPP_1102101236_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/data_type.hpp>

namespace oglplus {
namespace aux {

template <
	typename oglplus::enums::EnumValueType<
		oglplus::enums::SLDataType
	>::Type
> struct GLSL2Cpp;

#include <oglplus/auxiliary/glsl_to_cpp.ipp>

} // namespace aux

template <
	typename oglplus::enums::EnumValueType<
		oglplus::enums::SLDataType
	>::Type
> struct SLtoCpp;

} // namespace oglplus

#endif
