/**
 *  @file oglplus/extension.hpp
 *  @brief Funcions and classes for handling and wrapping OpenGL extensions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXTENSION_1203031825_HPP
#define OGLPLUS_EXTENSION_1203031825_HPP

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>

namespace oglplus {

inline void RequireExtension(const GLchar* name, bool available)
{
	if(!available)
	{
		oglplus::HandleError(
			GL_INVALID_OPERATION,
			"Missing extension",
			OGLPLUS_ERROR_INFO_STR(name),
			oglplus::Error::PropertyMap()
		);
	}
}

#if OGLPLUS_USE_GLEW
#define OGLPLUS_EXTENSION_AVAILABLE(VENDOR,EXTENSION) \
	(GLEW_ ## VENDOR ## _ ## EXTENSION)
#else
// TODO
#define OGLPLUS_EXTENSION_AVAILABLE(VENDOR,EXTENSION) true
#endif

#define OGLPLUS_REQUIRE_EXTENSION(VENDOR, EXTENSION) \
	::oglplus::RequireExtension( \
		#VENDOR "_" #EXTENSION, \
		OGLPLUS_EXTENSION_AVAILABLE(VENDOR, EXTENSION) \
	)

#define OGLPLUS_EXTENSION_CLASS(VENDOR, EXTENSION) \
	VENDOR ## _ ## EXTENSION(void) \
	{ \
		OGLPLUS_REQUIRE_EXTENSION(VENDOR, EXTENSION); \
	} \
	static bool Available(void) \
	{ \
		return OGLPLUS_EXTENSION_AVAILABLE(VENDOR, EXTENSION); \
	}

} // namespace oglplus

#endif // include guard
