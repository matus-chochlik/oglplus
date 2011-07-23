/**
 *  .file oglplus/auxiliary/info_log.hpp
 *  .brief Helper function getting the OpenGL info logs
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_INFO_LOG_1107121519_HPP
#define OGLPLUS_AUX_INFO_LOG_1107121519_HPP

#include <oglplus/error.hpp>
#include <string>
#include <vector>

namespace oglplus {
namespace aux {

inline std::string GetInfoLog(
	GLuint object_name,
	void (&GetObjectiv)(GLuint, GLenum, GLint*),
	void (&GetObjectInfoLog)(GLuint, GLsizei, GLsizei*, GLchar*),
	const char* name_GetObjectiv,
	const char* name_GetObjectInfoLog
)
{
	int length = 0;
	GetObjectiv(object_name, GL_INFO_LOG_LENGTH, &length);
	ThrowOnError(OGLPLUS_ERROR_INFO_STR(name_GetObjectiv));
	if(length > 0)
	{
		GLsizei real_length = 0;
		std::vector<GLchar> buffer(length);
		GetObjectInfoLog(
			object_name,
			buffer.size(),
			&real_length,
			buffer.data()
		);
		ThrowOnError(OGLPLUS_ERROR_INFO_STR(name_GetObjectInfoLog));
		return std::string(buffer.data(), buffer.size());
	}
	else return std::string();
}

} // namespace aux
} // namespace oglplus

#endif // include guard
