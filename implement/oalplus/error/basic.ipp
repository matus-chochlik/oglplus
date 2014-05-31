/**
 *  @file oalplus/error/basic.ipp
 *  @brief Implementation of Error / exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oalplus {

OALPLUS_LIB_FUNC
Error::Error(const char* message)
 : std::runtime_error(message)
 , _code(0)
#if !OALPLUS_ERROR_NO_FILE
 , _file(nullptr)
#endif
#if !OALPLUS_ERROR_NO_LINE
 , _line(0)
#endif
#if !OALPLUS_ERROR_NO_AL_SYMBOL
 , _allib_name(nullptr)
 , _alfunc_name(nullptr)
 , _enumpar_name(nullptr)
 , _enumpar(0)
 , _index(-1)
#endif
{ }

OALPLUS_LIB_FUNC
const char* Error::SourceFile(void) const
{
#if !OALPLUS_ERROR_NO_FILE
	return _file;
#else
	return nullptr;
#endif
}

OALPLUS_LIB_FUNC
const char* Error::SourceFunc(void) const
{
#if !OALPLUS_ERROR_NO_FUNC
	return _func;
#else
	return nullptr;
#endif
}

OALPLUS_LIB_FUNC
unsigned Error::SourceLine(void) const
{
#if !OALPLUS_ERROR_NO_LINE
	return _line;
#else
	return 0u;
#endif
}

OALPLUS_LIB_FUNC
const char* Error::ALLibName(void) const
{
#if !OALPLUS_ERROR_NO_AL_SYMBOL
	return _allib_name;
#else
	return nullptr;
#endif
}

OALPLUS_LIB_FUNC
const char* Error::ALFuncName(void) const
{
#if !OALPLUS_ERROR_NO_AL_SYMBOL
	return _alfunc_name;
#else
	return nullptr;
#endif
}

OALPLUS_LIB_FUNC
ALenum Error::EnumParam(void) const
{
#if !OALPLUS_ERROR_NO_AL_SYMBOL
	return _enumpar;
#else
	return 0;
#endif
}

OALPLUS_LIB_FUNC
const char* Error::EnumParamName(void) const
{
#if !OALPLUS_ERROR_NO_AL_SYMBOL
	return _enumpar_name;
#else
	return nullptr;
#endif
}

} // namespace oalplus

