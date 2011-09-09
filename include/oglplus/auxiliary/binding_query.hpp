/**
 *  @file oglplus/auxiliary/binding_query.hpp
 *  @brief Helper class for getting the OpenGL name of object bound to a target
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_BINDING_QUERY_1107121519_HPP
#define OGLPLUS_AUX_BINDING_QUERY_1107121519_HPP

#include <cassert>

namespace oglplus {

template <class Object>
class BindingQuery
{
public:
	static GLuint QueryBinding(typename Object::Target target)
	{
		GLint result = 0;
		GLenum query = Object::_binding_query(target);
		if(query != 0) ::glGetIntegerv(query, &result);
		assert(result >= 0);
		return GLuint(result);
	}
};

} // namespace oglplus

#endif // include guard
