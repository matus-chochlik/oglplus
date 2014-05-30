/**
 *  @file oglplus/object/type.hpp
 *  @brief ObjectType enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_TYPE_1405022040_HPP
#define OGLPLUS_OBJECT_TYPE_1405022040_HPP

#include <oglplus/enumerations.hpp>
#include <oglplus/object/tags.hpp>

namespace oglplus {

/// Enumeration of object types
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(ObjectType, GLenum)
#include <oglplus/enums/object_type.ipp>
OGLPLUS_ENUM_CLASS_END(ObjectType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/object_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/object_type_range.ipp>
#endif

template <typename ObjTag>
struct ObjTypeOps
{
	static oglplus::ObjectType ObjectType(void)
	{
		return oglplus::ObjectType(GL_NONE);
	}
};

#define OGLPLUS_SPEC_OBJ_TYPE_OPS(TYPE) \
template <> \
struct ObjTypeOps<tag::TYPE> \
{ \
	static oglplus::ObjectType ObjectType(void) \
	{ \
		return oglplus::ObjectType::TYPE; \
	} \
};

OGLPLUS_SPEC_OBJ_TYPE_OPS(Buffer)
OGLPLUS_SPEC_OBJ_TYPE_OPS(Framebuffer)
OGLPLUS_SPEC_OBJ_TYPE_OPS(ProgramPipeline)
OGLPLUS_SPEC_OBJ_TYPE_OPS(Program)
OGLPLUS_SPEC_OBJ_TYPE_OPS(Query)
OGLPLUS_SPEC_OBJ_TYPE_OPS(Renderbuffer)
OGLPLUS_SPEC_OBJ_TYPE_OPS(Sampler)
OGLPLUS_SPEC_OBJ_TYPE_OPS(Shader)
OGLPLUS_SPEC_OBJ_TYPE_OPS(Texture)
OGLPLUS_SPEC_OBJ_TYPE_OPS(TransformFeedback)
OGLPLUS_SPEC_OBJ_TYPE_OPS(VertexArray)

#undef OGLPLUS_SPEC_OBJ_TYPE_OPS

} // namespace oglplus

#endif // include guard
