/**
 *  @file oglplus/shapes/wrapper.hpp
 *  @brief Wrapper managing VAOs, VBOs and instructions used to render a shape
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_WRAPPER_1202020923_HPP
#define OGLPLUS_SHAPES_WRAPPER_1202020923_HPP

#include <oglplus/vertex_array.hpp>
#include <oglplus/vertex_attrib.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/array.hpp>
#include <oglplus/program.hpp>
#include <oglplus/context.hpp>
#include <oglplus/error.hpp>
#include <oglplus/string.hpp>

#include <oglplus/shapes/draw.hpp>
#include <oglplus/shapes/vert_attr_info.hpp>

#include <vector>
#include <functional>

namespace oglplus {
namespace shapes {

/// Wraps instructions and VAO+VBOs used to render a shape built by @p ShapeBuilder
template <typename ShapeBuilder>
class ShapeWrapper
{
protected:
	FaceOrientation face_winding;
	// helper object encapsulating shape drawing instructions
	shapes::DrawingInstructions shape_instr;
	// indices pointing to shape primitive elements
	typename ShapeBuilder::IndexArray shape_indices;

	Context gl;

	// A vertex array object for the rendered shape
	VertexArray vao;

	// VBOs for the shape's vertex attributes
	Array<Buffer> vbos;

	// numbers of values per vertex for the individual attributes
	std::vector<GLuint> npvs;

	// names of the individual vertex attributes
	std::vector<String> names;

	template <typename Iterator>
	void _init(const ShapeBuilder& builder, Iterator name, Iterator end)
	{
		// bind the VAO for the shape
		vao.Bind();

		typename ShapeBuilder::VertexAttribs vert_attr_info;
		size_t i = 0;
		std::vector<GLfloat> data;
		while(name != end)
		{
			auto getter = vert_attr_info.VertexAttribGetter(
				data,
				*name
			);
			if(getter != nullptr)
			{
				// bind the VBO for the vertex attribute
				vbos[i].Bind(Buffer::Target::Array);
				npvs[i] = getter(builder, data);
				names[i] = *name;
				// upload the data
				Buffer::Data(Buffer::Target::Array, data);
			}
			++name;
			++i;
		}
	}
public:
	template <typename StdRange>
	ShapeWrapper(const StdRange& names, const ShapeBuilder& builder)
	 : face_winding(builder.FaceWinding())
	 , shape_instr(builder.Instructions())
	 , shape_indices(builder.Indices())
	 , vbos(names.end() - names.begin())
	 , npvs(names.end() - names.begin(), 0)
	 , names(names.end() - names.begin())
	{
		_init(builder, names.begin(), names.end());
	}

	template <typename StdRange>
	ShapeWrapper(
		const StdRange& names,
		const ShapeBuilder& builder,
		const Program& prog
	): face_winding(builder.FaceWinding())
	 , shape_instr(builder.Instructions())
	 , shape_indices(builder.Indices())
	 , vbos(names.end() - names.begin())
	 , npvs(names.end() - names.begin(), 0)
	 , names(names.end() - names.begin())
	{
		_init(builder, names.begin(), names.end());
		UseInProgram(prog);
	}

	ShapeWrapper(
		const std::initializer_list<const GLchar*>& names,
		const ShapeBuilder& builder,
		const Program& prog
	): face_winding(builder.FaceWinding())
	 , shape_instr(builder.Instructions())
	 , shape_indices(builder.Indices())
	 , vbos(names.end() - names.begin())
	 , npvs(names.end() - names.begin(), 0)
	 , names(names.end() - names.begin())
	{
		_init(builder, names.begin(), names.end());
		UseInProgram(prog);
	}

	void UseInProgram(const Program& prog)
	{
		vao.Bind();
		size_t i=0, n = npvs.size();
		while(i != n) if(npvs[i] != 0) try
		{
			vbos[i].Bind(Buffer::Target::Array);
			VertexAttribArray attr(prog, names[i]);
			attr.Setup(npvs[i], DataType::Float);
			attr.Enable();
			++i;
		}
		catch(Error& e){ }
	}

	void Use(void)
	{
		vao.Bind();
	}

	void Draw(void)
	{
		gl.FrontFace(face_winding);
		shape_instr.Draw(shape_indices);
	}

	void Draw(const std::function<bool (GLuint)>& drawing_driver)
	{
		gl.FrontFace(face_winding);
		shape_instr.Draw(shape_indices, 1, drawing_driver);
	}
};
} // shapes
} // oglplus

#endif // include guard
