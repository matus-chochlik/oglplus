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
#include <oglplus/auxiliary/named.hpp>
#include <oglplus/auxiliary/strings.hpp>
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
 *  OGLplus defines classes like @ref oglplus::Buffer "Buffer",
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
 *    // If object has a Kind typedef, construct with kind specification
 *    Object(Object::Kind kind);
 *
 *    // Construction with a textual description
 *    Object(String description);
 *
 *    // Construct with kind specification and textual description
 *    Object(Object::Kind kind, String description);
 *
 *    // Returns the textual description (if any) of the Object
 *    const String Description(void) const;
 *
 *  };
 *  @endcode
 */

template <class Object>
class Array;

/// Allows to make managed copies of instances of Object
/** For obvious reasons @ref oglplus_object "objects" are not copyable,
 *  only movable. There may however be situations where a temporary copy
 *  of the "master" object (with the knowledge that the original will
 *  be kept alive during the whole lifetime of the copy) is needed.
 *  The Managed template class allows to do such temporary copies
 *  which have the same members and friend functions as the original
 *  object, and can be use in the same way, provided that to original
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

// Helper base class for OpenGL object wrappers
/*
 *  @note Do not use this class directly, use the derived classes instead.
 *
 *  @ingroup objects
 */
template <class ObjectOps, bool MultiObject>
class Object
 : public ObjectOps
 , public aux::ObjectDescRegistry<ObjectOps>
{
private:
	GLuint _release(void)
	{
		GLuint res = this->_name;
		this->_name = 0;
		return res;
	}

	static inline void _do_init(GLsizei _c, GLuint& _n)
	{
		assert(_c != 0);
		assert(_n == 0);
		assert(MultiObject || (_c == 1));
		ObjectOps::_init(_c, _n);
		assert(_n != 0);
	}

	template <typename Kind>
	static inline void _do_init(GLsizei _c, GLuint& _n, Kind _k)
	{
		assert(_n == 0);
		assert(!MultiObject);
		ObjectOps::_init(_c, _n, _k);
		assert(_n != 0);
	}

	static inline void _do_cleanup(GLsizei _c, GLuint& _n)
	{
		assert(_c != 0);
		assert(_n != 0);
		assert(MultiObject || (_c == 1));
		ObjectOps::_cleanup(_c, _n);
		assert(::glGetError() == GL_NO_ERROR);
		assert((_n = 0) == 0);
	}

	static inline bool _type_ok(GLuint _name)
	{
		assert(_name != 0);
#if OGLPLUS_DONT_TEST_OBJECT_TYPE
		return true;
#else
		return ObjectOps::_is_x(_name) == GL_TRUE;
#endif
	}

	friend class Array<Object>;
public:
	Object(void)
	{
		_do_init(1, this->_name);
		assert(this->_name != 0);
		assert(_type_ok(this->_name));
	}

	Object(const char* desc)
	{
		_do_init(1, this->_name);
		assert(this->_name != 0);
		assert(_type_ok(this->_name));
		this->_register_desc(this->_name, desc);
	}

	Object(const String& desc)
	{
		_do_init(1, this->_name);
		assert(this->_name != 0);
		assert(_type_ok(this->_name));
		this->_register_desc(this->_name, desc);
	}

	Object(const Object&) = delete;

	Object(Object&& temp)
	{
		assert(this->_name == 0);
		assert(temp._name  != 0);
		this->_name = temp._release();
		assert(this->_name != 0);
		assert(temp._name  == 0);
		assert(_type_ok(this->_name));
	}

	template <typename _Object = Object>
	Object(typename _Object::Kind kind)
	{
		_do_init(1, this->_name, kind);
		assert(this->_name != 0);
		assert(_type_ok(this->_name));
	}

	template <typename _Object = Object>
	Object(
		typename _Object::Kind kind,
		const char* desc
	)
	{
		_do_init(1, this->_name, kind);
		assert(this->_name != 0);
		assert(_type_ok(this->_name));
		this->_register_desc(this->_name, desc);
	}

	template <typename _Object = Object>
	Object(
		typename _Object::Kind kind,
		const String& desc
	)
	{
		_do_init(1, this->_name, kind);
		assert(this->_name != 0);
		assert(_type_ok(this->_name));
		this->_register_desc(this->_name, desc);
	}

	~Object(void)
	{
		if(this->_name != 0)
		{
			assert(_type_ok(this->_name));
			this->_unregister_desc(this->_name);
			_do_cleanup(1, this->_name);
		}
	}

	const String& Description(void) const
	{
		return this->_get_desc(this->_name);
	}
};

template <class ObjectOps, bool MultiObject>
class Managed<Object<ObjectOps, MultiObject> >
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

	~Managed(void)
	{
		FriendOf<ObjectOps>::SetName(*this, 0);
	}
};

} // namespace oglplus

#endif // include guard
