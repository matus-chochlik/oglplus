/**
 *  @file oglplus/object.hpp
 *  @brief Generic OpenGL object wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_OBJECT_1107121519_HPP
#define OGLPLUS_OBJECT_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/auxiliary/named.hpp>
#include <oglplus/auxiliary/strings.hpp>
#include <type_traits>
#include <cassert>

namespace oglplus {

/** @defgroup objects OGLplus objects
 *
 *  An @ref oglplus_object is a class wrapping around OpenGL objects
 *  like shaders, programs, textures, etc. Its using the RAII technique
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

// checks if the Object has Property::Type
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
	static int _get(...);

	typedef decltype(_get((Object*)nullptr)) Type;
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

// Helper base class for OpenGL object wrappers
/*
 *  @note Do not use this class directly, use the derived classes instead.
 *
 *  @ingroup objects
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
	static inline void _do_init(GLsizei _c, GLuint* _n, Type _k)
	{
		assert(_n != nullptr);
		assert(*_n == 0);
		assert(!ObjectOps::IsMultiObject::value);
		ObjectOps::_init(_c, _n, _k);
		assert(_can_be_zero() || *_n != 0);
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
		assert((*_n = 0) == 0);
	}

	static inline bool _type_ok(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_can_be_zero() || _name != 0);
#if OGLPLUS_DONT_TEST_OBJECT_TYPE
		return true;
#else
		try{return ObjectOps::_is_x(_name) == GL_TRUE;}
		catch(...){return false;}
#endif
	}

	friend class ObjectInitializer<Object>;
public:
	Object(void)
	{
		_do_init(1, &this->_name);
		assert(_can_be_zero() || this->_name != 0);
		assert(_type_ok(this->_name));
	}

	Object(const GLchar* desc)
	{
		_do_init(1, &this->_name);
		assert(_can_be_zero() || this->_name != 0);
		assert(_type_ok(this->_name));
		this->_register_desc(this->_name, desc);
	}

	Object(const String& desc)
	{
		_do_init(1, &this->_name);
		assert(_can_be_zero() || this->_name != 0);
		assert(_type_ok(this->_name));
		this->_register_desc(this->_name, desc);
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
		assert(this->_name == 0);
		assert(_can_be_zero() || temp._name  != 0);
		this->_name = temp._release();
		assert(_can_be_zero() || this->_name != 0);
		assert(temp._name  == 0);
		assert(_type_ok(this->_name));
	}

	template <typename ObjectType>
	Object(ObjectType type)
	{
		static_assert(
			ObjectWithType<Object>::HasType::value &&
			std::is_same<
				typename ObjectWithType<Object>::Type,
				ObjectType
			>::value,
			"Invalid ObjectType for this Object"
		);
		_do_init(1, &this->_name, type);
		assert(_can_be_zero() || this->_name != 0);
		assert(_type_ok(this->_name));
	}

	template <typename ObjectType>
	Object(ObjectType type, const GLchar* desc)
	{
		static_assert(
			ObjectWithType<Object>::HasType::value &&
			std::is_same<
				typename ObjectWithType<Object>::Type,
				ObjectType
			>::value,
			"Invalid ObjectType for this Object"
		);
		_do_init(1, &this->_name, type);
		assert(_can_be_zero() || this->_name != 0);
		assert(_type_ok(this->_name));
		this->_register_desc(this->_name, desc);
	}

	template <typename ObjectType>
	Object(ObjectType type, const String& desc)
	{
		static_assert(
			ObjectWithType<Object>::HasType::value &&
			std::is_same<
				typename ObjectWithType<Object>::Type,
				ObjectType
			>::value,
			"Invalid ObjectType for this Object"
		);
		_do_init(1, &this->_name, type);
		assert(_can_be_zero() || this->_name != 0);
		assert(_type_ok(this->_name));
		this->_register_desc(this->_name, desc);
	}

	~Object(void) OGLPLUS_NOEXCEPT(true)
	{
		if(this->_name != 0)
		{
			assert(_type_ok(this->_name));
			try{this->_unregister_desc(this->_name);}
			catch(...){ }
			_do_cleanup(1, &this->_name);
		}
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
	static inline void _init(GLsizei _c, GLuint* _n)
	{
		Object<ObjectOps>::_do_init(_c, _n);
	}

	static inline void _cleanup(GLsizei _c, GLuint* _n)
	OGLPLUS_NOEXCEPT(true)
	{
		Object<ObjectOps>::_do_cleanup(_c, _n);
	}

	static inline bool _type_ok(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		return Object<ObjectOps>::_type_ok(_name);
	}
};

#if !OGLPLUS_DOCUMENTATION_ONLY && !OGLPLUS_DOXYGEN_PARSE
template <class ObjectOps>
struct ObjectBaseOps<Object<ObjectOps> >
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

	Managed(void)
	{ }
public:
	Managed(const ObjectOps& obj)
	 : ObjectOps(obj)
	{ }

	Managed(GLuint _name)
	{
		FriendOf<ObjectOps>::SetName(*this, _name);
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
static const String& ObjectDescription(const _Object& object)
{
	return FriendOf<
		typename ObjectBaseOps<_Object>::Type
	>::GetDescription(object);
}
#endif

} // namespace oglplus

#endif // include guard
