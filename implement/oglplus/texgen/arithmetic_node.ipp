/**
 *  @file oglplus/texgen/arithmetic_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <oglplus/texgen/data_type.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
UnaryArithmeticOutputSlot::
UnaryArithmeticOutputSlot(Node& parent, UnaryArithmeticOp op)
 : BaseOutputSlot(parent)
 , _a(parent, "A", Vec4f(0.0f))
 , _op(op)
{ }

OGLPLUS_LIB_FUNC
const char*
UnaryArithmeticOutputSlot::
TypeName(void)
{
	switch(_op)
	{
		case UnaryArithmeticOp::Abs:
			return "Abs";
		case UnaryArithmeticOp::Sign:
			return "Sign";
		case UnaryArithmeticOp::Sqrt:
			return "Sqrt";
		case UnaryArithmeticOp::InverseSqrt:
			return "InverseSqrt";
		case UnaryArithmeticOp::Floor:
			return "Floor";
		case UnaryArithmeticOp::Ceiling:
			return "Ceiling";
		case UnaryArithmeticOp::Exp:
			return "Exp";
		case UnaryArithmeticOp::Exp2:
			return "Exp2";
		case UnaryArithmeticOp::Log:
			return "Log";
		case UnaryArithmeticOp::Log2:
			return "Log2";
		default:;
	}
	return "UnaryArithmetic";
}

OGLPLUS_LIB_FUNC
SlotDataType
UnaryArithmeticOutputSlot::
ValueType(void)
{
	return MakeDataType(
		SlotDataType::Float,
		DataTypeDims(_a.ValueType())
	);
}

OGLPLUS_LIB_FUNC
std::ostream&
UnaryArithmeticOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_a.Definitions(result, version);

	const SlotDataType itype = _a.ValueType();
	const SlotDataType otype = ValueType();

	result << DataTypeName(otype) << " ";
	AppendId(result);
	result << "(vec3 po, vec3 so){\n\t";

	result << "return ";

	switch(_op)
	{
		case UnaryArithmeticOp::Abs:
			result << "abs("; break;
		case UnaryArithmeticOp::Sign:
			result << "sign("; break;
		case UnaryArithmeticOp::Sqrt:
			result << "sqrt("; break;
		case UnaryArithmeticOp::InverseSqrt:
			result << "inversesqrt("; break;
		case UnaryArithmeticOp::Floor:
			result << "floor("; break;
		case UnaryArithmeticOp::Ceiling:
			result << "ceil("; break;
		case UnaryArithmeticOp::Exp:
			result << "exp("; break;
		case UnaryArithmeticOp::Exp2:
			result << "exp2("; break;
		case UnaryArithmeticOp::Log:
			result << "log("; break;
		case UnaryArithmeticOp::Log2:
			result << "log2("; break;
	}
	ConversionPrefix(result, itype, otype);
	_a.Expression(result, version) << "(po, so)";
	ConversionSuffix(result, itype, otype);
	result << ");\n}\n";
	return result;
}

OGLPLUS_LIB_FUNC
UnaryArithmeticNode::
UnaryArithmeticNode(UnaryArithmeticOp op)
 : _output(*this, op)
{ }

OGLPLUS_LIB_FUNC
std::size_t
UnaryArithmeticNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
UnaryArithmeticNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _output._a;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
UnaryArithmeticNode::
SingleOutput(void)
{
	return _output;
}

OGLPLUS_LIB_FUNC
BinaryArithmeticOutputSlot::
BinaryArithmeticOutputSlot(Node& parent, BinaryArithmeticOp op)
 : BaseOutputSlot(parent)
 , _a(parent, "A", Vec4f(0.0f))
 , _b(parent, "B", Vec4f(1.0f))
 , _op(op)
{
	_a.AddSibling(_b);
	_b.AddSibling(_a);
}

OGLPLUS_LIB_FUNC
const char*
BinaryArithmeticOutputSlot::
TypeName(void)
{
	switch(_op)
	{
		case BinaryArithmeticOp::Equal:
			return "Equal";
		case BinaryArithmeticOp::NotEqual:
			return "NotEqual";
		case BinaryArithmeticOp::Less:
			return "Less";
		case BinaryArithmeticOp::LessEqual:
			return "LessEqual";
		case BinaryArithmeticOp::Greater:
			return "Greater";
		case BinaryArithmeticOp::GreaterEqual:
			return "GreaterEqual";
		case BinaryArithmeticOp::Addition:
			return "Addition";
		case BinaryArithmeticOp::Subtraction:
			return "Subtraction";
		case BinaryArithmeticOp::Multiplication:
			return "Multiplication";
		case BinaryArithmeticOp::Division:
			return "Division";
		case BinaryArithmeticOp::Modulo:
			return "Modulo";
		case BinaryArithmeticOp::Distance:
			return "Distance";
		case BinaryArithmeticOp::Maximum:
			return "Maximum";
		case BinaryArithmeticOp::Minimum:
			return "Minimum";
		case BinaryArithmeticOp::Power:
			return "Power";
		case BinaryArithmeticOp::Dot:
			return "Dot";
		default:;
	}
	return "BinaryArithmetic";
}

OGLPLUS_LIB_FUNC
SlotDataType
BinaryArithmeticOutputSlot::
ValueType(void)
{
	switch(_op)
	{
		case BinaryArithmeticOp::Distance:
			return SlotDataType::Float;
		default:;
	}
	return CommonDataType(_a.ValueType(), _b.ValueType());
}

OGLPLUS_LIB_FUNC
std::ostream&
BinaryArithmeticOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_a.Definitions(result, version);
	_b.Definitions(result, version);

	const SlotDataType otype = ValueType();

	result << DataTypeName(otype) << " ";
	AppendId(result);
	result << "(vec3 po, vec3 so){\n\t";

	result << "return ";

	switch(_op)
	{
		case BinaryArithmeticOp::Equal:
			result << "(" << DataTypeName(otype);
			result << "(1)-abs(sign("; break;
		case BinaryArithmeticOp::NotEqual:
			result << "abs(sign("; break;
		case BinaryArithmeticOp::Less:
			result << "max(-sign("; break;
		case BinaryArithmeticOp::LessEqual:
			result << "(" << DataTypeName(otype);
			result << "(1)-max(sign("; break;
		case BinaryArithmeticOp::Greater:
			result << "max(sign("; break;
		case BinaryArithmeticOp::GreaterEqual:
			result << "(" << DataTypeName(otype);
			result << "(1)-max(-sign("; break;
		case BinaryArithmeticOp::Modulo:
			result << "mod("; break;
		case BinaryArithmeticOp::Distance:
			result << "distance("; break;
		case BinaryArithmeticOp::Maximum:
			result << "max("; break;
		case BinaryArithmeticOp::Minimum:
			result << "min("; break;
		case BinaryArithmeticOp::Power:
			result << "pow("; break;
		case BinaryArithmeticOp::Dot:
			result << "dot("; break;
		default:
			result << "("; break;
	}
	result << "\n\t\t";
	ConversionPrefix(result, _a.ValueType(), otype);
	_a.Expression(result, version) << "(po, so)";
	ConversionSuffix(result, _a.ValueType(), otype);

	switch(_op)
	{
		case BinaryArithmeticOp::Addition:
			result << "+"; break;
		case BinaryArithmeticOp::Equal:
			OGLPLUS_FALLTHROUGH
		case BinaryArithmeticOp::NotEqual:
			OGLPLUS_FALLTHROUGH
		case BinaryArithmeticOp::Less:
			OGLPLUS_FALLTHROUGH
		case BinaryArithmeticOp::LessEqual:
			OGLPLUS_FALLTHROUGH
		case BinaryArithmeticOp::Greater:
			OGLPLUS_FALLTHROUGH
		case BinaryArithmeticOp::GreaterEqual:
			OGLPLUS_FALLTHROUGH
		case BinaryArithmeticOp::Subtraction:
			result << "-"; break;
		case BinaryArithmeticOp::Multiplication:
			result << "*"; break;
		case BinaryArithmeticOp::Division:
			result << "/"; break;
		default:
			result << ","; break;
	}

	result << "\n\t\t";
	ConversionPrefix(result, _b.ValueType(), otype);
	_b.Expression(result, version) << "(po, so)";
	ConversionSuffix(result, _b.ValueType(), otype);
	result << "\n\t";
	switch(_op)
	{
		case BinaryArithmeticOp::Equal:
			result << ")))"; break;
		case BinaryArithmeticOp::NotEqual:
			result << "))"; break;
		case BinaryArithmeticOp::Less:
			OGLPLUS_FALLTHROUGH
		case BinaryArithmeticOp::Greater:
			result << ")," << DataTypeName(otype);
			result << "(0))"; break;
		case BinaryArithmeticOp::LessEqual:
			OGLPLUS_FALLTHROUGH
		case BinaryArithmeticOp::GreaterEqual:
			result << ")," << DataTypeName(otype);
			result << "(0)))"; break;
		default:
			result << ")"; break;
	};
	result << ";\n}\n";
	return result;
}

OGLPLUS_LIB_FUNC
BinaryArithmeticNode::
BinaryArithmeticNode(BinaryArithmeticOp op)
 : _output(*this, op)
{ }

OGLPLUS_LIB_FUNC
std::size_t
BinaryArithmeticNode::
InputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
InputSlot&
BinaryArithmeticNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._a;
	return _output._b;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
BinaryArithmeticNode::
SingleOutput(void)
{
	return _output;
}

OGLPLUS_LIB_FUNC
void
BinaryArithmeticNode::
Validate(InputSlot&)
{
	// TODO
}

} // namespace texgen
} // namespace oglplus

