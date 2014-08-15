/**
 *  @file oglplus/text/bitmap_glyph/layout.hpp
 *  @brief Bitmap-font-based text rendering, layout class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_LAYOUT_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_LAYOUT_HPP

#include <oglplus/buffer.hpp>
#include <oglplus/text/unicode.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>
#include <oglplus/text/bitmap_glyph/font.hpp>
#include <oglplus/text/bitmap_glyph/layout_storage.hpp>

#include <vector>
#include <algorithm>

namespace oglplus {
namespace text {

template <typename BitmapFont>
class BitmapGlyphLayoutTpl
{
private:
	// reference to the parent rendering system
	BitmapGlyphRenderingBase& _parent;

	// the font used by this layout
	BitmapFont _font;

	// layout data used by a renderer
	BitmapGlyphLayoutData _data;

	// the list of font pages that this layout references
	std::vector<GLint> _pages;

	friend class BitmapGlyphRenderer;

	// sanity check
	bool _is_ok(void) const
	{
		return	(_data._offset >= 0) &&
			(_data._capacity > 0) &&
			(_data._storage);
	}
public:
	BitmapGlyphLayoutTpl(
		BitmapGlyphRenderingBase& parent,
		const BitmapFont& font,
		GLsizei max_len
	): _parent(parent)
	 , _font(font)
	 , _data(max_len)
	{
		BitmapGlyphAllocateLayoutData(_parent, _data);
		assert(_is_ok());
	}

	BitmapGlyphLayoutTpl(const BitmapGlyphLayoutTpl& other)
	 : _parent(other._parent)
	 , _font(other._font)
	 , _data(other._data._capacity)
	 , _pages(other._pages)
	{
		BitmapGlyphAllocateLayoutData(_parent, _data);
		assert(_is_ok());
	}

	BitmapGlyphLayoutTpl(BitmapGlyphLayoutTpl&& tmp)
	 : _parent(tmp._parent)
	 , _font(std::move(tmp._font))
	 , _data(std::move(tmp._data))
	 , _pages(std::move(tmp._pages))
	{
		tmp._data._storage = nullptr;
		assert(_is_ok());
	}

	~BitmapGlyphLayoutTpl(void)
	{
		if(_data._storage)
			BitmapGlyphDeallocateLayoutData(_parent, _data);
	}

	GLsizei Capacity(void) const
	{
		return _data._capacity;
	}

	GLfloat Width(void) const
	{
		return _data._width;
	}

	void Set(const CodePoint* cps, GLsizei size)
	{
		assert(_is_ok());
		assert(size <= Capacity());

		// update the list of referenced font pages
		_pages.clear();
		for(GLsizei cp=0; cp!=size; ++cp)
		{
			GLint page = BitmapGlyphPageOfCP(_parent, cps[cp]);
			auto i = _pages.begin(), e = _pages.end();
			if(std::find(i, e, page) == e)
				_pages.push_back(page);
		}
		_font._essence->LoadPages(_pages.data(), _pages.size());

		// initialize the layout data
		BitmapGlyphInitializeLayoutData(_parent,_data,_font, cps, size);
	}

	void Set(const CodePoints& cps)
	{
		Set(cps.data(), GLsizei(cps.size()));
	}

	void Set(StrCRef str)
	{
		Set(UTF8ToCodePoints(str.begin(), str.size()));
	}
};

} // namespace text
} // namespace oglplus

#endif // include guard
