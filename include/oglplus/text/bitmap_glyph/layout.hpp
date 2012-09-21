/**
 *  @file oglplus/text/bitmap_glyph/layout.hpp
 *  @brief Bitmap-font-based text rendering, layout class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_LAYOUT_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_LAYOUT_HPP

#include <oglplus/config.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/text/unicode.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>
#include <oglplus/text/bitmap_glyph/font.hpp>
#include <oglplus/text/bitmap_glyph/layout_storage.hpp>

namespace oglplus {
namespace text {

class BitmapGlyphLayout
{
private:
	BitmapGlyphRendering& _parent;

	BitmapGlyphFont _font;

	BitmapGlyphLayoutData _data;

	friend class BitmapGlyphRenderer;

	bool _is_ok(void) const
	{
		return	(_data._offset >= 0) &&
			(_data._offset < _data._count);
	}
public:
	BitmapGlyphLayout(
		BitmapGlyphRendering& parent,
		const BitmapGlyphFont& font,
		GLsizei max_len
	): _parent(parent)
	 , _font(font)
	 , _data(max_len)
	{
		BitmapGlyphAllocateLayoutData(_parent, _data);
		assert(_is_ok());
	}

	BitmapGlyphLayout(const BitmapGlyphLayout& other)
	 : _parent(other._parent)
	 , _font(other._font)
	 , _data(other._data)
	{
		_data._offset = -1;
		BitmapGlyphAllocateLayoutData(_parent, _data);
		assert(_is_ok());
	}

	BitmapGlyphLayout(BitmapGlyphLayout&& tmp)
	 : _parent(tmp._parent)
	 , _font(std::move(tmp._font))
	 , _data(std::move(tmp._data))
	{
		tmp._data._offset = -1;
		assert(_is_ok());
	}

	~BitmapGlyphLayout(void)
	{
		if(_data._offset >= 0)
			BitmapGlyphDeallocateLayoutData(_parent, _data);
	}

	GLsizei Capacity(void) const
	{
		return _data._count;
	}

	void Set(const CodePoint* cps, GLsizei size)
	{
		assert(_is_ok());
		assert(size <= Capacity());
		BitmapGlyphInitializeLayoutData(_parent, _data, cps, size);
	}

	void Set(const std::vector<CodePoint>& cps)
	{
		Set(cps.data(), GLsizei(cps.size()));
	}

	void Set(const StrLit& lit)
	{
		Set(UTF8ToCodePoints(lit.c_str(), lit.size()));
	}

	void Set(const String& str)
	{
		Set(UTF8ToCodePoints(str.c_str(), str.size()));
	}
};

} // namespace text
} // namespace oglplus

#endif // include guard
