/**
 *  @file oglplus/texgen/voronoi_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_VORONOI_NODE_HPP
#define OGLPLUS_TEXGEN_VORONOI_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/base_output.hpp>
#include <oglplus/texgen/global_node.hpp>
#include <oglplus/texgen/adaptive_output.hpp>

namespace oglplus {
namespace texgen {

class Voronoi2DOutputSlot
 : public BaseOutputSlot
{
private:
	class CoordSlot
	 : public BaseOutputSlot
	{
	public:
		FallbackInputSlot<GlobalCoordinateSlot,true> _coord;
		FallbackInputSlot<ConstantOutputSlot<Vec2f>> _cells;
		std::size_t _version;

		CoordSlot(Node& parent);

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
public:
	FallbackInputSlot<AdaptiveConstantOutputSlot,true> _cell_offs;
	CoordSlot _coord;

	Voronoi2DOutputSlot(Node& parent);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

class Voronoi2DNode
 : public BaseNode
{
private:
	Voronoi2DOutputSlot _output;
public:
	Voronoi2DNode(void);

	Voronoi2DNode& SetCellCount(const Vec2f& cc);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	std::size_t OutputCount(void)
	OGLPLUS_OVERRIDE;

	OutputSlot& Output(std::size_t i)
	OGLPLUS_OVERRIDE;
};


} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/voronoi_node.ipp>
//#endif

#endif // include guard
