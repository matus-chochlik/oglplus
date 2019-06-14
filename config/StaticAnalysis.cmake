#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#

if(OGLPLUS_WITH_CLANG_TIDY)
	find_program(
		CLANG_TIDY_PROG
		NAMES clang-tidy-7 clang-tidy
		DOC "Path to clang-tidy executable"
	)

	file(
		READ
		"${PROJECT_SOURCE_DIR}/config/clang-tidy-filter.json"
		CLANG_TIDY_FILTER
	)

	if(CLANG_TIDY_PROG)
		set(
			INVOKE_CLANG_TIDY
			"${CLANG_TIDY_PROG}"
			"-line-filter=${CLANG_TIDY_FILTER}"
		)
	endif()
endif()
