/**
 *  @file oglplus/shapes/draw.hpp
 *  @brief Implementation of shape draw instructions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_DRAW_1107121519_HPP
#define OGLPLUS_SHAPES_DRAW_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/string.hpp>
#include <oglplus/primitive_type.hpp>
#include <oglplus/data_type.hpp>

#include <vector>

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
	OGLPLUS_ENUM_CLASS_BEGIN(Method, GLuint)
		OGLPLUS_ENUM_CLASS_VALUE(DrawArrays, 0)
		OGLPLUS_ENUM_CLASS_COMMA
		OGLPLUS_ENUM_CLASS_VALUE(DrawElements, 1)
		// TODO
	OGLPLUS_ENUM_CLASS_END

	/// The method to be used to draw
	Method method;
	/// The primitive type to be used to draw
	PrimitiveType mode;

	/// The first element
	GLuint first;

	/// Count of elements
	GLuint count;

	/// The phase of the drawing process
	/** The phase is a shape-builder-specific value that indicates
	 *  which part of the shape is being rendered. Together with a
	 *  "driver" function it can be used to change the shading
	 *  program parameters (like the values of uniform variables)
	 *  to switch the whole program or change GL state.
	 */
	GLuint phase;

	/// Draw the part of a shape
	template <typename IT>
	void Draw(
		const std::vector<IT>& indices,
		GLuint inst_count = 1
	) const
	{
		if(inst_count == 1)
		{
			switch(method)
			{
				case OGLPLUS_CONST_ENUM_VALUE(
					Method::DrawArrays
				): return _DrawArrays();

				case OGLPLUS_CONST_ENUM_VALUE(
					Method::DrawElements
				): return _DrawElements(indices);
			}
		}
		else
		{
			switch(method)
			{
				case OGLPLUS_CONST_ENUM_VALUE(
					Method::DrawArrays
				): return _DrawArrays(inst_count);

				case OGLPLUS_CONST_ENUM_VALUE(
					Method::DrawElements
				): return _DrawElements(
						indices,
						inst_count
					);
			}
		}
	}
private:
	void _DrawArrays(void) const
	{
		OGLPLUS_GLFUNC(DrawArrays)(GLenum(mode), first, count);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DrawArrays));
	}

	void _DrawArrays(GLuint inst_count) const
	{
		OGLPLUS_GLFUNC(DrawArraysInstanced)(
			GLenum(mode),
			first,
			count,
			inst_count
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DrawArraysInstanced));
	}

	template <typename IT>
	void _DrawElements(const std::vector<IT>& indices) const
	{
		const IT* base = indices.empty() ? nullptr : indices.data();
		OGLPLUS_GLFUNC(DrawElements)(
			GLenum(mode),
			count,
			GLenum(GetDataType<IT>()),
			(void*)(base + first)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DrawElements));
	}

	template <typename IT>
	void _DrawElements(
		const std::vector<IT>& indices,
		GLuint inst_count
	) const
	{
		const IT* base = indices.empty() ? nullptr : indices.data();
		OGLPLUS_GLFUNC(DrawElementsInstanced)(
			GLenum(mode),
			count,
			GLenum(GetDataType<IT>()),
			(void*)(base + first),
			inst_count
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DrawElementsInstanced));
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

	DrawingInstructions(void)
	{ }

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

	struct DefaultDriver
	{
		inline bool operator()(GLuint /*phase*/) const
		{
			return true;
		}
	};

	/// Draw the shape from data in currently bound VBOs indexed by indices
	template <typename IT, typename Driver>
	void Draw(
		const std::vector<IT>& indices,
		GLuint inst_count,
		Driver driver
	) const
	{
		auto i=_ops.begin(),e=_ops.end();
		if(i != e)
		{
			bool do_draw;
			if(driver(i->phase))
			{
				do_draw = true;
				i->Draw(indices, inst_count);
			}
			else do_draw = false;
			GLuint prev_phase = i->phase;
			++i;

			while(i!=e)
			{
				if(prev_phase != i->phase)
				{
					do_draw = driver(i->phase);
					prev_phase = i->phase;
				}
				if(do_draw) i->Draw(indices, inst_count);
				++i;
			}
		}
	}

	template <typename IT>
	void Draw(const std::vector<IT>& indices, GLuint inst_count = 1)
	{
		Draw(indices, inst_count, DefaultDriver());
	}

};

// Helper base class for shape builder classes making the drawing instructions
class DrawingInstructionWriter
{
private:
	typedef DrawingInstructions::DrawOperationSeq Operations;
protected:
	static DrawingInstructions MakeInstructions(void)
	{
		return DrawingInstructions();
	}

	static void AddInstruction(
		DrawingInstructions& instr,
		const DrawOperation& operation
	)
	{
		instr._ops.push_back(operation);
	}

	static DrawingInstructions MakeInstructions(const DrawOperation& operation)
	{
		DrawingInstructions instr;
		instr._ops.push_back(operation);
		return instr;
	}

	static DrawingInstructions MakeInstructions(Operations&& ops)
	{
		return DrawingInstructions(std::forward<Operations>(ops));
	}
};

} // shapes
} // oglplus

#endif // include guard
