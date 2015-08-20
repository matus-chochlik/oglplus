/**
 *  @file oglplus/texgen/cell_coord_output.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_CELL_COORD_OUTPUT_HPP
#define OGLPLUS_TEXGEN_CELL_COORD_OUTPUT_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/base_output.hpp>
#include <oglplus/texgen/global_node.hpp>
#include <oglplus/texgen/constant_output.hpp>

namespace oglplus {
namespace texgen {

class CellCoordOutputSlot
 : public BaseOutputSlot
{
public:
	FallbackInputSlot<GlobalCoordinateSlot,true> _coord;
	FallbackInputSlot<ConstantOutputSlot<Vec2f>> _cells;
	std::size_t _version;

	CellCoordOutputSlot(Node& parent);

	const char* Name(void)
	OGLPLUS_OVERRIDE;

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;

	bool Render(const RenderParams&)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/cell_coord_output.ipp>
//#endif

#endif // include guard
