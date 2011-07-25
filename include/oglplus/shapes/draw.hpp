/**
 *  @file oglplus/shapes/draw.hpp
 *  @brief Implementation of shape draw instructions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_DRAW_1107121519_HPP
#define OGLPLUS_SHAPES_DRAW_1107121519_HPP

namespace oglplus {
namespace shapes {

/// Structure containing information about how to draw a part of a shape
/**
 *  @note Do not use this class directly, use DrawingInstructions returned
 *  by the various shape builder classes instead.
 */
struct DrawOperation
{
	/// Enumeration of drawing methods
	enum class Method {
		DrawArrays,
		DrawElements
		// TODO
	};

	/// The method to be used to draw
	const Method method;
	/// The primitive type to be used to draw
	const PrimitiveType mode;

	/// The first element
	const GLuint first;

	/// Count of elements
	const GLuint count;

	// TODO

	/// Draw the part of a shape
	void Draw(GLuint inst_count = 1) const
	{
		// TODO: drawing multiple instances
		assert(inst_count == 1);
		switch(method)
		{
			case Method::DrawArrays:
				return _DrawArrays();
			case Method::DrawElements:
				return _DrawElements();
		}
	}
private:
	void _DrawArrays(void) const
	{
		::glDrawArrays(GLenum(mode), first, count);
		ThrowOnError(OGLPLUS_ERROR_INFO(DrawArrays));
	}

	void _DrawElements(void) const
	{
		::glDrawElements(
			GLenum(mode),
			count,
			GL_UNSIGNED_INT, // TODO
			nullptr
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(DrawElements));
	}
};

class DrawingInstructionWriter;

/// Class encapsulating the instructions for drawing of a shape
/** Instances of this class are produced by various shape builder
 *  classes implemented in the @c oglplus::shapes namespace and
 *  can be used to draw a shape from the data stored in vertex
 *  attrib buffers initialized from data returned by the member
 *  functions of the shape builder classes.
 *  @note Do not instantiate this class directly, use the appropriate
 *  member functions of the shape builder classes.
 *
 *  @see Cube
 */
class DrawingInstructions
{
private:

	typedef std::vector<DrawOperation> DrawOperationSeq;
	DrawOperationSeq _ops;

	DrawingInstructions(DrawOperationSeq&& ops)
	 : _ops(std::move(ops))
	{ }

	friend class DrawingInstructionWriter;
public:
	DrawingInstructions(DrawingInstructions&& temp)
	 : _ops(std::move(temp._ops))
	{ }

	DrawingInstructions(const DrawingInstructions& other)
	 : _ops(other._ops)
	{ }

	// TODO: drawing multiple instances
	/// Draw the shape from data in currently bound VBO's
	void Draw(GLuint inst_count = 1) const
	{
		for(auto i=_ops.begin(),e=_ops.end();i!=e;++i)
			i->Draw(inst_count);
	}
};

// Helper base class for shape builder classes making the drawing instructions
class DrawingInstructionWriter
{
private:
	typedef DrawingInstructions::DrawOperationSeq Ops;
protected:
	static DrawingInstructions MakeInstructions(Ops&& ops)
	{
		return DrawingInstructions(std::forward<Ops>(ops));
	}
};

} // shapes
} // oglplus

#endif // include guard
