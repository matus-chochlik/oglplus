/**
 *  @file oglplus/os/semaphore.hpp
 *  @brief Wrapper for OS semaphores
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef UTILS_OGLPLUS_OS_SEMAPHORE_1203040931_HPP
#define UTILS_OGLPLUS_OS_SEMAPHORE_1203040931_HPP

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdexcept>

namespace oglplus {
namespace os {

class Semaphore
{
private:
	int _sem;
	bool _master;

	void _op(int diff) const
	{
		struct ::sembuf param;
		param.sem_num = 0;
		param.sem_op = diff;
		param.sem_flg = SEM_UNDO;
		if(::semop(_sem, &param, 1) < 0)
			throw std::runtime_error("Semaphore operation failed");
	}
public:
	Semaphore(::key_t key, unsigned max = 1, bool master = false)
	 : _sem(::semget(key, 1, 0644 | IPC_CREAT | (master?IPC_EXCL:0)))
	 , _master(master)
	{
		if(_sem < 0)
			throw std::runtime_error("Semaphore construction failed");
		int initial = max;
		if(::semctl(_sem, 0, SETVAL, initial) < 0)
			throw std::runtime_error("Semaphore initialization failed");
	}

	Semaphore(const Semaphore&) = delete;

	~Semaphore(void)
	{
		if(_master) ::semctl(_sem, 0, IPC_RMID);
	}

	void Wait(void) const
	{
		_op(-1);
	}

	void Release(void) const
	{
		_op(+1);
	}
};

class CriticalSection
{
private:
	Semaphore _sem;
public:
	CriticalSection(key_t key)
	 : _sem(key)
	{
		_sem.Wait();
	}

	CriticalSection(const CriticalSection&) = delete;

	~CriticalSection(void)
	{
		_sem.Release();
	}
};

} // namespace os
} // namespace oglplus

#endif // include guard
