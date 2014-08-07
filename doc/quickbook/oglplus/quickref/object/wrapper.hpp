/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_object_wrapper
namespace oglplus {

template <typename __OpsTag, typename __ObjTag>
class Object<ObjectOps<__OpsTag, __ObjTag>>
{
};

} // namespace oglplus
//]

