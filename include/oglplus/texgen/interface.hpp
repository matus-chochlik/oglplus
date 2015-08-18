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
	Int, IntVec2, IntVec3, IntVec4,
	Bool, BoolVec2, BoolVec3, BoolVec4
};

struct InputSlot;
struct OutputSlot;
struct Node;

struct RenderParams
{
	std::size_t version;
	unsigned width;
	unsigned height;
};

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

	virtual
	bool Render(const RenderParams&) = 0;
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

	virtual
	bool Render(const RenderParams&) = 0;
};

// Node
struct Node
{
	virtual
	~Node(void)
	OGLPLUS_NOEXCEPT(true)
	{ }

	virtual
	const char* TypeName(void) = 0;

	virtual
	std::size_t InputCount(void) = 0;

	virtual
	InputSlot& Input(std::size_t index = 0) = 0;

	InputSlot& InputByName(const char* name);

	virtual
	std::size_t OutputCount(void) = 0;

	virtual
	OutputSlot& Output(std::size_t index = 0) = 0;

	OutputSlot& OutputByName(const char* name);

	virtual
	void Validate(InputSlot& input) = 0;

	virtual
	void Update(void) = 0;

	virtual
	bool Render(const RenderParams&) = 0;
};

static inline
InputSlot& operator > (std::size_t index, Node& node)
{
	return node.Input(index);
}

static inline
InputSlot& operator / (const char* input_name, Node& node)
{
	return node.InputByName(input_name);
}

static inline
OutputSlot& operator / (Node& node, const char* output_name)
{
	return node.OutputByName(output_name);
}

static inline
OutputSlot& operator > (Node& node, std::size_t index)
{
	return node.Output(index);
}

bool Connect(OutputSlot& output, InputSlot& input);
void Disconnect(OutputSlot& output, InputSlot& input);

static inline
bool operator + (OutputSlot& output, InputSlot& input)
{
	return Connect(output, input);
}

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/interface.ipp>
//#endif

#endif // include guard
