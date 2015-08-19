/**
 *  @file oglplus/texgen/base_output.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_BASE_OUTPUT_HPP
#define OGLPLUS_TEXGEN_BASE_OUTPUT_HPP

#include <oglplus/texgen/interface.hpp>
#include <iostream>
#include <set>

namespace oglplus {
namespace texgen {

class BaseOutputSlot
 : public OutputSlot
{
private:
	Node* _parent;
	std::set<InputSlot*> _slots;
public:
	BaseOutputSlot(Node& parent);

	~BaseOutputSlot(void)
	OGLPLUS_NOEXCEPT(true);

	Node& Parent(void)
	OGLPLUS_NOEXCEPT(true);

	virtual
	const char* TypeName(void) = 0;

	const char* Name(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;

	bool IsConnected(InputSlot& slot)
	OGLPLUS_OVERRIDE;

	bool Connect(InputSlot& slot)
	OGLPLUS_OVERRIDE;

	void Disconnect(InputSlot& slot)
	OGLPLUS_OVERRIDE;

	void DisconnectIncompatible(void);

	void UpdateConnected(void)
	OGLPLUS_OVERRIDE;

	bool Render(const RenderParams&)
	OGLPLUS_OVERRIDE;

	std::intptr_t GetId(void);

	void AppendId(std::ostream&, const char*);
	void AppendId(std::ostream&);

	std::ostream& Expression(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/base_output.ipp>
//#endif

#endif // include guard
