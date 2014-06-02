/**
 *  @file oglplus/object/wrap_tpl.hpp
 *  @brief Template for object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_WRAP_TPL_1107121519_HPP
#define OGLPLUS_OBJECT_WRAP_TPL_1107121519_HPP

#include <oglplus/object/desc.hpp>
#include <oglplus/object/name_tpl.hpp>
#include <oglplus/object/seq_tpl.hpp>
#include <oglplus/detail/nothing.hpp>
#include <type_traits>
#include <cassert>

namespace oglplus {

template <typename ObjTag>
struct ObjectSubtype : Nothing
{ };

template <typename ObjTag>
class ObjGenDelOps;

template <typename OpsTag, typename ObjTag>
class ObjectOps;

template <typename OpsTg, typename ObjTg>
struct Classify<ObjectOps<OpsTg, ObjTg>>
{
	typedef ObjectOps<OpsTg, ObjTg> Base;
	typedef tag::ObjectOps Tag;
	typedef OpsTg OpsTag;
	typedef ObjTg ObjTag;
};

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

/// Template for GL/AL/etc. objects wrappers.
/** The main purpose of Object is to do lifetime management of the underlying
 *  GL/AL/etc. object. It uses the @c ObjGenDelOps template to create
 *  new instance in the constructor and delete it in the destructor.
 *
 *  Since GL/AL don't support object copying @c Object is also non-copyable.
 */
template <typename OpsTag, typename ObjTag>
class Object<ObjectOps<OpsTag, ObjTag>>
 : public ObjectOps<OpsTag, ObjTag>
 , public ObjGenDelOps<ObjTag>
{
private:
	typedef typename ObjTag::NameType NameT;

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
		if(this->_name != 0u)
		{
			_undescribe();
			ObjGenDelOps<ObjTag>::Delete(1, &this->_name);
		}
	}
protected:
	struct Uninitialized_ { };

	Object(Uninitialized_) { }

	Object(NameT name)
	{
		this->_name = name;
	}

	Object(NameT name, ObjectDesc&& description)
	{
		this->_name = name;
		_describe(std::move(description));
	}
public:
	static Object FromRawName(ObjectName<ObjTag> name)
	{
		return Object(GetName(name));
	}

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

	/// Construction with subtype specification
	Object(typename ObjectSubtype<ObjTag>::Type type)
	{
		_init(type);
	}

	/// A textual description can be attached to objects
	Object(
		typename ObjectSubtype<ObjTag>::Type type,
		ObjectDesc&& description
	)
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

	/// Returns the textual description of this object
	const std::string& Description(void) const
	{
		return aux::ObjectDescRegistry::_get_desc(
			ObjTag::value,
			this->_name
		);
	}


	Sequence<ObjectName<ObjTag>> seq(void) const
	{
		return Sequence<ObjectName<ObjTag>>(&this->_name, 1);
	}

	/// Returns a sequence referencing the name of this object
	/** Note that the returned sequence must not be used after
	 *  this object has been destroyed.
	 */
	operator Sequence<ObjectName<ObjTag>> (void) const
	{
		return seq();
	}

};

template <typename OpsTg, typename ObjTg>
struct Classify<Object<ObjectOps<OpsTg, ObjTg>>>
 : Classify<ObjectOps<OpsTg, ObjTg>>
{
	typedef Object<ObjectOps<OpsTg, ObjTg>> Base;
	typedef tag::Object Tag;
};

} // namespace oglplus

#endif // include guard
