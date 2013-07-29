/**
 *  @file oglplus/auto_bind.hpp
 *  @brief OGLplus AutoBind objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUTO_BIND_1201190831_HPP
#define OGLPLUS_AUTO_BIND_1201190831_HPP

#include <oglplus/bound.hpp>

namespace oglplus {

template <class Bindable, class BindableOps>
class SafeAutoBindBase
 : public Bindable
 , public FriendOf<Bindable>
{
private:
	typedef typename Bindable::Target Target;

	static bool _is_bound(
		const Bindable& bindable,
		Target target
	)
	{
		auto name = FriendOf<Bindable>::GetName(bindable);
		auto sname = BindingQuery<BindableOps>::QueryBinding(target);
		return name == sname;
	}

	static void _bind_if_necessary(
		const Bindable& bindable,
		Target target
	)
	{
		if(!_is_bound(bindable, target))
			bindable.Bind(target);
	}

	Target _bind_target;
protected:
	SafeAutoBindBase(Target target)
	 : _bind_target(target)
	{ }
public:
	SafeAutoBindBase(SafeAutoBindBase&& tmp)
	 : Bindable(static_cast<Bindable&&>(tmp))
	 , _bind_target(tmp._bind_target)
	{ }

	void Bind(void) const
	{
		_bind_if_necessary(*this, _bind_target);
	}

	typename Bindable::Target BindTarget(void) const
	{
		_bind_if_necessary(*this, _bind_target);
		return _bind_target;
	}
};

template <class Bindable>
class SafeAutoBindBase<Bindable, TextureOps>
 : public Bindable
 , public FriendOf<Bindable>
{
private:
	typedef typename Bindable::Target Target;

	static bool _is_bound(
		const Bindable& bindable,
		Target target
	)
	{
		auto name = FriendOf<Bindable>::GetName(bindable);
		auto sname = BindingQuery<TextureOps>::QueryBinding(target);
		return name == sname;
	}

	static void _bind_if_necessary(
		const Bindable& bindable,
		Target target,
		GLuint tex_unit
	)
	{
		if(GLuint(TextureOps::Active()) != tex_unit)
			TextureOps::Active(tex_unit);
		if(!_is_bound(bindable, target))
			bindable.Bind(target);
	}

	Target _bind_target;
	GLuint _tex_unit;
protected:
	SafeAutoBindBase(Target target)
	 : _bind_target(target)
	 , _tex_unit(0)
	{ }

	SafeAutoBindBase(Target target, GLuint tex_unit)
	 : _bind_target(target)
	 , _tex_unit(tex_unit)
	{ }
public:
	SafeAutoBindBase(SafeAutoBindBase&& tmp)
	 : Bindable(static_cast<Bindable&&>(tmp))
	 , _bind_target(tmp._bind_target)
	 , _tex_unit(tmp._tex_unit)
	{ }

	void Bind(void) const
	{
		_bind_if_necessary(*this, _bind_target, _tex_unit);
	}

	typename Bindable::Target BindTarget(void) const
	{
		_bind_if_necessary(*this, _bind_target, _tex_unit);
		return _bind_target;
	}

	void TextureUnit(GLuint tex_unit)
	{
		_tex_unit = tex_unit;
		_bind_if_necessary(*this, _bind_target, _tex_unit);
	}

	GLuint TexureUnit(void)
	{
		_bind_if_necessary(*this, _bind_target, _tex_unit);
		return _tex_unit;
	}
};

template <class Bindable, class BindableOps>
class FastAutoBindBase
 : public Bindable
 , public FriendOf<Bindable>
{
private:
	typedef typename Bindable::Target Target;
	static GLuint& _currently_bound(void)
	{
		static GLuint cb = 0;
		return cb;
	}

	static bool _is_bound(
		const Bindable& bindable,
		Target target
	)
	{
		auto name = FriendOf<Bindable>::GetName(bindable);
		auto sname = _currently_bound();
		return name == sname;
	}

	static void _bind_if_necessary(
		const Bindable& bindable,
		Target target
	)
	{
		if(!_is_bound(bindable, target))
		{
			bindable.Bind(target);
			_currently_bound() =
				FriendOf<Bindable>::GetName(bindable);
		}
	}

	Target _bind_target;
protected:
	FastAutoBindBase(Target target)
	 : _bind_target(target)
	{ }
public:
	void Bind(void) const
	{
		_bind_if_necessary(*this, _bind_target);
	}

	typename Bindable::Target BindTarget(void) const
	{
		_bind_if_necessary(*this, _bind_target);
		return _bind_target;
	}
};

template <class Bindable>
class SafeAutoBind;

template <class Bindable>
class FastAutoBind;

#if OGLPLUS_DOCUMENTATION_ONLY
/// A wraper that automatically binds @ref oglplus_object "objects" to a target
/**
 *  @ref bound_objects make the usage of @ref oglplus_object "objects" that
 *  can be bound to a OpenGL binding point or "target" easier.
 *  This includes objects like @ref oglplus::Buffer "Buffer,"
 *  @ref oglplus::Texture "Texture", @ref oglplus::Renderbuffer "Renderbuffer"
 *  or @ref oglplus::Framebuffer "Framebuffer"
 *  which have a target to which individual
 *  instances can be bound and operated on through the binding point.
 *
 *  @ingroup utility_classes
 */
template <class Bindable>
class SafeAutoBind
 : public Bindable
{
public:
	/// Creates a @c Bindable so that it binds to a @c target when necessary
	/**
	 *  @see Bound
	 */
	SafeAutoBind(typename Bindable::Target target);
};
#else
template <class BindableOps>
class SafeAutoBind<Object<BindableOps> >
 : public BoundTemplate<SafeAutoBindBase, Object<BindableOps>, BindableOps>
{
private:
	typedef BoundTemplate<
		SafeAutoBindBase,
		Object<BindableOps>,
		BindableOps
	> _Base;
public:
	SafeAutoBind(typename BindableOps::Target target)
	 : _Base(target)
	{ }

	template <typename _Target>
	SafeAutoBind(
		_Target target,
		typename std::enable_if<
			std::is_same<
				typename TextureOps::Target,
				_Target
			>::value,
			GLuint
		>::type tex_unit
	): _Base(target, tex_unit)
	{ }

	SafeAutoBind(SafeAutoBind&& tmp)
	 : _Base(std::move(tmp))
	{ }
};

template <class Bindable>
class FastAutoBind<Object<Bindable> >
 : public BoundTemplate<FastAutoBindBase, Object<Bindable>, Bindable>
{
public:
	FastAutoBind(typename Bindable::Target target)
	 : BoundTemplate<FastAutoBindBase, Object<Bindable>, Bindable>(target)
	{ }
};
#endif

} // namespace oglplus

#endif // include guard
