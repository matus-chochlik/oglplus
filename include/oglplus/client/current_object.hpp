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

#include <oglplus/client/setting.hpp>

namespace oglplus {
namespace client {

template <
	typename ObjTag,
	typename ObjBindingOps<ObjTag>::Target ObjTgt
>
class CurrentObject
 : public SettingStack<GLuint>
{
private:
	static
	void _do_bind(GLuint obj)
	{
		ObjBindingOps<ObjTag>::Bind(ObjTgt, ObjectName<ObjTag>(obj));
	}
public:
	CurrentObject(void)
	 : SettingStack<GLuint>(&_do_bind)
	{
		this->_init(GetName(ObjBindingOps<ObjTag>::Binding(ObjTgt)));
	}

	ObjectName<ObjTag> Get(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectName<ObjTag>(this->_top());
	}

	operator ObjectName<ObjTag> (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return Get();
	}

	typedef SettingHolder<GLuint> Holder;

	Holder Push(ObjectName<ObjTag> obj)
	{
		return this->_push(GetName(obj));
	}

	void Bind(ObjectName<ObjTag> obj)
	{
		return this->_set(GetName(obj));
	}
};

class CurrentObjects
{
public:
	CurrentObject<tag::Buffer, BufferTarget::Array>
		ArrayBuffer;
	CurrentObject<tag::Buffer, BufferTarget::ElementArray>
		ElementArrayBuffer;

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
