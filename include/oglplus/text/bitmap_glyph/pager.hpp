/**
 *  @file oglplus/text/bitmap_glyph/pager.hpp
 *  @brief Bitmap-font-based text rendering, page swapping
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_PAGER_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_PAGER_HPP

#include <oglplus/config.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/text/unicode.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>

#include <vector>
#include <unordered_map>
#include <cassert>

namespace oglplus {
namespace text {

class BitmapGlyphPager
{
private:
	// reference to the parent rendering system
	BitmapGlyphRendering& _parent;

	// the frames into which pages are loaded
	std::vector<GLint> _frames;

	// basic logical consistency check
	bool _is_ok(void) const
	{
		return (_frames.size() == _ages.size()) &&
			(_active_pages.size() <= _frames.size());
	}

	// checks if the values in _frames and _gpu_page_map
	// are consistent
	bool _frames_consistent(void) const
	{
		_gpu_page_map.Bind(Buffer::Target::Uniform);
		Buffer::TypedMap<gpu_frame_t> page_frame_map(
			Buffer::Target::Uniform,
			BufferMapAccess::Read
		);
		const std::size_t n = _frames.size();
		for(std::size_t i=0; i!=n; ++i)
		{
			GLint page = _frames[i];
			if(page >= 0)
			{
				for(std::size_t j=0; j!=i; ++j)
					if(page == _frames[j])
						return false;
				gpu_frame_t frame = page_frame_map.At(page);
				if(frame != gpu_frame_t(i))
					return false;
			}
		}
		return true;
	}

	// checks if the specified page is in _frames
	bool _page_in_frames(GLint page) const
	{
		for(auto i=_frames.begin(), e=_frames.end(); i!=e; ++i)
			if(*i == page) return true;
		return false;
	}

	typedef unsigned long age_t;

	static OGLPLUS_CONSTEXPR age_t _zero_age(void)
	{
		return age_t(0);
	}

	static OGLPLUS_CONSTEXPR age_t _full_age(void)
	{
		return ~_zero_age();
	}

	static OGLPLUS_CONSTEXPR age_t _init_age(void)
	{
		return ~(_full_age() >> 1);
	}

	std::vector<age_t> _ages;

	std::unordered_map<GLint, GLint> _active_pages;

	typedef GLubyte gpu_frame_t;

	static OGLPLUS_CONSTEXPR gpu_frame_t _invalid_gpu_frame(void)
	{
		return ~gpu_frame_t(0);
	}

	// notes frame usage
	void _touch_frame(std::size_t frame)
	{
		_ages[frame] >>= 1;
		_ages[frame] |= _init_age();
	}

	Buffer _gpu_page_map;
	TextureUnitSelector _pg_map_tex_unit;
	Texture _page_map_tex;

	// replaces the page in the specified frame
	// with a new one
	void _replace_page(GLint frame, GLint page)
	{
		assert(!_page_in_frames(page));
		// the previous page in the frame
		GLint previous = _frames[frame];
		// assign the new page to the frame
		_frames[frame] = page;
		// update the age of the other frames
		Update();
		// initialize the age of the frame
		_ages[frame] = _init_age();
		//
		// we'll need to update the page map on gpu
		_gpu_page_map.Bind(Buffer::Target::Uniform);
		Buffer::TypedMap<gpu_frame_t> page_frame_map(
			Buffer::Target::Uniform,
			BufferMapAccess::Write
		);
		if(previous >= 0)
		{
			// remove the previous page from active list
			_active_pages.erase(previous);
			page_frame_map.At(previous) = _invalid_gpu_frame();
			// add the new page into the active list
		}
		_active_pages[page] = frame;
		page_frame_map.At(page) = gpu_frame_t(frame);
	}
public:
	BitmapGlyphPager(
		BitmapGlyphRendering& parent,
		TextureUnitSelector pg_map_tex_unit,
		GLsizei frame_count
	): _parent(parent)
	 , _frames(frame_count, GLint(-1))
	 , _ages(frame_count, _zero_age())
	 , _pg_map_tex_unit(pg_map_tex_unit)
	{
		_gpu_page_map.Bind(Buffer::Target::Uniform);
		std::vector<gpu_frame_t> data(
			BitmapGlyphPlaneCount(_parent)*
			BitmapGlyphPagesPerPlane(_parent),
			_invalid_gpu_frame()
		);
		Buffer::Data(Buffer::Target::Uniform, data);

		Texture::Active(_pg_map_tex_unit);
		_page_map_tex.Bind(Texture::Target::Buffer);
		Texture::Buffer(
			Texture::Target::Buffer,
			PixelDataInternalFormat::R8UI,
			_gpu_page_map
		);

		assert(_is_ok());
	}

	void Bind(void) const
	{
		Texture::Active(_pg_map_tex_unit);
		_page_map_tex.Bind(Texture::Target::Buffer);
	}

	std::size_t FrameCount(void) const
	{
		assert(_is_ok());
		return _frames.size();
	}

	TextureUnitSelector PageMapSampler(void) const
	{
		return _pg_map_tex_unit;
	}

	void Update(void)
	{
		assert(_is_ok());
		for(auto i=_ages.begin(), e=_ages.end(); i!=e; ++i)
			*i >>= 1;
	}

	// finds the best frame for a new page
	GLint FindFrame(void)
	{
		assert(_is_ok());

		const std::size_t n = _frames.size();

		for(std::size_t i=0; i!=n; ++i)
			if(_frames[i] < 0) return GLint(i);

		age_t min = _full_age();
		std::size_t m = 0;
		for(std::size_t i=0; i!=n; ++i)
		{
			if(min > _ages[i])
			{
				min = _ages[i];
				m = i;
			}
		}
		return GLint(m);
	}

	// Checks if a page is available for usage
	bool UsePage(GLint page)
	{
		assert(_is_ok());

		auto pos = _active_pages.find(page);
		// if this is a page miss
		if(pos == _active_pages.end())
		{
			assert(!_page_in_frames(page));
			return false;
		}
		// if this is a page hit
		else
		{
			assert(_page_in_frames(page));
			// note frame usage
			_touch_frame(pos->second);
		}
		return true;
	}

	GLint FrameOfPage(GLint page) const
	{
		auto pos = _active_pages.find(page);
		if(pos != _active_pages.end())
			return pos->second;
		else return GLint(-1);
	}

	// Swaps the specified page into a frame
	// Use only if the page is not already swapped in
	void SwapPageIn(GLint frame, GLint page)
	{
		assert(_is_ok());
		_replace_page(frame, page);
		assert(_frames_consistent());
	}
};

} // namespace text
} // namespace oglplus

#endif // include guard
