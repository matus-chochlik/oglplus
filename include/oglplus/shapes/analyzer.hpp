/**
 *  @file oglplus/shapes/analyzer.hpp
 *  @brief Class that analyzes mesh/shape properties for further processing
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHAPES_ANALYZER_1308151449_HPP
#define OGLPLUS_SHAPES_ANALYZER_1308151449_HPP

#include <oglplus/config.hpp>
#include <oglplus/vector.hpp>

#include <oglplus/shapes/draw.hpp>

#include <cstddef>
#include <cassert>
#include <vector>


namespace oglplus {
namespace shapes {

class ShapeAnalyzerGraphData
{
private:
	template <typename Index>
	static std::vector<GLuint> _adapt(const Index& index)
	{
		return std::vector<GLuint>(
			index.begin(),
			index.end()
		);
	}

	static std::vector<GLuint>&& _adapt(std::vector<GLuint>&& index)
	{
		return static_cast<std::vector<GLuint>&&>(index);
	}

	GLuint _guess_face_count(void);
	GLuint _guess_vertex_count(GLuint);

	void _initialize(void);

	void _init_draw_arrays(const DrawOperation& draw_op);

	void _init_dr_ar_triangles(const DrawOperation& draw_op);
	void _init_dr_ar_triangle_strip(const DrawOperation& draw_op);
	void _init_dr_ar_triangle_fan(const DrawOperation& draw_op);

	void _init_draw_elements(const DrawOperation& draw_op);

	void _init_dr_el_triangles(const DrawOperation& draw_op);
	void _init_dr_el_triangle_strip(const DrawOperation& draw_op);
	void _init_dr_el_triangle_fan(const DrawOperation& draw_op);

	void _detect_adjacent(void);
	bool _adjacent_faces(GLuint fa, GLuint ea, GLuint fb, GLuint eb);
public:
	DrawingInstructions _instr;
	std::vector<GLuint> _index;

	// main vertex attribute (usually position)
	std::vector<GLdouble> _main_va;
	// number of values per vertex for the main attribute
	GLuint _main_vpv;

	// index pointing to the start of face vertices
	std::vector<GLuint> _face_index;
	std::vector<GLuint> _face_phase;

	std::vector<GLuint> _face_verts;
	std::vector<GLuint> _face_adj_f;
	std::vector<GLuint> _face_adj_e;

	static GLuint _face_arity(GLuint /*face*/)
	{
		// TODO Arity or triangles only?
		return 3;
	}

	typedef oglplus::ShapeDrawOperationMethod Method;
	typedef oglplus::PrimitiveType Mode;

	template <typename ShapeBuilder>
	ShapeAnalyzerGraphData(const ShapeBuilder& builder)
	 : _instr(builder.Instructions())
	 , _index(_adapt(builder.Indices()))
	 , _main_va()
	 , _main_vpv(builder.Positions(_main_va))
	{
		_initialize();
	}

	static  GLuint _nil_face(void) { return ~GLuint(0); }
};

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::
_init_dr_ar_triangles(const DrawOperation& draw_op)
{
	assert(draw_op.count % 3 == 0);

	GLuint i=0;
	while(i != draw_op.count)
	{
		_face_index.push_back(_face_verts.size());
		_face_phase.push_back(draw_op.phase);

		_face_verts.push_back(draw_op.first+i++);
		_face_verts.push_back(draw_op.first+i++);
		_face_verts.push_back(draw_op.first+i++);

		_face_adj_f.push_back(_nil_face());
		_face_adj_f.push_back(_nil_face());
		_face_adj_f.push_back(_nil_face());

		_face_adj_e.push_back(0);
		_face_adj_e.push_back(0);
		_face_adj_e.push_back(0);
	}
}

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::
_init_dr_ar_triangle_strip(const DrawOperation& draw_op)
{
	assert((draw_op.count == 0) || (draw_op.count >= 3));
	GLuint i=0;
	GLuint v=0;

	_face_index.push_back(_face_verts.size());
	_face_phase.push_back(draw_op.phase);

	_face_verts.push_back(draw_op.first+i++);
	_face_verts.push_back(draw_op.first+i++);
	_face_verts.push_back(draw_op.first+i++);

	_face_adj_f.push_back(_nil_face());
	_face_adj_f.push_back(_nil_face());
	_face_adj_f.push_back(_nil_face());

	_face_adj_e.push_back(0);
	_face_adj_e.push_back(0);
	_face_adj_e.push_back(0);

	v+=3;

	while(i != draw_op.count)
	{
		_face_index.push_back(_face_verts.size());
		_face_phase.push_back(draw_op.phase);
		if(i % 2 != 0)
		{
			_face_verts.push_back(draw_op.first+i-1);
			_face_verts.push_back(draw_op.first+i-2);
			_face_verts.push_back(draw_op.first+i+0);

			_face_adj_f.push_back(_nil_face());
			_face_adj_f.push_back(_nil_face());
			_face_adj_f.push_back(_nil_face());

			_face_adj_f[v-2] = _face_index.size()-1;
			_face_adj_f[v+0] = _face_index.size()-2;

			_face_adj_e.push_back(0);
			_face_adj_e.push_back(0);
			_face_adj_e.push_back(0);

			_face_adj_e[v-2] = 0;
			_face_adj_e[v+0] = 1;
		}
		else
		{
			_face_verts.push_back(draw_op.first+i-2);
			_face_verts.push_back(draw_op.first+i-1);
			_face_verts.push_back(draw_op.first+i+0);

			_face_adj_f.push_back(_nil_face());
			_face_adj_f.push_back(_nil_face());
			_face_adj_f.push_back(_nil_face());

			_face_adj_f[v-1] = _face_index.size()-1;
			_face_adj_f[v+0] = _face_index.size()-1;

			_face_adj_e.push_back(0);
			_face_adj_e.push_back(0);
			_face_adj_e.push_back(0);

			_face_adj_e[v-1] = 0;
			_face_adj_e[v+0] = 2;
		}
		++i;
		v+=3;
	}
}

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::
_init_dr_ar_triangle_fan(const DrawOperation& /*draw_op*/)
{
	// TODO
}

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::_init_draw_arrays(const DrawOperation& draw_op)
{
	switch(draw_op.mode)
	{
		case Mode::Triangles:
			_init_dr_ar_triangles(draw_op);
			break;
		case Mode::TriangleStrip:
			_init_dr_ar_triangle_strip(draw_op);
			break;
		case Mode::TriangleFan:
			_init_dr_ar_triangle_fan(draw_op);
			break;
		default: assert(
			"Only Triangles, TriangleStrip and "
			"TriangleFan are currently supported"
		);
	}
}

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::
_init_dr_el_triangles(const DrawOperation& draw_op)
{
	assert(draw_op.count % 3 == 0);

	GLuint i=0;
	while(i != draw_op.count)
	{
		if(_index[draw_op.first+i] == draw_op.restart_index)
		{
			++i;
			continue;
		}

		_face_index.push_back(_face_verts.size());
		_face_phase.push_back(draw_op.phase);

		_face_verts.push_back(_index[draw_op.first+i++]);
		_face_verts.push_back(_index[draw_op.first+i++]);
		_face_verts.push_back(_index[draw_op.first+i++]);

		_face_adj_f.push_back(_nil_face());
		_face_adj_f.push_back(_nil_face());
		_face_adj_f.push_back(_nil_face());

		_face_adj_e.push_back(0);
		_face_adj_e.push_back(0);
		_face_adj_e.push_back(0);
	}
}

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::
_init_dr_el_triangle_strip(const DrawOperation& draw_op)
{
	assert((draw_op.count == 0) || (draw_op.count >= 3));
	GLuint i=0;
	GLuint v=0;

	while(i != draw_op.count)
	{
		if(_index[draw_op.first+i] == draw_op.restart_index)
		{
			++i;
			continue;
		}

		_face_index.push_back(_face_verts.size());
		_face_phase.push_back(draw_op.phase);

		_face_verts.push_back(_index[draw_op.first+i++]);
		_face_verts.push_back(_index[draw_op.first+i++]);
		_face_verts.push_back(_index[draw_op.first+i++]);

		_face_adj_f.push_back(_nil_face());
		_face_adj_f.push_back(_nil_face());
		_face_adj_f.push_back(_nil_face());

		_face_adj_e.push_back(0);
		_face_adj_e.push_back(0);
		_face_adj_e.push_back(0);

		v+=3;

		while(i != draw_op.count)
		{
			if(_index[draw_op.first+i] == draw_op.restart_index)
			{
				++i;
				break;
			}

			_face_index.push_back(_face_verts.size());
			_face_phase.push_back(draw_op.phase);

			if(i % 2 != 0)
			{
				_face_verts.push_back(_index[draw_op.first+i-1]);
				_face_verts.push_back(_index[draw_op.first+i-2]);
				_face_verts.push_back(_index[draw_op.first+i+0]);

				_face_adj_f.push_back(_nil_face());
				_face_adj_f.push_back(_nil_face());
				_face_adj_f.push_back(_nil_face());

				_face_adj_f[v-2] = _face_index.size()-1;
				_face_adj_f[v] = _face_index.size()-2;

				_face_adj_e.push_back(0);
				_face_adj_e.push_back(0);
				_face_adj_e.push_back(0);

				_face_adj_e[v-2] = 0;
				_face_adj_e[v+0] = 1;
			}
			else
			{
				_face_verts.push_back(_index[draw_op.first+i-2]);
				_face_verts.push_back(_index[draw_op.first+i-1]);
				_face_verts.push_back(_index[draw_op.first+i+0]);

				_face_adj_f.push_back(_nil_face());
				_face_adj_f.push_back(_nil_face());
				_face_adj_f.push_back(_nil_face());

				_face_adj_f[v-1] = _face_index.size()-1;
				_face_adj_f[v] = _face_index.size()-2;

				_face_adj_e.push_back(0);
				_face_adj_e.push_back(0);
				_face_adj_e.push_back(0);

				_face_adj_e[v-1] = 0;
				_face_adj_e[v+0] = 2;
			}
			++i;
			v+=3;
		}
	}
}

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::
_init_dr_el_triangle_fan(const DrawOperation& /*draw_op*/)
{
	//TODO
}

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::_init_draw_elements(const DrawOperation& draw_op)
{
	switch(draw_op.mode)
	{
		case Mode::Triangles:
			_init_dr_el_triangles(draw_op);
			break;
		case Mode::TriangleStrip:
			_init_dr_el_triangle_strip(draw_op);
			break;
		case Mode::TriangleFan:
			_init_dr_el_triangle_fan(draw_op);
			break;
		default: assert(
			"Only Triangles, TriangleStrip and "
			"TriangleFan are currently supported"
		);
	}
}

