/**
 *  @file oglplus/ext/AMD_performance_monitor.hpp
 *  @brief Wrapper for the AMD_performance_monitor extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXT_AMD_PERFORMANCE_MONITOR_1203031902_HPP
#define OGLPLUS_EXT_AMD_PERFORMANCE_MONITOR_1203031902_HPP

#include <oglplus/extension.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTAMDON_ONLY || GL_AMD_performance_monitor

class PerfMonitorGroupAMD
{
};


/// Wrapper for the AMD_performance_monitor extension
/**
 *  @glsymbols
 *  @glextref{AMD,performance_monitor}
 *
 *  @ingroup extensions
 */
class AMD_performance_monitor
{
public:

	OGLPLUS_EXTENSION_CLASS(AMD, performance_monitor)

};
#endif

} // namespace oglplus

#endif // include guard
