//  File implement/oglplus/enums/ext/reset_notif_strategy_range.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/reset_notif_strategy.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2019 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	ResetNotificationStrategyARB
> ValueRange_(ResetNotificationStrategyARB*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_RESETNOTIFICATIONSTRATEGYARB)
#define OGLPLUS_IMPL_EVR_RESETNOTIFICATIONSTRATEGYARB
{
static const GLenum _values[] = {
#if defined GL_NO_RESET_NOTIFICATION_ARB
GL_NO_RESET_NOTIFICATION_ARB,
#endif
#if defined GL_LOSE_CONTEXT_ON_RESET_ARB
GL_LOSE_CONTEXT_ON_RESET_ARB,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	ResetNotificationStrategyARB
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

