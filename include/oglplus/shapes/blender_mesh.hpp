/**
 *  @file oglplus/shapes/blender_mesh.hpp
 *  @brief Blender mesh loader
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_BLENDER_MESH_1206011111_HPP
#define OGLPLUS_SHAPES_BLENDER_MESH_1206011111_HPP

#include <oglplus/face_mode.hpp>
#include <oglplus/shapes/draw.hpp>

#include <oglplus/shapes/vert_attr_info.hpp>

#include <oglplus/imports/blend_file.hpp>

#include <vector>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for drawing of a mesh
class BlenderMesh
 : public DrawingInstructionWriter
{
private:
	struct _loading_options
	{
		const char* scene_name;
		bool load_normals;
		bool load_texcoords;
	};

	// vertex positions
	std::vector<GLfloat> _pos_data;
	// vertex normals
	std::vector<GLfloat> _nml_data;
	// vertex tex coords
	std::vector<GLfloat> _uvc_data;

	// vectors with vertex indices
	std::vector<GLuint> _idx_data;

	// find the scene by name or the default scene
	imports::BlendFileFlatStructBlockData _find_scene(
		const _loading_options& /*opts*/,
		imports::BlendFile& blend_file,
		imports::BlendFileStructGlobBlock& glob_block
	)
	{
		// TODO: find the scene by name
		return  blend_file[glob_block.curscene];
	}

	// load a single mesh from a scene
	void _load_mesh(
		const _loading_options& opts,
		imports::BlendFile& blend_file,
		imports::BlendFileFlatStructBlockData& object_mesh_data,
		const Mat4f& mesh_matrix,
		GLuint& index_offset
	)
	{
		// the number of vertices
		std::size_t n_verts = 0;
		// the number of additional vertices
		std::size_t n_add_verts = 0;

		// get the vertex block pointer
		imports::BlendFilePointer vertex_ptr =
			object_mesh_data.Field<void*>("mvert").Get();
		// open the vertex block (if any)
		if(vertex_ptr)
		{
			auto vertex_data = blend_file[vertex_ptr];
			// get the number of vertices in the block
			n_verts = vertex_data.BlockElementCount();
			// get the vertex coordinate and normal fields
			auto vertex_co_field = vertex_data.Field<float>("co");
			auto vertex_no_field = vertex_data.Field<short>("no");
			// make two vectors of position and normal data
			std::vector<GLfloat> ps(3 * n_verts);
			std::vector<GLfloat> ns(opts.load_normals?3*n_verts:0);
			std::vector<GLfloat> ts(opts.load_texcoords?2*n_verts:0,-1.0f);
			for(std::size_t v=0; v!=n_verts; ++v)
			{
				// (transpose y and z axes)
				// get the positional coordinates
				Vec4f position(
					vertex_co_field.Get(v, 0),
					vertex_co_field.Get(v, 1),
					vertex_co_field.Get(v, 2),
					1.0f
				);
				Vec4f newpos = mesh_matrix * position;
				ps[3*v+0] = newpos.x();
				ps[3*v+1] = newpos.z();
				ps[3*v+2] =-newpos.y();
				//
				// get the normals
				if(opts.load_normals)
				{
					Vec4f normal(
						vertex_no_field.Get(v, 0),
						vertex_no_field.Get(v, 1),
						vertex_no_field.Get(v, 2),
						0.0f
					);
					Vec4f newnorm = mesh_matrix * normal;
					ns[3*v+0] = newnorm.x();
					ns[3*v+1] = newnorm.z();
					ns[3*v+2] =-newnorm.y();
				}
			}
			// append the values:
			// positions
			_pos_data.insert(_pos_data.end(), ps.begin(), ps.end());
			// normals
			if(opts.load_normals)
				_nml_data.insert(_nml_data.end(), ns.begin(), ns.end());
			if(opts.load_texcoords)
				_uvc_data.insert(_uvc_data.end(), ts.begin(), ts.end());
		}

		// additional positions, normals and uv coords
		// and indices that might be added due when
		// loading uv-coordinates for vertices with the same
		// positions/normals but different texture coordinates
		std::vector<GLfloat> aps, ans, ats;
		std::vector<GLuint> ais;

		// get the face block pointer
		auto face_ptr = object_mesh_data.Field<void*>("mface").Get();
		// get the face texture block pointer
		auto tface_ptr = object_mesh_data.Field<void*>("mtface").Get();
		//
		// if we wanted to load the uv-coordinates and they are available
		if(face_ptr && tface_ptr && opts.load_texcoords)
		{
			auto face_data = blend_file[face_ptr];
			auto tface_data = blend_file[tface_ptr];
			// get the number of faces in the block
			std::size_t n_faces = face_data.BlockElementCount();
			assert(n_faces == tface_data.BlockElementCount());
			// get the vertex index fields of the face
			auto face_v1_field = face_data.Field<int>("v1");
			auto face_v2_field = face_data.Field<int>("v2");
			auto face_v3_field = face_data.Field<int>("v3");
			auto face_v4_field = face_data.Field<int>("v4");
			// get the uv coords fields
			auto tface_uv_field = tface_data.Field<float>("uv");
			// make a vector of index data
			std::vector<GLuint> is(5 * n_faces);

			std::size_t ii = 0;
			for(std::size_t f=0; f!=n_faces; ++f)
			{
				// get face vertex indices
				int fv[4] = {
					face_v1_field.Get(f),
					face_v2_field.Get(f),
					face_v3_field.Get(f),
					face_v4_field.Get(f)
				};

				float uv[8];
				for(std::size_t i=0; i!=8; ++i)
					uv[i] = tface_uv_field.Get(f, i);

				int fi[4] = {
					fv[0]+index_offset,
					fv[1]+index_offset,
					fv[2]+index_offset,
					fv[3]?fv[3]+index_offset:0
				};

				bool needs_vertex_copy = false;
				for(std::size_t i=0; i!=4; ++i)
					for(std::size_t j=0; j!=2; ++j)
						needs_vertex_copy |=
							(fi[i] != 0) &&
							(_uvc_data[fi[i]*2+j] >= 0.0f) &&
							(_uvc_data[fi[i]*2+j] != uv[i*2+j]);

				if(needs_vertex_copy)
				{
					for(std::size_t i=0; i!=4; ++i)
					{
						if(fi[i] != 0)
						{
							aps.push_back(_pos_data[fi[i]*3+0]);
							aps.push_back(_pos_data[fi[i]*3+1]);
							aps.push_back(_pos_data[fi[i]*3+2]);

							if(opts.load_normals)
							{
								ans.push_back(_nml_data[fi[i]*3+0]);
								ans.push_back(_nml_data[fi[i]*3+1]);
								ans.push_back(_nml_data[fi[i]*3+2]);
							}

							ats.push_back(uv[i*2+0]);
							ats.push_back(uv[i*2+1]);

							ais.push_back(
								index_offset+
								n_verts +
								n_add_verts
							);
							++n_add_verts;
						}
					}
					// primitive restart index
					ais.push_back(0);
				}
				else
				{
					for(std::size_t i=0; i!=4; ++i)
					{
						if(fi[i] != 0)
						{
							for(std::size_t j=0; j!=2; ++j)
								_uvc_data[fi[i]*2+j] = uv[i*2+j];
							is[ii++] = fi[i];
						}
					}
					// primitive restart index
					is[ii++] = 0;
				}
			}
			is.resize(ii);
			// append the values
			_idx_data.insert(_idx_data.end(), is.begin(), is.end());
		}
		else if(face_ptr)
		{
			auto face_data = blend_file[face_ptr];
			// get the number of faces in the block
			std::size_t n_faces = face_data.BlockElementCount();
			// get the vertex index fields of the face
			auto face_v1_field = face_data.Field<int>("v1");
			auto face_v2_field = face_data.Field<int>("v2");
			auto face_v3_field = face_data.Field<int>("v3");
			auto face_v4_field = face_data.Field<int>("v4");
			// make a vector of index data
			std::vector<GLuint> is(5 * n_faces);
			std::size_t ii = 0;
			for(std::size_t f=0; f!=n_faces; ++f)
			{
				// get face vertex indices
				int v1 = face_v1_field.Get(f);
				int v2 = face_v2_field.Get(f);
				int v3 = face_v3_field.Get(f);
				int v4 = face_v4_field.Get(f);

				is[ii++] = v1+index_offset;
				is[ii++] = v2+index_offset;
				is[ii++] = v3+index_offset;
				if(v4) is[ii++] = v4+index_offset;
				is[ii++] = 0; // primitive restart index
			}
			is.resize(ii);
			// append the values
			_idx_data.insert(_idx_data.end(), is.begin(), is.end());
		}

		// get the poly block pointer
		auto poly_ptr = object_mesh_data.TryGet<void*>("mpoly", nullptr);
		// and the loop block pointer
		auto loop_ptr = object_mesh_data.TryGet<void*>("mloop", nullptr);
		//
		// TODO: add loading of UV-coordinates here
		//
		// open the poly and loop blocks (if we have both)
		if(poly_ptr && loop_ptr)
		{
			auto poly_data = blend_file[poly_ptr];
			auto loop_data = blend_file[loop_ptr];
			// get the number of polys in the block
			std::size_t n_polys = poly_data.BlockElementCount();
			// get the fields of poly and loop
			auto poly_loopstart_field = poly_data.Field<int>("loopstart");
			auto poly_totloop_field = poly_data.Field<int>("totloop");
			auto loop_v_field = loop_data.Field<int>("v");

			// make a vector of index data
			std::vector<GLuint> is;
			for(std::size_t f=0; f!=n_polys; ++f)
			{
				int ls = poly_loopstart_field.Get(f);
				int tl = poly_totloop_field.Get(f);

				for(int l=0; l!=tl; ++l)
				{
					int v = loop_v_field.Get(ls+l);
					is.push_back(v+index_offset);
				}
				// primitive restart index
				is.push_back(0);
			}
			// append the values
			_idx_data.insert(_idx_data.end(), is.begin(), is.end());
		}

		// if there is some additional vertex data and indices
		if(n_add_verts)
		{
			// add it
			_pos_data.insert(_pos_data.end(), aps.begin(), aps.end());
			_nml_data.insert(_nml_data.end(), ans.begin(), ans.end());
			_uvc_data.insert(_uvc_data.end(), ats.begin(), ats.end());
			_idx_data.insert(_idx_data.end(), ais.begin(), ais.end());
		}
		index_offset += n_verts + n_add_verts;
	}

	// load a single object from a scene
	void _load_object(
		const _loading_options& opts,
		imports::BlendFile& blend_file,
		imports::BlendFileFlatStructBlockData& object_data,
		imports::BlendFilePointer object_data_ptr,
		GLuint& index_offset
	)
	{
		imports::BlendFileFlatStructBlockData object_data_data =
			blend_file[object_data_ptr];
		// if it is a mesh
		if(object_data_data.StructureName() == "Mesh")
		{
			// get the object matrix field
			auto object_obmat_field = object_data.Field<float>("obmat");
			// make a transformation matrix
			Mat4f obmat(
				Vec4f(
					object_obmat_field.Get(0, 0),
					object_obmat_field.Get(0, 4),
					object_obmat_field.Get(0, 8),
					object_obmat_field.Get(0,12)
				),
				Vec4f(
					object_obmat_field.Get(0, 1),
					object_obmat_field.Get(0, 5),
					object_obmat_field.Get(0, 9),
					object_obmat_field.Get(0,13)
				),
				Vec4f(
					object_obmat_field.Get(0, 2),
					object_obmat_field.Get(0, 6),
					object_obmat_field.Get(0,10),
					object_obmat_field.Get(0,14)
				),
				Vec4f(
					object_obmat_field.Get(0, 3),
					object_obmat_field.Get(0, 7),
					object_obmat_field.Get(0,11),
					object_obmat_field.Get(0,15)
				)
			);

			_load_mesh(
				opts,
				blend_file,
				object_data_data,
				obmat,
				index_offset
			);
		}
	}

	void _load_meshes(
		const _loading_options& opts,
		imports::BlendFile& blend_file
	)
	{
		// the values at index 0 is unused
		// 0 is used as primitive restart index
		_idx_data.push_back(0);
		// unused position
		_pos_data.push_back(0.0);
		_pos_data.push_back(0.0);
		_pos_data.push_back(0.0);
		// unused normal
		if(opts.load_normals)
		{
			_nml_data.push_back(0.0);
			_nml_data.push_back(0.0);
			_nml_data.push_back(0.0);
		}
		// unused tex coord
		if(opts.load_texcoords)
		{
			_uvc_data.push_back(0.0);
			_uvc_data.push_back(0.0);
		}
		//
		// index offset starting at 1
		GLuint index_offset = 1;
		// get the file's global block
		imports::BlendFileStructGlobBlock glob_block =
			blend_file.StructuredGlobalBlock();

		// find the scene
		imports::BlendFileFlatStructBlockData scene_data =
			_find_scene(opts, blend_file, glob_block);
		//
		// get the pointer to the first object in the scene
		imports::BlendFilePointer object_link_ptr =
			scene_data.Field<void*>("base.first").Get();
		// and go through the whole list of objects
		while(object_link_ptr)
		{
			// for each list element open the linked list block
			imports::BlendFileFlatStructBlockData object_link_data =
				blend_file[object_link_ptr];
			// get the pointer to its object
			imports::BlendFilePointer object_ptr =
				object_link_data.Field<void*>("object").Get();
			// open the object block (if any)
			if(object_ptr)
			{
				// get the object data
				imports::BlendFileFlatStructBlockData object_data =
					blend_file[object_ptr];
				// get the data pointer
				imports::BlendFilePointer object_data_ptr =
					object_data.Field<void*>("data").Get();
				// open the data block (if any)
				if(object_data_ptr)
				{
					_load_object(
						opts,
						blend_file,
						object_data,
						object_data_ptr,
						index_offset
					);
				}
			}
			// and get the pointer to the next block
			object_link_ptr =
				object_link_data.Field<void*>("next").Get();
		}
	}
