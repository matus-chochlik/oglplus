//  File doc/quickbook/oalplus/quickref/enums/data_format.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oalplus/data_format.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_data_format
namespace oalplus {

enum class DataFormat : ALenum
{
	Mono8    = AL_FORMAT_MONO8,
	Mono16   = AL_FORMAT_MONO16,
	Stereo8  = AL_FORMAT_STEREO8,
	Stereo16 = AL_FORMAT_STEREO16
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<DataFormat> __EnumValueName<DataFormat>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(DataFormat);
#endif

} // namespace oalplus
//]
