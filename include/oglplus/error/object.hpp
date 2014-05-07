/**
 *  @file oglplus/error/object.hpp
 *  @brief Declaration of OGLplus object-related error
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ERROR_OBJECT_1107121317_HPP
#define OGLPLUS_ERROR_OBJECT_1107121317_HPP

#include <oglplus/error/basic.hpp>
#include <oglplus/object/tags.hpp>
#include <oglplus/object/name.hpp>

namespace oglplus {

/// Exception class for GL object-related errors
class ObjectError
 : public Error
{
private:
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_TYPE
	GLenum _obj_type;
#endif
#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
	const char* _cls_name;
#endif
#if !OGLPLUS_ERROR_INFO_NO_BIND_TARGET
	GLenum _bind_tgt;
#endif
#if !OGLPLUS_ERROR_INFO_NO_TARGET_NAME
	const char* _tgt_name;
#endif
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
	int _obj_typeid;
	GLuint _obj_name;
#endif
public:
	ObjectError(const char* message);

	template <typename ObjectType_>
	ObjectError& ObjectType(ObjectType_ obj_type)
	{
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_TYPE
		_obj_type = GLenum(obj_type);
#endif
#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
		_cls_name = EnumValueName(obj_type).c_str();
#endif
		(void)obj_type;
		return *this;
	}

	/// Returns the object type
	GLenum ObjectType(void) const;

	/// Returns the class name
	const char* ClassName(void) const;

	template <typename BindTarget_>
	ObjectError& BindTarget(BindTarget_ bind_tgt)
	{
#if !OGLPLUS_ERROR_INFO_NO_BIND_TARGET
		_bind_tgt = GLenum(bind_tgt);
#endif
#if !OGLPLUS_ERROR_INFO_NO_TARGET_NAME
		_tgt_name = EnumValueName(bind_tgt).c_str();
#endif
		(void)bind_tgt;
		return *this;
	}

	/// Returns the bind target
	GLenum BindTarget(void) const;

	/// Returns the bind target name
	const char* TargetName(void) const;

	template <typename ObjTag>
	ObjectError& Object(oglplus::ObjectName<ObjTag> object)
	{
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
		_obj_typeid = ObjTag::value;
		_obj_name = GetGLName(object);
#endif
		(void)object;
		return *this;
	}

	/// Object GL name
	GLuint ObjectName(void) const;
};

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/error/object.ipp>
#endif

#endif // include guard
