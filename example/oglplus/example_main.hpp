/**
 *  @file oglplus/example_main.hpp
 *  @brief Implements common code shared by examples
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef __OGLPLUS_EXAMPLE_EXAMPLE_MAIN_1119071146_HPP__
#define __OGLPLUS_EXAMPLE_EXAMPLE_MAIN_1119071146_HPP__

#include <oglplus/compile_error.hpp>
#include <oglplus/opt/application.hpp>

#include <oglplus/os/semaphore.hpp>

#include <iostream>
#include <cstring>

namespace oglplus {

inline void example_print_std_error_common(std::exception& error)
{
	std::cerr << " '" << error.what() << "'" << std::endl;
}

inline void example_print_error_common(Error& error)
{
	example_print_std_error_common(error);
	std::cerr << "in '" << error.GLSymbol() << "'" << std::endl;
	std::cerr << "at [" << error.File() << ":" << error.Line() << "]" << std::endl;

	bool nl = false;
	if(std::strlen(error.ClassName()))
	{
		std::cerr << error.ClassName();
		nl |= true;
	}
	if(!error.ObjectDescription().empty())
	{
		if(nl) std::cerr << " ";
		std::cerr << "'" << error.ObjectDescription() << "'";
		nl |= true;
	}
	if(std::strlen(error.BindTarget()))
	{
		if(!nl) std::cerr << "Object";
		std::cerr << " bound to '" << error.BindTarget() << "'";
		nl |= true;
	}
	if(nl) std::cerr << std::endl;

	auto i = error.Properties().begin(), e = error.Properties().end();
	if(i != e)
	{
		std::cerr << "Properties: " << std::endl;
		while(i != e)
		{
			std::cerr << "<" << i->first << "='" << i->second << "'>";
			++i;
			if(i != e) std::cerr << ", ";
			else std::cerr << ".";
		}
		std::cerr << std::endl;
	}
}

inline int example_main(int (*main_func)(int, char**), int argc, char ** argv)
{
	try
	{
		// this won't let multiple examples run at the same time
		os::CriticalSection cs("OGLplus example");
		// look at the options and extract useful things
		Application::ParseCommandLineOptions(argc, argv);
		//
		return main_func(argc, argv);
	}
	catch(ShaderVariableError& sve)
	{
		std::cerr << "Shader variable error";
		example_print_error_common(sve);
		sve.Cleanup();
	}
	catch(ProgramBuildError& pbe)
	{
		std::cerr << "Program build error";
		example_print_error_common(pbe);
		std::cerr << "Build log:" << std::endl;
		std::cerr << pbe.Log() << std::endl;
		pbe.Cleanup();
	}
	catch(LimitError& le)
	{
		std::cerr << "Limit error";
		example_print_error_common(le);
		std::cerr << "Value " << le.Value() << " exceeds limit ";
		std::cerr << le.Limit() << std::endl;
		le.Cleanup();
	}
	catch(Error& err)
	{
		std::cerr << "GL error";
		example_print_error_common(err);
		err.Cleanup();
	}
	catch(std::runtime_error& rte)
	{
		std::cerr << "Runtime error";
		example_print_std_error_common(rte);
		std::cerr << std::endl;
	}
	catch(std::exception& se)
	{
		std::cerr << "Error";
		example_print_std_error_common(se);
		std::cerr << std::endl;
	}
	return 1;
}

} // namespace oglplus

#endif // include guard
