/**
 *  @example standalone/004_bitmap_text_rendering.cpp
 *  @brief Shows the usage of OGLplus' text rendering utilities
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "glut_glew_example.hpp"

#include <oglplus/all.hpp>
#include <oglplus/images/png.hpp>

#include <oglplus/text/bitmap_glyph.hpp>

#include <sstream>
#include <iomanip>


class BitmapGlyphExample
 : public oglplus::SingleExample
{
private:
	oglplus::Context gl;

	typedef oglplus::text::BitmapGlyphRendering TextRendering;

	TextRendering tr;

	TextRendering::Font font;

	TextRendering::Layout oglp_layout;
	TextRendering::Layout desc_layout;

	TextRendering::Layout time_layout;
	std::string time_str;

	std::stringstream text_stream;

	TextRendering::CustomRenderer rndr;

	oglplus::ProgramUniform<oglplus::Mat4f>
		rndr_projection_matrix,
		rndr_camera_matrix,
		rndr_layout_matrix;

	oglplus::ProgramUniform<GLfloat>
		rndr_time;
public:
	BitmapGlyphExample(int argc, const char** argv)
	 : gl()
	 , tr((argc>1)?argv[1]:"./_font", 0, 1, 2)
	 , font(tr.LoadFont((argc>2)?argv[2]:"Sans"))
	 , oglp_layout(tr.MakeLayout(font, oglplus::StrLit("OGLplus")))
	 , desc_layout(tr.MakeLayout(font, oglplus::StrLit(u8"a C++ wrapper for OpenGL©")))
	 , time_layout(tr.MakeLayout(font, 25))
	 , rndr(tr.GetRenderer(
			oglplus::GeometryShader(
				oglplus::ObjectDesc("Layout transform"),
				oglplus::StrLit("#version 330\n"
				"uniform mat4  ProjectionMatrix,CameraMatrix,LayoutMatrix;"
				"mat4 Matrix = ProjectionMatrix*CameraMatrix*LayoutMatrix;"

				"vec4 TransformLayout(vec3 GlyphPosition)"
				"{"
				"	return Matrix * vec4(GlyphPosition, 1.0);"
				"}")
			),
			oglplus::GeometryShader(
				oglplus::ObjectDesc("Glyph transform"),
				oglplus::StrLit("#version 330\n"
				"uniform float Time;"

				"vec3 TransformGlyph("
				"	vec4 LM,"
				"	vec4 IM,"
				"	vec2 Pos,"
				"	float XOffs,"
				"	float LW,"
				"	int Idx"
				")"
				"{"
				"	float a = Idx*0.7+Time*2.4;"
				"	return vec3("
				"		Pos.x+XOffs,"
				"		Pos.y+sin(a)*0.1,"
				"		cos(a)*0.05"
				"	);"
				"}")
			),
			oglplus::FragmentShader(
				oglplus::ObjectDesc("Pixel color"),
				oglplus::StrLit("#version 330\n"
				"vec4 PixelColor(vec4 TexelColor)"
				"{"
				"	return TexelColor.rrrr;"
				"}")
			)
		)
	), rndr_projection_matrix(rndr.GetUniform<oglplus::Mat4f>("ProjectionMatrix"))
	 , rndr_camera_matrix(rndr.GetUniform<oglplus::Mat4f>("CameraMatrix"))
	 , rndr_layout_matrix(rndr.GetUniform<oglplus::Mat4f>("LayoutMatrix"))
	 , rndr_time(rndr.GetUniform<GLfloat>("Time"))
	{
		using namespace oglplus;

		rndr.Use();

		gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gl.Enable(Capability::Blend);
		gl.BlendFunc(
			BlendFunction::SrcAlpha,
			BlendFunction::DstAlpha
		);
	}

	void Reshape(void)
	{
		using namespace oglplus;

		gl.Viewport(Width(), Height());

		rndr_projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(48),
				Width()/Height(),
				1, 100
			)
		);
	}

	void Render(void)
	{
		using namespace oglplus;

		gl.Clear().ColorBuffer().DoIt();

		GLfloat t = GLfloat(FrameTime());

		rndr.Use();

		rndr_time.Set(t);

		text_stream.str(std::string());
		text_stream << "Time: " << std::setprecision(4) << t << " [s]";
		if(time_str != text_stream.str())
		{
			time_str = text_stream.str();
			time_layout.Set(time_str);
		}

		rndr_camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				9.0 + SineWave(t / 7.0)*3.0,
				-FullCircles(t / 17.0),
				Degrees(SineWave(t / 21.0) * 35)
			)
		);

		rndr_layout_matrix.Set(ModelMatrixf::Translation(-3.0f, 0.7f, 0.1f));
		rndr.Render(oglp_layout);

		rndr_layout_matrix.Set(ModelMatrixf::Translation(-8.0f,-0.7f, 0.0f));
		rndr.Render(desc_layout);

		rndr_layout_matrix.Set(
			ModelMatrixf::Translation(-4.0f,-2.0f, 0.0f)*
			ModelMatrixf::Scale(0.7f, 0.7f, 0.5f)
		);
		rndr.Render(time_layout);
	}
};

int main(int argc, char* argv[])
{
	return oglplus::GlutGlewMain<BitmapGlyphExample>(
		"Example of usage of OGLplus' bitmap glyph text rendering",
		argc, argv
	);
}

