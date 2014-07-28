/**
 *  @file oglplus/shapes/plane.ipp
 *  @brief Implementation of shapes::Plane
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {
namespace shapes {

OGLPLUS_LIB_FUNC
Plane::IndexArray
Plane::Indices(Plane::Default) const
{
	unsigned k = 0;
	unsigned offs = 0, leap = _udiv + 1;

	// primitive restart index (the count of indices)
	GLuint pri = _vdiv * (2 * leap + 1);
	IndexArray indices(pri);

	for(unsigned j=0; j!=_vdiv; ++j)
	{
		for(unsigned i=0; i!=leap; ++i)
		{
			indices[k++] = offs + i;
			indices[k++] = offs + i + leap;
		}
		indices[k++] = pri;
		offs += leap;
	}
	assert(k == indices.size());
	//
	// return the indices
	return indices;
}

OGLPLUS_LIB_FUNC
DrawingInstructions
Plane::Instructions(Plane::Default) const
{
	auto instructions = this->MakeInstructions();

	GLuint pri = _vdiv * (2 * (_udiv + 1) + 1);
	DrawOperation operation;
	operation.method = DrawOperation::Method::DrawElements;
	operation.mode = PrimitiveType::TriangleStrip;
	operation.first = GLuint(0);
	operation.count = pri;
	operation.restart_index = pri;
	operation.phase = 0;
	this->AddInstruction(instructions, operation);

	return instructions;
}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
OGLPLUS_LIB_FUNC
Plane::IndexArray
Plane::Indices(Plane::Patches) const
{
	unsigned k = 0;
	unsigned offs = 0, leap = _udiv + 1;
	IndexArray indices(_vdiv * _udiv * 6);

	for(unsigned j=0; j!=_vdiv; ++j)
	{
		for(unsigned i=0; i!=_udiv; ++i)
		{
			indices[k++] = offs + i;
			indices[k++] = offs + i + leap;
			indices[k++] = offs + i + 1;
			indices[k++] = offs + i + 1;
			indices[k++] = offs + i + leap;
			indices[k++] = offs + i + leap + 1;
		}
		offs += leap;
	}
	assert(k == indices.size());
	//
	// return the indices
	return indices;
}

OGLPLUS_LIB_FUNC
DrawingInstructions
Plane::Instructions(Plane::Patches) const
{
	auto instructions = this->MakeInstructions();

	DrawOperation operation;
	operation.method = DrawOperation::Method::DrawElements;
	operation.mode = PrimitiveType::Patches;
	operation.first = GLuint(0);
	operation.count = GLuint(_vdiv * _udiv * 6);
	operation.restart_index = DrawOperation::NoRestartIndex();
	operation.phase = 0;

	this->AddInstruction(instructions, operation);
	return instructions;
}
#endif //GL_VERSION_4_0

OGLPLUS_LIB_FUNC
Plane::IndexArray
Plane::Indices(Plane::Edges) const
{
	unsigned k = 0;
	unsigned leap = _udiv + 1;
	IndexArray indices(1 + 2*(_udiv+_vdiv));

	for(unsigned i=0; i!=leap; ++i)
		indices[k++] = i;
	for(unsigned j=0; j!=_vdiv; ++j)
		indices[k++] = (j + 2)*leap - 1;
	for(unsigned i=0; i!=_udiv; ++i)
		indices[k++] = (leap*(_vdiv+1)) - 2 - i;
	for(unsigned j=0; j!=_vdiv; ++j)
		indices[k++] = (_vdiv - j - 1)*leap;

	assert(k == indices.size());
	//
	// return the indices
	return indices;
}

OGLPLUS_LIB_FUNC
DrawingInstructions
Plane::Instructions(Plane::Edges) const
{
	auto instructions = this->MakeInstructions();

	DrawOperation operation;
	operation.method = DrawOperation::Method::DrawElements;
	operation.mode = PrimitiveType::LineStrip;
	operation.first = 0;
	operation.count = GLuint(1 + 2*(_udiv+_vdiv));
	operation.restart_index = DrawOperation::NoRestartIndex();
	operation.phase = 0;

	this->AddInstruction(instructions, operation);
	return instructions;
}

} // shapes
} // oglplus

