/**
 *  @file oglplus/client/viewport.hpp
 *  @brief Client current viewport setting stack
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_VIEWPORT_1412071213_HPP
#define OGLPLUS_CLIENT_VIEWPORT_1412071213_HPP

#include <oglplus/client/setting.hpp>
#include <oglplus/context/viewport.hpp>
#include <cassert>

namespace oglplus {
namespace client {
namespace aux {

template <typename Base>
class ViewportOps
 : public Base
{
private:
	inline
	Base* _that(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return this;
	}
protected:
	ViewportOps(void)
	{ }

	template <typename T, typename P>
	ViewportOps(T (*query)(P), void(*apply)(T, P), P param = P())
	 : Base(query, apply, param)
	{ }
public:
	using Base::Set;

	void Set(GLsizei width, GLsizei height)
	{
		_that()->Set(context::ViewportExtents(0, 0, width, height));
	}

	void Set(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		_that()->Set(context::ViewportExtents(x, y, width, height));
	}
};

#if GL_VERSION_4_1 || GL_ARB_viewport_array

class ViewportIndexed
 : public ViewportOps<SettingStack<context::ViewportExtents, GLuint>>
{
private:
	static
	context::ViewportExtents _do_get(GLuint index)
	{
		return context::ViewportOps::Viewport(index);
	}

	static
	void _do_set(context::ViewportExtents vp, GLuint index)
	{
		context::ViewportOps::Viewport(index, vp);
	}
public:
	ViewportIndexed(GLuint index)
	 : ViewportOps<SettingStack<context::ViewportExtents, GLuint>>(
		&_do_get,
		&_do_set,
		index
	)
	{ }
};

class Viewport
 : public ViewportOps<
	SettingStackIndexed<ViewportIndexed, context::ViewportExtents>
>
{ };

#else

class Viewport
 : public ViewportOps<SettingStack<context::ViewportExtents, Nothing>>
{
private:
	static
	context::ViewportExtents _do_get(Nothing)
	{
		return context::ViewportOps::Viewport();
	}

	static
	void _do_set(context::ViewportExtents vp, Nothing)
	{
		context::ViewportOps::Viewport(vp);
	}
public:
	Viewport(void)
	 : ViewportOps<SettingStack<context::ViewportExtents, Nothing>>(
		&_do_get,
		&_do_set
	)
	{ }
};

#endif

} // namespace aux

class ViewportOps
{
public:
	aux::Viewport Viewport;
};

} // namespace client
} // namespace oglplus

#endif // include guard