OGLPLUS_LIB_FUNC
GLuint ShapeAnalyzerGraphData::_guess_face_count(void)
{
	const std::vector<DrawOperation>& draw_ops = _instr.Operations();
	GLuint result = 0;
	for(auto i=draw_ops.begin(), e=draw_ops.end(); i!=e; ++i)
	{
		switch(i->mode)
		{
			case Mode::Triangles:
			{
				assert(i->count % 3 == 0);
				result += i->count / 3;
				break;
			}
			case Mode::TriangleStrip:
			{
				assert((i->count == 0) || (i->count >= 3));
				if(i->count) result += 1+i->count-3;
				break;
			}
			case Mode::TriangleFan:
			{
				assert((i->count == 0) || (i->count >= 3));
				if(i->count) result += 1+i->count-3;
				break;
			}
			default: assert(
				"Only Triangles, TriangleStrip and "
				"TriangleFan are currently supported"
			);
		}
	}
	return result;
}

OGLPLUS_LIB_FUNC
GLuint ShapeAnalyzerGraphData::_guess_vertex_count(GLuint face_count)
{
	return face_count * 3; // TODO n-gons or just triangles?
}

OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::_initialize(void)
{
	const std::vector<DrawOperation>& draw_ops = _instr.Operations();

	GLuint fc = _guess_face_count();
	GLuint vc = _guess_vertex_count(fc);

	_face_index.reserve(fc);
	_face_phase.reserve(fc);

	_face_verts.reserve(vc);
	_face_adj_f.reserve(vc);
	_face_adj_e.reserve(vc);

	for(auto i=draw_ops.begin(), e=draw_ops.end(); i!=e; ++i)
	{
		switch(i->method)
		{
			case Method::DrawArrays:
				_init_draw_arrays(*i);
				break;
			case Method::DrawElements:
				_init_draw_elements(*i);
				break;
		}
	}

	_detect_adjacent();
}

