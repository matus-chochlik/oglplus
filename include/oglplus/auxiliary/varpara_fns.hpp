/**
 *  .file oglplus/auxiliary/info_log.hpp
 *  .brief Helper tools for working with OpenGL function "overloads" for various types
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_VARPARA_FNS_1107121519_HPP
#define OGLPLUS_AUX_VARPARA_FNS_1107121519_HPP

#include <tuple>

namespace oglplus {

#define OGLPLUS_AUX_VARPARA_FNS(PREFIX, SUFFIX, SELECTOR, TYPE) \
	static decltype( \
		std::make_tuple( \
			::gl ## PREFIX ## 1 ## SUFFIX, \
			::gl ## PREFIX ## 2 ## SUFFIX, \
			::gl ## PREFIX ## 3 ## SUFFIX, \
			::gl ## PREFIX ## 4 ## SUFFIX  \
		) \
	) _fns_ ## SELECTOR(const TYPE*, ...) \
	{ \
		return std::make_tuple( \
			::gl ## PREFIX ## 1 ## SUFFIX, \
			::gl ## PREFIX ## 2 ## SUFFIX, \
			::gl ## PREFIX ## 3 ## SUFFIX, \
			::gl ## PREFIX ## 4 ## SUFFIX  \
		); \
	}

#define OGLPLUS_AUX_VARPARA_FNS_EXT(PREFIX, SUFFIX, EXT, SELECTOR, TYPE) \
	OGLPLUS_AUX_VARPARA_FNS(PREFIX, SUFFIX##EXT, SELECTOR, TYPE)

#define OGLPLUS_AUX_VARPARA_MAT_FNS(PREFIX, SUFFIX, SELECTOR, TYPE) \
	static decltype( \
		std::make_tuple( \
			std::make_tuple( \
				::gl ## PREFIX ## 2 ## SUFFIX, \
				::gl ## PREFIX ## 2x3 ## SUFFIX,  \
				::gl ## PREFIX ## 2x4 ## SUFFIX  \
			), \
			std::make_tuple( \
				::gl ## PREFIX ## 3x2 ## SUFFIX,  \
				::gl ## PREFIX ## 3 ## SUFFIX, \
				::gl ## PREFIX ## 3x4 ## SUFFIX  \
			), \
			std::make_tuple( \
				::gl ## PREFIX ## 4x2 ## SUFFIX, \
				::gl ## PREFIX ## 4x3 ## SUFFIX, \
				::gl ## PREFIX ## 4 ## SUFFIX  \
			) \
		) \
	) _fns_ ## SELECTOR(const TYPE*, ...) \
	{ \
		return std::make_tuple( \
			std::make_tuple( \
				::gl ## PREFIX ## 2 ## SUFFIX, \
				::gl ## PREFIX ## 2x3 ## SUFFIX,  \
				::gl ## PREFIX ## 2x4 ## SUFFIX  \
			), \
			std::make_tuple( \
				::gl ## PREFIX ## 3x2 ## SUFFIX,  \
				::gl ## PREFIX ## 3 ## SUFFIX, \
				::gl ## PREFIX ## 3x4 ## SUFFIX  \
			), \
			std::make_tuple( \
				::gl ## PREFIX ## 4x2 ## SUFFIX, \
				::gl ## PREFIX ## 4x3 ## SUFFIX, \
				::gl ## PREFIX ## 4 ## SUFFIX  \
			) \
		);\
	}

#define OGLPLUS_AUX_VARPARA_MAT_FNS_EXT(PREFIX, SUFFIX, EXT, SELECTOR, TYPE) \
	OGLPLUS_AUX_VARPARA_MAT_FNS(PREFIX, SUFFIX##EXT, SELECTOR, TYPE)

} // namespace oglplus

#endif // include guard
