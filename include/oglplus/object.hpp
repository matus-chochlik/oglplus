/**
 *  @file oglplus/object.hpp
 *  @brief Generic OpenGL object wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_1107121519_HPP
#define OGLPLUS_OBJECT_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/auxiliary/named.hpp>
#include <oglplus/auxiliary/strings.hpp>
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


template <class Object>
class Array;

template <class Object>
struct ObjectBaseOps
{
	template <typename X>
	static typename X::BaseOps _get(X*, typename X::BaseOps* = nullptr);
	static Object _get(...);

	typedef decltype(_get((Object*)nullptr)) Type;
};

// checks if an Object has the Property::Type typedef
template <class Object>
struct ObjectWithType
{
	template <typename X>
	static std::true_type _has(X*, typename X::Property::Type* = nullptr);
	static std::false_type _has(...);

	typedef decltype(_has((Object*)nullptr)) HasType;

	template <typename X>
	static typename X::Property::Type
		_get(X*, typename X::Property::Type* = nullptr);
	static Nothing _get(...);

	typedef decltype(_get((Object*)nullptr)) Type;
};

// checks if an Object has the Target typedef
template <class Object>
struct ObjectWithTarget
{
	template <typename X>
	static std::true_type _has(X*, typename X::Target* = nullptr);
	static std::false_type _has(...);

	typedef decltype(_has((Object*)nullptr)) HasTarget;

	template <typename X>
	static typename X::Target
		_get(X*, typename X::Target* = nullptr);
	static Nothing _get(...);

	typedef decltype(_get((Object*)nullptr)) Target;
};

template <class Object>
struct ObjectTypeOrTarget
{
	typedef typename std::conditional<
		ObjectWithType<Object>::HasType::value,
		typename ObjectWithType<Object>::Type,
		typename ObjectWithTarget<Object>::Target
	>::type Type;

	typedef typename enums::EnumValueType<Type>::Type ValueType;
};

/// Allows to make managed copies of instances of Object
/** For obvious reasons @ref oglplus_object "objects" are not copyable,
 *  only movable. There may however be situations where a temporary copy
 *  of the "master" object (with the knowledge that the original will
 *  be kept alive during the whole lifetime of the copy) is needed.
 *  The Managed template class allows to do such temporary copies
 *  which have the same members and friend functions as the original
 *  object, and can be use in the same way, provided that the original
 *  instance is not destroyed before the managed copy.
 *
 *  Managed instances are may for be example created when accessing or iterating
 *  through the elements of an @ref oglplus::Array "Array".
 *
 *  @ingroup modifier_classes
 */
template <class Object>
#if OGLPLUS_DOCUMENTATION_ONLY
class Managed
 : public Object
{ };
#else
class Managed;
#endif

template <class Object>
class ObjectInitializer;

// Base class for object operations
template <bool MultiObject>
class BaseObject
{
public:
	typedef std::integral_constant<
		bool,
		MultiObject
	> IsMultiObject;
};

template <typename Object>
OGLPLUS_CONSTEXPR inline int GetObjectTypeId(const Object&)
{
	return ObjectTypeId<
		typename ObjectBaseOps<Object>::Type
	>::value;
}

// Helper base class for OpenGL object wrappers
/*
 *  @note Do not use this class directly, use the derived classes instead.
 *
 *  @ingroup oglplus_objects
 */
