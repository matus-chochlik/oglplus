/**
 *  @file oglplus/error/object.ipp
 *  @brief Implementation of ObjectError
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
ObjectError::ObjectError(const char* message)
 : Error(message)
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_TYPE
 , _obj_type(0)
#endif
#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
 , _cls_name(nullptr)
#endif
#if !OGLPLUS_ERROR_INFO_NO_BIND_TARGET
 , _bind_tgt(0)
#endif
#if !OGLPLUS_ERROR_INFO_NO_TARGET_NAME
 , _tgt_name(nullptr)
#endif
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
 , _obj_typeid(0)
 , _obj_name(0)
#endif
{ }


OGLPLUS_LIB_FUNC
GLenum ObjectError::ObjectType(void) const
{
#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
	return _obj_type;
#else
	return GLenum(0);
#endif
}

OGLPLUS_LIB_FUNC
const char* ObjectError::ClassName(void) const
{
#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
	return _cls_name;
#else
	return nullptr;
#endif
}

OGLPLUS_LIB_FUNC
GLenum ObjectError::BindTarget(void) const
{
#if !OGLPLUS_ERROR_INFO_NO_TARGET_NAME
	return _bind_tgt;
#else
	return GLenum(0);
#endif
}

OGLPLUS_LIB_FUNC
const char* ObjectError::TargetName(void) const
{
#if !OGLPLUS_ERROR_INFO_NO_TARGET_NAME
	return _tgt_name;
#else
	return nullptr;
#endif
}

OGLPLUS_LIB_FUNC
GLuint ObjectError::ObjectName(void) const
{
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
	return _obj_name;
#else
	return 0;
#endif
}

} // namespace oglplus