OGLPLUS_LIB_FUNC
bool ShapeAnalyzerGraphData::
_adjacent_faces(GLuint fa, GLuint ea, GLuint fb, GLuint eb)
{
	GLuint va0 = _face_verts[_face_index[fa]+ea];
	GLuint va1 = _face_verts[_face_index[fa]+(ea+1)%_face_arity(fa)];

	GLuint vb0 = _face_verts[_face_index[fb]+eb];
	GLuint vb1 = _face_verts[_face_index[fb]+(eb+1)%_face_arity(fb)];

	if((va0 == vb0) && (va1 == vb1)) return true;
	if((va0 == vb1) && (va1 == vb0)) return true;

	bool equal = true;
	for(GLuint c=0; c!=_main_vpv; ++c)
	{
		if(_main_va[va0*_main_vpv+c] != _main_va[vb0*_main_vpv+c])
		{
			equal = false;
			break;
		}
		if(_main_va[va1*_main_vpv+c] != _main_va[vb1*_main_vpv+c])
		{
			equal = false;
			break;
		}
	}
	if(equal) return true;
	else equal = true;

	for(GLuint c=0; c!=_main_vpv; ++c)
	{
		if(_main_va[va0*_main_vpv+c] != _main_va[vb1*_main_vpv+c])
		{
			equal = false;
			break;
		}
		if(_main_va[va1*_main_vpv+c] != _main_va[vb0*_main_vpv+c])
		{
			equal = false;
			break;
		}
	}
	if(equal) return true;

	return false;
}


