/**
 *  @file oglplus/text/bitmap_glyph/renderer.hpp
 *  @brief Bitmap-font-based text rendering, renderer class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_FONT_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_FONT_HPP

#include <oglplus/config.hpp>
#include <oglplus/program.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>
#include <oglplus/text/bitmap_glyph/font.hpp>
#include <oglplus/text/bitmap_glyph/layout.hpp>

namespace oglplus {
namespace text {

class BitmapGlyphRenderer
{
private:
	BitmapGlyphRendering& _parent;

	Program _program;
public:
	BitmapGlyphRenderer(
		BitmapGlyphRendering& parent
	): _parent(parent)
	 , _program(ObjectDesc("BitmapGlyphRenderer"))
	{
		_program.AttachShader(VertexShader(
			ObjectDesc("BitmapGlyphRenderer - Vertex"),
			StrLit("#version 330\n"
			"uniform sampler2DArray LogMetrics;"
			"uniform sampler2DArray InkMetrics;"
			"uniform sampler2DArray TexMetrics;"

			"layout (location = 0) in uint  CodePoint;"
			"layout (location = 1) in float XOffset;"

			"out vec4 vertLogMetrics;"
			"out vec4 vertInkMetrics;"
			"out vec4 vertTexMetrics;"

			"void main(void)"
			"{"
			"	ivec3 tc = ivec3("
			"		(CodePoint >>  0) & 0xFF,"
			"		(CodePoint >>  8) & 0xFF,"
			"		(CodePoint >> 16) & 0xFF "
			"	);"
			"	vertLogMetrics = texelFetch(LogMetrics, tc);"
			"	vertInkMetrics = texelFetch(InkMetrics, tc);"
			"	vertTexMetrics = texelFetch(TexMetrics, tc);"
			"}"
			)
		));

		_program.AttachShader(GeometryShader(
			ObjectDesc("BitmapGlyphRenderer - Geometry"),
			StrLit("#version 330\n"
			"layout (points) in;"
			"layout (triangle_strip, max_vertices = 6) out;"

			"layout (std140) uniform {"
			"};"

			"void main(void)"
			"{"
			"}"
			)
		));

		_program.AttachShader(VertexShader(
			ObjectDesc("BitmapGlyphRenderer - Fragment"),
			StrLit("#version 330\n"
			""
			)
		));

		_program.Link();
	}

	void Use(void)
	{
		_program.Use();
	}

	void Render(const BitmapFontLayout& layout)
	{
	}
};

} // namespace text
} // namespace oglplus

#endif // include guard
