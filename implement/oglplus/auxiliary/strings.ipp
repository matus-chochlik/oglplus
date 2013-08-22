/**
 *  @file oglplus/auxiliary/strings.ipp
 *  @brief Implementation of string helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {
namespace aux {

#if !OGLPLUS_NO_OBJECT_DESCS

OGLPLUS_LIB_FUNC ::std::map<GLuint, String>& ObjectDescRegistryStorage(int id)
{
	static ::std::map<int, ::std::map<GLuint, String> > _maps;
	return _maps[id];
}

OGLPLUS_LIB_FUNC ::std::map<GLuint, String>& ObjectDescRegistryArchive(int id)
{
	static ::std::map<int, ::std::map<GLuint, String> > _maps;
	return _maps[id];
}

#endif // OGLPLUS_NO_OBJECT_DESCS

} // namespace aux
} // namespace oglplus

