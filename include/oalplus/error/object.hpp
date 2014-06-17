/**
 *  @file oalplus/error/object.hpp
 *  @brief Declaration of OALplus object-related error
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_ERROR_OBJECT_1107121317_HPP
#define OALPLUS_ERROR_OBJECT_1107121317_HPP

#include <oalplus/error/basic.hpp>
#include <oalplus/object/tags.hpp>
#include <oalplus/object/name.hpp>
#include <oalplus/object/desc.hpp>

namespace oalplus {

/// Exception class for AL object-related errors
class ObjectError
 : public Error
{
private:
#if !OALPLUS_ERROR_NO_OBJECT_TYPE
	ALenum _obj_type;
#endif
	int _obj_typeid;
	ALuint _obj_name;
public:
	ObjectError(const char* message);

	/// Returns the object type
	ALenum ObjectType(void) const;

	template <typename ObjTag>
	ObjectError& Object(oalplus::ObjectName<ObjTag> object)
	{
		// TODO object type
		_obj_typeid = ObjTag::value;
		_obj_name = GetALName(object);
		return *this;
	}

	/// Object AL name
	ALint ObjectName(void) const;

	/// Object textual description
	const String& ObjectDesc(void) const;
};

} // namespace oalplus

#if !OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)
#include <oalplus/error/object.ipp>
#endif

#endif // include guard
