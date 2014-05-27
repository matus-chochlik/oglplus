/**
 *  @file oalplus/object/wrapper.hpp
 *  @brief Generic OpenAL object wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_OBJECT_WRAPPER_1107121519_HPP
#define OALPLUS_OBJECT_WRAPPER_1107121519_HPP

#include <oalplus/fwd.hpp>
#include <oalplus/object/tags.hpp>
#include <oalplus/object/name.hpp>
#include <oalplus/object/desc.hpp>
#include <type_traits>
#include <cassert>

namespace oalplus {

/** @defgroup oalplus_objects OALplus objects
 *
 *  An @ref oalplus_object is a class wrapping around OpenAL objects
 *  like shaders, programs, textures, etc. It is using the RAII technique
 *  to provide automated resource management for these OpenAL resources.
 *  They also wrap operations related to these objects and provide
 *  additional type safety and more robust error handling. Look
 *  @ref oalplus_object "here" for more details.
 */

/// TODO: doc
/*
 *  @ingroup oalplus_objects
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

	void _move_in(Object&& temp)
	OALPLUS_NOEXCEPT(true)
	{
		this->_name = temp._name;
		temp._name = 0;
	}

	void _cleanup(void)
	{
		if(this->_name != 0u)
		{
			_undescribe();
			ObjGenDelOps<ObjTag>::Delete(1, &this->_name);
		}
	}
protected:
	struct Uninitialized_ { };

	Object(Uninitialized_) { }

	Object(ALuint name)
	{
		this->_name = name;
	}

	Object(ALuint name, ObjectDesc&& description)
	{
		this->_name = name;
		_describe(std::move(description));
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

	/// Objects are movable
	Object(Object&& temp)
	OALPLUS_NOEXCEPT(true)
	{
		_move_in(std::move(temp));
	}

	~Object(void)
	OALPLUS_NOEXCEPT(true)
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

	static Object FromRawName(ObjectName<ObjTag> name)
	{
		return Object(GetALName(name));
	}

	/// Returns the textual description of this object
	const std::string& Description(void) const
	{
		return aux::ObjectDescRegistry::_get_desc(
			ObjTag::value,
			this->_name
		);
	}
};

} // namespace oalplus

#endif // include guard
