/**
 *  @file oglplus/client/common.hpp
 *  @brief Client context utilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_COMMON_1412071213_HPP
#define OGLPLUS_CLIENT_COMMON_1412071213_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/fwd.hpp>
#include <vector>
#include <cassert>

namespace oglplus {
namespace client {
namespace aux {

template <typename T>
class SettingPopper
{
private:
	std::vector<T>* _pstk;
	void (*_pop)(std::vector<T>&);
public:
	SettingPopper(
		std::vector<T>& stk,
		void (*pop)(std::vector<T>&)
	) OGLPLUS_NOEXCEPT(true)
	 : _pstk(&stk)
	 , _pop(pop)
	{ }

	void Pop(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_pstk);
		assert(_pop);

		_pop(*_pstk);
	}
};

} // namespace aux

template <typename T>
class SettingHolder
{
private:
	const aux::SettingPopper<T>* _pppr;

	SettingHolder(const SettingHolder&)/* = delete*/;
public:
	SettingHolder(void)
	OGLPLUS_NOEXCEPT(true)
	 : _pppr(nullptr)
	{ }

	SettingHolder(const aux::SettingPopper<T>& ppr)
	OGLPLUS_NOEXCEPT(true)
	 : _pppr(&ppr)
	{ }

	SettingHolder(SettingHolder&& tmp)
	OGLPLUS_NOEXCEPT(true)
	 : _pppr(tmp._pppr)
	{
		tmp._pppr = nullptr;
	}

	~SettingHolder(void)
	OGLPLUS_NOEXCEPT(true)
	{
		if(_pppr)
		{
			_pppr->Pop();
		}
	}

	void Release(void)
	OGLPLUS_NOEXCEPT(true)
	{
		if(_pppr)
		{
			_pppr->Pop();
			_pppr = nullptr;
		}
	}
};

} // namespace client
} // namespace oglplus

#endif // include guard
