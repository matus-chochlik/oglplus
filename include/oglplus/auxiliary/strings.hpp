/**
 *  @file oglplus/auxiliary/strings.hpp
 *  @brief Functions returning strings shared by various parts of the library,etc.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_STRINGS_1107121519_HPP
#define OGLPLUS_AUX_STRINGS_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/string.hpp>

#if OGLPLUS_NO_OBJECT_DESCS == 0
#include <cassert>
#include <map>
#endif

namespace oglplus {

namespace aux {

inline const String& EmptyString(void)
OGLPLUS_NOEXCEPT(true)
{
	static String empty;
	return empty;
}

} // namespace aux

class ObjectDesc
{
private:
#if !OGLPLUS_NO_OBJECT_DESCS
	String _str;
#endif
public:
	ObjectDesc(const GLchar* cstr)
#if !OGLPLUS_NO_OBJECT_DESCS
	 : _str(cstr)
#endif
	{
		OGLPLUS_FAKE_USE(cstr);
	}

	ObjectDesc(const StrLit& lit)
#if !OGLPLUS_NO_OBJECT_DESCS
	 : _str(lit.str())
#endif
	{
		OGLPLUS_FAKE_USE(lit);
	}

	ObjectDesc(const String& str)
#if !OGLPLUS_NO_OBJECT_DESCS
	 : _str(str)
#endif
	{
		OGLPLUS_FAKE_USE(str);
	}

	ObjectDesc(String&& str)
#if !OGLPLUS_NO_OBJECT_DESCS
	 : _str(std::forward<String>(str))
#endif
	{
		OGLPLUS_FAKE_USE(str);
	}

	ObjectDesc(void){ }

	ObjectDesc(ObjectDesc&& tmp)
#if !OGLPLUS_NO_OBJECT_DESCS
	 : _str(std::move(tmp._str))
#endif
	{
		OGLPLUS_FAKE_USE(tmp);
	}

	const String& Str(void)
	{
#if !OGLPLUS_NO_OBJECT_DESCS
		return _str;
#else
		return aux::EmptyString();
#endif
	}

#if !OGLPLUS_NO_OBJECT_DESCS
	String&& Release(void)
	{
		return std::move(_str);
	}
#endif
};

namespace aux {

template <class ObjectOps>
class ObjectDescRegistry
{
private:
#if !OGLPLUS_NO_OBJECT_DESCS
	typedef ::std::map<GLuint, String> _desc_map;
	static _desc_map& _storage(void)
	{
		static _desc_map _store;
		return _store;
	}

	static _desc_map& _archive(void)
	{
		static _desc_map _ar;
		return _ar;
	}
#endif
protected:
	static void _register_desc(GLuint name, ObjectDesc&& desc)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true)
#endif
	{
		OGLPLUS_FAKE_USE(name);
		OGLPLUS_FAKE_USE(desc);
#if !OGLPLUS_NO_OBJECT_DESCS
		assert(name != 0);
		assert(_storage().find(name) == _storage().end());
		_storage().insert(
			typename _desc_map::value_type(
				name,
				desc.Release()
			)
		);
#endif
	}

	static void _unregister_desc(GLuint name)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true)
#endif
	{
		OGLPLUS_FAKE_USE(name);
#if !OGLPLUS_NO_OBJECT_DESCS
		assert(name != 0);
		auto pos = _storage().find(name);
		if(pos != _storage().end())
		{
			if(std::uncaught_exception())
				_archive().insert(*pos);
			_storage().erase(pos);
		}
#endif
	}

public:
	// internal implementation detail. do not use directly
	static void _purge_archive(void)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true)
#endif
	{
#if !OGLPLUS_NO_OBJECT_DESCS
		_archive().clear();
#endif
	}

	// internal implementation detail. do not use directly
	static const String& _get_desc(GLuint name)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true)
#endif
	{
		OGLPLUS_FAKE_USE(name);
#if !OGLPLUS_NO_OBJECT_DESCS
		assert(name != 0);
		auto pos = _storage().find(name);
		if(pos != _storage().end()) return pos->second;
		pos = _archive().find(name);
		if(pos != _archive().end()) return pos->second;
#endif
		return aux::EmptyString();
	}
};

} // namespace aux
} // namespace oglplus

#endif // include guard
