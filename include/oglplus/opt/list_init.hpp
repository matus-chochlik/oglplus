/**
 *  @file oglplus/opt/list_init.hpp
 *  @brief Helper classes and function for compile-time container initialization
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_OPT_LIST_INIT_HPP
#define OGLPLUS_OPT_LIST_INIT_HPP

#include <oglplus/config.hpp>

#include <array>

namespace oglplus {
namespace aux {

template <typename T, std::size_t I>
class ListInitializerBase
{
private:
	T _value;
	const ListInitializerBase<T, I-1>* _prev;

	friend class ListInitializerBase<T, I+1>;
protected:
	template <typename RandomAccessContainer>
	void _init(RandomAccessContainer& dest) const
	{
		dest[I] = _value;
		_prev->_init(dest);
	}

	ListInitializerBase(T value, const ListInitializerBase<T, I-1>* prev)
	 : _value(value)
	 , _prev(prev)
	{ }
};

template <typename T>
class ListInitializerBase<T, 0>
{
private:
	T _value;

	friend class ListInitializerBase<T, 1>;

protected:
	template <typename RandomAccessContainer>
	void _init(RandomAccessContainer& dest) const
	{
		dest[0] = _value;
	}

	ListInitializerBase(T value)
	 : _value(value)
	{ }
};

template <typename T, std::size_t I>
class ListInitializer
 : public ListInitializerBase<T, I>
{
private:
	typedef ListInitializerBase<T, I> _Base;

	friend class ListInitializer<T, I-1>;

	ListInitializer(T value, const ListInitializer<T, I-1>* prev)
	 : _Base(value, prev)
	{ }

	// non copyable
	ListInitializer(const ListInitializer&);
public:
	ListInitializer(T value)
	 : _Base(value)
	{ }

	ListInitializer(ListInitializer&& temp)
	 : _Base(temp)
	{ }

	ListInitializer<T, I+1> operator()(T value) const
	{
		return ListInitializer<T, I+1>(value, this);
	}

	std::array<T, I+1> Get(void) const
	{
		std::array<T, I+1> result;
		this->_init(result);
		return result;
	}

	template <typename RandomAccessContainer>
	std::vector<T> As(void) const
	{
		RandomAccessContainer result;
		result.resize(I+1);
		this->_init(result);
		return std::move(result);
	}
};

} // namespace aux

template <typename T>
class ListOf
 : public aux::ListInitializer<T, 0>
{
public:
	ListOf(T value)
	 : aux::ListInitializer<T, 0>(value)
	{ }
};

template <typename T>
inline aux::ListInitializer<T, 0> List(T value)
{
	return aux::ListInitializer<T, 0>(value);
}

} // namespace oglplus

#endif // include guard
