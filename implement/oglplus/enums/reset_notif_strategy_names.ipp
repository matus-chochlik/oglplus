//  File implement/oglplus/enums/reset_notif_strategy_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/reset_notif_strategy.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	ResetNotificationStrategy*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_RESETNOTIFICATIONSTRATEGY)
#define OGLPLUS_IMPL_EVN_RESETNOTIFICATIONSTRATEGY
{
switch(value)
{
#if defined GL_NO_RESET_NOTIFICATION
	case GL_NO_RESET_NOTIFICATION: return CStrRef("NO_RESET_NOTIFICATION");
#endif
#if defined GL_LOSE_CONTEXT_ON_RESET
	case GL_LOSE_CONTEXT_ON_RESET: return CStrRef("LOSE_CONTEXT_ON_RESET");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

