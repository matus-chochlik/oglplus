/**
 *  @file oglplus/client/current_object.hpp
 *  @brief Client current object stack
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_CURRENT_OBJECT_1412071213_HPP
#define OGLPLUS_CLIENT_CURRENT_OBJECT_1412071213_HPP

#include <oglplus/client/common.hpp>

namespace oglplus {
namespace client {

template <
	typename ObjTag,
	typename ObjBindingOps<ObjTag>::Target ObjTgt
>
class CurrentObject
{
private:
	std::vector<GLuint> _stk;

	static
	void _push(std::vector<GLuint>& stk, ObjectName<ObjTag> obj)
	{
		stk.push_back(GetName(obj));
	}

	static
	void _pop(std::vector<GLuint>& stk)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(!stk.empty());
		stk.pop_back();
	}

	aux::SettingPopper<GLuint> _ppr;
public:
	CurrentObject(void)
	 : _ppr(_stk, _pop)
	{
		_push(_stk, ObjBindingOps<ObjTag>::Binding(ObjTgt));
	}

	void Reserve(std::size_t n)
	{
		_stk.reserve(n);
	}

	ObjectName<ObjTag> Get(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		assert(!_stk.empty());
		return ObjectName<ObjTag>(_stk.back());
	}

	operator ObjectName<ObjTag> (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return Get();
	}

	typedef SettingHolder<GLuint> Holder;

	Holder Use(ObjectName<ObjTag> obj)
	{
		if(Get() != obj)
		{
			_push(_stk, obj);
			try { ObjBindingOps<ObjTag>::Bind(ObjTgt, obj); }
			catch(...)
			{
				_pop(_stk);
				throw;
			}

			return Holder(_ppr);
		}
		return Holder();
	}
};

class CurrentObjects
{
public:
	CurrentObject<tag::Framebuffer, FramebufferTarget::Read>
		ReadFramebuffer;
	CurrentObject<tag::Framebuffer, FramebufferTarget::Draw>
		DrawFramebuffer;

	CurrentObject<tag::Renderbuffer, RenderbufferTarget::Renderbuffer>
		Renderbuffer;
};

} // namespace client
} // namespace oglplus

#endif // include guard
