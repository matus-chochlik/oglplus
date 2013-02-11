/**
 *  @file oglplus/os/semaphore.hpp
 *  @brief Wrapper for OS semaphores
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
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

	static int _init_sem(::key_t key, int max, bool master)
	{
		int flg = 0600;
		if(master) flg |= IPC_EXCL;
		int result = ::semget(key, 1, flg);
		if(result < 0)
		{
			result = ::semget(key, 1, flg | IPC_CREAT);
			if(result < 0)
			{
				throw std::runtime_error(
					"Semaphore construction failed"
				);
			}
			if(::semctl(result, 0, SETVAL, max) < 0)
			{
				throw std::runtime_error(
					"Semaphore initialization failed"
				);
			}
		}
		return result;
	}
public:
	Semaphore(::key_t key, int max = 1, bool master = false)
	 : _sem(_init_sem(key, max, master))
	 , _master(master)
	{ }

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
	CriticalSection(const CriticalSection&);
public:
	CriticalSection(key_t key)
	 : _sem(key)
	{
		_sem.Wait();
	}

	~CriticalSection(void)
	{
		_sem.Release();
	}
};

} // namespace os
} // namespace oglplus

#endif // include guard
