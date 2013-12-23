/**
 *  @file oglplus/text/pango_cairo/layout.hpp
 *  @brief Pango/Cairo-based text rendering - layout.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_PANGO_CAIRO_LAYOUT_HPP
#define OGLPLUS_TEXT_PANGO_CAIRO_LAYOUT_HPP

#include <oglplus/config.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/text/common.hpp>
#include <oglplus/text/pango_cairo/fwd.hpp>
#include <oglplus/text/pango_cairo/handle.hpp>
#include <oglplus/text/pango_cairo/layout_storage.hpp>
#include <oglplus/texture.hpp>


namespace oglplus {
namespace text {

class PangoCairoLayout
{
private:
	friend class PangoCairoRenderer;

	PangoCairoRendering& _parent;

	PangoCairoFont _font;
	const GLsizei _capacity;
	int _curr_width;
	int _width;
	int _height;

	Vec4f _log_coords, _tex_coords;

	PangoCairoHandle< ::cairo_surface_t*> _surface;

	PangoCairoLayoutData _data;

	PangoCairoLayout(const PangoCairoLayout&);
public:
	PangoCairoLayout(
		PangoCairoRendering& parent,
		const PangoCairoFont& font,
		GLsizei capacity
	);

	PangoCairoLayout(PangoCairoLayout&& tmp)
	 : _parent(tmp._parent)
	 , _font(std::move(tmp._font))
	 , _capacity(tmp._capacity)
	 , _curr_width(tmp._curr_width)
	 , _width(tmp._width)
	 , _height(tmp._height)
	 , _surface(std::move(tmp._surface))
	 , _data(std::move(tmp._data))
	{ }

	~PangoCairoLayout(void)
	{
		PangoCairoDeallocateLayoutData(_parent, _data);
	}

	TextureUnitSelector Use(void) const
	{
		return PangoCairoUseLayoutData(_parent, _data);
	}

	GLsizei Capacity(void) const
	{
		return _capacity;
	}

	GLfloat Width(void) const
	{
		return GLfloat(_curr_width) / GLfloat(_height);
	}

	void Set(const char* c_str, const std::size_t size);

	void Set(const StrLit& string_literal)
	{
		Set(string_literal.c_str(), string_literal.size());
	}

	void Set(const String& string)
	{
		Set(string.c_str(), string.size());
	}

	void Set(const CodePoint* code_points, const GLsizei length)
	{
		std::vector<char> str;
		CodePointsToUTF8(code_points, length, str);
		Set(str.data(), str.size());
	}
};

} // namespace text
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/text/pango_cairo/layout.ipp>
#endif

#endif // include guard
