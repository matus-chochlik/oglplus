/**
 *  @file oglplus/texgen/base_input.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_BASE_INPUT_HPP
#define OGLPLUS_TEXGEN_BASE_INPUT_HPP

#include <oglplus/texgen/interface.hpp>
#include <oglplus/texgen/data_type.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

// BaseInputSlot
class BaseInputSlot
 : public InputSlot
{
private:
	Node* _parent;
	const char* _name;
	OutputSlot* _output;
protected:
	BaseInputSlot(Node& parent, const char* name)
	OGLPLUS_NOEXCEPT(true);
public:
	~BaseInputSlot(void)
	OGLPLUS_NOEXCEPT(true);

	Node& Parent(void);
	OutputSlot& Output(void);

	const char* Name(void)
	OGLPLUS_OVERRIDE;

	bool IsConnected(void)
	OGLPLUS_OVERRIDE;

	bool IsConnected(OutputSlot& output)
	OGLPLUS_OVERRIDE;

	bool DoConnect(OutputSlot& output);

	bool Connect(OutputSlot& output)
	OGLPLUS_OVERRIDE;

	void Disconnect(OutputSlot& output)
	OGLPLUS_OVERRIDE;

	void Disconnect(void);

	void Update(void)
	OGLPLUS_OVERRIDE;
};

// FallbackInputSlot
template <typename FallbackOutputSlot, bool AcceptsAny = false>
class FallbackInputSlot
 : public BaseInputSlot
{
private:
	FallbackOutputSlot _fallback;
public:
	FallbackInputSlot(Node& parent, const char* name)
	 : BaseInputSlot(parent, name)
	 , _fallback()
	{ }

	template <typename ... P>
	FallbackInputSlot(Node& parent, const char* name, P&& ... p)
	 : BaseInputSlot(parent, name)
	 , _fallback(std::forward<P>(p)...)
	{ }

	FallbackOutputSlot& Fallback(void)
	{
		return _fallback;
	}

	bool AcceptsValueType(SlotDataType type)
	OGLPLUS_OVERRIDE
	{
		return AcceptsAny ||
			DataTypeConvertible(type, _fallback.ValueType());
	}

	SlotDataType ValueType(void)
	{
		if(IsConnected())
		{
			return Output().ValueType();
		}
		else
		{
			return _fallback.ValueType();
		}
	}

	std::ostream& Definitions(std::ostream& out, unsigned version)
	{
		if(IsConnected())
		{
			return Output().Definitions(out, version);
		}
		else
		{
			return _fallback.Definitions(out, version);
		}
	}

	std::ostream& Expression(std::ostream& out, unsigned version)
	{
		if(IsConnected())
		{
			return Output().Expression(out, version);
		}
		else
		{
			return _fallback.Expression(out, version);
		}
	}
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/base_input.ipp>
//#endif

#endif // include guard
