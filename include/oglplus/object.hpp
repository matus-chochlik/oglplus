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
#include <oglplus/glfunc.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/object/tags.hpp>
#include <oglplus/object/name.hpp>
#include <oglplus/object/desc.hpp>
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

/** @page oglplus_object OGLplus object
 *
 *  @OGLplus defines classes like @ref oglplus::Buffer "Buffer",
 *  @ref oglplus::Program "Program", @ref oglplus::Texture "Texture",
 *  @ref oglplus::Query "Query" and many others, wrapping around OpenGL
 *  "objects". Such classes have, besides the object-type-specific functions,
 *  several common constuctors and members as shown by the following pseudo
 *  code. (The @c Object class does not actually exist, the following declaration
 *  is just a sort of template).
 *
 *  @code
 *  class Object
 *  {
 *  public:
 *    // Objects are default constructible
 *    Object(void);
 *
 *    // Objects are not copy constructible
 *    Object(const Object&) = delete;
 *
 *    // Objects are move constructible
 *    Object(Object&&);
 *
 *    // If object has a Property::Type typedef, construct with type specification
 *    Object(Object::Property::Type type);
 *
 *    // Construction with a textual description
 *    Object(String description);
 *
 *    // Construct with type specification and textual description
 *    Object(Object::Property::Type type, String description);
 *
 *    // Returns the textual description (if any) of the Object
 *    friend const String Description(Object);
 *
 *  };
 *  @endcode
 */

/// TODO: doc
/*
 *  @ingroup oglplus_objects
 */
template <class OpsTag, class ObjTag>
class Object<ObjectOps<OpsTag, ObjTag>>
 : public ObjectOps<OpsTag, ObjTag>
 , public GenDelOps<ObjTag>
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

	void _init(void)
	{
		GenDelOps<ObjTag>::Gen(1, &this->_name);
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
			GenDelOps<ObjTag>::Delete(1, &this->_name);
		}
	}
public:
	Object(void)
	{
		_init();
	}

	Object(ObjectDesc&& description)
	{
		_init();
		_describe(std::move(description));
	}

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

	Object& operator = (Object&& temp)
	{
		_cleanup();
		_move_in(std::move(temp));
		return *this;
	}

/* TODO
	static oglplus::ObjectType ObjectType(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return _get_object_type<ObjectOps>(nullptr);
	}
*/
	const String& Description(void) const
	{
		aux::ObjectDescRegistry::_get_desc(
			ObjTag::value,
			this->_name
		);
	}
};

template <class OpsTag, class ObjTag>
class ObjectZero<CommonOps<OpsTag, ObjTag>>
 : public CommonOps<OpsTag, ObjTag>
{
public:
	ObjectZero(void) { }
};

} // namespace oglplus

#endif // include guard
