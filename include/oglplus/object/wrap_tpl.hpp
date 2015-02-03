/**
 *  @file oglplus/object/wrap_tpl.hpp
 *  @brief Template for object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
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
	constexpr inline
	ObjCommonOps(ObjectName<ObjTag> name)
	noexcept
	 : ObjectName<ObjTag>(name)
	{ }
public:
	ObjCommonOps(ObjCommonOps&&) = default;
	ObjCommonOps(const ObjCommonOps&) = default;
	ObjCommonOps& operator = (ObjCommonOps&&) = default;
	ObjCommonOps& operator = (const ObjCommonOps&) = default;
};

/// Implements operations applicable to any object including object 0 (zero)
template <class OpsTag, class ObjTag>
class ObjZeroOps
 : public ObjCommonOps<ObjTag>
{
protected:
	constexpr inline
	ObjZeroOps(ObjectName<ObjTag> name)
	noexcept
	 : ObjCommonOps<ObjTag>(name)
	{ }
public:
	ObjZeroOps(ObjZeroOps&&) = default;
	ObjZeroOps(const ObjZeroOps&) = default;
	ObjZeroOps& operator = (ObjZeroOps&&) = default;
	ObjZeroOps& operator = (const ObjZeroOps&) = default;
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
	constexpr inline
	ObjectZero(void)
	noexcept
	 : ObjZeroOps<OpsTag, ObjTag>(ObjectName<ObjTag>(0))
	{ }
};

/// Implements operations applicable to named (non-zero) objects
template <class OpsTag, class ObjTag>
class ObjectOps
 : public ObjZeroOps<OpsTag, ObjTag>
{
protected:
	constexpr inline
	ObjectOps(ObjectName<ObjTag> name)
	noexcept
	 : ObjZeroOps<OpsTag, ObjTag>(name)
	{ }
public:
	ObjectOps(ObjectOps&&) = default;
	ObjectOps(const ObjectOps&) = default;
	ObjectOps& operator = (ObjectOps&&) = default;
	ObjectOps& operator = (const ObjectOps&) = default;
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
			this->_obj_name(),
			std::move(description)
		);
	}

	void _undescribe(void)
	{
		aux::ObjectDescRegistry::_unregister_desc(
			ObjTag::value,
			this->_obj_name()
		);
	}

	template <typename GenTag>
	void _init(GenTag gen_tag, Nothing)
	{
		ObjGenDelOps<ObjTag>::Gen(gen_tag, 1, this->_name_ptr());
	}

	template <typename GenTag, typename ObjectSubtype>
	void _init(GenTag gen_tag, ObjectSubtype type)
	{
		this->_type = GLenum(type);
		_init(gen_tag, Nothing());
	}

	void _cleanup(void)
	{
		if(this->_has_deletable_name())
		{
			_undescribe();
			ObjGenDelOps<ObjTag>::Delete(1, this->_name_ptr());
		}
	}
protected:
	struct Uninitialized_ { };

	ObjectTpl(Uninitialized_)
	noexcept
	 : NameHolder(ObjectName<ObjTag>())
	{ }

	ObjectTpl(ObjectName<ObjTag> name)
	noexcept
	 : NameHolder(name)
	{ }

	ObjectTpl(ObjectName<ObjTag> name, ObjectDesc&& description)
	noexcept
	 : NameHolder(name)
	{
		_describe(std::move(description));
	}
public:
	template <typename GenTag>
	ObjectTpl(GenTag gen_tag)
	 : NameHolder(ObjectName<ObjTag>())
	{
		_init(gen_tag, Nothing());
	}

	template <typename GenTag>
	ObjectTpl(GenTag gen_tag, ObjectDesc&& description)
	 : NameHolder(ObjectName<ObjTag>())
	{
		_init(gen_tag, Nothing());
		_describe(std::move(description));
	}

	typedef typename ObjectSubtype<ObjTag>::Type Subtype;

	template <typename GenTag>
	ObjectTpl(GenTag gen_tag, Subtype subtype)
	 : NameHolder(ObjectName<ObjTag>())
	{
		_init(gen_tag, subtype);
	}

	template <typename GenTag>
	ObjectTpl(GenTag gen_tag, Subtype subtype, ObjectDesc&& description)
	 : NameHolder(ObjectName<ObjTag>())
	{
		_init(gen_tag, subtype);
		_describe(std::move(description));
	}

	/// Objects are movable
	ObjectTpl(ObjectTpl&& temp)
	noexcept
	 : NameHolder(static_cast<NameHolder&&>(temp))
	{ }

	~ObjectTpl(void)
	noexcept
	{
		try { _cleanup(); }
		catch(...) { }
	}

	/// Objects are move-assignable
	ObjectTpl& operator = (ObjectTpl&& temp)
	noexcept
	{
		if(this != &temp)
		{
			try { _cleanup(); }
			catch(...) { }
			NameHolder::operator = (
				static_cast<NameHolder&&>(temp)
			);
		}
		return *this;
	}

	/// Returns the textual description of this object
	const std::string& Description(void) const
	noexcept
	{
		return aux::ObjectDescRegistry::_get_desc(
			ObjTag::value,
			this->_obj_name()
		);
	}

	Sequence<ObjectName<ObjTag>> seq(void) const
	{
		return Sequence<ObjectName<ObjTag>>(this->_name_ptr(), 1);
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
	noexcept
	 : Base_(static_cast<Base_&&>(temp))
	{ }

	/// Object handles are move assignable
	ObjHandle& operator = (ObjHandle&& temp)
	noexcept
	{
		Base_::operator = (static_cast<Base_&&>(temp));
		return *this;
	}
};

/// Template for GL objects wrappers.
/** The main purpose of Object is to do lifetime management of the underlying
 *  GL object. It uses the @c ObjGenDelOps template to create
 *  new instance in the constructor and delete it in the destructor.
 *
 *  Since GL don't support object copying @c Object is also non-copyable.
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
	noexcept
	 : Base_(uninit)
	{ }

	Object(ObjectName<ObjTag> name)
	noexcept
	 : Base_(name)
	{ }

	Object(ObjectName<ObjTag> name, ObjectDesc&& description)
	noexcept
	 : Base_(name, std::move(description))
	{ }
public:
	static
	Object FromRawName(ObjectName<ObjTag> name)
	noexcept
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
	noexcept
	 : Base_(static_cast<Base_&&>(temp))
	{ }

	/// Objects are move assignable
	Object& operator = (Object&& temp)
	noexcept
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
