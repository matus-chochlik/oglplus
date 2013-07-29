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
#include <oglplus/auxiliary/base_array.hpp>
#include <type_traits>

namespace oglplus {
namespace aux {

template <class Bindable, class BindableOps, bool Safe>
class AutoBindUnit
{
protected:
	static void _select_unit_if_necessary(void){ }
};

template <class Bindable>
class AutoBindUnit<Bindable, TextureOps, true>
{
private:
	GLuint _tex_unit;
protected:
	AutoBindUnit(GLuint unit)
	 : _tex_unit(unit)
	{ }

	void _select_unit_if_necessary(void) const
	{
		if(GLuint(TextureOps::Active()) != _tex_unit)
			TextureOps::Active(_tex_unit);
	}
};

template <class Bindable>
class AutoBindUnit<Bindable, TextureOps, false>
{
private:
	GLuint _tex_unit;

	static GLuint& _current_tex_unit(void)
	{
		GLuint tu = 0;
		return tu;
	}
protected:
	AutoBindUnit(GLuint unit)
	 : _tex_unit(unit)
	{ }

	void _select_unit_if_necessary(void) const
	{
		if(_current_tex_unit() != _tex_unit)
		{
			TextureOps::Active(_tex_unit);
			_current_tex_unit() = _tex_unit;
		}
	}
};

template <class Bindable, class BindableOps, bool Safe>
class AutoBindBase
 : public Bindable
 , public FriendOf<Bindable>
 , public AutoBindUnit<Bindable, BindableOps, Safe>
{
private:
	typedef AutoBindUnit<Bindable, BindableOps, Safe> _UnitSel;
	typedef typename Bindable::Target Target;
	typedef std::integral_constant<bool, Safe> _IsSafe;

	static GLuint& _currently_bound(void)
	{
		static GLuint cb = 0;
		return cb;
	}

	static bool _is_bound(
		const Bindable& bindable,
		Target target,
		std::true_type /*is_safe*/
	)
	{
		auto name = FriendOf<Bindable>::GetName(bindable);
		auto sname = BindingQuery<BindableOps>::QueryBinding(target);
		return name == sname;
	}

	static bool _is_bound(
		const Bindable& bindable,
		Target target,
		std::false_type /*is_fast*/
	)
	{
		auto name = FriendOf<Bindable>::GetName(bindable);
		auto sname = _currently_bound();
		return name == sname;
	}

	static void _do_bind(
		const Bindable& bindable,
		Target target,
		std::true_type /*is_safe*/
	)
	{
		bindable.Bind(target);
	}

	static void _do_bind(
		const Bindable& bindable,
		Target target,
		std::false_type /*is_fast*/
	)
	{
		bindable.Bind(target);
		_currently_bound() = FriendOf<Bindable>::GetName(bindable);
	}

	void _bind_if_necessary(
		const Bindable& bindable,
		Target target
	) const
	{
		_UnitSel::_select_unit_if_necessary();
		_IsSafe is_safe;
		if(!_is_bound(bindable, target, is_safe))
		{
			_do_bind(bindable, target, is_safe);
		}
	}

	Target _bind_target;
protected:
	AutoBindBase(Target target)
	 : _bind_target(target)
	{ }

	AutoBindBase(Target target, GLuint unit)
	 : _UnitSel(unit)
	 , _bind_target(target)
	{ }

	AutoBindBase(const BindableOps& bindable, Target target)
	 : _bind_target(bindable, target)
	{ }

	AutoBindBase(const BindableOps& bindable, Target target, GLuint unit)
	 : _UnitSel(unit)
	 , _bind_target(bindable, target)
	{ }

	AutoBindBase(AutoBindBase&& tmp)
	 : Bindable(static_cast<Bindable&&>(tmp))
	 , _UnitSel(static_cast<_UnitSel&&>(tmp))
	 , _bind_target(tmp._bind_target)
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


template <bool Safe>
struct AutoBindBaseSelect
{
	template <class Bindable, class BindableOps>
	class Result
	 : public AutoBindBase<Bindable, BindableOps, Safe>
	{
	private:
		typedef typename Bindable::Target Target;
		typedef AutoBindBase<Bindable, BindableOps, Safe> _Base;
	protected:
		Result(Target target)
		 : _Base(target)
		{ }

		Result(Target target, GLuint unit)
		 : _Base(target, unit)
		{ }

		Result(const BindableOps& bindable, Target target)
		 : _Base(bindable, target)
		{ }

		Result(const BindableOps& bindable, Target target, GLuint unit)
		 : _Base(bindable, target, unit)
		{ }

		Result(Result&& tmp)
		 : _Base(static_cast<_Base&&>(tmp))
		{ }
	};
};

} // namespace aux

template <typename Object, bool Safe = true>
class AutoBind;

template <class BindableOps, bool Safe>
class AutoBind<Object<BindableOps>, Safe>
 : public BoundTemplate<
	aux::AutoBindBaseSelect<Safe>::template Result,
	Object<BindableOps>,
	BindableOps
>
{
private:
	typedef BoundTemplate<
		aux::AutoBindBaseSelect<Safe>::template Result,
		Object<BindableOps>,
		BindableOps
	> _Base;
public:
	AutoBind(typename BindableOps::Target target)
	 : _Base(target)
	{ }

	template <typename _Target>
	AutoBind(
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

	AutoBind(AutoBind&& tmp)
	 : _Base(std::move(tmp))
	{ }
};

template <class BindableOps, bool Safe>
class AutoBind<Managed<BindableOps>, Safe>
 : public BoundTemplate<
	aux::AutoBindBaseSelect<Safe>::template Result,
	Managed<BindableOps>,
	BindableOps
>
{
private:
	typedef BoundTemplate<
		aux::AutoBindBaseSelect<Safe>::template Result,
		Managed<BindableOps>,
		BindableOps
	> _Base;
public:
	AutoBind(
		const BindableOps& bindable,
		typename BindableOps::Target target
	): _Base(bindable, target)
	{ }

	template <typename _Target>
	AutoBind(
		const BindableOps& bindable,
		_Target target,
		typename std::enable_if<
			std::is_same<
				typename TextureOps::Target,
				_Target
			>::value,
			GLuint
		>::type tex_unit
	): _Base(bindable, target, tex_unit)
	{ }

	AutoBind(AutoBind&& tmp)
	 : _Base(static_cast<_Base&&>(tmp))
	{ }
};

/* TODO
template <typename Object>
class Array;

template <typename ObjectOps, bool Safe>
class Array<AutoBind<Object<ObjectOps>, Safe> >
 : public aux::BaseArray<
	SafeAutoBind<Object<ObjectOps> >,
	ObjectOps::IsMultiObject::value
>
{
private:
	typedef aux::BaseArray<
		AutoBind<Object<ObjectOps>, Safe>,
		ObjectOps::IsMultiObject::value
	> BaseArray;

	Array(const Array&);
public:
	Array(GLsizei c, typename ObjectOps::Target target)
	 : BaseArray(c, target)
	{ }

	Array(Array&& tmp)
	 : BaseArray(static_cast<BaseArray&&>(tmp))
	{ }
};
*/

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
template <class Bindable, bool Safe = true>
class AutoBind
 : public Bindable
{
public:
	/// Creates a @c Bindable so that it binds to a @c target when necessary
	/**
	 *  @see Bound
	 */
	AutoBind(typename Bindable::Target target);
};
#endif

} // namespace oglplus

#endif // include guard
