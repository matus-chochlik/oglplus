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

#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_RENDERER_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_RENDERER_HPP

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

	LazyProgramUniform<Mat4f>
		_projection_matrix,
		_camera_matrix,
		_layout_matrix;

	LazyProgramUniformSampler
		_bitmap_sampler,
		_metric_sampler,
		_pg_map_sampler;

	const BitmapGlyphFontEssence* _prev_font_essence;
	void _use_font(const BitmapGlyphFontEssence& essence)
	{
		if(_prev_font_essence != &essence)
		{
			_bitmap_sampler.Set(GLint(
				essence._page_storage.BitmapSampler()
			));
			_metric_sampler.Set(GLint(
				essence._page_storage.MetricSampler()
			));
			_pg_map_sampler.Set(GLint(
				essence._pager.PageMapSampler()
			));
			_prev_font_essence = &essence;
		}
	}

	const BitmapGlyphStaticLayoutStorage* _prev_layout_storage;
	void _use_layout(const BitmapGlyphLayoutData& layout_data)
	{
		if(_prev_layout_storage != layout_data._storage)
		{
			assert(layout_data._storage);

			layout_data._storage->Use();
			_prev_layout_storage = layout_data._storage;
		}
	}
public:
	BitmapGlyphRenderer(
		BitmapGlyphRendering& parent,
		const GeometryShader& layout_transform_shader,
		const GeometryShader& glyph_transform_shader,
		const FragmentShader& pixel_color_shader
	): _parent(parent)
	 , _program(ObjectDesc("BitmapGlyphRenderer"))
	 , _projection_matrix(_program, "ProjectionMatrix")
	 , _camera_matrix(_program, "CameraMatrix")
	 , _layout_matrix(_program, "LayoutMatrix")
	 , _bitmap_sampler(_program, "Bitmap")
	 , _metric_sampler(_program, "Metric")
	 , _pg_map_sampler(_program, "PageMap")
	 , _prev_font_essence(nullptr)
	 , _prev_layout_storage(nullptr)
	{
		VertexShader vs(ObjectDesc("BitmapGlyphRenderer - Vertex"));
		vs.Source(StrLit(
			"#version 330\n"

			"uniform uint GlyphsPerPage;"

			"uniform sampler2DRect Metric;"
			"uniform isamplerBuffer PageMap;"

			"layout (location = 0) in uint CodePoint;"
			"layout (location = 1) in float XOffset;"

			"out vec4 vertLogData;"
			"out vec4 vertInkData;"
			"out vec4 vertTexData;"
			"out float vertXOffset;"

			"void main(void)"
			"{"
			"	int goffs = int(CodePoint % GlyphsPerPage)*3;"
			"	int page =  int(CodePoint / GlyphsPerPage);"
			"	int frame = texelFetch(PageMap, page).r;"

			"	vertLogData = texelFetch("
			"		Metric,"
			"		ivec2(goffs+0, frame)"
			"	);"
			"	vertInkData = texelFetch("
			"		Metric,"
			"		ivec2(goffs+1, frame)"
			"	);"
			"	vertTexData = texelFetch("
			"		Metric,"
			"		ivec2(goffs+2, frame)"
			"	);"
			"	vertXOffset = XOffset;"
			"}"
		));
		vs.Compile();
		_program.AttachShader(vs);

		_program.AttachShader(layout_transform_shader);
		_program.AttachShader(glyph_transform_shader);

		GeometryShader gs(ObjectDesc("BitmapGlyphRenderer - Geometry"));
		gs.Source(StrLit(
			"#version 330\n"
			"layout (points) in;"
			"layout (triangle_strip, max_vertices = 6) out;"

			"vec3 TransformGlyph("
			"	vec2 Position,"
			"	float XOffset,"
			"	int Index"
			");"

			"vec4 TransformLayout(vec3 GlyphPosition);"

			"in vec4 vertLogData[1];"
			"in vec4 vertInkData[1];"
			"in vec4 vertTexData[1];"
			"in float vertXOffset[1];"

			"out vec3 geomTexCoord;"

			"void make_vertex(vec2 Position, vec2 TexCoord)"
			"{"
			"	vec3 GlyphPosition = TransformGlyph("
			"		Position,"
			"		float(vertXOffset[0]),"
			"		int(gl_PrimitiveIDIn)"
			"	);"
			"	gl_Position = TransformLayout(GlyphPosition);"
			"	geomTexCoord = vec3(TexCoord, 0.0);"
			"	EmitVertex();"
			"}"

			"void main(void)"
			"{"
			//      left bearing
			"       float lb = vertInkData[0].x;"
			//      right bearing
			"       float rb = vertInkData[0].y;"
			//      ascender
			"       float as = vertInkData[0].z;"
			//      descender
			"       float ds = vertInkData[0].w;"
			//      height
			"       float ht = as + ds;"
			//      glyph origin in texture space
			"       vec2  to = vertTexData[0].xy;"
			//      glyph width in texture space
			"       float tw = vertTexData[0].z;"
			//      glyph height in texture space
			"       float th = vertTexData[0].w;"
			//      glyph ascent in texture space
			"       float ta = th * (as / ht);"
			//      glyph descent in texture space
			"       float td = th * (ds / ht);"

			"       make_vertex(vec2( rb, -ds), to+vec2( tw, -td));"
			"       make_vertex(vec2( lb, -ds), to+vec2(0.0, -td));"
			"       make_vertex(vec2( rb, 0.0), to+vec2( tw, 0.0));"
			"       make_vertex(vec2( lb, 0.0), to+vec2(0.0, 0.0));"
			"       make_vertex(vec2( rb,  as), to+vec2( tw,  ta));"
			"       make_vertex(vec2( lb,  as), to+vec2(0.0,  ta));"
			"       EndPrimitive();"
			"}"
		));
		gs.Compile();
		_program.AttachShader(gs);

		_program.AttachShader(pixel_color_shader);

		FragmentShader fs(ObjectDesc("BitmapGlyphRenderer - Fragment"));
		fs.Source(StrLit(
			"#version 330\n"
			"uniform sampler2DArray Bitmap;"

			"in vec3 geomTexCoord;"

			"out vec4 fragColor;"

			"vec4 PixelColor(vec4 TexelColor);"

			"void main(void)"
			"{"
			"       fragColor = PixelColor(texture(Bitmap, geomTexCoord));"
			"}"

		));
		fs.Compile();
		_program.AttachShader(fs);

		_program.Link();
		ProgramUniform<GLuint>(_program, "GlyphsPerPage").Set(
			BitmapGlyphGlyphsPerPage(_parent)
		);
	}

	void Use(void)
	{
		_program.Use();
	}

	template <typename T>
	ProgramUniform<T> GetUniform(const GLchar* name) const
	{
		return ProgramUniform<T>(_program, name);
	}

	void Render(const BitmapGlyphLayout& layout)
	{
		// we'll need the layout font's essence
		assert(layout._font._essence);
		// use the layout's font
		_use_font(*layout._font._essence);
		// use the layout's storage
		_use_layout(layout._data);

		// load the font pages referenced by the layout
		layout._font._essence->LoadPages(
			layout._pages.data(),
			layout._pages.size()
		);

		// draw the glyphs
		Context gl;
		gl.DrawArrays(
			PrimitiveType::Points,
			layout._data._offset,
			layout._data._length
		);
	}
};

} // namespace text
} // namespace oglplus

#endif // include guard
