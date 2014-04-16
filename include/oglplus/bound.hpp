/**
 *  @file oglplus/bound.hpp
 *  @brief OGLplus bound objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BOUND_1201190831_HPP
#define OGLPLUS_BOUND_1201190831_HPP

#include <oglplus/fwd.hpp>

namespace oglplus {

/// A common base class for Bound objects
/**
 *  @note Do not use directly, use @c Context::Bound or @c Context::Current
 *  instead.
 *
 *  @ingroup modifier_classes
 */
template <class Bindable, class BindableOps>
class BoundBase
 : public Bindable
{
private:
	typename Bindable::Target _bind_target;
protected:
	BoundBase(const Bindable& bindable, typename Bindable::Target target)
	 : Bindable(bindable)
	 , _bind_target(target)
	{ }
public:
	typename Bindable::Target BindTarget(void) const
	{
		return _bind_target;
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// Specializations of this template wrap functions of Bindable with bind target
/**
 *  @note Do not use directly, use @c Context::Bound or @c Context::Current
 *  instead.
 *
 *  @see Context::Bind()
 *  @see Context::Bound()
 *
 *  @ingroup utility_classes
 */
template <template <class, class> class Base, class BaseParam, class BindableOps>
class BoundTemplate
 : public Base<BaseParam, BindableOps>
{ };
#endif

/// A wraper that binds @ref oglplus_object "objects" to a specified target
/**
 *  @ref bound_objects make the usage of @ref oglplus_object "objects" that
 *  can be bound to a OpenGL binding point or "target" easier.
 *  This includes objects like @ref oglplus::Buffer "Buffer,"
 *  @ref oglplus::Texture "Texture", @ref oglplus::Renderbuffer "Renderbuffer"
 *  or @ref oglplus::Framebuffer "Framebuffer"
 *  which have a target to which individual
 *  instances can be bound and operated on through the binding point.
 *  Generally @c Bound<Object> classes re-implement those functions of @c Object
 *  which have a @c target parameter of the @c Object::Target type. These
 *  re-implemented functions have all the other parameters of the original
 *  member functions, but lack the @c target parameter and supply it to the
 *  original function call automatically.
 *
 *  @see Context::Bind()
 *  @see Context::Bound()
 *  @see Context::Current()
 *
 *  @ingroup modifier_classes
 */
template <class Object>
class Bound
 : public BoundTemplate<
	BoundBase,
	Managed<typename ObjectBaseOps<Object>::Type>,
	typename ObjectBaseOps<Object>::Type
>
{
private:
	typedef typename ObjectBaseOps<Object>::Type ObjectOps;
public:
	Bound(
		const Managed<ObjectOps>& obj,
		typename ObjectOps::Target tgt
	): BoundTemplate<
		oglplus::BoundBase,
		Managed<ObjectOps>,
		ObjectOps
	>(obj, tgt)
	{ }
};

} // namespace oglplus

#endif // include guard
