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
namespace aux {

template <typename ObjTag>
struct CurrentObject
{
	template <typename ObjBindingOps<ObjTag>::Target ObjTgt>
	class WithTarget
	 : public SettingStack<GLuint>
	{
	private:
		static
		void _do_bind(GLuint obj)
		{
			ObjBindingOps<ObjTag>::Bind(
				ObjTgt,
				ObjectName<ObjTag>(obj)
			);
		}
	public:
		WithTarget(void)
		 : SettingStack<GLuint>(&_do_bind)
		{
			GLuint name = 0;
			try
			{
				name = GetGLName(
					ObjBindingOps<ObjTag>::Binding(ObjTgt)
				);
			}
			catch(Error&){ }
			this->_init(name);
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
};

template <typename ObjTag>
class CurrentObjectsWithTarget
 : public oglplus::enums::EnumToClass<
	Nothing,
	typename ObjBindingOps<ObjTag>::Target,
	CurrentObject<ObjTag>::template WithTarget
>
{
public:
	CurrentObjectsWithTarget(void) { }
};

} // namespace aux
} // namespace client

#include <oglplus/enums/buffer_target_class.ipp>
#include <oglplus/enums/framebuffer_target_class.ipp>
#include <oglplus/enums/renderbuffer_target_class.ipp>
#include <oglplus/enums/texture_target_class.ipp>
#include <oglplus/enums/transform_feedback_target_class.ipp>

namespace client {

class CurrentObjects
{
public:
	aux::CurrentObjectsWithTarget<tag::Buffer> Buffer;
	aux::CurrentObjectsWithTarget<tag::Framebuffer> Framebuffer;
	aux::CurrentObjectsWithTarget<tag::Renderbuffer> Renderbuffer;
	aux::CurrentObjectsWithTarget<tag::Texture> Texture;
	aux::CurrentObjectsWithTarget<tag::TransformFeedback> TransformFeedback;
};

} // namespace client
} // namespace oglplus

#endif // include guard
