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
#include <cassert>

#if OGLPLUS_NO_OBJECT_NAMES == 0
#include <map>
#endif

namespace oglplus {

template <class ObjectOps>
class ObjectDescRegistry
{
private:
#if OGLPLUS_NO_OBJECT_NAMES == 0
	typedef ::std::map<GLuint, ::std::string> _desc_map;
	static _desc_map& _storage(void)
	{
		static _desc_map _store;
		return _store;
	}
#endif
protected:
	static void _register_desc(GLuint name, const std::string& desc)
	{
#if OGLPLUS_NO_OBJECT_NAMES == 0
		assert(name != 0);
		assert(_storage().find(name) == _storage().end());
		_storage().insert(typename _desc_map::value_type(name, desc));
#endif
	}

	static void _unregister_desc(GLuint name)
	{
#if OGLPLUS_NO_OBJECT_NAMES == 0
		assert(name != 0);
		_storage().erase(name);
#endif
	}

	static const ::std::string& _get_desc(GLuint name)
	{
		static ::std::string nodesc;
#if OGLPLUS_NO_OBJECT_NAMES == 0
		assert(name != 0);
		auto pos = _storage().find(name);
		if(pos != _storage().end()) return pos->second;
#endif
		return nodesc;
	}
};


template <class Object>
class Array;

template <class Object>
class Managed;

// Helper base class for OpenGL object wrappers
/*
 *  .note Do not use this class directly, use the derived classes instead.
 */
template <class ObjectOps, bool MultiObject>
class Object
 : public ObjectOps
 , public ObjectDescRegistry<ObjectOps>
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

	Object(const ::std::string& desc)
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
		const ::std::string& desc
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

	const ::std::string& Description(void) const
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
