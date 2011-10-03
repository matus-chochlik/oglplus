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
{
	static String empty;
	return empty;
}

template <class ObjectOps>
class ObjectDescRegistry
{
private:
#if OGLPLUS_NO_OBJECT_DESCS == 0
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
	static void _register_desc(GLuint name, const char* desc)
	{
#if OGLPLUS_NO_OBJECT_DESCS == 0
		assert(name != 0);
		assert(desc != 0);
		assert(_storage().find(name) == _storage().end());
		_storage().insert(typename _desc_map::value_type(name, desc));
#endif
	}

	static void _register_desc(GLuint name, const String& desc)
	{
#if OGLPLUS_NO_OBJECT_DESCS == 0
		assert(name != 0);
		assert(_storage().find(name) == _storage().end());
		_storage().insert(typename _desc_map::value_type(name, desc));
#endif
	}

	static void _unregister_desc(GLuint name)
	{
#if OGLPLUS_NO_OBJECT_DESCS == 0
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
	{
#if OGLPLUS_NO_OBJECT_DESCS == 0
		_archive().clear();
#endif
	}

	// internal implementation detail. do not use directly
	static const String& _get_desc(GLuint name)
	{
#if OGLPLUS_NO_OBJECT_DESCS == 0
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
