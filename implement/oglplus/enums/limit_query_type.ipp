//  File implement/oglplus/enums/limit_query_type.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/limit_query.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2019 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

namespace enums {
#if defined GL_MAX_FRAGMENT_INTERPOLATION_OFFSET
template <>
struct EnumAssocType<LimitQuery, LimitQuery::MaxFragmentInterpolationOffset> {
    using Type = float;
};
#endif
#if defined GL_MAX_PROGRAM_TEXEL_OFFSET
template <>
struct EnumAssocType<LimitQuery, LimitQuery::MaxProgramTexelOffset> {
    using Type = float;
};
#endif
#if defined GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET
template <>
struct EnumAssocType<LimitQuery, LimitQuery::MaxProgramTextureGatherOffset> {
    using Type = float;
};
#endif
#if defined GL_MAX_SERVER_WAIT_TIMEOUT
template <>
struct EnumAssocType<LimitQuery, LimitQuery::MaxServerWaitTimeout> {
    using Type = int64_t;
};
#endif
#if defined GL_MAX_TEXTURE_LOD_BIAS
template <>
struct EnumAssocType<LimitQuery, LimitQuery::MaxTextureLodBias> {
    using Type = float;
};
#endif
#if defined GL_MIN_FRAGMENT_INTERPOLATION_OFFSET
template <>
struct EnumAssocType<LimitQuery, LimitQuery::MinFragmentInterpolationOffset> {
    using Type = float;
};
#endif
#if defined GL_MIN_PROGRAM_TEXEL_OFFSET
template <>
struct EnumAssocType<LimitQuery, LimitQuery::MinProgramTexelOffset> {
    using Type = float;
};
#endif
#if defined GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET
template <>
struct EnumAssocType<LimitQuery, LimitQuery::MinProgramTextureGatherOffset> {
    using Type = float;
};
#endif
} // namespace enums
