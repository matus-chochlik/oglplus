/**
 *  @file oglplus/util/tagged.hpp
 *  @brief Tagged type helper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_UTIL_TAGGED_1405062241_HPP
#define OGLPLUS_UTIL_TAGGED_1405062241_HPP

#include <utility>
#include <type_traits>

namespace oglplus {

template <typename T, typename IsScalar>
class TaggedBase;

template <typename T>
class TaggedBase<T, std::true_type>
{
private:
	T _value;
public:
	TaggedBase(T value)
	 : _value(value)
	{ }

	operator T(void) const
	{
		return _value;
	}
};

template <typename T>
class TaggedBase<T, std::false_type>
 : public T
{
public:
	TaggedBase(T&& v)
	 : T(std::move(v))
	{ }
};

template <typename Tag, typename T>
class Tagged
 : public TaggedBase<T, typename std::is_scalar<T>::type>
{
public:
	Tagged(T&& v)
	 : TaggedBase<T, typename std::is_scalar<T>::type>(std::move(v))
	{ }
};

template <typename Tg, typename T>
inline Tagged<Tg, T> Tag(T&& value)
{
	return Tagged<Tg, T>(std::forward<T>(value));
}

} // namespace oglplus

#endif // include guard
