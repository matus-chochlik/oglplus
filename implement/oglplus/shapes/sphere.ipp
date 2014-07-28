/**
 *  @file oglplus/shapes/sphere.ipp
 *  @brief Implementation of shapes::Sphere
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
Sphere::IndexArray
Sphere::Indices(Sphere::Default) const
{
	assert((1<<(sizeof(GLushort)*8))-1>=((_rings+2)*(_sections+1)));
	//
	const unsigned n = (_rings + 1)*(2 * (_sections + 1) + 1);
	//
	IndexArray indices(n);
	unsigned k = 0;
	unsigned offs = 0;
	// the triangle strips
	for(unsigned r=0; r!=(_rings+1); ++r)
	{
		for(unsigned s=0; s!=(_sections+1); ++s)
		{
			indices[k++] = offs + s;
			indices[k++] = offs + s + (_sections+1);
		}
		indices[k++] = n;
		offs += _sections + 1;
	}
	assert(k == indices.size());
	//
	// return the indices
	return std::move(indices);
}

OGLPLUS_LIB_FUNC
DrawingInstructions
Sphere::Instructions(Sphere::Default) const
{
	auto instructions = this->MakeInstructions();

	const GLuint n = (_rings + 1)*(2 * (_sections + 1) + 1);

	DrawOperation operation;
	operation.method = DrawOperation::Method::DrawElements;
	operation.mode = PrimitiveType::TriangleStrip;
	operation.first =  GLuint(0);
	operation.count = n;
	operation.restart_index = n;
	operation.phase = 0;
	this->AddInstruction(instructions, operation);

	return std::move(instructions);
}

} // shapes
} // oglplus

