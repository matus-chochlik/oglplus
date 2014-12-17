/**
 *  @file oglplus/client/hints.hpp
 *  @brief Client current hint setting stack
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_HINTS_1412071213_HPP
#define OGLPLUS_CLIENT_HINTS_1412071213_HPP

#include <oglplus/client/setting.hpp>
#include <oglplus/context/hints.hpp>
#include <cassert>

namespace oglplus {
namespace client {
namespace aux {

template <HintTarget Hint>
class CurrentHint
 : public SettingStack<HintOption, Nothing>
{
private:
	static
	HintOption _do_get(Nothing)
	{
		return context::Hints::Hint(Hint);
	}

	static
	void _do_set(HintOption option, Nothing)
	{
		context::Hints::Hint(Hint, option);
	}
public:
	CurrentHint(void)
	 : SettingStack<HintOption, Nothing>(&_do_get, &_do_set)
	{ }
};

} // namespace aux
} // namespace client

#include <oglplus/enums/hint_target_class.ipp>

namespace client {

class CurrentHints
{
public:
	oglplus::enums::EnumToClass<
		Nothing,
		HintTarget,
		aux::CurrentHint
	> Hints;
};

} // namespace client
} // namespace oglplus

#endif // include guard
