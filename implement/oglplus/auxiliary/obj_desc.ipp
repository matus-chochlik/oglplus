/**
 *  @file oglplus/auxiliary/obj_desc.ipp
 *  @brief Implementation of Object string description
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {
namespace aux {

#if !OGLPLUS_NO_OBJECT_DESCS

OGLPLUS_LIB_FUNC
::std::map<GLuint, String>& ObjectDescRegistryStorage(int id)
{
	static ::std::map<int, ::std::map<GLuint, String> > _maps;
	return _maps[id];
}

OGLPLUS_LIB_FUNC
::std::map<GLuint, String>& ObjectDescRegistryArchive(int id)
{
	static ::std::map<int, ::std::map<GLuint, String> > _maps;
	return _maps[id];
}

OGLPLUS_LIB_FUNC
void ObjectDescRegistryBase::_do_register_desc(
	_desc_map& storage,
	GLenum type,
	GLuint name,
	ObjectDesc&& desc
)
{
	OGLPLUS_FAKE_USE(type);
	assert(name != 0);
	assert(storage.find(name) == storage.end());
	storage.insert(
		_desc_map::value_type(
			name,
			desc.Release()
		)
	);
}

OGLPLUS_LIB_FUNC
void ObjectDescRegistryBase::_do_unregister_desc(
	_desc_map& storage,
	_desc_map& archive,
	GLenum type,
	GLuint name
)
{
	OGLPLUS_FAKE_USE(type);
	assert(name != 0);
	auto pos = storage.find(name);
	if(pos != storage.end())
	{
		if(std::uncaught_exception())
			archive.insert(*pos);
		storage.erase(pos);
	}
}

OGLPLUS_LIB_FUNC
void ObjectDescRegistryBase::_do_purge_archive(_desc_map& archive)
{
	archive.clear();
}

OGLPLUS_LIB_FUNC
const String& ObjectDescRegistryBase::_do_get_desc(
	_desc_map& storage,
	_desc_map& archive,
	GLuint name
)
{
	assert(name != 0);
	auto pos = storage.find(name);
	if(pos != storage.end()) return pos->second;
	pos = archive.find(name);
	if(pos != archive.end()) return pos->second;
	return EmptyString();
}

#endif // OGLPLUS_NO_OBJECT_DESCS

} // namespace aux
} // namespace oglplus

