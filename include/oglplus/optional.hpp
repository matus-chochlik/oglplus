/**
 *  @file oglplus/optional.hpp
 *  @brief Template wrapper for Objects, making them optional
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OPTIONAL_1107121519_HPP
#define OGLPLUS_OPTIONAL_1107121519_HPP

#include <oglplus/config_compiler.hpp>

namespace oglplus {

/// Modifier that allows to create uninitialized Object(s)
/** The Optional template class is a modifier for @ref oglplus_object "Objects"
 *  and in contrast to Objects it does allow to construct uninitialized
 *  instances which can be initialized later.
 *
 *  An Optional<Object> can be used everywhere an Object could be
 *  used but it must be initialized (the IsInitialized() member function
 *  must return true), otherwise usage results in undefined behavior.
 *
 *  @ingroup modifier_classes
 */
template <class Object_>
class Optional
 : public Object_
{
public:
	/// Construction of an uninitialized instance
	/** The only things that can safely be done with
	 *  an uninitialized Optional<Object> is assignment,
	 *  moving, destruction and checking whether it is
	 *  initialized.
	 *
	 *  @see IsInitialized
	 *  @see Assign
	 */
	Optional(void)
	OGLPLUS_NOEXCEPT(true)
	 : Object_(typename Object_::Uninitialized_())
	{ }

	/// Construction of an initialized instance
	/** Initialized Optional<Object> can be used everywhere where
	 *  a plain Object could be used, furthermore Optional<Object>
	 *  can also be cleared (this brings it in uninitialized state)
	 *
	 *  @see IsInitialized
	 *  @see Clear
	 */
	Optional(Object_&& temp)
	OGLPLUS_NOEXCEPT(true)
	 : Object_(std::move(temp))
	{ }

	/// Move constructor
	Optional(Optional&& temp)
	OGLPLUS_NOEXCEPT(true)
	 : Object_(typename Object_::Uninitialized_())
	{
		this->_move_in_uninit(static_cast<Object_&&>(temp));
	}

	/// Returns true if the object is initialized, false otherwise
	/** The only things that can safely be done with
	 *  an uninitialized Optional<Object> is assignment,
	 *  moving, destruction and checking whether it is
	 *  initialized. On the other hand initialized
	 *  Optional<Object> can be used everywhere where
	 *  a plain Object could be used.
	 *
	 *  @see Assign
	 *  @see Clear
	 */
	bool IsInitialized(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return this->_is_initialized();
	}

	/// Assigns an initialized Object to this Optional<Object>
	/** After this the Optional<Object> is initialized.
	 *
	 *  @see Clear
	 *  @see IsInitialized
	 */
	void Assign(Object_&& temp)
	OGLPLUS_NOEXCEPT(true)
	{
		this->_cleanup_if_needed();
		this->_move_in(std::move(temp));
	}

	/// Clears this Optional<Object>
	/** After clearing, this Optional<Object> is uninitialized.
	 *
	 *  @see Assign
	 *  @see IsInitialized
	 */
	void Clear(void)
	OGLPLUS_NOEXCEPT(true)
	{
		this->_cleanup_if_needed();
	}
};

} // namespace oglplus

#endif // include guard
