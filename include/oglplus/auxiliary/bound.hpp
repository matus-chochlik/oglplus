/**
 *  @file oglplus/auxiliary/bound.hpp
 *  @brief Base class for OpenGL "bound" objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_BOUND_1107121519_HPP
#define OGLPLUS_AUX_BOUND_1107121519_HPP

namespace oglplus {

// A common base class for Bound<>
template <class Bindable>
class BoundBase
{
private:
	typename Bindable::Target _bind_target;
protected:
	BoundBase(Bindable& bindable, typename Bindable::Target target)
	 : _bind_target(target)
	{
		bindable.Bind(target);
	}
public:
	typename Bindable::Target BindTarget(void) const
	{
		return _bind_target;
	}
};

template <class Bindable>
class Bound;

template <class Bindable>
inline Bound<Bindable> Bind(Bindable& bindable, typename Bindable::Target target)
{
	return Bound<Bindable>(bindable, target);
}

} // namespace oglplus

#endif // include guard
