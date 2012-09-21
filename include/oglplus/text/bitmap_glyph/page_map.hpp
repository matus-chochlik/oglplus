/**
 *  @file oglplus/text/bitmap_glyph/page_map.hpp
 *  @brief Bitmap-font-based text rendering, texture unit mapping
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_PAGE_MAP_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_PAGE_MAP_HPP

#include <oglplus/config.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/text/unicode.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>

namespace oglplus {
namespace text {

// Maps code-point's plane/page pair to a texture image number
class BitmapGlyphPageMap
{
private:
	BitmapGlyphRendering& _parent;
	Buffer _storage;
public:
	BitmapGlyphPageMap(BitmapGlyphRendering& parent)
	 : _parent(parent)
	{
		_storage.Bind(Buffer::Target::Uniform);
		std::vector<GLubyte> data(
			BitmapGlyphPlaneCount(_parent)*
			BitmapGlyphPagesPerPlane(_parent),
			~GLubyte(0)
		);
		Buffer::Data(Buffer::Target::Uniform, data);
	}

	GLubyte FrameOfPage(CodePoint cp)
	{
		_storage.Bind(Buffer::Target::Uniform);
		return Buffer::TypedMap<GLubyte>(
			Buffer::Target::Uniform,
			BufferMapAccess::Read
		).At(BitmapGlyphPageOfCP(_parent, cp));
	}

	void FrameOfPage(CodePoint cp, GLubyte frame)
	{
		_storage.Bind(Buffer::Target::Uniform);
		Buffer::TypedMap<GLubyte>(
			Buffer::Target::Uniform,
			BufferMapAccess::Write
		).At(BitmapGlyphPageOfCP(_parent, cp)) = frame;
	}
};

} // namespace text
} // namespace oglplus

#endif // include guard
