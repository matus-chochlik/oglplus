/**
 *  @file oalplus/object/reference.hpp
 *  @brief Reference to an existing Object
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_OBJECT_REFERENCE_1405011014_HPP
#define OALPLUS_OBJECT_REFERENCE_1405011014_HPP

#include <oalplus/fwd.hpp>
#include <oalplus/object/name.hpp>

namespace oalplus {

/// Allows to make managed copies of instances of Object
/** For obvious reasons @ref oalplus_object "objects" are not copyable,
 *  only movable. There may however be situations where a temporary reference
 *  to the "master" object (with the knowledge that the original will
 *  be kept alive during the whole lifetime of the copy) is needed.
 *  The Reference template class allows to do such temporary references
 *  which have the same members and friend functions as the original
 *  object, and can be use in the same way, provided that the original
 *  instance is not destroyed before the managed copy.
 *
 *  Instances of Reference are may be for example created when accessing
 *  or iterating through the elements of an @ref oalplus::Sequence "Sequence".
 *
 *  @ingroup modifier_classes
 */
template <typename OpsTag, typename ObjTag>
class Reference<ObjectOps<OpsTag, ObjTag>>
 : public ObjectOps<OpsTag, ObjTag>
{
public:
	Reference(ObjectName<ObjTag> object)
	{
		this->_copy(object);
	}
};

template <typename OpsTag, typename ObjTag>
struct Reference<Object<ObjectOps<OpsTag, ObjTag>>>
 : public Reference<ObjectOps<OpsTag, ObjTag>>
{
public:
	Reference(ObjectName<ObjTag> object)
	 : Reference<ObjectOps<OpsTag, ObjTag>>(object)
	{ }
};

} // namespace oalplus

#endif // include guard
