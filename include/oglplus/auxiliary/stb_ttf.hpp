/**
 *  .file oglplus/auxiliary/stb_ttf.hpp
 *  .brief Helper wrapper around the Sean Barrett's truetype rendering lib.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2011-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef __OGLPLUS_AUX_STB_TTF_1102101236_HPP
#define __OGLPLUS_AUX_STB_TTF_1102101236_HPP

#include <oglplus/config.hpp>

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#define STB_TRUETYPE_IMPLEMENTATION
#endif
#include <stb_truetype.h>

#include <istream>
#include <stdexcept>

namespace oglplus {
namespace aux {

class STBTTFont;

class STBTTFontGlyph
{
private:
	friend class STBTTFont;

	const ::stbtt_fontinfo* _font;
	int _code_point;
	int _index;

	STBTTFontGlyph(
		const ::stbtt_fontinfo& font,
		int code_point
	): _font(&font)
	 , _code_point(code_point)
	 , _index(::stbtt_FindGlyphIndex(_font, _code_point))
	{ }
public:
	void GetHMetrics(int& left_bearing, int& width) const
	{
		::stbtt_GetGlyphHMetrics(_font, _index, &width, &left_bearing);
	}

	void GetVMetrics(int& ascent, int& descent, int& line_gap) const
	{
		::stbtt_GetFontVMetrics(_font, &ascent, &descent, &line_gap);
	}

	void GetBitmapBox(int& x0, int& y0, int& x1, int& y1) const
	{
		::stbtt_GetGlyphBitmapBox(_font, _index, 1,1, &x0,&y0,&x1,&y1);
	}

	int LeftBearing(void) const
	{
		int result = 0;
		::stbtt_GetGlyphHMetrics(_font, _index, nullptr, &result);
		return result;
	}

	int RightBearing(void) const
	{
		int w = 0, lb = 0;
		::stbtt_GetGlyphHMetrics(_font, _index, &w, &lb);
		return lb + w;
	}

	int Width(void) const
	{
		int result = 0;
		::stbtt_GetGlyphHMetrics(_font, _index, &result, nullptr);
		return result;
	}

	int Ascent(void) const
	{
		int result = 0;
		::stbtt_GetFontVMetrics(_font, &result, nullptr, nullptr);
		return result;
	}

	int Descent(void) const
	{
		int result = 0;
		::stbtt_GetFontVMetrics(_font, nullptr, &result, nullptr);
		return result;
	}

	int Height(void) const
	{
		int asc = 0, dsc = 0;
		::stbtt_GetFontVMetrics(_font, &asc, &dsc, nullptr);
		return asc - dsc;
	}

	int LineGap(void) const
	{
		int result = 0;
		::stbtt_GetFontVMetrics(_font, nullptr, nullptr, &result);
		return result;
	}

	void MakeBitmap(
		unsigned char* start,
		int glyph_width,
		int glyph_height,
		int stride,
		float scale
	) const
	{
		::stbtt_MakeGlyphBitmap(
			_font,
			start,
			glyph_width,
			glyph_height,
			stride,
			scale,
			scale,
			_index
		);
	}

	friend int KernAdvance(
		const STBTTFontGlyph& glyph1,
		const STBTTFontGlyph& glyph2
	)
	{
		assert(glyph1._font == glyph2._font);
		return ::stbtt_GetCodepointKernAdvance(
			glyph1._font,
			glyph1._index,
			glyph2._index
		);
	}
};


class STBTTFont
{
private:
	std::vector<unsigned char> _ttf_data;

	static std::vector<unsigned char> _load_ttf(std::istream& input)
	{
		if(!input.good())
		{
			throw std::runtime_error("Error reading TTF input");
		}
		input.seekg(0, std::ios_base::end);
		std::streampos size = input.tellg();
		input.seekg(0, std::ios_base::beg);
		std::vector<unsigned char> result(size, 0x00);
		if(input.read((char*)result.data(), size).gcount() != size)
		{
			throw std::runtime_error("Error reading TTF input");
		}
		return std::move(result);
	}

	::stbtt_fontinfo _font;

	void _load_font(const unsigned char* ttf_buffer)
	{
		if(!::stbtt_InitFont(
			&_font,
			ttf_buffer,
			::stbtt_GetFontOffsetForIndex(ttf_buffer, 0)
		)) throw std::runtime_error("Error loading true type font");
	}
public:
	STBTTFont(std::istream&& input)
	 : _ttf_data(_load_ttf(input))
	{
		_load_font(_ttf_data.data());
	}

	STBTTFont(std::istream& input)
	 : _ttf_data(_load_ttf(input))
	{
		_load_font(_ttf_data.data());
	}

	STBTTFont(std::vector<unsigned char>&& ttf_data)
	 : _ttf_data(std::move(ttf_data))
	{
		_load_font(_ttf_data.data());
	}

	STBTTFontGlyph GetGlyph(int code_point) const
	{
		return STBTTFontGlyph(_font, code_point);
	}

	float ScaleForPixelHeight(float pixels) const
	{
		return ::stbtt_ScaleForPixelHeight(&_font, pixels);
	}

};

} // namespace aux
} // namespace oglplus

#endif
