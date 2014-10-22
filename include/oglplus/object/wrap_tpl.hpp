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
#include <oglplus/utils/nothing.hpp>
#include <type_traits>
#include <cassert>

namespace oglplus {
namespace tag {

struct Generate { };
struct Create { };

} // namespace tag

template <typename ObjTag>
struct ObjectSubtype : Nothing
{ };

template <typename OpsTag, typename ObjTag>
struct ObjGenTag
{
	typedef tag::Generate Type;
};

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

template <typename ObjTag, typename NameHolder>
class ObjectTpl
 : public NameHolder
 , public ObjGenDelOps<ObjTag>
{
private:
	typedef typename ObjTag::NameType NameT;

	// Object is not copy-constructible
	ObjectTpl(const ObjectTpl&);

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

	template <typename GenTag>
	void _init(GenTag gen_tag, Nothing)
	{
		ObjGenDelOps<ObjTag>::Gen(gen_tag, 1, &this->_name);
	}

	template <typename GenTag, typename ObjectSubtype>
	void _init(GenTag gen_tag, ObjectSubtype type)
	{
		this->_type = GLenum(type);
		_init(gen_tag, Nothing());
	}

	void _move_in(ObjectTpl&& temp)
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

	ObjectTpl(Uninitialized_) { }

	ObjectTpl(ObjectName<ObjTag> name)
	{
		this->_name = GetName(name);
	}

	ObjectTpl(ObjectName<ObjTag> name, ObjectDesc&& description)
	{
		this->_name = GetName(name);
		_describe(std::move(description));
	}
public:
	template <typename GenTag>
	ObjectTpl(GenTag gen_tag)
	{
		_init(gen_tag, Nothing());
	}

	template <typename GenTag>
	ObjectTpl(GenTag gen_tag, ObjectDesc&& description)
	{
		_init(gen_tag, Nothing());
		_describe(std::move(description));
	}

	typedef typename ObjectSubtype<ObjTag>::Type Subtype;

	template <typename GenTag>
	ObjectTpl(GenTag gen_tag, Subtype subtype)
	{
		_init(gen_tag, subtype);
	}

	template <typename GenTag>
	ObjectTpl(GenTag gen_tag, Subtype subtype, ObjectDesc&& description)
	{
		_init(gen_tag, subtype);
		_describe(std::move(description));
	}

	/// Objects are movable
	ObjectTpl(ObjectTpl&& temp)
	OGLPLUS_NOEXCEPT(true)
	{
		_move_in(std::move(temp));
	}

	~ObjectTpl(void)
	OGLPLUS_NOEXCEPT(true)
	{
		try { _cleanup(); }
		catch(...) { }
	}

	/// Objects are move-assignable
	ObjectTpl& operator = (ObjectTpl&& temp)
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

/// Template
template <typename ObjTag>
class ObjHandle
 : public ObjectTpl<ObjTag, ObjectName<ObjTag>>
{
private:
	typedef ObjectTpl<ObjTag, ObjectName<ObjTag>> Base_;
	ObjHandle(const ObjHandle&);
public:
	/// Construction with a specific method of object creation
	ObjHandle(tag::Generate generate)
	 : Base_(generate)
	{ }

	/// Construction with a specific method of object creation
	ObjHandle(tag::Create create)
	 : Base_(create)
	{ }

	ObjHandle(tag::Generate generate, ObjectDesc&& description)
	 : Base_(generate, std::move(description))
	{ }

	ObjHandle(tag::Create create, ObjectDesc&& description)
	 : Base_(create, std::move(description))
	{ }

	/// Object subtype
	typedef typename ObjectSubtype<ObjTag>::Type Subtype;

	ObjHandle(tag::Generate generate, Subtype subtype)
	 : Base_(generate, subtype)
	{ }

	ObjHandle(tag::Create create, Subtype subtype)
	 : Base_(create, subtype)
	{ }

	/// Object handles are move constructible
	ObjHandle(ObjHandle&& temp)
	 : Base_(static_cast<Base_&&>(temp))
	{ }

	/// Object handles are move assignable
	ObjHandle& operator = (ObjHandle&& temp)
	{
		Base_::operator = (static_cast<Base_&&>(temp));
		return *this;
	}
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
 : public ObjectTpl<ObjTag, ObjectOps<OpsTag, ObjTag>>
{
private:
	typedef typename ObjGenTag<OpsTag, ObjTag>::Type DefGenTag;
	typedef ObjectTpl<ObjTag, ObjectOps<OpsTag, ObjTag>> Base_;

	Object(const Object&);
protected:
	Object(typename Base_::Uninitialized_ uninit)
	 : Base_(uninit)
	{ }

	Object(ObjectName<ObjTag> name)
	 : Base_(name)
	{ }

	Object(ObjectName<ObjTag> name, ObjectDesc&& description)
	 : Base_(name, std::move(description))
	{ }
public:
	static Object FromRawName(ObjectName<ObjTag> name)
	{
		return Object(name);
	}

	/// Most objects are default constructible
	Object(void)
	 : Base_(DefGenTag())
	{ }

	/// Construction with a specific method of object creation
	Object(tag::Generate generate)
	 : Base_(generate)
	{ }

	/// Construction with a specific method of object creation
	Object(tag::Create create)
	 : Base_(create)
	{ }

	/// A textual description can be attached to objects
	Object(ObjectDesc&& description)
	 : Base_(DefGenTag(), std::move(description))
	{ }

	Object(tag::Generate generate, ObjectDesc&& description)
	 : Base_(generate, std::move(description))
	{ }

	Object(tag::Create create, ObjectDesc&& description)
	 : Base_(create, std::move(description))
	{ }

	/// Object subtype
	typedef typename ObjectSubtype<ObjTag>::Type Subtype;

	/// Construction with subtype specification
	Object(Subtype subtype)
	 : Base_(DefGenTag(), subtype)
	{ }

	Object(tag::Generate generate, Subtype subtype)
	 : Base_(generate, subtype)
	{ }

	Object(tag::Create create, Subtype subtype)
	 : Base_(create, subtype)
	{ }

	/// A textual description can be attached to objects
	Object(Subtype subtype, ObjectDesc&& description)
	 : Base_(DefGenTag(), subtype, std::move(description))
	{ }

	Object(tag::Generate generate, Subtype subtype, ObjectDesc&& description)
	 : Base_(generate, subtype, std::move(description))
	{ }

	Object(tag::Create create, Subtype subtype, ObjectDesc&& description)
	 : Base_(create, subtype, std::move(description))
	{ }

	/// Objects are move constructible
	Object(Object&& temp)
	 : Base_(static_cast<Base_&&>(temp))
	{ }

	/// Objects are move assignable
	Object& operator = (Object&& temp)
	{
		Base_::operator = (static_cast<Base_&&>(temp));
		return *this;
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
