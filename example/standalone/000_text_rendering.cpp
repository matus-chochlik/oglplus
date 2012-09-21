/**
 *  @example standalone/000_text_rendering.cpp
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

#include <vector>

namespace oglplus {

} // namespace oglplus


class BitmapGlyphExample
 : public oglplus::SingleExample
{
private:
	oglplus::Context gl;

	static std::vector<oglplus::TextureUnitSelector> tr_tex_units(void)
	{
		std::vector<oglplus::TextureUnitSelector> result(2);
		result[0] = 0;
		result[1] = 1;
		return result;
	}
	oglplus::text::BitmapGlyphRendering tr;

public:
	BitmapGlyphExample(int argc, const char** argv)
	 : gl()
	 , tr((argc>0)?argv[0]:".", tr_tex_units())
	{
		using namespace oglplus;

		gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gl.Enable(Capability::Blend);
		gl.BlendFunc(
			BlendFunction::SrcAlpha,
			BlendFunction::DstAlpha
		);
size_t l;
const char s[] = u8"A";
size_t sl = sizeof(s)/sizeof(s[0]);
std::cerr << oglplus::text::BitmapGlyphPageName(tr, oglplus::aux::ConvertUTF8ToCodePoint(s, sl, l)) << std::endl;
	}

	void Reshape(void)
	{
		using namespace oglplus;

		gl.Viewport(Width(), Height());
	}

	void Render(void)
	{
		using namespace oglplus;

		gl.Clear().ColorBuffer().DoIt();
	}
};

int main(int argc, char* argv[])
{
	return oglplus::GlutGlewMain<BitmapGlyphExample>(
		"Example of usage of OGLplus' font rendering",
		argc, argv
	);
}

