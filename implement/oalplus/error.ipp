/**
 *  @file oalplus/error.ipp
 *  @brief Implementation of OALplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OALPLUS_CUSTOM_ERROR_HANDLING
#include <stack>
#endif

namespace oalplus {

#if OALPLUS_CUSTOM_ERROR_HANDLING

namespace aux {

OALPLUS_LIB_FUNC
std::stack<ErrorHandlerFunc>& _error_handlers(void)
{
	static std::stack<ErrorHandlerFunc> _handlers;
	return _handlers;
}

OALPLUS_LIB_FUNC
bool _has_error_handler(void)
{
	return !_error_handlers().empty();
}

OALPLUS_LIB_FUNC
ErrorHandlerFunc& _get_error_handler(void)
{
	assert(!_error_handlers().empty());
	return _error_handlers().top();
}

} // namespace aux

OALPLUS_LIB_FUNC
LocalErrorHandler::LocalErrorHandler(ErrorHandlerFunc handler)
{
	aux::_error_handlers().push(handler);
	_installed = aux::_error_handlers().size();
}

OALPLUS_LIB_FUNC
LocalErrorHandler::~LocalErrorHandler(void)
{
	if(_installed)
	{
		assert(aux::_error_handlers().size() == _installed);
		aux::_error_handlers().pop();
	}
}

#endif // OALPLUS_CUSTOM_ERROR_HANDLING

OALPLUS_LIB_FUNC
void HandleError(
	ALenum code,
	const ALchar* msg,
	const ErrorInfo& info,
	bool assertion
)
{
#if OALPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			code,
			msg,
			info,
			assertion,
			code == AL_OUT_OF_MEMORY,
			false,
			false
		)
	)) return;
#endif // OALPLUS_CUSTOM_ERROR_HANDLING
	throw Error(code, msg?msg:"Unknown error", info, assertion);
}

OALPLUS_LIB_FUNC
void HandleALUTError(ALenum code, const ErrorInfo& info, bool assertion)
{
	const ALchar* msg = "Unknown error";
	switch(code)
	{
		case ALUT_ERROR_OUT_OF_MEMORY:
			msg = "ALUT out of memory";
			break;
		case ALUT_ERROR_INVALID_OPERATION:
			msg = "Invalid ALUT operation";
			break;
		case ALUT_ERROR_NO_CURRENT_CONTEXT:
			msg = "There is no current AL context";
			break;
		case ALUT_ERROR_AL_ERROR_ON_ENTRY:
			msg = "An AL error on entry to ALUT call";
			break;
		case ALUT_ERROR_ALC_ERROR_ON_ENTRY:
			msg = "An ALC error on entry to ALUT call";
			break;
		case ALUT_ERROR_UNSUPPORTED_FILE_TYPE:
			msg = "Unsupported file type";
			break;
		case ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE:
			msg = "Unsupported mode within an otherwise usable file type";
			break;
		case ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA:
			msg = "The sound data was corrupt or truncatd";
			break;
	}
	HandleError(code, msg, info, assertion);
}

} // namespace oalplus

