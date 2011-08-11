/**
 *  .file devel/test01.cpp
 *  Development / testing file.
 *  NOTE. this file is here for feature development / testing purposes only
 *  and its source code, input, output can change witout prior notice.
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/shapes/sphere.hpp>
#include <oglplus/shapes/torus.hpp>
#include <oglplus/bound/buffer.hpp>
#include <oglplus/bound/texture.hpp>

#include <iostream>

#include <oglplus/images/random.hpp>
#include <oglplus/images/newton.hpp>
#include <oglplus/images/load.hpp>

#include <cmath>

#include "test.hpp"

namespace oglplus {
namespace images {

template <typename T, size_t EPP>
class FilteredImage
 : public Image<T>
{
private:
	static_assert(
		EPP > 0 && EPP <= 4,
		"Number of Elements Per Pixel must be between 1 and 4"
	);
protected:
	template <typename IT>
	struct _sampler
	{
	private:
		size_t _width, _height, _iepp, _n;
		const IT* _data;
	public:
		_sampler(
			size_t width,
			size_t height,
			size_t iepp,
			size_t n,
			const IT* data
		): _width(width)
		 , _height(height)
		 , _iepp(iepp)
		 , _n(n)
		 , _data(data)
		{
			assert(_iepp > 0 && _iepp <= 4);
		}

		template <int Xoffs, int Yoffs>
		Vector<IT, 4> get(void) const
		{
			assert(Xoffs > int(-_width));
			assert(Yoffs > int(-_height));
			assert(Xoffs < int( _width));
			assert(Yoffs < int( _height));

			size_t xoffs = (Xoffs < 0)?
				(Xoffs+_width) % _width :
				Xoffs;
			size_t yoffs = (Yoffs < 0)?
				(Yoffs+_height) % _height:
				Yoffs;
			size_t offs = _n + yoffs*_width + xoffs;
			const IT* p = _data + _iepp*offs;
			return Vector<IT, 4>(
				*p,
				(_iepp > 1) ? *(p+1) : T(0),
				(_iepp > 2) ? *(p+2) : T(0),
				(_iepp > 3) ? *(p+3) : T(0)
			);
		}
	};
private:
	template <typename IT, typename Filter, typename Extractor>
	void _calculate(
		const Image<IT>& input,
		Filter filter,
		Extractor extractor,
		T one,
		IT ione
	)
	{
		size_t iepp = input.ElementsPerPixel();
		auto p = this->_data.begin(), e = this->_data.end();
		size_t n = 0;
		for(size_t k=0,d=input.Depth();  k!=d; ++k)
		for(size_t j=0,h=input.Height(); j!=h; ++j)
		for(size_t i=0,w=input.Width();  i!=w; ++i)
		{
			_sampler<IT> sampler(w,h,iepp,n++,input.Data());
			Vector<T, EPP> outv = filter(
				extractor,
				sampler,
				one,
				ione
			);
			for(size_t c=0; c!= EPP; ++c)
			{
				assert(p != e);
				*p = outv.At(c);
				++p;
			}
		}
		assert(p == e);
	}

	static GLubyte _one(GLubyte*)
	{
		return 0xFF;
	}

	static GLfloat _one(GLfloat*)
	{
		return 1.0f;
	}

	template <typename IT>
	static IT _one(void)
	{
		return _one((IT*)0);
	}
public:

	template <size_t I>
	struct FromComponentI
	{
		template <typename IT>
		IT operator()(const Vector<IT, 4>& v) const
		{
			return v.template At<I>();
		}
	};

	typedef FromComponentI<0> FromRed;
	typedef FromComponentI<1> FromGreen;
	typedef FromComponentI<2> FromBlue;
	typedef FromComponentI<3> FromAlpha;

	template <typename IT, typename Filter, typename Extractor>
	FilteredImage(
		const Image<IT>& input,
		Filter filter,
		Extractor extractor
	): Image<T>(input.Width(), input.Height(), input.Depth())
	{
		this->_data.resize(
			input.Width()*
			input.Height()*
			input.Depth()*
			EPP
		);
		assert(this->ElementsPerPixel() == EPP);
		_calculate(input, filter, extractor, _one<T>(), _one<IT>());

		this->_type = PixelDataType(oglplus::GetDataType((T*)0));
	}
};

template <typename T>
class NormalMap
 : public FilteredImage<T, 3>
{
private:
	typedef FilteredImage<T, 3> Base;

	struct _filter
	{
		template <typename Extractor, typename Sampler, typename IT>
		Vector<T, 3> operator()(
			const Extractor& extractor,
			const Sampler& sampler,
			T one,
			IT ione
		) const
		{
			float sc = extractor(sampler.template get< 0,  0>());
			float sx = extractor(sampler.template get< 1,  0>());
			float sy = extractor(sampler.template get< 0,  1>());
			Vector<float, 3> vx(0.5f, 0, (sc-sx)/ione);
			Vector<float, 3> vy(0, 0.5f, (sc-sy)/ione);
			return Normalized(Cross(vx, vy)) * one;
		}
	};
public:
	template <typename IT>
	NormalMap(const Image<IT>& input)
	 : Base(input, _filter(), typename Base::FromRed())
	{
		this->_format = PixelDataFormat::RGB;
		this->_internal = PixelDataInternalFormat::RGB;
	}
};

} // namespace images


class Test01 : public Test
{
private:
	typedef shapes::Cube Shape;
	//typedef shapes::Sphere Shape;
	//typedef shapes::Torus Shape;
	//
	Shape shape;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered shape
	VertexArray vao;

	// VBOs for the shape's vertices and normals
	Buffer verts;
	Buffer normals;
	Buffer tangents;
	Buffer texcoords;

	// textures for the shape
	Texture color_tex, bump_tex;
public:
	Test01(void)
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 projectionMatrix, cameraMatrix, modelMatrix;"
			"in vec4 vertex;"
			"in vec3 normal;"
			"in vec3 tangent;"
			"in vec2 texcoord;"
			"out vec3 fragLight;"
			"out vec2 fragTexCoord;"
			"out mat3 normalMatrix;"
			"const vec4 lightPos = vec4(1.0, 2.0, 3.0, 1.0);"
			"void main(void)"
			"{"
			"	vec3 fragTangent = ("
			"		modelMatrix *"
			"		vec4(tangent, 0.0)"
			"	).xyz;"
			"	vec3 fragNormal = ("
			"		modelMatrix *"
			"		vec4(normal, 0.0)"
			"	).xyz;"
			"	normalMatrix[0] = fragTangent;"
			"	normalMatrix[1] = cross(fragNormal, fragTangent);"
			"	normalMatrix[2] = fragNormal;"
			"	fragLight = ("
			"		lightPos-"
			"		modelMatrix*vertex"
			"	).xyz;"
			"	fragTexCoord = texcoord;"
			"	gl_Position = "
			"		projectionMatrix *"
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vertex;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		// (uses the absolute value of normal as color)
		fs.Source(
			"#version 330\n"
			"uniform sampler2D colorTex;"
			"uniform sampler2D bumpTex;"
			"in vec2 fragTexCoord;"
			"in vec3 fragLight;"
			"in mat3 normalMatrix;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = dot(fragLight, fragLight);"
			"	vec3 finalNormal = "
			"		normalMatrix *"
			"		texture2D(bumpTex, fragTexCoord).rgb;"
			"	float i = (l > 0)?"
			"		dot(finalNormal, fragLight)/l:"
			"		0.0;"
			"	vec3 c = texture2D(colorTex, fragTexCoord).rgb;"
			"	fragColor = vec4(c*(3.0*i+0.2), 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the shape
		vao.Bind();

		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = shape.Vertices(data);
			Bind(verts, Buffer::Target::Array).Data(data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = shape.Normals(data);
			Bind(normals, Buffer::Target::Array).Data(data);
			// setup the vertex attribs array for the normals
			VertexAttribArray attr(prog, "normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = shape.Tangents(data);
			Bind(tangents, Buffer::Target::Array).Data(data);
			VertexAttribArray attr(prog, "tangent");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the shape tex-coords
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = shape.TexCoordinates(data);
			Bind(texcoords, Buffer::Target::Array).Data(data);
			//
			VertexAttribArray attr(prog, "texcoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// setup the textures
		{
			Texture::Active(0);
			Uniform(prog, "colorTex").Set(0);
			auto bound_tex = Bind(color_tex, Texture::Target::_2D);
			bound_tex.Image2D(images::LoadTexture("wooden_crate"));
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		}
		{
			Texture::Active(1);
			Uniform(prog, "bumpTex").Set(1);
			auto bound_tex = Bind(bump_tex, Texture::Target::_2D);
			bound_tex.Image2D(
				images::NormalMap<GLubyte>(images::LoadTexture("wooden_crate-hmap"))
			);
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		}

		// set the projection matrix fov = 24 deg. aspect = 1.25
		Uniform(prog, "projectionMatrix").SetMatrix(
			CamMatrixf::Perspective(Degrees(24), 1.25, 1, 100)
		);
		//
		VertexArray::Unbind();
		gl.ClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		//
		gl.FrontFace(shape.FaceWinding());
		gl.CullFace(Face::Back);
		gl.Enable(Capability::CullFace);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		Uniform(prog, "cameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				//4.5 + std::sin(time)*3.0,
				1.5,
				Degrees(time * 135),
				Degrees(std::sin(time * 0.1) * 90)
			)
		);

		Uniform(prog, "modelMatrix").SetMatrix(Matrix4f());

		vao.Bind();
		// This is not very effective
		shape.Instructions().Draw(shape.Indices());
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Test> makeTest(void)
{
	return std::unique_ptr<Test>(new Test01);
}

} // namespace oglplus
