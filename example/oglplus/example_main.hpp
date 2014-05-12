/**
 *  @file oglplus/example_main.hpp
 *  @brief Implements common code shared by examples
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef __OGLPLUS_EXAMPLE_EXAMPLE_MAIN_1119071146_HPP__
#define __OGLPLUS_EXAMPLE_EXAMPLE_MAIN_1119071146_HPP__

#include <oglplus/error/prog_var.hpp>
#include <oglplus/error/program.hpp>
#include <oglplus/error/limit.hpp>
#include <oglplus/opt/application.hpp>

#include <oglplus/os/semaphore.hpp>

#include <stdexcept>
#include <system_error>
#include <iostream>
#include <cstring>

namespace oglplus {

inline void example_print_std_error_common(
	std::exception& error,
	std::ostream& errstr
)
{
	errstr << " '" << error.what() << "'" << std::endl;
}

inline void example_print_error_common(
	Error& error,
	std::ostream& errstr
)
{
	example_print_std_error_common(error, errstr);
	errstr << "in '" << error.GLFuncName() << "'" << std::endl;
	errstr << "at [";
	errstr << error.SourceFile() << ":" << error.SourceLine();
	errstr << "]" << std::endl;
}

inline void example_print_error_common(
	ObjectError& error,
	std::ostream& errstr
)
{
	example_print_std_error_common(error, errstr);
	bool nl = false;
	if(std::strlen(error.ClassName()))
	{
		errstr << error.ClassName();
		nl |= true;
	}
	if(!error.ObjectDesc().empty())
	{
		if(nl) errstr << " ";
		errstr << "'" << error.ObjectDesc() << "'";
		nl |= true;
	}
	if(std::strlen(error.TargetName()))
	{
		if(!nl) errstr << "Object";
		errstr << " bound to '" << error.TargetName() << "'";
		nl |= true;
	}
	if(nl) errstr << std::endl;
}

template <typename Func>
inline int example_guarded_exec(Func func, std::ostream& errstr)
{
	try
	{
		return func();
	}
	catch(ProgVarError& pve)
	{
		errstr << "Program variable error";
		example_print_error_common(pve, errstr);
	}
	catch(ProgramBuildError& pbe)
	{
		errstr << "Program build error";
		example_print_error_common(pbe, errstr);
		errstr << "Build log:" << std::endl;
		errstr << pbe.Log() << std::endl;
	}
	catch(LimitError& le)
	{
		errstr << "Limit error";
		example_print_error_common(le, errstr);
		errstr << "Value " << le.Value() << " exceeds limit ";
		errstr << le.Limit() << std::endl;
	}
	catch(ObjectError& oe)
	{
		errstr << "Object error";
		example_print_error_common(oe, errstr);
	}
	catch(Error& err)
	{
		errstr << "GL error";
		example_print_error_common(err, errstr);
	}
	catch(std::system_error& sye)
	{
		errstr << "System error";
		example_print_std_error_common(sye, errstr);
		errstr << "Error code: " << sye.code() << std::endl;
		errstr << std::endl;
	}
	catch(std::runtime_error& rte)
	{
		errstr << "Runtime error";
		example_print_std_error_common(rte, errstr);
		errstr << std::endl;
	}
	catch(std::exception& se)
	{
		errstr << "Error";
		example_print_std_error_common(se, errstr);
		errstr << std::endl;
	}
	return 1;
}

inline int example_main(
	int (*main_func)(int, char**),
	int argc,
	char ** argv
)
{
	struct main_wrapper
	{
		int (*main_func)(int, char**);
		int argc;
		char** argv;

		int operator()(void) const
		{
			os::CriticalSection cs("OGLplus example");
			Application::ParseCommandLineOptions(argc, argv);
			return main_func(argc, argv);
		}
	} wrapped_main = {main_func, argc, argv};

	return example_guarded_exec(wrapped_main, std::cerr);
}

} // namespace oglplus

#endif // include guard
