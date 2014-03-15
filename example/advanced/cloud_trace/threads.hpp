/**
 *  @file advanced/cloud_trace/threads.hpp
 *  @brief Declaration of thread-helper classes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_TRACE_THREADS_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_TRACE_THREADS_1119071146_HPP

#include <mutex>
#include <condition_variable>

namespace oglplus {
namespace cloud_trace {

class Semaphore
{
private:
	unsigned _value;
	std::mutex _mutex;
	std::condition_variable _cv;

	void _decr(void);
	void _incr(unsigned n);
public:
	Semaphore(unsigned initial = 0);

	void Wait(unsigned n = 1);
	void Signal(unsigned n = 1);
	bool Signalled(unsigned n = 1);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
