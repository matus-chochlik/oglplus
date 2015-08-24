/**
 *  @file oglplus/texgen/base_input.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/config/basic.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
BaseInputSlot::
BaseInputSlot(Node& parent, const char* name)
OGLPLUS_NOEXCEPT(true)
 : _parent(&parent)
 , _name(name)
 , _output(nullptr)
{
	assert(_parent != nullptr);
}

OGLPLUS_LIB_FUNC
BaseInputSlot::
~BaseInputSlot(void)
OGLPLUS_NOEXCEPT(true)
{
	if(_output)
	{
		_output->Disconnect(*this);
	}
}

OGLPLUS_LIB_FUNC
Node&
BaseInputSlot::
Parent(void)
{
	assert(_parent != nullptr);
	return *_parent;
}

OGLPLUS_LIB_FUNC
OutputSlot&
BaseInputSlot::
Output(void)
{
	assert(IsConnected());
	return *_output;
}

OGLPLUS_LIB_FUNC
const char*
BaseInputSlot::
Name(void)
{
	return _name;
}

OGLPLUS_LIB_FUNC
bool
BaseInputSlot::
IsConnected(void)
{
	return _output != nullptr;
}

OGLPLUS_LIB_FUNC
bool
BaseInputSlot::
IsConnected(OutputSlot& output)
{
	return _output == &output;
}

OGLPLUS_LIB_FUNC
bool
BaseInputSlot::
DoConnect(OutputSlot& output)
{
	if(AcceptsValueType(output.ValueType()))
	{
		if(IsConnected())
		{
			texgen::Disconnect(*_output, *this);
		}
		_output = &output;
		return true;
	}
	return false;
}

OGLPLUS_LIB_FUNC
bool
BaseInputSlot::
Connect(OutputSlot& output)
{
	if(DoConnect(output))
	{
		try
		{
			_parent->Validate(*this);
			_parent->Update();
			return true;
		}
		catch(...)
		{
			_output = nullptr;
			throw;
		}
	}
	return false;
}

OGLPLUS_LIB_FUNC
void
BaseInputSlot::
Disconnect(void)
{
	_output = nullptr;
	_parent->Update();
}

OGLPLUS_LIB_FUNC
void
BaseInputSlot::
Disconnect(OutputSlot& output)
{
	assert(IsConnected(output));
	Disconnect();
}

OGLPLUS_LIB_FUNC
void
BaseInputSlot::
Update(void)
{
	assert(_parent != nullptr);
	_parent->Update();
}

OGLPLUS_LIB_FUNC
bool
BaseInputSlot::
Render(const RenderParams& params)
{
	if(IsConnected())
	{
		return Output().Render(params);
	}
	return true;
}

} // namespace texgen
} // namespace oglplus