OGLPLUS_LIB_FUNC
void ShapeAnalyzerGraphData::_detect_adjacent(void)
{
	const auto fb=_face_index.begin();
	const auto fe=_face_index.end();

	assert(fb != fe);

	auto fi=fb;
	// for each face
	while(fi != fe)
	{
		GLuint fien = _face_arity(fi-fb);
		for(GLuint fie=0; fie!=fien; ++fie)
		{
			if(_face_adj_f[*fi+fie] == _nil_face())
			{
				auto fj = fi+1;
				while(fj != fe)
				{
					GLuint fjen = _face_arity(fj-fb);
					for(GLuint fje=0; fje!=fjen; ++fje)
					{
						if(_adjacent_faces(
							fi-fb,
							fie,
							fj-fb,
							fje
						))
						{
							GLuint i=*fi+fie;
							GLuint j=*fj+fje;
							_face_adj_f[i]=fj-fb;
							_face_adj_f[j]=fi-fb;

							_face_adj_e[i]=fje;
							_face_adj_e[j]=fie;
						}
					}
					++fj;
				}
			}
		}
		++fi;
	}

}
#endif // OGLPLUS_LINK_LIBRARY

class ShapeAnalyzerVert;
class ShapeAnalyzerEdge;
class ShapeAnalyzerFace;

class ShapeAnalyzerVert
{
private:
	const ShapeAnalyzerGraphData& _data;
	GLuint _face_index;
	GLuint _vert_index;

	friend class ShapeAnalyzer;
	friend class ShapeAnalyzerEdge;
	friend class ShapeAnalyzerFace;
public:
	ShapeAnalyzerVert(
		const ShapeAnalyzerGraphData& data,
		GLuint face_index,
		GLuint vert_index
	): _data(data)
	 , _face_index(face_index)
	 , _vert_index(vert_index)
	{
		assert(_face_index < data._face_index.size());
		assert(_vert_index < data._face_arity(_face_index));
	}

	GLuint Index(void) const
	{
		return _vert_index;
	}

	Vec4d MainAttrib(void) const;
};

class ShapeAnalyzerEdge
{
private:
	const ShapeAnalyzerGraphData& _data;
	GLuint _face_index;
	GLuint _edge_index;

	friend class ShapeAnalyzer;
	friend class ShapeAnalyzerFace;

