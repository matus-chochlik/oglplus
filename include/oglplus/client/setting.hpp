/**
 *  @file oglplus/client/setting.hpp
 *  @brief Client context utilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_SETTING_1412071213_HPP
#define OGLPLUS_CLIENT_SETTING_1412071213_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/fwd.hpp>
#include <vector>
#include <cassert>

namespace oglplus {
namespace client {

template <typename T>
class SettingStack;

template <typename T>
class SettingHolder
{
private:
	SettingStack<T>* _pstk;

	friend class SettingStack<T>;

	SettingHolder(void)
	OGLPLUS_NOEXCEPT(true)
	 : _pstk(nullptr)
	{ }

	SettingHolder(SettingStack<T>& stk)
	OGLPLUS_NOEXCEPT(true)
	 : _pstk(&stk)
	{ }

	SettingHolder(const SettingHolder&)/* = delete*/;
public:
	SettingHolder(SettingHolder&& tmp)
	OGLPLUS_NOEXCEPT(true)
	 : _pstk(tmp._pstk)
	{
		tmp._pstk = nullptr;
	}

	~SettingHolder(void)
	OGLPLUS_NOEXCEPT(true)
	{
		if(_pstk)
		{
			_pstk->_pop();
		}
	}

	void Pop(void)
	OGLPLUS_NOEXCEPT(true)
	{
		if(_pstk)
		{
			_pstk->_pop();
			_pstk = nullptr;
		}
	}
};

template <typename T>
class SettingStack
{
private:
	void (*_apply)(T);
	std::vector<T> _stk;

	friend class SettingHolder<T>;
protected:
	void _init(T value)
	{
		assert(_stk.empty());
		_stk.push_back(value);
	}

	T _top(void) const
	{
		assert(!_stk.empty());
		return _stk.back();
	}

	void _pop(void)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(!_stk.empty());
		assert(_apply);

		_stk.pop_back();
		_apply(_stk.back());
		// aborts if restoring throws
	}

	SettingHolder<T> _push(T value)
	{
		assert(!_stk.empty());
		assert(_apply);

		if(_stk.back() != value)
		{
			_stk.push_back(value);
			try { _apply(value); }
			catch(...)
			{
				_pop();
				throw;
			}

			return SettingHolder<T>(*this);
		}
		return SettingHolder<T>();
	}

	void _set(T value)
	{
		assert(!_stk.empty());
		assert(_apply);

		T prev = _stk.back();

		if(prev != value)
		{
			_stk.back() = value;
			try { _apply(value); }
			catch(...)
			{
				_stk.back() = prev;
				throw;
			}
		}
	}
protected:
	SettingStack(void(*apply)(T))
	 : _apply(apply)
	{ }
public:
	void Reserve(std::size_t n)
	{
		_stk.reserve(n);
	}
};

} // namespace client
} // namespace oglplus

#endif // include guard
