/**
 *  @file oglplus/texgen/arithmetic_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_ARITHMETIC_NODE_HPP
#define OGLPLUS_TEXGEN_ARITHMETIC_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/sibling_input.hpp>

namespace oglplus {
namespace texgen {

enum class UnaryArithmeticOp
{
	Abs,
	Sign,
	Sqrt,
	InverseSqrt,
	Floor,
	Ceiling,
	Exp,
	Exp2,
	Log,
	Log2
};

class UnaryArithmeticNode;

class UnaryArithmeticOutputSlot
 : public BaseOutputSlot
{
private:
	friend class UnaryArithmeticNode;

	FallbackInputSlot<AdaptiveConstantOutputSlot> _a;
	UnaryArithmeticOp _op;
public:
	UnaryArithmeticOutputSlot(Node& parent, UnaryArithmeticOp op);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class UnaryArithmeticNode
 : public BaseNode
{
private:
	UnaryArithmeticOutputSlot _output;
public:
	UnaryArithmeticNode(UnaryArithmeticOp);

	template <typename T>
	UnaryArithmeticNode& SetA(T v)
	{
		_output._a.Fallback().SetValue(v);
		return *this;
	}

	UnaryArithmeticNode& SetOp(UnaryArithmeticOp op)
	{
		_output._op = op;
		return *this;
	}

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	std::size_t OutputCount(void)
	OGLPLUS_OVERRIDE;

	OutputSlot& Output(std::size_t i)
	OGLPLUS_OVERRIDE;
};

template <UnaryArithmeticOp Op>
class FixedUnaryArithmeticNode
 : public UnaryArithmeticNode
{
public:
	FixedUnaryArithmeticNode(void)
	 : UnaryArithmeticNode(Op)
	{ }
};

enum class BinaryArithmeticOp
{
	Equal,
	NotEqual,
	Less,
	LessEqual,
	Greater,
	GreaterEqual,
	Addition,
	Subtraction,
	Multiplication,
	Division,
	Modulo,
	Maximum,
	Minimum,
	Distance,
	Dot
};

class BinaryArithmeticNode;

class BinaryArithmeticOutputSlot
 : public BaseOutputSlot
{
private:
	friend class BinaryArithmeticNode;

	SiblingInputSlot _a;
	SiblingInputSlot _b;
	BinaryArithmeticOp _op;
public:
	BinaryArithmeticOutputSlot(Node& parent, BinaryArithmeticOp op);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class BinaryArithmeticNode
 : public BaseNode
{
private:
	BinaryArithmeticOutputSlot _output;
public:
	BinaryArithmeticNode(BinaryArithmeticOp);

	template <typename T>
	BinaryArithmeticNode& SetA(T v)
	{
		_output._a.SetValue(v);
		return *this;
	}

	template <typename T>
	BinaryArithmeticNode& SetB(T v)
	{
		_output._b.SetValue(v);
		return *this;
	}

	BinaryArithmeticNode& SetOp(BinaryArithmeticOp op)
	{
		_output._op = op;
		return *this;
	}

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	std::size_t OutputCount(void)
	OGLPLUS_OVERRIDE;

	OutputSlot& Output(std::size_t i)
	OGLPLUS_OVERRIDE;

	void Validate(InputSlot&)
	OGLPLUS_OVERRIDE;
};

template <BinaryArithmeticOp Op>
class FixedBinaryArithmeticNode
 : public BinaryArithmeticNode
{
public:
	FixedBinaryArithmeticNode(void)
	 : BinaryArithmeticNode(Op)
	{ }
};

typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Equal>
	EqualNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::NotEqual>
	NotEqualNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Less>
	LessNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::LessEqual>
	LessEqualNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::GreaterEqual>
	GreaterEqualNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Greater>
	GreaterNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Equal>
	EqualNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Addition>
	AdditionNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Subtraction>
	SubtractionNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Multiplication>
	MultiplicationNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Division>
	DivisionNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Modulo>
	ModuloNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Distance>
	DistanceNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Maximum>
	MaximumNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Minimum>
	MinimumNode;
typedef FixedBinaryArithmeticNode<BinaryArithmeticOp::Dot>
	DotNode;

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/arithmetic_node.ipp>
//#endif

#endif // include guard