public:
	BlenderMesh(
		imports::BlendFile& blend_file,
		bool load_normals = true,
		bool load_texcoords = true
	)
	{
		_loading_options opts;
		opts.scene_name = nullptr;
		opts.load_normals = load_normals;
		opts.load_texcoords = load_texcoords;

		// do load the meshes
		_load_meshes(opts, blend_file);
	}

	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CCW;
	}

	typedef GLuint (BlenderMesh::*VertexAttribFunc)(std::vector<GLfloat>&) const;

	/// Makes the vertex positions and returns the number of values per vertex
	template <typename T>
	GLuint Positions(std::vector<T>& dest) const
	{
		dest.clear();
		dest.insert(dest.end(), _pos_data.begin(), _pos_data.end());
		return 3;
	}

	/// Makes the vertex normals and returns the number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		dest.clear();
		dest.insert(dest.end(), _nml_data.begin(), _nml_data.end());
		return 3;
	}

	/// Makes the texture coordinates and returns the number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.clear();
		dest.insert(dest.end(), _uvc_data.begin(), _uvc_data.end());
		return 2;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** BlenderMesh provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 *  - "Normal" the vertex normals (Normals)
	 */
	typedef VertexAttribsInfo<BlenderMesh> VertexAttribs;
#else
	typedef VertexAttribsInfo<
		BlenderMesh,
		std::tuple<
			VertexPositionsTag,
			VertexNormalsTag,
			VertexTexCoordinatesTag
		>
	> VertexAttribs;