template <class ObjectOps>
class Object
 : public ObjectOps
 , public aux::ObjectDescRegistry<ObjectOps>
{
private:
	static OGLPLUS_CONSTEXPR bool _can_be_zero(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectOps::_can_be_zero::value;
	}

	GLuint _release(void)
	OGLPLUS_NOEXCEPT(true)
	{
		GLuint res = this->_name;
		this->_name = 0;
		return res;
	}

	template <typename ObjectType>
	static inline OGLPLUS_CONSTEXPR
	typename std::is_same<
		typename ObjectWithType<Object>::Type,
		ObjectType
	>::type _is_object_type(ObjectType)
	OGLPLUS_NOEXCEPT(true)
	{
		return typename std::is_same<
			typename ObjectWithType<Object>::Type,
			ObjectType
		>::type();
	}

	template <typename ObjectTarget>
	static inline OGLPLUS_CONSTEXPR
	typename std::is_same<
		typename ObjectWithTarget<Object>::Target,
		ObjectTarget
	>::type _is_object_target(ObjectTarget)
	OGLPLUS_NOEXCEPT(true)
	{
		return typename std::is_same<
			typename ObjectWithTarget<Object>::Target,
			ObjectTarget
		>::type();
	}

	template <
		typename _ObjectOps,
		oglplus::ObjectType (*Get)(void)
	> struct _hlp_object_type { };

	template <typename _ObjectOps>
	static oglplus::ObjectType _get_object_type(
		_hlp_object_type<_ObjectOps, &_ObjectOps::_object_type>*
	) OGLPLUS_NOEXCEPT(true)
	{
		return _ObjectOps::_object_type();
	}

	// calling this means that the _object_type function is not implemented
	// by ObjectOps which means that some GL symbols are not properly
	// defined by the used GL header
	template <typename _ObjectOps>
	static oglplus::ObjectType _get_object_type(...)
	OGLPLUS_NOEXCEPT(true)
	{
#ifdef None
#pragma push_macro("None")
#undef None
		return oglplus::ObjectType::None;
#pragma pop_macro("None")
#else
		return oglplus::ObjectType::None;
#endif
	}

	static inline bool _type_ok(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
#if OGLPLUS_DONT_TEST_OBJECT_TYPE
		OGLPLUS_FAKE_USE(_name);
		return true;
#else
		try{return ObjectOps::_is_x(_name) == GL_TRUE;}
		catch(...){return false;}
#endif
	}

	static inline bool _verified_name(const Object* that)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(that);
		return (_can_be_zero() || that->_name != 0);
	}

	static inline bool _verified_type(const Object* that)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(that);
		return (_type_ok(that->_name));
	}

	static inline void _verify(const Object* that)
	OGLPLUS_NOEXCEPT(true)
	{
		OGLPLUS_FAKE_USE(that);
		assert(_verified_name(that) && _verified_type(that));
	}

	static inline void _describe(
		const Object* that,
		ObjectDesc&& description
	) OGLPLUS_NOEXCEPT(true)
	{
		try
		{
			that->_register_desc(
				GLenum(_get_object_type<ObjectOps>(nullptr)),
				that->_name,
				std::move(description)
			);
		}
		catch(...){ }
	}

	static inline void _undescribe(const Object* that)
	OGLPLUS_NOEXCEPT(true)
	{
		try
		{
			that->_unregister_desc(
				GLenum(_get_object_type<ObjectOps>(nullptr)),
				that->_name
			);
		}
		catch(...){ }
	}

	static inline void _do_init(GLsizei _c, GLuint* _n)
	{
		assert(_c != 0);
		assert(_n != nullptr);
		assert(*_n == 0);
		assert(ObjectOps::IsMultiObject::value || (_c == 1));
		ObjectOps::_init(_c, _n);
		assert(_can_be_zero() || *_n != 0);
	}

	template <typename Type>
	static inline void _do_init(
		GLsizei _c,
		GLuint* _n,
		Type _t,
		std::true_type /*_t_is_type*/,
		std::false_type /*_t_is_target*/
	)
	{
		assert(_c > 0);
		assert(_n != nullptr);
		assert(*_n == 0);
		for(GLsizei i=0; i!=_c; ++i)
			ObjectOps::_init(1, _n+i, _t);
		assert(_can_be_zero() || *_n != 0);
	}

	template <typename Target>
	static inline void _do_init(
		GLsizei _c,
		GLuint* _n,
		Target _t,
		std::false_type /*_t_is_type*/,
		std::true_type /*_t_is_target*/
	)
	{
		assert(_n != nullptr);
		assert(*_n == 0);
		ObjectOps::_init(_c, _n);
		assert(_can_be_zero() || *_n != 0);
		try
		{
			for(GLsizei i=0; i!=_c; ++i)
				ObjectOps::_bind(_n[i], _t);
		}
		catch(...)
		{
			ObjectOps::_cleanup(_c, _n);
			*_n = 0;
		}
	}

	template <typename TypeOrTarget>
	static inline void _do_init(GLsizei _c, GLuint* _n, TypeOrTarget _t)
	{
		_do_init(_c, _n, _t, _is_object_type(_t),_is_object_target(_t));
	}

	static inline void _do_cleanup(GLsizei _c, GLuint* _n)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_c != 0);
		assert(_n != nullptr);
		assert(ObjectOps::IsMultiObject::value || (_c == 1));
		try
		{
			ObjectOps::_cleanup(_c, _n);
			assert((OGLPLUS_GLFUNC(GetError)()) == GL_NO_ERROR);
		}
		catch(...){ }
		*_n = 0;
	}

	friend class ObjectInitializer<Object>;
