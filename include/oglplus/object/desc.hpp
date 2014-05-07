/**
 *  @file oglplus/object/desc.hpp
 *  @brief Declaration of Object description
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_DESC_1107121519_HPP
#define OGLPLUS_OBJECT_DESC_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/string/def.hpp>
#include <oglplus/fwd.hpp>

#if OGLPLUS_NO_OBJECT_DESCS == 0
#include <cassert>
#include <map>
#endif

namespace oglplus {

class ObjectDesc
{
private:
#if !OGLPLUS_NO_OBJECT_DESCS
	String _str;
#endif
public:
	ObjectDesc(void) { }

	ObjectDesc(String&& str)
#if !OGLPLUS_NO_OBJECT_DESCS
	 : _str(std::forward<String>(str))
#endif
	{
		OGLPLUS_FAKE_USE(str);
	}

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

#if !OGLPLUS_NO_OBJECT_DESCS
::std::map<GLuint, String>& ObjectDescRegistryStorage(int id);
::std::map<GLuint, String>& ObjectDescRegistryArchive(int id);
#endif

#if !OGLPLUS_NO_OBJECT_DESCS
class ObjectDescRegistryBase
{
private:
	typedef ::std::map<GLuint, String> _desc_map;
protected:
	static void _do_register_desc(
		_desc_map& storage,
		GLuint name,
		ObjectDesc&& desc
	);

	static void _do_unregister_desc(
		_desc_map& storage,
		_desc_map& archive,
		GLuint name
	);

	static void _do_purge_archive(_desc_map& archive);

	static const String& _do_get_desc(
		_desc_map& storage,
		_desc_map& archive,
		GLuint name
	);
};
#endif // !OGLPLUS_NO_OBJECT_DESCS

class ObjectDescRegistry
#if !OGLPLUS_NO_OBJECT_DESCS
 : public ObjectDescRegistryBase
#endif
{
private:
#if !OGLPLUS_NO_OBJECT_DESCS
	typedef ObjectDescRegistryBase _base;
	typedef ::std::map<GLuint, String> _desc_map;

	static _desc_map& _storage(int id)
	{
		return ObjectDescRegistryStorage(id);
	}

	static _desc_map& _archive(int id)
	{
		return ObjectDescRegistryArchive(id);
	}
#endif
public:
	// internal implementation detail. do not use directly
	static void _register_desc(int id, GLuint name, ObjectDesc&& desc)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true) { (void)id; (void)name; (void)desc; }
#else
	{
		_base::_do_register_desc(
			_storage(id),
			name,
			std::move(desc)
		);
	}
#endif

	// internal implementation detail. do not use directly
	static void _unregister_desc(int id, GLuint name)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true) { (void)id; (void)name; }
#else
	{
		_base::_do_unregister_desc(
			_storage(id),
			_archive(id),
			name
		);
	}
#endif

	// internal implementation detail. do not use directly
	static void _purge_archive(int id)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true) { (void)id; }
#else
	{
		_base::_do_purge_archive(_archive(id));
	}
#endif

	// internal implementation detail. do not use directly
	static const String& _get_desc(int id, GLuint name)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true)
	{
		(void)id;
		(void)name;
		return aux::EmptyString();
	}
#else
	{
		return _base::_do_get_desc(
			_storage(id),
			_archive(id),
			name
		);
	}
#endif
};

} // namespace aux

// TODO: return ObjectDesc
template <typename ObjTag>
inline const String& DescriptionOf(ObjectName<ObjTag> object)
{
	return aux::ObjectDescRegistry::_get_desc(
		ObjTag::value,
		GetGLName(object)
	);
}

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/object/desc.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
