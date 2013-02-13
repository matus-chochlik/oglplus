/**
 *  @file oglplus/example_mt.hpp
 *  @brief Declares a common utilities for multi-threaded examples
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef __OGLPLUS_EXAMPLE_EXAMPLE_MT_1119071146_HPP__
#define __OGLPLUS_EXAMPLE_EXAMPLE_MT_1119071146_HPP__

#include <cassert>

#include <queue>
#include <mutex>
#include <condition_variable>


namespace oglplus {

class ExampleSyncQueue
{
private:
	std::queue<Sync> sync_queue;
	std::mutex sync_mutex;
	std::condition_variable sync_cv;
	bool done;
public:
	ExampleSyncQueue(void)
	 : done(false)
	{ }

	~ExampleSyncQueue(void)
	{
		Cancel();
	}

	void Cancel(void)
	{
		std::unique_lock<std::mutex> l(sync_mutex);
		if(!done)
		{
			done = true;
			sync_cv.notify_all();
		}
	}

	void Push(Sync&& sync)
	{
		std::unique_lock<std::mutex> l(sync_mutex);
		sync_queue.emplace(std::move(sync));
		sync_cv.notify_all();
	}

	void Signal(void)
	{
		Push(Sync());
	}

	Sync Pop(void)
	{
		std::unique_lock<std::mutex> l(sync_mutex);
		while(sync_queue.empty() && !done) sync_cv.wait(l);
		Sync tmp(done?Sync():std::move(sync_queue.front()));
		if(!done) sync_queue.pop();
		return std::move(tmp);
	}

	void Wait(void)
	{
		Pop().Wait();
	}
};

} // namespace oglplus

#endif // include guard