protected:
	inline bool _is_initialized(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return this->_name != 0;
	}

	void _move_in(Object&& temp)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(!_is_initialized());
		_verify(&temp);
		this->_name = temp._release();
		_verify(this);
		assert(!temp._is_initialized());
	}

	void _move_in_uninit(Object&& temp)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(!_is_initialized());
		bool is_init = _verified_name(&temp);
		this->_name = temp._release();
		if(is_init) _verify(this);
		assert(!temp._is_initialized());
	}

	void _cleanup_if_needed(void)
	OGLPLUS_NOEXCEPT(true)
	{
		if(_is_initialized())
		{
			_verify(this);
			_undescribe(this);
			_do_cleanup(1, &this->_name);
		}
	}

	struct _Uninitialized { };

	Object(_Uninitialized)
	OGLPLUS_NOEXCEPT(true)
	{ }
public:
	Object(void)
	{
		_do_init(1, &this->_name);
		_verify(this);
	}

	Object(ObjectDesc&& description)
	{
		_do_init(1, &this->_name);
		_verify(this);
		_describe(this, std::move(description));
	}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	Object(const Object&) = delete;
#else
private:
	Object(const Object&);
public:
#endif

	Object(Object&& temp)
	OGLPLUS_NOEXCEPT(true)
	{
		_move_in(std::move(temp));
	}

	Object(typename ObjectTypeOrTarget<ObjectOps>::Type type_or_target)
	{
		_do_init(1, &this->_name, type_or_target);
		_verify(this);
	}

	Object(
		typename ObjectTypeOrTarget<ObjectOps>::Type type_or_target,
		ObjectDesc&& description
	)
	{
		_do_init(1, &this->_name, type_or_target);
		_verify(this);
		_describe(this, std::move(description));
	}

	~Object(void)
	OGLPLUS_NOEXCEPT(true)
	{
		_cleanup_if_needed();
	}

	Object& operator = (Object&& temp)
	OGLPLUS_NOEXCEPT(true)
	{
		_cleanup_if_needed();
		_move_in(std::move(temp));
		return *this;
	}

	static oglplus::ObjectType ObjectType(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return _get_object_type<ObjectOps>(nullptr);
	}

	const String& Description(void) const
	{
		return this->_get_desc(this->_name);
	}
};

template <class ObjectOps>
class ObjectInitializer<Object<ObjectOps> >
{
protected:
	static inline bool _type_ok(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		return Object<ObjectOps>::_type_ok(_name);
	}

	static inline void _init(GLsizei _c, GLuint* _n)
	{
		Object<ObjectOps>::_do_init(_c, _n);
	}

	static inline void _cleanup(GLsizei _c, GLuint* _n)
	OGLPLUS_NOEXCEPT(true)
	{
		Object<ObjectOps>::_do_cleanup(_c, _n);
	}
};

