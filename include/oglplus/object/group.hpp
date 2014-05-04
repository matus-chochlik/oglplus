/**
 *  @file oglplus/object/group.hpp
 *  @brief A group of object references
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_GROUP_1405011014_HPP
#define OGLPLUS_OBJECT_GROUP_1405011014_HPP

#include <oglplus/object/sequence.hpp>
#include <array>
#include <vector>
#include <cassert>

namespace oglplus {

template <typename ObjName, std::size_t N>
class StaticGroup;

template <typename ObjTag, std::size_t N>
class StaticGroup<ObjectName<ObjTag>, N>
{
private:
	std::array<GLuint, N> _names;
public:
	StaticGroup(const ObjectName<ObjTag> (&names)[N])
	{
		for(std::size_t i=0; i!=N; ++i)
		{
			_names[i] = GetGLName(names[i]);
		}
	}

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename ... Tag>
	StaticGroup(ObjectName<Tag>... names)
	 : _names({GetGLName<ObjTag>(names)...})
	{ }
#endif

	Sequence<ObjectName<ObjTag>> seq(void) const
	{
		return Sequence<ObjectName<ObjTag>>(
			_names.data(),
			_names.size()
		);
	}

	operator Sequence<ObjectName<ObjTag>> (void) const
	{
		return seq();
	}
};

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
template <typename ObjTag, typename ... ObjTags>
inline StaticGroup<ObjectName<ObjTag>, 1+sizeof...(ObjTags)>
MakeGroup(ObjectName<ObjTag> name, ObjectName<ObjTags>... names)
{
	return StaticGroup<ObjectName<ObjTag>, 1+sizeof...(ObjTags)>(
		name,
		names...
	);
}
#endif

} // namespace oglplus

#endif // include guard
