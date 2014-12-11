/**
 *  @file oglplus/client/capabilities.hpp
 *  @brief Client current capability status stack
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_CAPABILITIES_1412071213_HPP
#define OGLPLUS_CLIENT_CAPABILITIES_1412071213_HPP

#include <oglplus/client/setting.hpp>
#include <oglplus/context/capabilities.hpp>
#include <cassert>

namespace oglplus {
namespace client {
namespace aux {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
template <Capability Cap>
class CurrentCapabilityIndexed
 : public SettingStack<bool, GLuint>
{
private:
	static
	bool _do_get(GLuint index)
	{
		if(index == 0)
		{
			return context::Capabilities::IsEnabled(Cap);
		}
		else
		{
			return context::Capabilities::IsEnabled(Cap, index);
		}
	}

	static
	void _do_set(bool status, GLuint index)
	{
		if(index == 0)
		{
			if(status)
			{
				context::Capabilities::Enable(Cap);
			}
			else
			{
				context::Capabilities::Disable(Cap);
			}
		}
		else
		{
			if(status)
			{
				context::Capabilities::Enable(Cap, index);
			}
			else
			{
				context::Capabilities::Disable(Cap, index);
			}
		}
	}
public:
	CurrentCapabilityIndexed(GLuint index = 0)
	 : SettingStack<bool, GLuint>(&_do_get, &_do_set, index)
	{ }

	bool IsEnabled(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return this->_top();
	}

	OGLPLUS_EXPLICIT
	operator bool (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return IsEnabled();
	}

	void Enable(bool status = true)
	{
		return this->_set(status);
	}

	void Disable(void)
	{
		return this->_set(false);
	}
};

template <Capability Cap>
class CurrentCapability
 : public SettingStackIndexed<CurrentCapabilityIndexed<Cap>, bool>
{
private:
	using SettingStackIndexed<CurrentCapabilityIndexed<Cap>, bool>::_zero;
public:
	bool IsEnabled(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _zero().IsEnabled();
	}

	OGLPLUS_EXPLICIT
	operator bool (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return IsEnabled();
	}

	void Enable(bool status = true)
	{
		return _zero().Enable(status);
	}

	void Disable(void)
	{
		return _zero().Disable();
	}
};

#else

template <Capability Cap>
class CurrentCapability
 : public SettingStack<bool, Nothing>
{
private:
	static
	bool _do_get(Nothing)
	{
		return context::Capabilities::IsEnabled(Cap);
	}

	static
	void _do_set(bool status, Nothing)
	{
		if(status)
		{
			context::Capabilities::Enable(Cap);
		}
		else
		{
			context::Capabilities::Disable(Cap);
		}
	}
public:
	CurrentCapability(void)
	 : SettingStack<bool, Nothing>(&_do_get, &_do_set)
	{ }

	bool IsEnabled(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return this->_top();
	}

	OGLPLUS_EXPLICIT
	operator bool (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return IsEnabled();
	}

	void Enable(bool status = true)
	{
		return this->_set(status);
	}

	void Disable(void)
	{
		return this->_set(false);
	}
};
#endif

} // namespace aux
} // namespace client

#include <oglplus/enums/capability_class.ipp>

namespace client {

class CurrentCapabilities
{
public:
	oglplus::enums::EnumToClass<
		Nothing,
		Capability,
		aux::CurrentCapability
	> Capabilities;

	oglplus::enums::EnumToClass<
		Nothing,
		Capability,
		aux::CurrentCapability
	>& Caps;

	CurrentCapabilities(void)
	 : Caps(Capabilities)
	{ }
};

} // namespace client
} // namespace oglplus

#endif // include guard
