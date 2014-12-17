/**
 *  @file oglplus/client/buffer_masking.hpp
 *  @brief Client buffer masking ops and status stack.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_BUFFER_MASKING_1412071213_HPP
#define OGLPLUS_CLIENT_BUFFER_MASKING_1412071213_HPP

#include <oglplus/client/setting.hpp>
#include <oglplus/context/buffer_masking.hpp>
#include <cassert>

namespace oglplus {
namespace client {
namespace aux {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0

class ColorMaskIndexed
 : public SettingStack<context::RGBAMask, GLuint>
{
private:
	static
	context::RGBAMask _do_get(GLuint index)
	{
		if(index == 0)
		{
			return context::BufferMaskingState::ColorWriteMask();
		}
		else
		{
			return context::BufferMaskingState::ColorWriteMask(
				index
			);
		}
	}

	static
	void _do_set(context::RGBAMask value, GLuint index)
	{
		if(index == 0)
		{
			context::BufferMaskingState::ColorMask(value);
		}
		else
		{
			context::BufferMaskingState::ColorMask(index, value);
		}
	}
public:
	ColorMaskIndexed(GLuint index = 0)
	 : SettingStack<context::RGBAMask, GLuint>(
		&_do_get,
		&_do_set,
		index
	)
	{ }
};

class ColorMask
 : public SettingStackIndexed<
	ColorMaskIndexed,
	context::RGBAMask
>
{ };

#else

class ColorMask
 : public SettingStack<context::RGBAMask, Nothing>
{
private:
	static
	context::RGBAMask _do_get(Nothing)
	{
		return context::BufferMaskingState::ColorMask();
	}

	static
	void _do_set(context::RGBAMask value, Nothing)
	{
		context::BufferClearingState::ColorWriteMask();
	}
public:
	ClearColor(void)
	 : SettingStack<context::RGBAValue, Nothing>(
		&_do_get,
		&_do_set
	)
	{ }
};

#endif

class DepthMask
 : public SettingStack<bool, Nothing>
{
private:
	static
	bool _do_get(Nothing)
	{
		return context::BufferMaskingState::DepthWriteMask();
	}

	static
	void _do_set(bool value, Nothing)
	{
		context::BufferMaskingState::DepthMask(value);
	}
public:
	DepthMask(void)
	 : SettingStack<bool, Nothing>(
		&_do_get,
		&_do_set
	)
	{ }
};

// TODO stencil mask

} // namespace aux

class BufferMaskingState
{
public:
	aux::ColorMask ColorMask;
	aux::DepthMask DepthMask;
};

} // namespace client
} // namespace oglplus

#endif // include guard
