/**
 *  @example eglplus/001_string_queries.cpp
 *  @brief Shows very basic usage of EGLplus by printing some information
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <eglplus/egl.hpp>
#include <eglplus/all.hpp>

#include <iostream>

int main(void)
{
	// open the default display
	eglplus::Display display;
	// initialize the library
	eglplus::LibEGL egl(display);
	//
	// print some info
	std::cout << "Vendor: " << egl.Vendor() << std::endl;
	std::cout << "Version: " << egl.Version() << std::endl;
	//
	std::cout << "Client APIs:" << std::endl;
	for(auto r=egl.ClientAPIs(); !r.Empty(); r.Next())
		std::cout << '\t' << r.Front() << std::endl;
	//
	std::cout << "Extensions :" << std::endl;
	for(auto r=egl.Extensions(); !r.Empty(); r.Next())
		std::cout << '\t' << r.Front() << std::endl;
	//
	return 0;
}
