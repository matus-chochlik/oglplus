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

template <typename T, typename P>
class SettingStack;

template <typename T, typename P>
class SettingHolder
{
private:
	SettingStack<T, P>* _pstk;

	friend class SettingStack<T, P>;

	SettingHolder(void)
	OGLPLUS_NOEXCEPT(true)
	 : _pstk(nullptr)
	{ }

	SettingHolder(SettingStack<T, P>& stk)
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

	OGLPLUS_EXPLICIT
	operator bool (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _pstk != nullptr;
	}
};

template <typename T, typename P>
class SettingStack
{
private:
	void (*_apply)(T, P);
	P _param;
	std::vector<T> _stk;

	friend class SettingHolder<T, P>;
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
		_apply(_stk.back(), _param);
		// aborts if restoring throws
	}

	SettingHolder<T, P> _push(T value)
	{
		assert(!_stk.empty());
		assert(_apply);

		if(_stk.back() != value)
		{
			_stk.push_back(value);
			try { _apply(value, _param); }
			catch(...)
			{
				_pop();
				throw;
			}

			return SettingHolder<T, P>(*this);
		}
		return SettingHolder<T, P>();
	}

	void _set(T value)
	{
		assert(!_stk.empty());
		assert(_apply);

		T prev = _stk.back();

		if(prev != value)
		{
			_stk.back() = value;
			try { _apply(value, _param); }
			catch(...)
			{
				_stk.back() = prev;
				throw;
			}
		}
	}
protected:
	SettingStack(T (*query)(P), void(*apply)(T, P), P param = P())
	 : _apply(apply)
	 , _param(param)
	{
		try { _init(query(_param)); }
		catch(Error&){ }
	}
public:
	inline
	void Reserve(std::size_t n)
	{
		_stk.reserve(n);
	}

	typedef SettingHolder<T, P> Holder;

	inline
	Holder Push(T value)
	{
		return _push(value);
	}

	inline
	T Get(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _top();
	}

	inline
	void Set(T value)
	OGLPLUS_NOEXCEPT(true)
	{
		return _set(value);
	}
};


template <typename Derived, typename T>
class SettingStackIndexed
{
private:
	std::vector<Derived> _indexed;
protected:
	Derived& _zero(void)
	{
		assert(!_indexed.empty());
		return _indexed[0];
	}

	const Derived& _zero(void) const
	{
		assert(!_indexed.empty());
		return _indexed[0];
	}
public:
	SettingStackIndexed(void)
	{
		_indexed.emplace_back(0);
	}

	Derived& Indexed(std::size_t index)
	{
		for(std::size_t i=_indexed.size(); i<=index; ++i)
		{
			_indexed.emplace_back(GLuint(i));
		}
		return _indexed[index];
	}

	inline
	Derived&
	operator [] (std::size_t index)
	{
		return Indexed(index);
	}

	typedef SettingHolder<T, GLuint> Holder;

	inline
	Holder Push(T value)
	{
		return _zero().Push(value);
	}

	inline
	T Get(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _zero().Get();
	}

	inline
	void Set(T value)
	OGLPLUS_NOEXCEPT(true)
	{
		return _zero().Set(value);
	}
};

} // namespace client
} // namespace oglplus

#endif // include guard
