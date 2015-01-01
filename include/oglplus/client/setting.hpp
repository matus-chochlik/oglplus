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
	T _prev;

	friend class SettingStack<T, P>;

	SettingHolder(void)
	noexcept
	 : _pstk(nullptr)
	{ }

	SettingHolder(SettingStack<T, P>& stk, T prev)
	noexcept
	 : _pstk(&stk)
	 , _prev(prev)
	{ }

	SettingHolder(const SettingHolder&)/* = delete*/;
public:
	SettingHolder(SettingHolder&& tmp)
	noexcept
	 : _pstk(tmp._pstk)
	 , _prev(tmp._prev)
	{
		tmp._pstk = nullptr;
	}

	~SettingHolder(void)
	noexcept
	{
		if(_pstk)
		{
			_pstk->_set(_prev);
		}
	}

	void Pop(void)
	noexcept
	{
		assert(_pstk);
		_pstk->_set(_prev);
		_pstk = nullptr;
	}

	explicit
	operator bool (void) const
	noexcept
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
	T _curr;

	friend class SettingHolder<T, P>;
protected:
	inline
	T _get(void) const
	noexcept
	{
		return _curr;
	}

	bool _set(T value)
	{
		assert(_apply);

		if(_curr != value)
		{
			T prev = _curr;
			_curr = value;

			try { _apply(_curr, _param); }
			catch(...)
			{
				_curr = prev;
				throw;
			}
			return true;
		}
		return false;
	}

	SettingHolder<T, P> _push(T value)
	{
		T prev = _curr;
		if(_set(value))
		{
			return SettingHolder<T, P>(*this, prev);
		}
		return SettingHolder<T, P>();
	}
protected:
	SettingStack(T (*query)(P), void(*apply)(T, P), P param = P())
	 : _apply(apply)
	 , _param(param)
	{
		try { _curr = query(_param); }
		catch(Error&){ }
	}
public:
	typedef SettingHolder<T, P> Holder;

	inline
	Holder Push(T value)
	{
		return _push(value);
	}

	template <typename ... A>
	inline
	Holder Push(A&& ... a)
	{
		return _push(T(std::forward<A>(a)...));
	}

	inline
	typename std::vector<T>::const_reference
	Get(void) const
	noexcept
	{
		return _curr;
	}

	inline
	void Set(T value)
	{
		_set(value);
	}

	template <typename ... A>
	inline
	void Set(A&& ... a)
	{
		_set(T(std::forward<A>(a)...));
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

	template <typename ... A>
	inline
	Holder Push(A&& ... a)
	{
		_zero().Push(std::forward<A>(a)...);
	}

	inline
	typename std::vector<T>::const_reference
	Get(void) const
	noexcept
	{
		return _zero().Get();
	}

	inline
	void Set(T value)
	{
		_zero().Set(value);
	}

	template <typename ... A>
	inline
	void Set(A&& ... a)
	{
		_zero().Set(std::forward<A>(a)...);
	}
};

} // namespace client
} // namespace oglplus

#endif // include guard
