/**
 *  @file advanced/cloud_trace/main_common.hpp
 *  @brief Implements common code shared by various main implementations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "app_data.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/fix_gl_version.hpp>
#include <oglplus/compile_error.hpp>

#include <stdexcept>
#include <system_error>
#include <iostream>
#include <cstring>

namespace oglplus {
namespace cloud_trace {

void print_std_error_common(
	std::exception& error,
	std::ostream& errstr
)
{
	errstr << " '" << error.what() << "'" << std::endl;
}

inline void print_error_common(
	Error& error,
	std::ostream& errstr
)
{
	print_std_error_common(error, errstr);
	errstr << "in '" << error.GLSymbol() << "'" << std::endl;
	errstr << "at [";
	errstr << error.File() << ":" << error.Line();
	errstr << "]" << std::endl;

	bool nl = false;
	if(std::strlen(error.ClassName()))
	{
		errstr << error.ClassName();
		nl |= true;
	}
	if(!error.ObjectDescription().empty())
	{
		if(nl) errstr << " ";
		errstr << "'" << error.ObjectDescription() << "'";
		nl |= true;
	}
	if(std::strlen(error.BindTarget()))
	{
		if(!nl) errstr << "Object";
		errstr << " bound to '" << error.BindTarget() << "'";
		nl |= true;
	}
	if(nl) errstr << std::endl;

	auto i = error.Properties().begin(), e = error.Properties().end();
	if(i != e)
	{
		errstr << "Properties: " << std::endl;
		while(i != e)
		{
			errstr << "<" << i->first << "='" << i->second << "'>";
			++i;
			if(i != e) errstr << ", ";
			else errstr << ".";
		}
		errstr << std::endl;
	}
}

int do_run_main(int (*main_func)(AppData&), AppData& app_data)
{
	std::ostream& errstr = app_data.errstr();
	try
	{
		return main_func(app_data);
	}
	catch(ShaderVariableError& sve)
	{
		errstr << "Shader variable error";
		print_error_common(sve, errstr);
		sve.Cleanup();
	}
	catch(ProgramBuildError& pbe)
	{
		errstr << "Program build error";
		print_error_common(pbe, errstr);
		errstr << "Build log:" << std::endl;
		errstr << pbe.Log() << std::endl;
		pbe.Cleanup();
	}
	catch(LimitError& le)
	{
		errstr << "Limit error";
		print_error_common(le, errstr);
		errstr << "Value " << le.Value() << " exceeds limit ";
		errstr << le.Limit() << std::endl;
		le.Cleanup();
	}
	catch(Error& err)
	{
		errstr << "GL error";
		print_error_common(err, errstr);
		err.Cleanup();
	}
	catch(std::system_error& sye)
	{
		errstr << "System error";
		print_std_error_common(sye, errstr);
		errstr << "Error code: " << sye.code() << std::endl;
		errstr << std::endl;
	}
	catch(std::runtime_error& rte)
	{
		errstr << "Runtime error";
		print_std_error_common(rte, errstr);
		errstr << std::endl;
	}
	catch(std::exception& se)
	{
		errstr << "Error";
		print_std_error_common(se, errstr);
		errstr << std::endl;
	}
	return 1;
}

} // namespace cloud_trace
} // namespace oglplus
