/**
 *  @file eglplus/configs.ipp
 *  @brief Implementation of EGLplus' configurations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace eglplus {

EGLPLUS_LIB_FUNC
void Configs::_get_all(void)
{
	EGLint num = 0;
	EGLPLUS_EGLFUNC(GetConfigs)(
		FriendOf<Display>::GetHandle(_display),
		nullptr,
		0,
		&num
	);
	EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(GetConfigs));
	if(num)
	{
		_configs.resize(num);
		EGLPLUS_EGLFUNC(GetConfigs)(
			FriendOf<Display>::GetHandle(_display),
			_configs.data(),
			num,
			&num
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(GetConfigs));
	}
}

EGLPLUS_LIB_FUNC
void Configs::_choose(const FinishedConfigAttribs& attribs)
{
	EGLint num = 0;
	EGLPLUS_EGLFUNC(ChooseConfig)(
		FriendOf<Display>::GetHandle(_display),
		attribs.Get(),
		nullptr,
		0,
		&num
	);
	EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(ChooseConfig));
	if(num)
	{
		_configs.resize(num);
		EGLPLUS_EGLFUNC(ChooseConfig)(
			FriendOf<Display>::GetHandle(_display),
			attribs.Get(),
			_configs.data(),
			num,
			&num
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(ChooseConfig));
	}
}

} // namespace eglplus

