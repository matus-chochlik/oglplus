/**
 *  @file oglplus/error/outcome.hpp
 *  @brief Class combining a return value and deferred error handler
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ERROR_OUTCOME_1405082311_HPP
#define OGLPLUS_ERROR_OUTCOME_1405082311_HPP

#include <oglplus/error/deferred_handler.hpp>
#include <cassert>

namespace oglplus {

template <typename T>
class PositiveOutcome;

template <typename T>
class NegativeOutcome;

class BaseOutcome
{
protected:
	DeferredHandler _error;

	BaseOutcome(void) = default;

	BaseOutcome(BaseOutcome&&) = default;

	BaseOutcome(DeferredHandler&& handler)
	 : _error(std::move(handler))
	{ }
public:
	/// Return true if there was no error, false otherwise
	bool Done(void) const
	{
		return !_error;
	}

	// Dismisses the error handler and returns true if there was no error
	bool DoneWithoutError(void)
	{
		return !_error.cancel();
	}

	DeferredHandler ReleaseHandler(void)
	noexcept
	{
		return std::move(_error);
	}
};

template <typename T>
class Outcome
 : public BaseOutcome
{
protected:
	T _value;
public:
	Outcome(Outcome&&) = default;

	Outcome(T&& value)
	noexcept
	 : _value(std::move(value))
	{ }

	Outcome(DeferredHandler&& handler)
	 : BaseOutcome(std::move(handler))
	{ }

	/// Returns stored value or cancels the error and returns the parameter
	const T& ValueOr(const T& value)
	{
		return _error.cancel()?value:_value;
	}
};

template <>
class Outcome<void>
 : public BaseOutcome
{
public:
	Outcome(Outcome&&) = default;

	Outcome(DeferredHandler&& handler)
	 : BaseOutcome(std::move(handler))
	{ }
};

/// Stores a reference to T or a deferred error handler
/** If an instance of Outcome<T&> stores an error handler
 *  and it is not dismissed, then the deferred error handler
 *  is invoked in the dectructor.
 */
template <typename T>
class Outcome<T&>
 : public BaseOutcome
{
protected:
	T* _ptr;
public:
	Outcome(Outcome&&) = default;

	Outcome(T& ref)
	noexcept
	 : _ptr(&ref)
	{ }

	Outcome(DeferredHandler handler)
	 : BaseOutcome(std::move(handler))
	 , _ptr(nullptr)
	{ }

	Outcome(DeferredHandler handler, T& ref)
	noexcept
	 : BaseOutcome(std::move(handler))
	 , _ptr(&ref)
	{ }

	DeferredHandler ReleaseHandler(void)
	noexcept
	{
		return std::move(_error);
	}

	/// Trigger the error handler if any or return the stored reference
	T& Then(void)
	{
		_error.trigger();
		assert(_ptr != nullptr);
		return *_ptr;
	}
};

template <typename T>
class PositiveOutcome
 : public Outcome<T>
{
public:
	PositiveOutcome(Outcome<T>&& base)
	noexcept
	 : Outcome<T>(std::move(base))
	{ }

	explicit
	operator bool (void) const
	noexcept
	{
		return !this->_error;
	}

	bool operator ! (void) const
	noexcept
	{
		return bool(this->_error);
	}
};

template <typename T>
class NegativeOutcome
 : public Outcome<T>
{
public:
	NegativeOutcome(NegativeOutcome&&) = default;

	NegativeOutcome(Outcome<T>&& base)
	noexcept
	 : Outcome<T>(std::move(base))
	{ }

	explicit
	operator bool (void) const
	noexcept
	{
		return bool(this->_error);
	}

	bool operator ! (void) const
	noexcept
	{
		return !this->_error;
	}
};

template <typename T>
static inline
PositiveOutcome<T> Succeeded(Outcome<T>&& outcome)
noexcept
{
	return std::move(outcome);
}

template <typename T>
static inline
NegativeOutcome<T> Failed(Outcome<T>&& outcome)
noexcept
{
	return std::move(outcome);
}

} // namespace oglplus

#endif // include guard