#endif

	/// Queries the bounding sphere coordinates and dimensions
	template <typename T>
	void BoundingSphere(Vector<T, 4>& center_and_radius) const
	{
		GLfloat min_x = _pos_data[3], max_x = _pos_data[3];
		GLfloat min_y = _pos_data[4], max_y = _pos_data[4];
		GLfloat min_z = _pos_data[5], max_z = _pos_data[5];
		for(std::size_t v=1, vn=_pos_data.size()/3; v!=vn; ++v)
		{
			GLfloat x = _pos_data[v*3+0];
			GLfloat y = _pos_data[v*3+1];
			GLfloat z = _pos_data[v*3+2];

			if(min_x > x) min_x = x;
			if(min_y > y) min_y = y;
			if(min_z > z) min_z = z;
			if(max_x < x) max_x = x;
			if(max_y < y) max_y = y;
			if(max_z < z) max_z = z;
		}

		Vector<T, 3> c(
			T((min_x + max_x) * 0.5),
			T((min_y + max_y) * 0.5),
			T((min_z + max_z) * 0.5)
		);

		center_and_radius = Vector<T, 4>(
			c.x(),
			c.y(),
			c.z(),
			Distance(c, Vector<T, 3>(T(min_x), T(min_y), T(min_z)))
		);
	}

	/// The type of the index container returned by Indices()
	typedef std::vector<GLuint> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		return _idx_data;
	}

	/// Returns the instructions for rendering of faces
	DrawingInstructions Instructions(void) const
	{
		DrawOperation operation;
		operation.method = DrawOperation::Method::DrawElements;
		operation.mode = PrimitiveType::TriangleFan;
		operation.first = 0;
		operation.count = _idx_data.size();
		operation.restart_index = 0;
		operation.phase = 0;
		return this->MakeInstructions(operation);
	}
};

} // shapes
} // oglplus

#endif // include guard
