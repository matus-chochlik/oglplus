/**
 *  @file oglplus/error/deferred_handler.hpp
 *  @brief Enumeration the DeferredHandler template
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ERROR_DEFERRED_HANDLER_1405082311_HPP
#define OGLPLUS_ERROR_DEFERRED_HANDLER_1405082311_HPP

#include <oglplus/config/compiler.hpp>
#include <memory>

namespace oglplus {

class DeferredHandler
{
private:
	struct _handler_intf
	{
		virtual ~_handler_intf(void)
		noexcept
		{ }

		virtual void execute(bool) = 0;
	};

	struct _abort_handler : _handler_intf
	{
		void execute(bool destroying)
		override;
	};

	template <typename Func>
	struct _handler_impl : _handler_intf
	{
		Func _func;

		_handler_impl(Func&& func)
		 : _func(std::move(func))
		{ }

		void execute(bool)
		override
		{
			_func();
		}
	};

	std::unique_ptr<_handler_intf> _handler;

	template <typename Func>
	static
	std::unique_ptr<_handler_intf> _wrap_func(Func func)
	{
		return std::unique_ptr<_handler_intf>(
			new _handler_impl<Func>(
				std::move(func)
			)
		);
	}

	std::unique_ptr<_handler_intf> _release_handler(void);
public:
	DeferredHandler(void) = default;
	DeferredHandler(DeferredHandler&&) = default;

	template <typename Func>
	explicit
	DeferredHandler(Func func)
	 : _handler(_wrap_func(func))
	{ }

	~DeferredHandler(void)
	{
		if(_handler)
		{
			if(!std::uncaught_exception())
			{
				_release_handler()->execute(true);
			}
		}
	}

	void trigger(void)
	{
		if(_handler)
		{
			_release_handler()->execute(false);
		}
	}

	bool cancel(void)
	{
		return bool(_release_handler());
	}

	explicit
	operator bool (void) const
	noexcept
	{
		return bool(_handler);
	}

	bool operator ! (void) const
	noexcept
	{
		return !_handler;
	}
};

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/error/deferred_handler.ipp>
#endif

#endif // include guard
