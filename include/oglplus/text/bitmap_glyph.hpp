/**
 *  @file oglplus/text/bitmap_glyph.hpp
 *  @brief Bitmap-font-based text rendering.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_HPP

#include <oglplus/config.hpp>

#include <oglplus/text/bitmap_glyph/layout_storage.hpp>
#include <oglplus/text/bitmap_glyph/layout.hpp>
#include <oglplus/text/bitmap_glyph/font.hpp>
#include <oglplus/text/bitmap_glyph/renderer.hpp>

#include <oglplus/auxiliary/filesystem.hpp>

#include <oglplus/program.hpp>
#include <oglplus/uniform.hpp>

#include <vector>
#include <cassert>

namespace oglplus {
namespace text {

class BitmapGlyphRendering
{
private:
	// path to the directory where the font files are stored
	std::string _font_dir;

	friend std::string BitmapGlyphFontPagePath(
		const BitmapGlyphRendering& that,
		const std::string& font_name,
		GLint font_page
	)
	{
		std::string dirsep = oglplus::aux::FilesysPathSep();
		return that._font_dir+
			dirsep+
			font_name+
			dirsep+
			BitmapGlyphPageName(that, font_page);
	}

	TextureUnitSelector _bitmap_tex_unit;
	TextureUnitSelector _metric_tex_unit;
	TextureUnitSelector _pg_map_tex_unit;

	const unsigned _page_frames;

	// the number of frames (texture images) that are used to store
	// active glyph pages for rendering
	friend unsigned BitmapGlyphPageFrames(const BitmapGlyphRendering& that)
	{
		return that._page_frames;
	}


	// the number of planes supported by this instance
	// of the rendering utility
	const unsigned _plane_count;

	friend unsigned BitmapGlyphPlaneCount(const BitmapGlyphRendering& that)
	{
		return that._plane_count;
	}


	// the number of font pages per a single plane
	const unsigned _pages_per_plane;

	friend unsigned BitmapGlyphPagesPerPlane(const BitmapGlyphRendering& that)
	{
		return that._pages_per_plane;
	}


	// the number of glyphs per a single font page
	const unsigned _glyphs_per_page;

	friend unsigned BitmapGlyphGlyphsPerPage(const BitmapGlyphRendering& that)
	{
		return that._glyphs_per_page;
	}


	// TODO: replace this with a vector of data objects
	BitmapGlyphStaticLayoutStorage _static_layout_data;

	friend void BitmapGlyphAllocateLayoutData(
		BitmapGlyphRendering& that,
		BitmapGlyphLayoutData& layout_data
	)
	{
		that._static_layout_data.Allocate(layout_data);
	}

	friend void BitmapGlyphInitializeLayoutData(
		BitmapGlyphRendering& that,
		BitmapGlyphLayoutData& layout_data,
		BitmapGlyphFont& font,
		const CodePoint* cps,
		GLsizei length
	)
	{
		that._static_layout_data.Initialize(
			layout_data,
			font,
			cps,
			length
		);
	}

	friend void BitmapGlyphDeallocateLayoutData(
		BitmapGlyphRendering& that,
		BitmapGlyphLayoutData& layout_data
	)
	{
		that._static_layout_data.Deallocate(layout_data);
	}
public:
	BitmapGlyphRendering(
		const std::string& font_dir,
		TextureUnitSelector bitmap_tex_unit,
		TextureUnitSelector metric_tex_unit,
		TextureUnitSelector pg_map_tex_unit,
		unsigned max_glyphs = 1024,
		unsigned page_frames = 8,
		unsigned planes = 3,
		unsigned pages = 256,
		unsigned cells = 256
	): _font_dir(font_dir)
	 , _bitmap_tex_unit(bitmap_tex_unit)
	 , _metric_tex_unit(metric_tex_unit)
	 , _pg_map_tex_unit(pg_map_tex_unit)
	 , _page_frames(page_frames)
	 , _plane_count(planes)
	 , _pages_per_plane(pages)
	 , _glyphs_per_page(cells)
	 , _static_layout_data(*this, max_glyphs) //TODO
	{ }

	typedef BitmapGlyphRenderer Renderer;

	Renderer GetRenderer(
		const GeometryShader& layout_transform_shader,
		const GeometryShader& glyph_transform_shader,
		const FragmentShader& pixel_color_shader
	)
	{
		return Renderer(
			*this,
			layout_transform_shader,
			glyph_transform_shader,
			pixel_color_shader
		);
	}

	typedef BitmapGlyphFont Font;

	Font LoadFont(
		const std::string& font_name,
		TextureUnitSelector bitmap_tex_unit,
		TextureUnitSelector metric_tex_unit,
		TextureUnitSelector pg_map_tex_unit,
		GLsizei frames,
		GLint page
	)
	{
		return Font(
			*this,
			bitmap_tex_unit,
			metric_tex_unit,
			pg_map_tex_unit,
			font_name,
			frames,
			page
		);
	}

	Font LoadFont(const std::string& font_name)
	{
		return LoadFont(
			font_name,
			_bitmap_tex_unit,
			_metric_tex_unit,
			_pg_map_tex_unit,
			BitmapGlyphPageFrames(*this),
			0
		);
	}

	typedef BitmapGlyphLayout Layout;

	Layout MakeLayout(Font font, GLsizei max_len)
	{
		return Layout(*this, font, max_len);
	}

	Layout MakeLayout(Font font, const StrLit& lit)
	{
		std::vector<CodePoint> cps;
		UTF8ToCodePoints(lit.c_str(), lit.size(), cps);

		Layout layout(MakeLayout(font, cps.size()));
		layout.Set(cps);
		return std::move(layout);
	}
};


} // namespace text
} // namespace oglplus

#endif // include guard
