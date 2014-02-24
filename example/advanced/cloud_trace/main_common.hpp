/**
 *  @file advanced/cloud_trace/main_common.hpp
 *  @brief Declares common code shared by various main implementations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_TRACE_MAIN_COMMON_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_TRACE_MAIN_COMMON_1119071146_HPP

#include "render_data.hpp"

namespace oglplus {
namespace cloud_trace {

extern int do_run_main(int (*)(RenderData&), RenderData&);

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
