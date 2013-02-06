/**
 *  @file oglplus/text/bitmap_glyph.hpp
 *  @brief Bitmap-font-based text rendering.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
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
#include <list>
#include <cassert>
#include <sstream>

namespace oglplus {

namespace text {

struct BitmapGlyphRenderingConfig
{
	/// Number of frames used for paging
	unsigned page_frames;

	/// Number of unicode planes that should be supported (1, 2, or 3)
	unsigned plane_count;

	/// number of glyph pages per unicode plane
	unsigned pages_per_plane;

	/// Number of glyphs per single page
	unsigned glyphs_per_page;

	/// Max number of glyps in a single layout storage unit
	unsigned layout_storage_page;

	/// Minimal allocation unit for a layout storage unit
	unsigned layout_storage_unit;

	BitmapGlyphRenderingConfig(void)
	 : page_frames(8)
	 , plane_count(3)
	 , pages_per_plane(256)
	 , glyphs_per_page(256)
	 , layout_storage_page(1024)
	 , layout_storage_unit(4)
	{ }
};

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

	const BitmapGlyphRenderingConfig _config;

	// the number of frames (texture images) that are used to store
	// active glyph pages for rendering
	friend unsigned BitmapGlyphPageFrames(const BitmapGlyphRendering& that)
	{
		return that._config.page_frames;
	}


	friend unsigned BitmapGlyphPlaneCount(const BitmapGlyphRendering& that)
	{
		return that._config.plane_count;
	}


	friend unsigned BitmapGlyphPagesPerPlane(const BitmapGlyphRendering& that)
	{
		return that._config.pages_per_plane;
	}


	friend unsigned BitmapGlyphGlyphsPerPage(const BitmapGlyphRendering& that)
	{
		return that._config.glyphs_per_page;
	}


	std::list<BitmapGlyphLayoutStorage> _layout_storage;

	friend void BitmapGlyphAllocateLayoutData(
		BitmapGlyphRendering& that,
		BitmapGlyphLayoutData& layout_data
	)
	{
		auto	i = that._layout_storage.begin(),
			e = that._layout_storage.end();
		while(i != e)
		{
			if(i->Allocate(layout_data)) return;
			++i;
		}
		that._layout_storage.emplace_back(
			that,
			that._config.layout_storage_page,
			that._config.layout_storage_unit
		);
		that._layout_storage.back().Allocate(layout_data);
	}

	friend void BitmapGlyphDeallocateLayoutData(
		BitmapGlyphRendering& that,
		BitmapGlyphLayoutData& layout_data
	)
	{
		OGLPLUS_FAKE_USE(that);
		assert(layout_data._storage);
		BitmapGlyphLayoutStorage& _storage = *layout_data._storage;
		_storage.Deallocate(layout_data);
	}

	friend void BitmapGlyphInitializeLayoutData(
		BitmapGlyphRendering& that,
		BitmapGlyphLayoutData& layout_data,
		BitmapGlyphFont& font,
		const CodePoint* cps,
		GLsizei length
	)
	{
		OGLPLUS_FAKE_USE(that);
		assert(layout_data._storage);
		BitmapGlyphLayoutStorage& _storage = *layout_data._storage;
		_storage.Initialize(
			layout_data,
			font,
			cps,
			length
		);
	}
public:
	typedef BitmapGlyphRenderingConfig Config;

	BitmapGlyphRendering(
		const std::string& font_dir,
		TextureUnitSelector bitmap_tex_unit,
		TextureUnitSelector metric_tex_unit,
		TextureUnitSelector pg_map_tex_unit,
		const Config& config = Config()
	): _font_dir(font_dir)
	 , _bitmap_tex_unit(bitmap_tex_unit)
	 , _metric_tex_unit(metric_tex_unit)
	 , _pg_map_tex_unit(pg_map_tex_unit)
	 , _config(config)
	{ }

	typedef BitmapGlyphRenderer CustomRenderer;

	CustomRenderer GetRenderer(
		const GeometryShader& layout_transform_shader,
		const GeometryShader& glyph_transform_shader,
		const FragmentShader& pixel_color_shader
	)
	{
		return CustomRenderer(
			*this,
			layout_transform_shader,
			glyph_transform_shader,
			pixel_color_shader
		);
	}

	typedef BitmapGlyphDefaultRenderer Renderer;

	Renderer GetRenderer(const FragmentShader& pixel_color_shader)
	{
		return Renderer(*this, pixel_color_shader);
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

	Layout MakeLayout(Font font, const GLchar* c_str, std::size_t size)
	{
		std::vector<CodePoint> cps;
		UTF8ToCodePoints(c_str, size, cps);

		Layout layout(MakeLayout(font, size));
		layout.Set(cps);
		return std::move(layout);
	}

	Layout MakeLayout(Font font, const StrLit& lit)
	{
		return MakeLayout(font, lit.c_str(), lit.size());
	}

	Layout MakeLayout(Font font, const String& str)
	{
		return MakeLayout(font, str.c_str(), str.size());
	}
};


} // namespace text
} // namespace oglplus

#endif // include guard
