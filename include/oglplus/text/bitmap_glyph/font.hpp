/**
 *  @file oglplus/text/bitmap_glyph/font.hpp
 *  @brief Bitmap-font-based text rendering, font class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_FONT_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_FONT_HPP

#include <oglplus/config.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>
#include <oglplus/auxiliary/filesystem.hpp>

namespace oglplus {
namespace text {

class BitmapGlyphFont
{
private:
	BitmapGlyphRendering& _parent;
	const std::string _name;

	std::string _make_path(unsigned page)
	{
		std::string dirsep = oglplus::aux::FilesysPathSep();
		return BitmapGlyphFontDirPath(_parent)+
			dirsep+
			_name+
			dirsep+
			BitmapGlyphPageName(_parent, page);
	}
public:
	BitmapGlyphFont(
		BitmapGlyphRendering& parent,
		const std::string& name
	): _parent(parent)
	 , _name(name)
	{ }
};

} // namespace text
} // namespace oglplus

#endif // include guard
