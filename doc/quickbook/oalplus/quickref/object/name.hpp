/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oalplus_object_name

using __oglplus_ObjectName;

template <typename ObjTag>
const ALuint GetName(ObjectName<ObjTag> named) noexcept;

//]
//[oalplus_object_name_type_aliases

using BufferName = __ObjectName<__tag_Buffer>;
using SourceName = ObjectName<__tag_Source>;

//]
