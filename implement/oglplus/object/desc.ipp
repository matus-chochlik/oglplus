/**
 *  @file oglplus/object/desc.ipp
 *  @brief Implementation of Object string description
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#if !OGLPLUS_NO_OBJECT_DESC
#include <cassert>
#endif

namespace oglplus {
namespace aux {

#if !OGLPLUS_NO_OBJECT_DESC

OGLPLUS_LIB_FUNC
::std::map<unsigned, eagine::base::string>& ObjectDescRegistryStorage(int id)
noexcept // yes, we know that map::operator[] can throw
{
	static ::std::map<
		int,
		::std::map<unsigned, eagine::base::string>
	> _maps;
	return _maps[id];
}

OGLPLUS_LIB_FUNC
void ObjectDescRegistryBase::_do_register_desc(
	_desc_map& storage,
	unsigned name,
	ObjectDesc&& desc
)
{
	assert(storage.find(name) == storage.end());
	storage.insert(
		_desc_map::value_type(
			name,
			desc.str()
		)
	);
}

OGLPLUS_LIB_FUNC
void ObjectDescRegistryBase::_do_unregister_desc(
	_desc_map& storage,
	unsigned name
) noexcept // yes, we know that map::erase can throw
{
	if(!std::uncaught_exception())
	{
		auto pos = storage.find(name);
		if(pos != storage.end())
		{
			storage.erase(pos);
		}
	}
}

OGLPLUS_LIB_FUNC
eagine::base::cstrref ObjectDescRegistryBase::_do_get_desc(
	_desc_map& storage,
	unsigned name
) noexcept
{
	auto pos = storage.find(name);
	if(pos != storage.end()) return pos->second;
	return eagine::base::cstrref();
}

#endif // OGLPLUS_NO_OBJECT_DESC

} // namespace aux
} // namespace oglplus

