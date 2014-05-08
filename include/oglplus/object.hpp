/**
 *  @file oglplus/object.hpp
 *  @brief Generic OpenGL object wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_1107121519_HPP
#define OGLPLUS_OBJECT_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/object/tags.hpp>
#include <oglplus/object/name.hpp>
#include <oglplus/object/desc.hpp>
#include <oglplus/object/reference.hpp>
#include <type_traits>
#include <cassert>

namespace oglplus {

/** @defgroup oglplus_objects OGLplus objects
 *
 *  An @ref oglplus_object is a class wrapping around OpenGL objects
 *  like shaders, programs, textures, etc. It is using the RAII technique
 *  to provide automated resource management for these OpenGL resources.
 *  They also wrap operations related to these objects and provide
 *  additional type safety and more robust error handling. Look
 *  @ref oglplus_object "here" for more details.
 */

template <typename ObjTag>
struct ObjectSubtype : Nothing
{ };

/// Implements operations applicable to any object and any operation kind
template <class ObjTag>
class ObjCommonOps
 : public ObjectName<ObjTag>
{
protected:
	ObjCommonOps(void) { }
};

/// Implements operations applicable to any object including object 0 (zero)
template <class OpsTag, class ObjTag>
class ObjZeroOps
 : public ObjCommonOps<ObjTag>
{
protected:
	ObjZeroOps(void) { }
};

/// Wrapper for GL objects with name 0 (zero)
/** Depending on the object type (specified by ObjTag) the semantics
 *  is either "no-object" (for example NoBuffer, NoRenderbuffer, etc.)
 *  or "default-object" (for example DefaultTexture or DefaultFramebuffer).
 */
template <class OpsTag, class ObjTag>
class ObjectZero<ObjZeroOps<OpsTag, ObjTag>>
 : public ObjZeroOps<OpsTag, ObjTag>
{
public:
	/// ObjectZero is default constructible
	ObjectZero(void) { }
};

/// Implements operations applicable to named (non-zero) objects
template <class OpsTag, class ObjTag>
class ObjectOps
 : public ObjZeroOps<OpsTag, ObjTag>
{
protected:
	ObjectOps(void) { }
};

/// TODO: doc
/*
 *  @ingroup oglplus_objects
 */
template <class OpsTag, class ObjTag>
class Object<ObjectOps<OpsTag, ObjTag>>
 : public ObjectOps<OpsTag, ObjTag>
 , public ObjGenDelOps<ObjTag>
{
private:
	// Object is not copy-constructible
	Object(const Object&);

	void _describe(ObjectDesc&& description)
	{
		aux::ObjectDescRegistry::_register_desc(
			ObjTag::value,
			this->_name,
			std::move(description)
		);
	}

	void _undescribe(void)
	{
		aux::ObjectDescRegistry::_unregister_desc(
			ObjTag::value,
			this->_name
		);
	}

	void _init(Nothing)
	{
		ObjGenDelOps<ObjTag>::Gen(1, &this->_name);
	}

	template <typename ObjectSubtype>
	void _init(ObjectSubtype type)
	{
		this->_type = GLenum(type);
		_init(Nothing());
	}

	void _move_in(Object&& temp)
	OGLPLUS_NOEXCEPT(true)
	{
		this->_name = temp._name;
		temp._name = 0;
	}

	void _cleanup(void)
	{
		_undescribe();
		if(this->_name)
		{
			ObjGenDelOps<ObjTag>::Delete(1, &this->_name);
		}
	}
protected:
	Object(GLuint name)
	{
		this->_name = name;
	}

	Object(GLuint name, ObjectDesc&& description)
	{
		this->_name = name;
		_describe(std::move(description));
	}

	Object(typename ObjectSubtype<ObjTag>::Type type)
	{
		_init(type);
	}
public:
	/// Most object types are default-constructible
	Object(void)
	{
		_init(Nothing());
	}

	/// A textual description can be attached to objects
	Object(ObjectDesc&& description)
	{
		_init(Nothing());
		_describe(std::move(description));
	}

	/// A textual description can be attached to objects
	Object(typename ObjectSubtype<ObjTag>::Type type, ObjectDesc&& description)
	{
		_init(type);
		_describe(std::move(description));
	}

	/// Objects are movable
	Object(Object&& temp)
	OGLPLUS_NOEXCEPT(true)
	{
		_move_in(std::move(temp));
	}

	~Object(void)
	OGLPLUS_NOEXCEPT(true)
	{
		try { _cleanup(); }
		catch(...) { }
	}

	/// Objects are move-assignable
	Object& operator = (Object&& temp)
	{
		_cleanup();
		_move_in(std::move(temp));
		return *this;
	}

/* TODO
	static oglplus::ObjectSubtype ObjectSubtype(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return _get_object_type<ObjectOps>(nullptr);
	}
*/

	/// Returns the textual description of this object
	const String& Description(void) const
	{
		aux::ObjectDescRegistry::_get_desc(
			ObjTag::value,
			this->_name
		);
	}
};

} // namespace oglplus

#endif // include guard
