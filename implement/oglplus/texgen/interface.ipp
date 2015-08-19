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
#include <set>

namespace oglplus {
namespace texgen {

class CompileContextImpl
{
private:
	unsigned _glsl_version;

	std::set<std::string> _tags;
public:
	CompileContextImpl(unsigned glsl_version)
	 : _glsl_version(glsl_version)
	{ }

	unsigned GLSLVersion(void) const
	{
		return _glsl_version;
	}

	void AddTag(const std::string& tag)
	{
		_tags.insert(tag);
	}

	bool
	HasTag(const std::string& tag)
	{
		return _tags.find(tag) != _tags.end();
	}
};

const CompileContextImpl&
CompileContext::
Impl(void) const
{
	assert(_impl != nullptr);
	return *_impl;
}

CompileContextImpl&
CompileContext::
Impl(void)
{
	assert(_impl != nullptr);
	return *_impl;
}


OGLPLUS_LIB_FUNC
CompileContext::
CompileContext(void)
 : _impl(new CompileContextImpl(150))
{ }

OGLPLUS_LIB_FUNC
unsigned
CompileContext::
GLSLVersion(void) const
{
	return Impl().GLSLVersion();
}

OGLPLUS_LIB_FUNC
void
CompileContext::
AddTag(const std::string& tag)
{
	Impl().AddTag(tag);
}

OGLPLUS_LIB_FUNC
bool
CompileContext::
HasTag(const std::string& tag)
{
	return Impl().HasTag(tag);
}

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

	std::string message("No input slot with name '");
	message.append(name);
	message.append("' in '");
	message.append(TypeName());
	message.append("' node.");

	if(InputCount() > 0)
	{
		message.append(" Use one of {'");
		message.append(Input(0).Name());
		for(std::size_t i=1,n=InputCount(); i<n; ++i)
		{
			message.append("', '");
			message.append(Input(i).Name());
		}
		message.append("'}");
	}
	else
	{
		message.append(" This node type has no inputs");
	}

	message.append(".");

	throw std::runtime_error(message);
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

	std::string message("No output slot with name '");
	message.append(name);
	message.append("' in '");
	message.append(TypeName());
	message.append("' node.");

	if(OutputCount() > 0)
	{
		message.append(" Use one of {'");
		message.append(Output(0).Name());
		for(std::size_t i=1,n=OutputCount(); i<n; ++i)
		{
			message.append("', '");
			message.append(Output(i).Name());
		}
		message.append("'}");
	}
	else
	{
		message.append(" This node type has no outputs");
	}

	message.append(".");

	throw std::runtime_error(message);

	return Output(0);
}

OGLPLUS_LIB_FUNC
bool
Connect(OutputSlot& output, InputSlot& input)
{
	return
		input.Connect(output)&&
		output.Connect(input);
}

OGLPLUS_LIB_FUNC
void
Disconnect(OutputSlot& output, InputSlot& input)
{
	input.Disconnect(output);
	output.Disconnect(input);
}

} // namespace texgen
} // namespace oglplus

