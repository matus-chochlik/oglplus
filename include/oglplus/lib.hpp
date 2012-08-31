/**
 *  @file oglplus/lib.hpp
 *  @brief All-in-one Include file for the separatelly-built library
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_LIB_1208310818_HPP
#define OGLPLUS_LIB_1208310818_HPP

#include <oglplus/config.hpp>
#include <oglplus/string.hpp>
#include <oglplus/fwd.hpp>

#include <oglplus/auxiliary/utf8.hpp>
#include <oglplus/auxiliary/base_range.hpp>

#include <map>

namespace oglplus {
namespace aux {

::std::map<GLuint, String>& ObjectDescRegistryStorage(int id)
{
	static ::std::map<int, ::std::map<GLuint, String> > _maps;
	return _maps[id];
}

::std::map<GLuint, String>& ObjectDescRegistryArchive(int id)
{
	static ::std::map<int, ::std::map<GLuint, String> > _maps;
	return _maps[id];
}

} // namespace aux

bool ValidString(const GLchar* begin, const GLchar* end)
{
	return aux::ValidUTF8(begin, end);
}

#ifndef OGLPLUS_IMPLEMENTING_LIBRARY
#define OGLPLUS_IMPLEMENTING_LIBRARY
#endif

// EnumValueName implementations
#include <oglplus/lib/enum_value_name.ipp>
// EnumValueRange implementations
#include <oglplus/lib/enum_value_range.ipp>

#undef OGLPLUS_IMPLEMENTING_LIBRARY

} // namespace oglplus

#endif // include guard
