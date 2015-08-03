/**
 *  @file oglplus/texgen/interface.hpp
 *  @brief Texgen interfaces
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_INTERFACE_HPP
#define OGLPLUS_TEXGEN_INTERFACE_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/string/def.hpp>

#include <cstddef>
#include <iosfwd>

namespace oglplus {
namespace texgen {

enum class SlotDataType
{
	Float, FloatVec2, FloatVec3, FloatVec4,
	Int, IntVec2, IntVec3, IntVec4
};

struct InputSlot;
struct OutputSlot;
struct Node;

// InputSlot
struct InputSlot
{
	virtual
	~InputSlot(void)
	OGLPLUS_NOEXCEPT(true)
	{ }

	virtual
	const char* Name(void) = 0;

	virtual
	bool AcceptsValueType(SlotDataType type) = 0;

	virtual
	bool IsConnected(void) = 0;

	virtual
	bool IsConnected(OutputSlot& output) = 0;

	virtual
	bool Connect(OutputSlot& output) = 0;

	virtual
	void Disconnect(OutputSlot& output) = 0;

	virtual
	void Update(void) = 0;
};

// OutputSlot
struct OutputSlot
{
	virtual
	~OutputSlot(void)
	OGLPLUS_NOEXCEPT(true)
	{ }

	virtual
	const char* Name(void) = 0;

	virtual
	SlotDataType ValueType(void) = 0;

	virtual
	std::ostream& Definitions(std::ostream&, unsigned glsl_version) = 0;

	virtual
	std::ostream& Expression(std::ostream&, unsigned glsl_version) = 0;

	virtual
	bool IsConnected(InputSlot& input) = 0;

	virtual
	bool Connect(InputSlot& input) = 0;

	virtual
	void Disconnect(InputSlot& input) = 0;

	virtual
	void UpdateConnected(void) = 0;
};

// Node
struct Node
{
	virtual
	~Node(void)
	OGLPLUS_NOEXCEPT(true)
	{ }

	virtual
	std::size_t InputCount(void) = 0;

	virtual
	InputSlot& Input(std::size_t index = 0) = 0;

	virtual
	std::size_t OutputCount(void) = 0;

	virtual
	OutputSlot& Output(std::size_t index = 0) = 0;

	virtual
	void Validate(InputSlot& input) = 0;

	virtual
	void Update(void) = 0;
};


} // namespace texgen
} // namespace oglplus

#endif // include guard
