/**
 *  @file oglplus/text/bitmap_glyph/font.hpp
 *  @brief Bitmap-font-based text rendering, font class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_FONT_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_FONT_HPP

#include <oglplus/config.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>
#include <oglplus/text/bitmap_glyph/page_storage.hpp>
#include <oglplus/text/bitmap_glyph/pager.hpp>

#include <memory>

namespace oglplus {
namespace text {

class BitmapGlyphFontEssence
{
private:
	BitmapGlyphRendering& _parent;
	const std::string _font_name;

	inline std::string _page_bitmap_path(GLint page)
	{
		return BitmapGlyphFontPagePath(_parent,_font_name,page)+".png";
	}

	oglplus::images::Image _load_page_bitmap(GLint page)
	{
		return images::PNG(_page_bitmap_path(page).c_str());
	}

	inline std::string _page_metric_path(GLint page)
	{
		return BitmapGlyphFontPagePath(_parent,_font_name,page)+".bgm";
	}

	static void _check_input(std::istream& input)
	{
		assert(!input.fail());
		if(input.eof())
			throw std::runtime_error("Unexpected EOF in .bgm file");
		if(input.bad())
			throw std::runtime_error("Error reading .bgm file");
	}

	static void _unexpected_char(char)
	{
		throw std::runtime_error("Unexpected character in .bgm file");
	}

	static void _load_single_glyph(
		std::istream& input,
		char* line,
		const size_t linelen,
		GLfloat* values,
		const size_t n_values
	)
	{
		// read the code-point of the glyph
		_check_input(input);
		unsigned cp;
		input >> cp;
		// eat the newline
		_check_input(input);
		input.getline(line, linelen);
		// skip the hex code line
		_check_input(input);
		input.getline(line, linelen);
		// skip the code point's quoted utf-8 sequence
		char c;
		_check_input(input);
		input.get(c);
		_check_input(input);
		if(c != '\'') _unexpected_char(c);
		do { input.get(c); _check_input(input); }
		while(c != '\'');
		input.getline(line, linelen);
		//
		// read the n metric values
		for(unsigned v=0; v!=n_values; ++v)
		{
			// read the value
			GLfloat value;
			_check_input(input);
			input >> value;
			// store the value
			values[v] = value;
			// eat the rest of the line
			input.getline(line, linelen);
		}
		// skip the separating line
		_check_input(input);
		input.getline(line, linelen);
	}

	std::vector<GLfloat> _load_page_metric(GLint page)
	{
		std::ifstream input(_page_metric_path(page).c_str());
		if(!input.good())
		{
			std::string msg("Unable to open file '");
			msg.append(_page_metric_path(page));
			msg.append("' for reading.");
			throw std::runtime_error(msg);
		}

		unsigned values_per_glyph = 4*3;
		unsigned glyphs_per_page = BitmapGlyphGlyphsPerPage(_parent);
		std::vector<GLfloat> metrics(glyphs_per_page*values_per_glyph);

		const size_t linelen = 63;
		char line[linelen+1];
		for(unsigned g=0; g!=glyphs_per_page; ++g)
		{
			_load_single_glyph(
				input,
				line,
				linelen,
				metrics.data()+g*values_per_glyph,
				values_per_glyph
			);
		}
		return metrics;
	}

	BitmapGlyphPager _pager;
	const GLint _initial_frame;
	BitmapGlyphPageStorage _page_storage;

	template <typename PageGetter, typename Element>
	void _do_load_pages(
		PageGetter get_page,
		const Element* elem,
		GLsizei size
	)
	{
		_page_storage.Bind();
		// go through the list of code-points
		for(GLsizei i=0; i!=size; ++i)
		{
			// get the page number for the glyph
			GLint page = get_page(elem[i]);
			// check if the page is active
			if(!_pager.UsePage(page))
			{
				// if not let the pager find
				// a frame for the new page
				auto frame = _pager.FindFrame();
				// load the bitmap image
				_page_storage.LoadPage(
					frame,
					_load_page_bitmap(page),
					_load_page_metric(page)
				);
				// tell the pages that the page
				// is successfully loaded in the frame
				_pager.SwapPageIn(frame, page);
			}
		}
	}

	struct _page_to_page
	{
		GLint operator()(GLint page) const
		{
			return page;
		}
	};
public:
	BitmapGlyphFontEssence(
		BitmapGlyphRendering& parent,
		TextureUnitSelector bitmap_tex_unit,
		TextureUnitSelector metric_tex_unit,
		TextureUnitSelector pg_map_tex_unit,
		const std::string& font_name,
		GLsizei frames,
		GLint default_page
	): _parent(parent)
	 , _font_name(font_name)
	 , _pager(
		parent,
		pg_map_tex_unit,
		frames
	), _initial_frame(_pager.FindFrame())
	 , _page_storage(
		parent,
		bitmap_tex_unit,
		metric_tex_unit,
		_initial_frame,
		frames,
		_load_page_bitmap(default_page),
		_load_page_metric(default_page)
	)
	{
		_pager.SwapPageIn(_initial_frame, default_page);
	}

	void Use(void) const
	{
		_pager.Bind();
		_page_storage.Bind();
	}

	TextureUnitSelector BitmapSampler(void) const
	{
		return _page_storage.BitmapSampler();
	}

	TextureUnitSelector MetricSampler(void) const
	{
		return _page_storage.MetricSampler();
	}

	TextureUnitSelector PageMapSampler(void) const
	{
		return _pager.PageMapSampler();
	}

	void LoadPages(const GLint* pages, GLsizei size)
	{
		assert(size < GLsizei(_pager.FrameCount()));
		_do_load_pages(_page_to_page(), pages, size);
	}

	GLfloat QueryXOffsets(
		const CodePoint* cps,
		GLsizei size,
		std::vector<GLfloat>& x_offsets
	) const
	{
		if(size <= 0) return 0.0f;
		x_offsets.resize(size);

		GLsizei i = 0;

		GLint page = BitmapGlyphPageOfCP(_parent, cps[i]);
		GLint cell = BitmapGlyphCellOfCP(_parent, cps[i]);
		GLint frame = _pager.FrameOfPage(page);
		// Logical left bearing
		GLfloat sum = _page_storage.GetGlyphMetric(frame, cell, 0);
		x_offsets[i] = sum;

		while(++i != size)
		{
			sum += _page_storage.GetGlyphWidth(frame, cell);
			x_offsets[i] = sum;
			page = BitmapGlyphPageOfCP(_parent, cps[i]);
			cell = BitmapGlyphCellOfCP(_parent, cps[i]);
			frame = _pager.FrameOfPage(page);
			assert(frame >= 0);
		}
		return sum + _page_storage.GetGlyphWidth(frame, cell);
	}

	Rectangle GetGlyphMetrics(CodePoint code_point, GLint offs) const
	{
		GLint page = BitmapGlyphPageOfCP(_parent, code_point);
		GLint cell = BitmapGlyphCellOfCP(_parent, code_point);
		GLint frame = _pager.FrameOfPage(page);

		assert(offs % 4 == 0);
		GLfloat buf[4];
		_page_storage.QueryGlyphMetrics(frame, cell, offs, 4, buf);
		return Rectangle(buf[0], buf[1], buf[3], buf[2]);
	}
};

class BitmapGlyphFont
{
private:
	std::shared_ptr<BitmapGlyphFontEssence> _essence;

	friend class BitmapGlyphRenderer;
	friend class BitmapGlyphLayout;
public:
	BitmapGlyphFont(
		BitmapGlyphRendering& parent,
		TextureUnitSelector bitmap_tex_unit,
		TextureUnitSelector metric_tex_unit,
		TextureUnitSelector pg_map_tex_unit,
		const std::string& name,
		GLsizei frames,
		GLint default_page
	): _essence(std::make_shared<BitmapGlyphFontEssence>(
		parent,
		bitmap_tex_unit,
		metric_tex_unit,
		pg_map_tex_unit,
		name,
		frames,
		default_page
	))
	{ }

	GLfloat QueryXOffsets(
		const CodePoint* cps,
		GLsizei size,
		std::vector<GLfloat>& x_offsets
	) const
	{
		return _essence->QueryXOffsets(cps, size, x_offsets);
	}

	Rectangle GlyphLogicalMetrics(CodePoint cp)
	{
		return _essence->GetGlyphMetrics(cp, 0);
	}
};

} // namespace text
} // namespace oglplus

#endif // include guard
