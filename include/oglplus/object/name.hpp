/**
 *  @file oglplus/object/name.hpp
 *  @brief Base class for OpenGL "named" objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_NAME_1107121519_HPP
#define OGLPLUS_OBJECT_NAME_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/config.hpp>

#include <type_traits>
#include <utility>
#include <cassert>

namespace oglplus {

/// A common base class for "named" OpenGL objects like textures, buffers, etc.
/** This is a common base class for all OpenGL object wrappers which are
 *  identified by a (GLuint typed) name, i.e. object like Textures, Buffer, VAOs,
 *  Queries, etc. but also Shaders, Programs, and so on.
 *
 *  @note Do not use this class directly, it is used by the OpenGL object wrappers
 *  for basic initialization, error checking and access restriction.
 */
template <typename ObjTag>
class ObjectName
{
protected:
	friend GLuint GetGLName<ObjTag>(const ObjectName&);
	GLuint _name;

	void _adopt(ObjectName&& temp)
	{
		_name = temp._name;
		temp._name = 0;
	}
public:
	ObjectName(void)
	OGLPLUS_NOEXCEPT(true)
	 : _name(GLuint(0))
	{ }

	ObjectName(GLuint name)
	OGLPLUS_NOEXCEPT(true)
	 : _name(name)
	{ }

	ObjectName(ObjectName&& temp)
	OGLPLUS_NOEXCEPT(true)
	 : _name(temp._name)
	{
		temp._name = 0;
	}

	ObjectName& operator = (ObjectName&& temp)
	{
		_adopt(std::move(temp));
		return *this;
	}
};

/// Returns the GLuint OpenGL name assigned to @p named object
template <typename ObjTag>
inline GLuint GetGLName(const ObjectName<ObjTag>& named)
{
	return named._name;
}

} // namespace oglplus

#endif // include guard