	ShapeAnalyzerEdge(
		const ShapeAnalyzerGraphData& data,
		GLuint face_index,
		GLuint edge_index
	): _data(data)
	 , _face_index(face_index)
	 , _edge_index(edge_index)
	{
		assert(_face_index < data._face_index.size());
		assert(_edge_index < data._face_arity(_face_index));
	}
public:
	GLuint Index(void) const
	{
		return _edge_index;
	}

	ShapeAnalyzerFace Face(void) const;

	bool HasAdjacentEdge(void) const;
	ShapeAnalyzerEdge AdjacentEdge(void) const;
};

class ShapeAnalyzerFace
{
private:
	const ShapeAnalyzerGraphData& _data;
	GLuint _index;

	friend class ShapeAnalyzer;
	friend class ShapeAnalyzerEdge;

	ShapeAnalyzerFace(const ShapeAnalyzerGraphData& data, GLuint index)
	 : _data(data)
	 , _index(index)
	{
		assert(_index < data._face_index.size());
	}
public:
	GLuint Index(void) const
	{
		return _index;
	}

	GLuint Arity(void) const
	{
		return _data._face_arity(_index);
	}

	ShapeAnalyzerVert Vert(GLuint vert_index) const;

	ShapeAnalyzerEdge Edge(GLuint edge_index) const;

	bool HasAdjacentFace(GLuint edge_index) const;

	ShapeAnalyzerFace AdjacentFace(GLuint edge_index) const;
};

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)

OGLPLUS_LIB_FUNC
Vec4d ShapeAnalyzerVert::MainAttrib(void) const
{
	GLuint fi = _data._face_index[_face_index];
	GLuint vi = _data._face_verts[fi+_vert_index];
	return Vec4d(_data._main_va.data()+vi*_data._main_vpv, 4);
}

OGLPLUS_LIB_FUNC
ShapeAnalyzerFace ShapeAnalyzerEdge::
Face(void) const
{
	return ShapeAnalyzerFace(_data, _face_index);
}

OGLPLUS_LIB_FUNC
bool ShapeAnalyzerEdge::HasAdjacentEdge(void) const
{
	GLuint i = _data._face_index[_face_index]+_edge_index;
	return _data._face_adj_f[i] != _data._nil_face();
}

OGLPLUS_LIB_FUNC
ShapeAnalyzerEdge ShapeAnalyzerEdge::AdjacentEdge(void) const
{
	GLuint i = _data._face_index[_face_index]+_edge_index;
	return ShapeAnalyzerEdge(
		_data,
		_data._face_adj_f[i],
		_data._face_adj_e[i]
	);
}

OGLPLUS_LIB_FUNC
ShapeAnalyzerVert ShapeAnalyzerFace::Vert(GLuint vert_index) const
{
	return ShapeAnalyzerVert(
		_data,
		_index,
		vert_index
	);
}

OGLPLUS_LIB_FUNC
ShapeAnalyzerEdge ShapeAnalyzerFace::Edge(GLuint edge_index) const
{
	return ShapeAnalyzerEdge(
		_data,
		_index,
		edge_index
	);
}

OGLPLUS_LIB_FUNC
bool ShapeAnalyzerFace::HasAdjacentFace(GLuint edge_index) const
{
	return _data._face_adj_f[
		_data._face_index[_index]+
		edge_index
	] != _data._nil_face();
}

OGLPLUS_LIB_FUNC
ShapeAnalyzerFace ShapeAnalyzerFace::AdjacentFace(GLuint edge_index) const
{
	return ShapeAnalyzerFace(
		_data,
		_data._face_adj_f[
			_data._face_index[_index]+
			edge_index
		]
	);
}
#endif

class ShapeAnalyzer
{
private:
	ShapeAnalyzerGraphData _data;
public:
	template <typename ShapeBuilder>
	ShapeAnalyzer(const ShapeBuilder& builder)
	 : _data(builder)
	{ }

	GLuint FaceCount(void) const
	{
		assert(!_data._face_index.empty());
		return _data._face_index.size();
	}

	typedef ShapeAnalyzerFace ShapeFace;

	ShapeFace Face(GLuint face_index)
	{
		assert(face_index<_data._face_index.size());
		return ShapeFace(_data, face_index);
	}

	class Vertex
	{
	};
};



} // shapes
} // oglplus

#endif // include guard
