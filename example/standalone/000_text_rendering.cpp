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
#include <oglplus/bound/texture.hpp>

#include <oglplus/auxiliary/conversion.hpp>

#include <fstream>
#include <vector>

namespace oglplus {
namespace text {

typedef oglplus::aux::utf8::UnicodeCP CodePoint;

class Rectangle
{
private:
	GLfloat _left, _right, _bottom, _top;
public:
	Rectangle(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
	 : _left(left)
	 , _right(right)
	 , _bottom(bottom)
	 , _top(top)
	{ }

	GLfloat Left(void) const { return _left; }

	GLfloat Right(void) const { return _right; }

	GLfloat Bottom(void) const { return _bottom; }

	GLfloat Top(void) const { return _top; }

	GLfloat Width(void) const {return Right() - Left(); }

	GLfloat Height(void) const {return Top() - Bottom(); }
};

#if OGLPLUS_DOCUMENTATION_ONLY

class Font
{
public:
	GLfloat PixelsPerUnit(void);
};

class Layout
{
public:
	Rectangle LogicalMetrics(void);
};

class LayoutTransform
{
public:
};

class GlyphTransform
{
public:
};

class Renderer
{
public:
	void Render(
		const Layout& layout,
		LayoutTransform layout_transform,
		GlyphTransform glyph_transform
	);
};

#endif

class BitmapFontTextRendering
{
private:
public:
};

} // namespace text
} // namespace oglplus


class BitmapFontExample
 : public oglplus::SingleExample
{
private:
	oglplus::Context gl;

public:
	BitmapFontExample(int argc, const char** argv)
	 : gl()
	{
		using namespace oglplus;

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
	}

	void Render(void)
	{
		using namespace oglplus;

		gl.Clear().ColorBuffer().DoIt();
	}
};

int main(int argc, char* argv[])
{
	return oglplus::GlutGlewMain<BitmapFontExample>(
		"Example of usage of OGLplus' font rendering",
		argc, argv
	);
}

