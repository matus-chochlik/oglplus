/**
 *  @file oglplus/application.hpp
 *  @brief Application/startup options-related declarations unrelated to OpenGL
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_APPLICATION_1107121519_HPP
#define OGLPLUS_APPLICATION_1107121519_HPP

#include <string>
#include <cassert>
#include <iostream>

namespace oglplus {

/// A monostate class wrapping application and startup options-related things
/** @note This class is used mostly by internal library code.
 *
 *  @ingroup utility_classes
 */
class Application
{
private:
	static ::std::string& _app_rel_path(void)
	{
		static ::std::string str;
		return str;
	}

	static ::std::string& _app_name(void)
	{
		static ::std::string str;
		return str;
	}
public:
	/// Default constructor
	Application(void) = default;

	/// No copy construction
	Application(const Application&) = delete;

	static void ParseCommandLineOptions(int argc, const char** argv)
	{
		// TODO: switch this on platforms using other separators
		const char dirsep = '/';
		assert(argc > 0);
		assert(argv != 0);
		assert(argv[0] != 0);
		assert(argv[0] != 0);
		// now find the last separator
		const char* p = argv[0];
		const char* s = 0;
		while(*p)
		{
			if(*p == dirsep) s = p;
			++p;
		}
		// if found
		if(s != 0)
		{
			assert(s != p);
			_app_rel_path() = ::std::string(argv[0], s+1);
			_app_name() = ::std::string(s+1, p);
		}
		else _app_name() = ::std::string(argv[0], p);
	}

	static void ParseCommandLineOptions(int argc, char** argv)
	{
		ParseCommandLineOptions(argc, (const char**)argv);
	}

	/// Returns the path relative to the applications executable from CWD
	/** This function returns the path to the application executable
	 *  relative to the current working directory, including the trailing
	 *  path separator.
	 */
	static const ::std::string& RelativePath(void)
	{
		return _app_rel_path();
	}

	/// Returns the application executable base name
	static const ::std::string& Name(void)
	{
		return _app_name();
	}
};

} // namespace oglplus

#endif // include guard