#if !OGLPLUS_DOCUMENTATION_ONLY && !OGLPLUS_DOXYGEN_PARSE
template <class ObjectOps>
struct ObjectBaseOps<Object<ObjectOps> >
{
	typedef ObjectOps Type;
};
#endif

struct NoOpSpecializedInitializer
{
protected:
	typedef Nothing ParameterType;

	NoOpSpecializedInitializer(void)
	{ }

	template <class Object>
	NoOpSpecializedInitializer(
		Object& object,
		typename ObjectTypeOrTarget<Object>::Type,
		Nothing
	)
	{ }
};


template <
	class Object,
	typename ObjectTypeOrTarget<Object>::ValueType TypeOrTarget,
	typename Initializer = NoOpSpecializedInitializer
> class Specialized;

template <
	class ObjectOps,
	typename ObjectTypeOrTarget<Object<ObjectOps>>::ValueType TypeOrTarget,
	typename Initializer
>
class Specialized<Object<ObjectOps>, TypeOrTarget, Initializer>
 : public Object<ObjectOps>
 , public Initializer
{
private:
	typedef typename ObjectTypeOrTarget<Object<ObjectOps>>::Type _tot;
	static _tot _type_or_target(void)
	{
		return _tot(TypeOrTarget);
	}
protected:
	Object<ObjectOps>& _object(void)
	{
		return *this;
	}
public:
	Specialized(void)
	 : Object<ObjectOps>(_type_or_target())
	{ }

	Specialized(ObjectDesc&& description)
	 : Object<ObjectOps>(_type_or_target(), std::move(description))
	{ }

	Specialized(typename Initializer::ParameterType parameter)
	 : Object<ObjectOps>(_type_or_target())
	 , Initializer(
		_object(),
		_type_or_target(),
		static_cast<typename Initializer::ParameterType>(parameter)
	)
	{ }

	Specialized(
		ObjectDesc&& description,
		typename Initializer::ParameterType parameter
	): Object<ObjectOps>(_type_or_target(), std::move(description))
	 , Initializer(
		_object(),
		_type_or_target(),
		static_cast<typename Initializer::ParameterType>(parameter)
	)
	{ }

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	Specialized(const Specialized&) = delete;
#else
private:
	Specialized(const Specialized&);
public:
#endif

	Specialized(Specialized&& tmp)
	 : Object<ObjectOps>(std::forward<Object<ObjectOps>>(tmp))
	{ }
};

#if !OGLPLUS_DOCUMENTATION_ONLY && !OGLPLUS_DOXYGEN_PARSE
template <
	class ObjectOps,
	typename ObjectTypeOrTarget<Object<ObjectOps>>::ValueType TypeOrTarget,
	typename Initializer
>
struct ObjectBaseOps<Specialized<Object<ObjectOps>, TypeOrTarget, Initializer>>
{
	typedef ObjectOps Type;
};

template <class _Object>
class Managed
 : public ObjectBaseOps<_Object>::Type
 , public FriendOf<typename ObjectBaseOps<_Object>::Type>
{
private:
	typedef typename ObjectBaseOps<_Object>::Type ObjectOps;

	ObjectOps& _base(void){ return *this; }

	Managed(void)
	{ }
public:
	Managed(const ObjectOps& obj)
	 : ObjectOps(obj)
	{ }

	Managed(GLuint name)
	{
		FriendOf<ObjectOps>::SetName(*this, name);
	}

	~Managed(void)
	{
		FriendOf<ObjectOps>::SetName(*this, 0);
	}
};

template <class _Object>
struct ObjectBaseOps<Managed<_Object> >
{
	typedef typename ObjectBaseOps<_Object>::Type Type;
};

template <class _Object>
static const String& DescriptionOf(const _Object& object)
{
	return FriendOf<
		typename ObjectBaseOps<_Object>::Type
	>::GetDescription(object);
}
#endif

} // namespace oglplus

#endif // include guard
