/**
 *  @file oalplus/error/alc.hpp
 *  @brief Declaration of OALplus ALC exception
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_ERROR_ALC_1107121317_HPP
#define OALPLUS_ERROR_ALC_1107121317_HPP

#include <oalplus/error/basic.hpp>

namespace oalplus {

class ErrorALC
 : public Error
{
public:
	static const char* Message(::ALCdevice* device, ALenum error_code)
	{
		return ::alcGetString(device, error_code);
	}

	ErrorALC(const char* message)
	 : Error(message)
	{ }

	~ErrorALC(void) throw() { }

	ErrorALC Device(const ::ALCdevice*) // TODO
	{
		return *this;
	}
};

#define OALPLUS_CHECK_ALC(DEVICE, ALFUNC, ERROR, ERROR_INFO) \
	OALPLUS_HANDLE_ERROR_IF(\
		error_code != ALC_NO_ERROR,\
		alcGetError(DEVICE),\
		ERROR::Message(DEVICE, error_code),\
		ERROR,\
		ERROR_INFO.\
		ALLibName("alc").\
		ALFuncName(#ALFUNC)\
	)

#define OALPLUS_CHECK_SIMPLE_ALC(DEVICE, ALFUNC) \
	OALPLUS_CHECK_ALC(DEVICE, ALFUNC, ErrorALC, Device(DEVICE))

#if !OALPLUS_LOW_PROFILE
#define OALPLUS_VERIFY_ALC(DEVICE, ALFUNC, ERROR, ERROR_INFO) \
	OALPLUS_CHECK_ALC(DEVICE, ALFUNC, ERROR, ERROR_INFO)
#else
#define OALPLUS_VERIFY_ALC(DEVICE, ALFUNC, ERROR, ERROR_INFO)
#endif

#define OALPLUS_VERIFY_SIMPLE_ALC(DEVICE, ALFUNC) \
	OALPLUS_VERIFY_ALC(DEVICE, ALFUNC, ErrorALC, Device(DEVICE))

} // namespace oalplus

#endif // include guard
