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
#include <iterator>
#include <cassert>

namespace oglplus {
namespace shapes {

/// Wraps instructions and VAO+VBOs used to render a shape built by a ShapeBuilder
class ShapeWrapper
{
protected:
	FaceOrientation _face_winding;
	// helper object encapsulating shape drawing instructions
	shapes::DrawingInstructions _shape_instr;

	// index type properties
	shapes::ElementIndexInfo _index_info;

	Context _gl;

	// A vertex array object for the rendered shape
	VertexArray _vao;

	// VBOs for the shape's vertex attributes
	Array<Buffer> _vbos;

	// numbers of values per vertex for the individual attributes
	std::vector<GLuint> _npvs;

	// names of the individual vertex attributes
	std::vector<String> _names;

	template <class ShapeBuilder, typename Iterator>
	void _init(const ShapeBuilder& builder, Iterator name, Iterator end)
	{
		// bind the VAO for the shape
		_vao.Bind();

		typename ShapeBuilder::VertexAttribs vert_attr_info;
		unsigned i = 0;
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
				_vbos[i].Bind(Buffer::Target::Array);
				_npvs[i] = getter(builder, data);
				_names[i] = *name;
				// upload the data
				Buffer::Data(Buffer::Target::Array, data);
			}
			++name;
			++i;
		}
		auto shape_indices = builder.Indices();
		if(!shape_indices.empty())
		{
			assert((i+1) == _npvs.size());
			assert((i+1) == _vbos.size());

			_npvs[i] = 1;
			_vbos[i].Bind(Buffer::Target::ElementArray);
			Buffer::Data(
				Buffer::Target::ElementArray,
				shape_indices
			);
		}
	}
public:
	template <typename StdRange, class ShapeBuilder>
	ShapeWrapper(const StdRange& names, const ShapeBuilder& builder)
	 : _face_winding(builder.FaceWinding())
	 , _shape_instr(builder.Instructions())
	 , _index_info(builder)
	 , _vbos(std::distance(names.begin(), names.end())+1)
	 , _npvs(std::distance(names.begin(), names.end())+1, 0)
	 , _names(std::distance(names.begin(), names.end()))
	{
		_init(builder, names.begin(), names.end());
	}

	template <typename StdRange, class ShapeBuilder>
	ShapeWrapper(
		const StdRange& names,
		const ShapeBuilder& builder,
		const Program& prog
	): _face_winding(builder.FaceWinding())
	 , _shape_instr(builder.Instructions())
	 , _index_info(builder)
	 , _vbos(std::distance(names.begin(), names.end())+1)
	 , _npvs(std::distance(names.begin(), names.end())+1, 0)
	 , _names(std::distance(names.begin(), names.end()))
	{
		_init(builder, names.begin(), names.end());
		UseInProgram(prog);
	}

#if !OGLPLUS_NO_INITIALIZER_LISTS
	template <class ShapeBuilder>
	ShapeWrapper(
		const std::initializer_list<const GLchar*>& names,
		const ShapeBuilder& builder,
		const Program& prog
	): _face_winding(builder.FaceWinding())
	 , _shape_instr(builder.Instructions())
	 , _index_info(builder)
	 , _vbos(std::distance(names.begin(), names.end())+1)
	 , _npvs(std::distance(names.begin(), names.end())+1, 0)
	 , _names(std::distance(names.begin(), names.end()))
	{
		_init(builder, names.begin(), names.end());
		UseInProgram(prog);
	}
#endif

	template <class ShapeBuilder>
	ShapeWrapper(
		const GLchar** names,
		unsigned name_count,
		const ShapeBuilder& builder,
		const Program& prog
	): _face_winding(builder.FaceWinding())
	 , _shape_instr(builder.Instructions())
	 , _index_info(builder)
	 , _vbos(std::distance(names, names+name_count)+1)
	 , _npvs(std::distance(names, names+name_count)+1, 0)
	 , _names(std::distance(names, names+name_count))
	{
		_init(builder, names, names+name_count);
		UseInProgram(prog);
	}

	ShapeWrapper(ShapeWrapper&& temp)
	 : _face_winding(temp._face_winding)
	 , _shape_instr(std::move(temp._shape_instr))
	 , _index_info(temp._index_info)
	 , _gl(std::move(temp._gl))
	 , _vao(std::move(temp._vao))
	 , _vbos(std::move(temp._vbos))
	 , _npvs(std::move(temp._npvs))
	 , _names(std::move(temp._names))
	{ }

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	ShapeWrapper(const ShapeWrapper&) = delete;
#else
private:
	ShapeWrapper(const ShapeWrapper&);
public:
#endif

	void UseInProgram(const Program& prog)
	{
		prog.Use();
		_vao.Bind();
		size_t i=0, n = _names.size();
		while(i != n)
		{
			if(_npvs[i] != 0)
			{
				try
				{
					_vbos[i].Bind(Buffer::Target::Array);
					VertexAttribArray attr(prog, _names[i]);
					attr.Setup(_npvs[i], DataType::Float);
					attr.Enable();
				}
				catch(Error& e){ }
			}
			++i;
		}
		assert((i+1) == _npvs.size());
		if(_npvs[i] != 0)
		{
			assert((i+1) == _vbos.size());
			_vbos[i].Bind(Buffer::Target::ElementArray);
		}
	}

	void Use(void)
	{
		_vao.Bind();
	}

	void Draw(void)
	{
		_gl.FrontFace(_face_winding);
		_shape_instr.Draw(_index_info, 1);
	}

	void Draw(const std::function<bool (GLuint)>& drawing_driver)
	{
		_gl.FrontFace(_face_winding);
		_shape_instr.Draw(_index_info, 1, drawing_driver);
	}
};
} // shapes
} // oglplus

#endif // include guard
