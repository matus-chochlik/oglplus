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

#include <oglplus/object/seq_tpl.hpp>
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
	typedef typename ObjTag::NameType NameT;

	std::array<NameT, N> _names;

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	void _init(std::size_t) { }

	template <typename ... I>
	void _init(std::size_t i, NameT name, I ... names)
	{
		_names[i] = name;
		_init(i+1, names...);
	}
#endif
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
	{
		_init(0, GetGLName(names)...);
	}
#else
	StaticGroup(
		ObjectName<ObjTag> n0,
		ObjectName<ObjTag> n1
	)
	{
		_names[0] = GetGLName(n0);
		_names[1] = GetGLName(n1);
	}

	StaticGroup(
		ObjectName<ObjTag> n0,
		ObjectName<ObjTag> n1,
		ObjectName<ObjTag> n2
	)
	{
		_names[0] = GetGLName(n0);
		_names[1] = GetGLName(n1);
		_names[2] = GetGLName(n2);
	}
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
#else
template <typename ObjTag>
inline StaticGroup<ObjectName<ObjTag>, 2>
MakeGroup(ObjectName<ObjTag> n0, ObjectName<ObjTag> n1)
{
	return StaticGroup<ObjectName<ObjTag>, 2>(n0, n1);
}

template <typename ObjTag>
inline StaticGroup<ObjectName<ObjTag>, 3>
MakeGroup(ObjectName<ObjTag> n0, ObjectName<ObjTag> n1, ObjectName<ObjTag> n2)
{
	return StaticGroup<ObjectName<ObjTag>, 3>(n0, n1, n2);
}
#endif

} // namespace oglplus

#endif // include guard
