/**
 *  @file oalplus/object.hpp
 *  @brief Generic OpenAL object wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_OBJECT_1107121519_HPP
#define OALPLUS_OBJECT_1107121519_HPP

#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/enumerations.hpp>
#include <oalplus/auxiliary/named.hpp>

#include <type_traits>
#include <cassert>

namespace oalplus {

template <class Object>
class Array;

/** @defgroup oalplus_objects OALplus objects
 *
 *  An @ref oalplus_object is a class wrapping around OpenAL objects
 *  like sources, buffer, listeners, etc. It is using the RAII technique
 *  to provide automated resource management for these OpenAL resources.
 *  They also wrap operations related to these objects and provide
 *  additional type safety and more robust error handling. Look
 *  @ref oalplus_object "here" for more details.
 */

/** @page oalplus_object OALplus object
 *
 *  @OALplus defines classes like @ref oalplus::Buffer "Buffer",
 *  @ref oalplus::Source "Source", @ref oalplus::Listener "Listener",
 *  and many others, wrapping around OpenAL
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
 *  };
 *  @endcode
 */

/** For obvious reasons @ref oalplus_object "objects" are not copyable,
 *  only movable. There may however be situations where a temporary copy
 *  of the "master" object (with the knowledge that the original will
 *  be kept alive during the whole lifetime of the copy) is needed.
 *  The Managed template class allows to do such temporary copies
 *  which have the same members and friend functions as the original
 *  object, and can be use in the same way, provided that the original
 *  instance is not destroyed before the managed copy.
 *
 *  Managed instances are may for be example created when accessing or iterating
 *  through the elements of an @ref oalplus::Array "Array".
 *
 *  @ingroup modifier_classes
 */
template <class Object>
#if OALPLUS_DOCUMENTATION_ONLY
class Managed
 : public Object
{ };
#else
class Managed;
#endif

template <class Object>
class ObjectInitializer;

// Helper base class for OpenAL object wrappers
/*
 *  @note Do not use this class directly, use the derived classes instead.
 *
 *  @ingroup oalplus_objects
 */
template <class ObjectOps>
class Object
 : public ObjectOps
{
private:
	friend class ObjectInitializer<Object>;

	ALuint _release(void)
	{
		ALuint res = this->_name;
		this->_name = 0;
		return res;
	}

	static inline bool _type_ok(ALuint _name)
	{
#if OALPLUS_DONT_TEST_OBJECT_TYPE
		OALPLUS_FAKE_USE(_name);
		return true;
#else
		try{return ObjectOps::_is_x(_name) == AL_TRUE;}
		catch(...){return false;}
#endif
	}

	static inline bool _verified_name(const Object* that)
	{
		assert(that);
		return (that->_name != 0);
	}

	static inline bool _verified_type(const Object* that)
	{
		assert(that);
		return (_type_ok(that->_name));
	}

	static inline void _verify(const Object* that)
	{
		OALPLUS_FAKE_USE(that);
		assert(_verified_name(that) && _verified_type(that));
	}

	static inline void _do_init(ALsizei _c, ALuint* _n)
	{
		assert(_c != 0);
		assert(_n != nullptr);
		assert(*_n == 0);
		ObjectOps::_init(_c, _n);
		assert(*_n != 0);
	}

	static inline void _do_cleanup(ALsizei _c, ALuint* _n)
	{
		assert(_c != 0);
		assert(_n != nullptr);
		try
		{
			ObjectOps::_cleanup(_c, _n);
			assert((OALPLUS_ALFUNC(al,GetError)()) == AL_NO_ERROR);
		}
		catch(...){ }
		*_n = 0;
	}
protected:
	inline bool _is_initialized(void) const
	{
		return this->_name != 0;
	}

	void _move_in(Object&& temp)
	{
		assert(!_is_initialized());
		_verify(&temp);
		this->_name = temp._release();
		_verify(this);
		assert(!temp._is_initialized());
	}

	void _move_in_uninit(Object&& temp)
	{
		assert(!_is_initialized());
		bool is_init = _verified_name(&temp);
		this->_name = temp._release();
		if(is_init) _verify(this);
		assert(!temp._is_initialized());
	}

	void _cleanup_if_needed(void)
	{
		if(_is_initialized())
		{
			_verify(this);
			_do_cleanup(1, &this->_name);
		}
	}

	struct Uninitialized_ { };

	Object(Uninitialized_)
	OALPLUS_NOEXCEPT(true)
	{ }

	struct FromRawName_ { };

	Object(ALuint name, FromRawName_)
	{
		this->_name = name;
	}
public:
	static Object FromRawName(ALuint name)
	{
		return Object(name, FromRawName_());
	}

	Object(void)
	{
		_do_init(1, &this->_name);
		_verify(this);
	}

#if !OALPLUS_NO_DELETED_FUNCTIONS
	Object(const Object&) = delete;
#else
private:
	Object(const Object&);
public:
#endif

	Object(Object&& temp)
	OALPLUS_NOEXCEPT(true)
	{
		_move_in(std::move(temp));
	}

	~Object(void)
	OALPLUS_NOEXCEPT(true)
	{
		_cleanup_if_needed();
	}

	Object& operator = (Object&& temp)
	OALPLUS_NOEXCEPT(true)
	{
		_cleanup_if_needed();
		_move_in(std::move(temp));
		return *this;
	}
};

template <class ObjectOps>
class ObjectInitializer<Object<ObjectOps> >
{
protected:
	static inline bool _type_ok(ALuint _name)
	OALPLUS_NOEXCEPT(true)
	{
		return Object<ObjectOps>::_type_ok(_name);
	}

	static inline void _init(ALsizei _c, ALuint* _n)
	{
		Object<ObjectOps>::_do_init(_c, _n);
	}

	static inline void _cleanup(ALsizei _c, ALuint* _n)
	OALPLUS_NOEXCEPT(true)
	{
		Object<ObjectOps>::_do_cleanup(_c, _n);
	}
};

template <typename ObjectOps>
class Managed
 : public ObjectOps
 , public FriendOf<ObjectOps>
{
private:
	Managed(void)
	{ }
public:
	Managed(const ObjectOps& obj)
	 : ObjectOps(obj)
	{ }

	Managed(ALuint name)
	{
		FriendOf<ObjectOps>::SetName(*this, name);
	}

	~Managed(void)
	{
		FriendOf<ObjectOps>::SetName(*this, 0);
	}
};

} // namespace oalplus

#endif // include guard
