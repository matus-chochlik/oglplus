/**
 *  @file oglplus/error/object.ipp
 *  @brief Implementation of ObjectError
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/lib/incl_end.ipp>
#include <oglplus/object/desc.hpp>

namespace oglplus {

OGLPLUS_LIB_FUNC
ObjectError::ObjectError(const char* message)
  : Error(message)
#if !OGLPLUS_ERROR_NO_OBJECT_TYPE
  , _obj_type(GL_NONE)
#endif
#if !OGLPLUS_ERROR_NO_BIND_TARGET
  , _bind_tgt(0)
#endif
#if !OGLPLUS_ERROR_NO_TARGET_NAME
  , _tgt_name(nullptr)
#endif
  , _obj_typeid(0)
  , _obj_name(0) {
}

OGLPLUS_LIB_FUNC
GLenum ObjectError::ObjectType() const {
#if !OGLPLUS_ERROR_NO_OBJECT_TYPE
    return _obj_type;
#else
    return GLenum(0);
#endif
}

OGLPLUS_LIB_FUNC
const char* ObjectError::ObjectTypeName() const {
#if !OGLPLUS_ERROR_NO_CLASS_NAME
    return EnumValueName(oglplus::ObjectType(this->ObjectType())).c_str();
#else
    return nullptr;
#endif
}

OGLPLUS_LIB_FUNC
GLenum ObjectError::BindTarget() const {
#if !OGLPLUS_ERROR_NO_TARGET_NAME
    return _bind_tgt;
#else
    return GLenum(0);
#endif
}

OGLPLUS_LIB_FUNC
const char* ObjectError::TargetName() const {
#if !OGLPLUS_ERROR_NO_TARGET_NAME
    return _tgt_name;
#else
    return nullptr;
#endif
}

OGLPLUS_LIB_FUNC
GLint ObjectError::ObjectName() const {
    return GLint(_obj_name);
}

OGLPLUS_LIB_FUNC
const String& ObjectError::ObjectDesc() const {
    return aux::ObjectDescRegistry::_get_desc(_obj_typeid, _obj_name);
}

OGLPLUS_LIB_FUNC
ObjectPairError::ObjectPairError(const char* message)
  : ObjectError(message)
#if !OGLPLUS_ERROR_NO_OBJECT_TYPE
  , _sub_type(0)
#endif
  , _sub_typeid(0)
  , _sub_name(0) {
}

OGLPLUS_LIB_FUNC
GLenum ObjectPairError::SubjectType() const {
#if !OGLPLUS_ERROR_NO_OBJECT_TYPE
    return _sub_type;
#else
    return GLenum(0);
#endif
}

OGLPLUS_LIB_FUNC
const char* ObjectPairError::SubjectTypeName() const {
#if !OGLPLUS_ERROR_NO_CLASS_NAME
    return EnumValueName(oglplus::ObjectType(this->SubjectType())).c_str();
#else
    return nullptr;
#endif
}

OGLPLUS_LIB_FUNC
GLint ObjectPairError::SubjectName() const {
    return GLint(_sub_name);
}

OGLPLUS_LIB_FUNC
const String& ObjectPairError::SubjectDesc() const {
    return aux::ObjectDescRegistry::_get_desc(_sub_typeid, _sub_name);
}

} // namespace oglplus
