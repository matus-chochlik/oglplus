/**
 *  @file oglplus/texgen/data_type.hpp
 *  @brief Texgen interfaces
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_DATA_TYPE_HPP
#define OGLPLUS_TEXGEN_DATA_TYPE_HPP

#include <oglplus/texgen/interface.hpp>

namespace oglplus {
namespace texgen {

const char* DataTypeName(SlotDataType);
unsigned DataTypeDims(SlotDataType);

SlotDataType MakeDataType(SlotDataType scalar, unsigned dims);
SlotDataType ScalarDataType(SlotDataType);
SlotDataType CommonDataType(SlotDataType, SlotDataType);

bool DataTypeConvertible(SlotDataType from, SlotDataType to);

std::ostream& ConversionPrefix(std::ostream&, SlotDataType, SlotDataType);
std::ostream& ConversionSuffix(std::ostream&, SlotDataType, SlotDataType);

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/data_type.ipp>
//#endif

#endif // include guard
