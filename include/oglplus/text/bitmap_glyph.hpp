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

#include <oglplus/text/bitmap_glyph/page_map.hpp>
#include <oglplus/text/bitmap_glyph/layout_storage.hpp>
#include <oglplus/text/bitmap_glyph/layout.hpp>
#include <oglplus/text/bitmap_glyph/font.hpp>
#include <oglplus/text/bitmap_glyph/renderer.hpp>

#include <vector>
#include <cassert>

namespace oglplus {
namespace text {

class BitmapGlyphRendering
{
private:
	// path to the directory where the font files are stored
	std::string _font_dir;

	friend const std::string& BitmapGlyphFontDirPath(
		const BitmapGlyphRendering& that
	)
	{
		return that._font_dir;
	}

	// the list of texture units used by this instance
	// of the rendering utility
	std::vector<TextureUnitSelector> _tex_units;

	friend unsigned BitmapGlyphTexUnits(const BitmapGlyphRendering& that)
	{
		return that._tex_units.size();
	}


	// the number of planes supported by this instance
	// of the rendering utility
	unsigned _plane_count;

	friend unsigned BitmapGlyphPlaneCount(const BitmapGlyphRendering& that)
	{
		return that._plane_count;
	}


	// the number of font pages per a single plane
	unsigned _pages_per_plane;

	friend unsigned BitmapGlyphPagesPerPlane(const BitmapGlyphRendering& that)
	{
		return that._pages_per_plane;
	}


	// the number of glyphs per a single font page
	unsigned _glyphs_per_page;

	friend unsigned BitmapGlyphGlyphsPerPage(const BitmapGlyphRendering& that)
	{
		return that._glyphs_per_page;
	}


	// TODO:
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
		const CodePoint* cps,
		GLsizei length
	)
	{
		that._static_layout_data.Initialize(layout_data, cps, length);
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
		std::vector<TextureUnitSelector>&& tex_units,
		unsigned planes = 3,
		unsigned pages = 256,
		unsigned cells = 256
	): _font_dir(font_dir)
	 , _tex_units(std::move(tex_units))
	 , _plane_count(planes)
	 , _pages_per_plane(pages)
	 , _glyphs_per_page(cells)
	 , _static_layout_data(*this, 1024)
	{ }

	typedef BitmapGlyphFont Font;

	Font LoadFont(const std::string& font_name)
	{
		return Font(*this, font_name);
	}

	typedef BitmapGlyphLayout Layout;

	Layout MakeLayout(Font font, const StrLit& lit)
	{
	}
};


} // namespace text
} // namespace oglplus

#endif // include guard
