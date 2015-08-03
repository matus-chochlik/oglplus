/**
 *  @file oglplus/texgen/uniform_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <oglplus/program.hpp>
#include <sstream>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
UniformOutputSlot::
UniformOutputSlot(Node&, SlotDataType type)
 : _type(type)
{ }

OGLPLUS_LIB_FUNC
void
UniformOutputSlot::
BindLocation(void)
{
	std::stringstream identifier;
	AppendId(identifier);
	identifier << "u";

	_location = ProgVarLoc<tag::Uniform>(
		Program::Binding(),
		identifier.str()
	);
}

OGLPLUS_LIB_FUNC
const char*
UniformOutputSlot::
TypeName(void)
{
	return "Uniform";
}

OGLPLUS_LIB_FUNC
SlotDataType
UniformOutputSlot::
ValueType(void)
{
	return _type;
}

OGLPLUS_LIB_FUNC
String
UniformOutputSlot::
Definitions(unsigned)
{
	std::stringstream result;
	result << "uniform ";
	result << DataTypeName(_type);
	result << " ";
	AppendId(result);
	result << "u;\n";

	result << DataTypeName(_type) << " ";
	AppendId(result);
	result << "(vec3 o){return ";
	AppendId(result);
	result << "u;";
	result << "}\n";
	return String(result.str());
}

OGLPLUS_LIB_FUNC
UniformNode::
UniformNode(SlotDataType type)
 : _output(*this, type)
{ }

OGLPLUS_LIB_FUNC
std::size_t
UniformNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
UniformNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _output;
}

} // namespace texgen
} // namespace oglplus

