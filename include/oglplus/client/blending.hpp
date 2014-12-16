/**
 *  @file oglplus/client/blending.hpp
 *  @brief Client blending ops and status stack.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_BLENDING_1412071213_HPP
#define OGLPLUS_CLIENT_BLENDING_1412071213_HPP

#include <oglplus/client/setting.hpp>
#include <oglplus/context/blending.hpp>
#include <cassert>

namespace oglplus {
namespace client {
namespace aux {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0

class BlendEquationIndexed
 : public SettingStack<context::BlendEquationSeparate, GLuint>
{
private:
	static
	context::BlendEquationSeparate _do_get(GLuint index)
	{
		if(index == 0)
		{
			return context::BlendingState::BlendEquationSeparate();
		}
		else
		{
			return context::BlendingState::BlendEquationSeparate(
				index
			);
		}
	}

	static
	void _do_set(context::BlendEquationSeparate value, GLuint index)
	{
		if(index == 0)
		{
			if(value.Separate())
			{
				context::BlendingState::BlendEquationSeparate(
					value
				);
			}
			else
			{
				context::BlendingState::BlendEquation(
					value.Alpha()
				);
			}
		}
		else
		{
			if(value.Separate())
			{
				context::BlendingState::BlendEquationSeparate(
					index,
					value
				);
			}
			else
			{
				context::BlendingState::BlendEquation(
					index,
					value.Alpha()
				);
			}
		}
	}
public:
	BlendEquationIndexed(GLuint index = 0)
	 : SettingStack<context::BlendEquationSeparate, GLuint>(
		&_do_get,
		&_do_set,
		index
	)
	{ }

	using SettingStack<context::BlendEquationSeparate, GLuint>::Set;

	void Set(oglplus::BlendEquation rgb, oglplus::BlendEquation alpha)
	{
		Set(context::BlendEquationSeparate(rgb, alpha));
	}
};

class BlendEquation
 : public SettingStackIndexed<
	BlendEquationIndexed,
	context::BlendEquationSeparate
>
{
private:
	using SettingStackIndexed<
		BlendEquationIndexed,
		context::BlendEquationSeparate
	>::_zero;
public:
	void Set(const context::BlendEquationSeparate& value)
	{
		_zero().Set(value);
	}

	void Set(oglplus::BlendEquation rgb, oglplus::BlendEquation alpha)
	{
		_zero().Set(rgb, alpha);
	}
};

class BlendFunctionIndexed
 : public SettingStack<context::BlendFunctionSeparate, GLuint>
{
private:
	static
	context::BlendFunctionSeparate _do_get(GLuint index)
	{
		if(index == 0)
		{
			return context::BlendingState::BlendFuncSeparate();
		}
		else
		{
			return context::BlendingState::BlendFuncSeparate(
				index
			);
		}
	}

	static
	void _do_set(context::BlendFunctionSeparate value, GLuint index)
	{
		if(index == 0)
		{
			if(value.Separate())
			{
				context::BlendingState::BlendFuncSeparate(
					value
				);
			}
			else
			{
				context::BlendingState::BlendFunc(
					value.SrcAlpha(),
					value.DstAlpha()
				);
			}
		}
		else
		{
			if(value.Separate())
			{
				context::BlendingState::BlendFuncSeparate(
					index,
					value
				);
			}
			else
			{
				context::BlendingState::BlendFunc(
					index,
					value.SrcAlpha(),
					value.DstAlpha()
				);
			}
		}
	}
public:
	BlendFunctionIndexed(GLuint index = 0)
	 : SettingStack<context::BlendFunctionSeparate, GLuint>(
		&_do_get,
		&_do_set,
		index
	)
	{ }

	using SettingStack<context::BlendFunctionSeparate, GLuint>::Set;

	void Set(
		oglplus::BlendFunction src_rgb,
		oglplus::BlendFunction src_alpha,
		oglplus::BlendFunction dst_rgb,
		oglplus::BlendFunction dst_alpha
	)
	{
		Set(context::BlendFunctionSeparate(
			src_rgb,
			src_alpha,
			dst_rgb,
			dst_alpha
		));
	}
};

class BlendFunction
 : public SettingStackIndexed<
	BlendFunctionIndexed,
	context::BlendFunctionSeparate
>
{
private:
	using SettingStackIndexed<
		BlendFunctionIndexed,
		context::BlendFunctionSeparate
	>::_zero;
public:
	void Set(const context::BlendFunctionSeparate& value)
	{
		_zero().Set(value);
	}

	void Set(
		oglplus::BlendFunction src_rgb,
		oglplus::BlendFunction src_alpha,
		oglplus::BlendFunction dst_rgb,
		oglplus::BlendFunction dst_alpha
	)
	{
		_zero().Set(src_rgb, src_alpha, dst_rgb, dst_alpha);
	}
};

#else

class BlendEquation
 : public SettingStack<context::BlendEquationSeparate, Nothing>
{
private:
	static
	context::BlendEquationSeparate _do_get(Nothing)
	{
		return context::BlendingState::BlendEquationSeparate();
	}

	static
	void _do_set(context::BlendEquationSeparate value, Nothing)
	{
		if(value.Separate())
		{
			context::BlendingState::BlendEquationSeparate(value);
		}
		else
		{
			context::BlendingState::BlendEquation(value.Alpha());
		}
	}
public:
	BlendEquation(void)
	 : SettingStack<context::BlendEquationSeparate, Nothing>(
		&_do_get,
		&_do_set
	)
	{ }

	using SettingStack<context::BlendEquationSeparate, Nothing>::Set;

	void Set(oglplus::BlendEquation rgb, oglplus::BlendEquation alpha)
	{
		Set(context::BlendEquationSeparate(rgb, alpha));
	}
};

class BlendFunction
 : public SettingStack<context::BlendFunctionSeparate, Nothing>
{
private:
	static
	context::BlendFunctionSeparate _do_get(Nothing)
	{
		return context::BlendingState::BlendFuncSeparate();
	}

	static
	void _do_set(context::BlendFunctionSeparate value, Nothing)
	{
		if(value.Separate())
		{
			context::BlendingState::BlendFuncSeparate(value);
		}
		else
		{
			context::BlendingState::BlendFunc(
				value.SrcAlpha(),
				value.DstAlpha()
			);
		}
	}
public:
	BlendFunction(void)
	 : SettingStack<context::BlendFunctionSeparate, Nothing>(
		&_do_get,
		&_do_set
	)
	{ }

	using SettingStack<context::BlendFunctionSeparate, Nothing>::Set;

	void Set(
		oglplus::BlendFunction src_rgb,
		oglplus::BlendFunction src_alpha,
		oglplus::BlendFunction dst_rgb,
		oglplus::BlendFunction dst_alpha
	)
	{
		Set(context::BlendFunctionSeparate(
			src_rgb,
			src_alpha,
			dst_rgb,
			dst_alpha
		));
	}
};
#endif

} // namespace aux

class BlendingState
{
public:
	aux::BlendEquation BlendEquation;
	aux::BlendFunction BlendFunction;
};

using context::BlendingOps;

} // namespace client
} // namespace oglplus

#endif // include guard
