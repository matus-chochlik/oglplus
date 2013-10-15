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
#include <map>

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
		static GLuint tu = 0;
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
	typedef AutoBindUnit<Bindable, BindableOps, Safe> UnitSel_;
	typedef typename Bindable::Target Target;
	typedef std::integral_constant<bool, Safe> IsSafe_;

	static GLuint& _currently_bound(Target target)
	{
		static std::map<Target, GLuint> cb;
		return cb[target];
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
		auto sname = _currently_bound(target);
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
		_currently_bound(target) = FriendOf<Bindable>::GetName(bindable);
	}

	void _bind_if_necessary(
		const Bindable& bindable,
		Target target
	) const
	{
		UnitSel_::_select_unit_if_necessary();
		IsSafe_ is_safe;
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
	 : UnitSel_(unit)
	 , _bind_target(target)
	{ }

	AutoBindBase(const BindableOps& bindable, Target target)
	 : Bindable(bindable)
	 , _bind_target(target)
	{ }

	AutoBindBase(const BindableOps& bindable, Target target, GLuint unit)
	 : Bindable(bindable)
	 , UnitSel_(unit)
	 , _bind_target(target)
	{ }

	AutoBindBase(AutoBindBase&& tmp)
	 : Bindable(static_cast<Bindable&&>(tmp))
	 , UnitSel_(static_cast<UnitSel_&&>(tmp))
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
		typedef AutoBindBase<Bindable, BindableOps, Safe> _base;
	protected:
		Result(Target target)
		 : _base(target)
		{ }

		Result(Target target, GLuint unit)
		 : _base(target, unit)
		{ }

		Result(const BindableOps& bindable, Target target)
		 : _base(bindable, target)
		{ }

		Result(const BindableOps& bindable, Target target, GLuint unit)
		 : _base(bindable, target, unit)
		{ }

		Result(Result&& tmp)
		 : _base(static_cast<_base&&>(tmp))
		{ }
	};
};

} // namespace aux

template <typename Object, bool Safe = true>
class AutoBind;

#if !OGLPLUS_DOCUMENTATION_ONLY && !OGLPLUS_DOXYGEN_PARSE
template <class Object, bool Safe>
struct ObjectBaseOps<AutoBind<Object, Safe> >
{
	typedef typename ObjectBaseOps<Object>::Type Type;
};
#endif

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
	> _base;
public:
	AutoBind(typename BindableOps::Target target)
	 : _base(target)
	{ }

	template <typename Target_>
	AutoBind(
		Target_ target,
		typename std::enable_if<
			std::is_same<
				typename TextureOps::Target,
				Target_
			>::value,
			GLuint
		>::type tex_unit
	): _base(target, tex_unit)
	{ }

	AutoBind(AutoBind&& tmp)
	 : _base(std::move(tmp))
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
	> _base;
public:
	AutoBind(
		const BindableOps& bindable,
		typename BindableOps::Target target
	): _base(bindable, target)
	{ }

	template <typename Target_>
	AutoBind(
		const BindableOps& bindable,
		Target_ target,
		typename std::enable_if<
			std::is_same<
				typename TextureOps::Target,
				Target_
			>::value,
			GLuint
		>::type tex_unit
	): _base(bindable, target, tex_unit)
	{ }

	AutoBind(AutoBind&& tmp)
	 : _base(static_cast<_base&&>(tmp))
	{ }
};

template <typename Object>
class Array;

template <typename ObjectOps, bool Safe>
class Array<AutoBind<Object<ObjectOps>, Safe> >
 : public aux::MultiObjectBaseArray<Object<ObjectOps> >
{
private:
	typedef aux::MultiObjectBaseArray<Object<ObjectOps> > _base;
	typedef typename ObjectOps::Target Target;

	Target _target;
public:
	Array(GLsizei c, Target target)
	 : _base(c)
	 , _target(target)
	{ }

	Array(Array&& temp)
	 : _base(static_cast<_base&&>(temp))
	 , _target(temp.target)
	{ }

	typedef AutoBind<Managed<ObjectOps>, Safe> reference;
	typedef AutoBind<Managed<ObjectOps>, Safe> const_reference;

	const_reference front(void) const
	{
		return const_reference(
			Managed<ObjectOps>(this->_names.front()),
			_target
		);
	}

	const_reference back(void) const
	{
		return const_reference(
			Managed<ObjectOps>(this->_names.back()),
			_target
		);
	}

	const_reference at(GLuint index) const
	{
		assert(index < GLuint(this->size()));
		return const_reference(
			Managed<ObjectOps>(this->_names[index]),
			_target
		);
	}

	const_reference operator [](GLuint index) const
	{
		return at(index);
	}

/* TODO
	typedef aux::BaseIter<const_reference, GLuint> const_iterator;
	typedef const_iterator iterator;

	iterator begin(void) const
	{
		return iterator(this->_names.begin(), this->_names.end());
	}

	iterator end(void) const
	{
		return iterator(this->_names.end());
	}

	aux::ArrayRange<const_reference> all(void) const
	{
		return aux::ArrayRange<const_reference>(begin(), end());
	}
*/
};

template <bool Safe>
class Array<AutoBind<Object<TextureOps>, Safe> >
 : public aux::MultiObjectBaseArray<Object<TextureOps> >
{
private:
	typedef aux::MultiObjectBaseArray<Object<TextureOps> > _base;
	typedef typename TextureOps::Target Target;

	Target _target;
	GLuint _tex_unit;
public:
	Array(GLsizei c, Target target, GLuint base_tex_unit)
	 : _base(c)
	 , _target(target)
	 , _tex_unit(base_tex_unit)
	{ }

	Array(Array&& temp)
	 : _base(static_cast<_base&&>(temp))
	 , _target(temp._target)
	 , _tex_unit(temp._tex_unit)
	{ }

	typedef AutoBind<Managed<TextureOps>, Safe> reference;
	typedef AutoBind<Managed<TextureOps>, Safe> const_reference;

	const_reference front(void) const
	{
		return const_reference(
			Managed<TextureOps>(this->_names.front()),
			_target,
			_tex_unit
		);
	}

	const_reference back(void) const
	{
		return const_reference(
			Managed<TextureOps>(this->_names.back()),
			_target,
			_tex_unit+this->size()-1
		);
	}

	const_reference at(GLuint index) const
	{
		assert(index < GLuint(this->size()));
		return const_reference(
			Managed<TextureOps>(this->_names[index]),
			_target,
			_tex_unit+index
		);
	}

	const_reference operator [](GLuint index) const
	{
		return at(index);
	}

/* TODO
	typedef aux::BaseIter<const_reference, GLuint> const_iterator;
	typedef const_iterator iterator;

	iterator begin(void) const
	{
		return iterator(this->_names.begin(), this->_names.end());
	}

	iterator end(void) const
	{
		return iterator(this->_names.end());
	}

	aux::ArrayRange<const_reference> all(void) const
	{
		return aux::ArrayRange<const_reference>(begin(), end());
	}
*/
};

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
