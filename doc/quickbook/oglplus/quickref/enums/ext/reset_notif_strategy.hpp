//  File doc/quickbook/oglplus/quickref/enums/ext/reset_notif_strategy.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/reset_notif_strategy.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_ext_reset_notif_strategy
namespace oglplus {

enum class ResetNotificationStrategy : GLenum
{
	NoResetNotification = GL_NO_RESET_NOTIFICATION_ARB,
	LoseContextOnReset  = GL_LOSE_CONTEXT_ON_RESET_ARB
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<ResetNotificationStrategy> __EnumValueName<ResetNotificationStrategy>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(ResetNotificationStrategy);
#endif

} // namespace oglplus
//]
