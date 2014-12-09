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
	 : SettingStack<bool, GLuint>(&_do_set, index)
	{
		try
		{
			if(index == 0)
			{
				this->_init(
					context::Capabilities::IsEnabled(Cap)
				);
			}
			else
			{
				this->_init(
					context::Capabilities::IsEnabled(
						Cap,
						index
					)
				);
			}
		}
		catch(Error&){ }
	}

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
{
private:
	std::vector<CurrentCapabilityIndexed<Cap>> _indexed;

	CurrentCapabilityIndexed<Cap>& _zero(void)
	{
		assert(!_indexed.empty());
		return _indexed[0];
	}

	const CurrentCapabilityIndexed<Cap>& _zero(void) const
	{
		assert(!_indexed.empty());
		return _indexed[0];
	}
public:
	CurrentCapability(void)
	{
		_indexed.emplace_back(0);
	}

	CurrentCapabilityIndexed<Cap>&
	Indexed(std::size_t index)
	{
		for(std::size_t i=_indexed.size(); i<=index; ++i)
		{
			_indexed.emplace_back(GLuint(i));
		}
		return _indexed[index];
	}

	CurrentCapabilityIndexed<Cap>&
	operator [] (std::size_t index)
	{
		return Indexed(index);
	}

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

	typedef SettingHolder<bool, GLuint> Holder;

	Holder Push(bool status)
	{
		return _zero().Push(status);
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
	 : SettingStack<bool, Nothing>(&_do_set)
	{
		try { this->_init(context::Capabilities::IsEnabled(Cap)); }
		catch(Error&){ }
	}

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
