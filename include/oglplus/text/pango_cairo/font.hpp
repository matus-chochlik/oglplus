/**
 *  @file oglplus/text/pango_cairo/font.hpp
 *  @brief Pango/Cairo-based text rendering - font.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_PANGO_CAIRO_FONT_HPP
#define OGLPLUS_TEXT_PANGO_CAIRO_FONT_HPP

#include <oglplus/config.hpp>

#include <oglplus/text/pango_cairo/fwd.hpp>
#include <oglplus/text/pango_cairo/handle.hpp>

#include <pango/pangocairo.h>

#include <cassert>
#include <memory>

namespace oglplus {
namespace text {

class PangoCairoFontEssence
{
private:
	friend class PangoCairoLayout;

	PangoCairoHandle< ::PangoFontDescription*> _font_desc;
	PangoCairoHandle< ::PangoFontMap*, ::gpointer> _font_map;
	PangoCairoHandle< ::PangoContext*, ::gpointer> _context;
	PangoCairoHandle< ::PangoFont*, ::gpointer> _font;
	PangoCairoHandle< ::PangoFontMetrics*> _font_metrics;

	PangoCairoFontEssence(const PangoCairoFontEssence&);
public:
	PangoCairoFontEssence(
		const char* font_name
	): _font_desc(
		::pango_font_description_from_string(font_name),
		::pango_font_description_free
	), _font_map(
		::pango_cairo_font_map_get_default(),
		::g_object_unref
	), _context(
		::pango_font_map_create_context(_font_map),
		::g_object_unref
	), _font(
		::pango_font_map_load_font(_font_map, _context, _font_desc),
		::g_object_unref
	), _font_metrics(
		::pango_font_get_metrics(_font, nullptr),
		::pango_font_metrics_unref
	)
	{ }

	int Ascent(void)
	{
		return ::pango_font_metrics_get_ascent(_font_metrics)/
			PANGO_SCALE;
	}

	int Descent(void)
	{
		return ::pango_font_metrics_get_descent(_font_metrics)/
			PANGO_SCALE;
	}

	int Height(void)
	{
		return Ascent()+Descent();
	}

	int ApproxGlyphWidth(void)
	{
		int cw = ::pango_font_metrics_get_approximate_char_width(_font_metrics);
		int dw = ::pango_font_metrics_get_approximate_digit_width(_font_metrics);
		return ((cw > dw)? cw : dw)/PANGO_SCALE;
	}
};

class PangoCairoFont
{
private:
	friend class PangoCairoLayout;

	std::shared_ptr<PangoCairoFontEssence> _essence;
public:
	PangoCairoFont(const char* font_name)
	 : _essence(std::make_shared<PangoCairoFontEssence>(font_name))
	{ }
};

} // namespace text
} // namespace oglplus

#endif // include guard
