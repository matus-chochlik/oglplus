/**
 *  @file oglplus/texgen/interface.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/config/basic.hpp>
#include <stdexcept>
#include <cassert>
#include <cstring>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
InputSlot&
Node::
InputByName(const char* name)
{
	for(std::size_t i=0,n=InputCount(); i<n; ++i)
	{
		if(std::strcmp(Input(i).Name(), name) == 0)
		{
			return Input(i);
		}
	}
	throw std::runtime_error(
		std::string("No input slot with name '")+
		name+
		std::string("' in '")+
		TypeName()+
		std::string("' node")
	);
	return Input(0);
}

OGLPLUS_LIB_FUNC
OutputSlot&
Node::
OutputByName(const char* name)
{
	for(std::size_t i=0,n=OutputCount(); i<n; ++i)
	{
		if(std::strcmp(Output(i).Name(), name) == 0)
		{
			return Output(i);
		}
	}
	throw std::runtime_error(
		std::string("Invalid out slot name '")+
		name+
		std::string("' in '")+
		TypeName()+
		std::string("' node")
	);
	return Output(0);
}

} // namespace texgen
} // namespace oglplus

