/**
 *  @example standalone/004_bitmap_text_hello.cpp
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


class BitmapGlyphExample
 : public oglplus::SingleExample
{
private:
	oglplus::Context gl;

	typedef oglplus::text::BitmapGlyphRendering TextRendering;

	TextRendering tr;

	TextRendering::Font font;

	TextRendering::Layout layout;

	TextRendering::Renderer rndr;

	oglplus::ProgramUniform<oglplus::Vec3f> rndr_color;
	oglplus::ProgramUniform<GLfloat> rndr_opacity;

	int prev_interval;
	std::size_t current_text;
public:
	BitmapGlyphExample(int argc, const char** argv)
	 : gl()
	 , tr((argc>1)?argv[1]:"./_font", 0, 1, 2)
	 , font(tr.LoadFont((argc>2)?argv[2]:"Sans"))
	 , layout(tr.MakeLayout(font, 128))
	 , rndr(tr.GetRenderer(
			oglplus::FragmentShader(
				oglplus::ObjectDesc("Pixel color"),
				oglplus::StrLit("#version 330\n"
				"uniform vec3 Color;"
				"uniform float Opacity;"
				"vec4 PixelColor(vec4 TexelColor)"
				"{"
				"	return vec4(Color, TexelColor.r*Opacity);"
				"}")
			)
		)
	), rndr_color(rndr.GetUniform<oglplus::Vec3f>("Color"))
	 , rndr_opacity(rndr.GetUniform<GLfloat>("Opacity"))
	 , prev_interval(-1)
	 , current_text(0)
	{
		using namespace oglplus;

		rndr.Use();

		gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gl.Enable(Capability::Blend);
		gl.BlendFunc(
			BlendFunction::SrcAlpha,
			BlendFunction::DstAlpha
		);

		rndr.SetAlignment(TextRendering::Alignment::Center);
	}

	void LoadNext(void)
	{
		const char* texts[] = {
			u8"Hello world",
			u8"Nazdar svet",
			u8"Γεια σας κόσμο",
			u8"Привет мир",
			u8"Witaj świecie",
			u8"Здравей свят",
			u8"Ahoj světe",
			u8"Moi maailma",
			u8"Bonjour tout le monde",
			u8"Hallo welt",
			u8"Hej världen",
			u8"Прывітанне свет",
			u8"Olá mundo",
			u8"Здраво свете",
			u8"Zdravo svet",
			u8"Hola mundo",
			u8"Merhaba dünya",
			u8"Привіт світ",
			u8"Pozdrav svijetu",
			u8"Hello világ",
			u8"Ciao mondo",
			u8"Здраво светот",
			u8"Hei verden"
		};
		const std::size_t text_count = sizeof(texts)/sizeof(texts[0]);

		layout.Set(texts[current_text]);
		if(++current_text >= text_count)
			current_text = 0;

		rndr_color.Set(
			0.2f+GLfloat(0.8f*std::rand())/RAND_MAX,
			0.3f+GLfloat(0.7f*std::rand())/RAND_MAX,
			0.2f+GLfloat(0.8f*std::rand())/RAND_MAX
		);
	}

	void Reshape(void)
	{
		using namespace oglplus;

		gl.Viewport(Width(), Height());

		rndr.SetProjection(
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

		GLfloat t = GLfloat(FrameTime());
		GLfloat i = t*0.3f;
		int interval = int(i);
		GLfloat f = i - GLfloat(interval);
		if(prev_interval < interval)
		{
			LoadNext();
			prev_interval = interval;
		}

		gl.Clear().ColorBuffer().DoIt();

		rndr_opacity.Set(SineWave(f*0.5f));

		rndr.SetLayoutTransform(ModelMatrixf::TranslationZ(-20.0f+16.0f*f));
		rndr.Render(layout);
	}
};

int main(int argc, char* argv[])
{
	return oglplus::GlutGlewMain<BitmapGlyphExample>(
		"Example of usage of OGLplus' bitmap glyph text rendering",
		argc, argv
	);
}

