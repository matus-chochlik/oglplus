/**
 *  @file oglplus/auxiliary/obj_desc.hpp
 *  @brief Declaration of Object description
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_OBJ_DESC_1107121519_HPP
#define OGLPLUS_AUX_OBJ_DESC_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/string.hpp>
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
		GLenum type,
		GLuint name,
		ObjectDesc&& desc
	);

	static void _do_unregister_desc(
		_desc_map& storage,
		_desc_map& archive,
		GLenum type,
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

template <class ObjectOps>
class ObjectDescRegistry
#if !OGLPLUS_NO_OBJECT_DESCS
 : public ObjectDescRegistryBase
#endif
{
private:
#if !OGLPLUS_NO_OBJECT_DESCS
	typedef ObjectDescRegistryBase _base;
	typedef ::std::map<GLuint, String> _desc_map;

	static _desc_map& _storage(void)
	{
		return ObjectDescRegistryStorage(ObjectTypeId<ObjectOps>::value);
	}

	static _desc_map& _archive(void)
	{
		return ObjectDescRegistryArchive(ObjectTypeId<ObjectOps>::value);
	}
#endif
protected:
	static void _register_desc(GLenum type, GLuint name, ObjectDesc&& desc)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true) { (void)type; (void)name; (void)desc; }
#else
	{
		_base::_do_register_desc(
			_storage(),
			type,
			name,
			std::move(desc)
		);
	}
#endif

	static void _unregister_desc(GLenum type, GLuint name)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true) { (void)type; (void)name; }
#else
	{
		_base::_do_unregister_desc(
			_storage(),
			_archive(),
			type,
			name
		);
	}
#endif

public:
	// internal implementation detail. do not use directly
	static void _purge_archive(void)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true) { }
#else
	{
		_base::_do_purge_archive(_archive());
	}
#endif

	// internal implementation detail. do not use directly
	static const String& _get_desc(GLuint name)
#if OGLPLUS_NO_OBJECT_DESCS
	OGLPLUS_NOEXCEPT(true) { (void)name; return aux::EmptyString(); }
#else
	{
		return _base::_do_get_desc(_storage(), _archive(), name);
	}
#endif
};

} // namespace aux
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/auxiliary/obj_desc.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
