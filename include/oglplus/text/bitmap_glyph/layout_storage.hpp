/**
 *  @file oglplus/text/bitmap_glyph/layout_storage.hpp
 *  @brief Bitmap-font-based text rendering, attribute storage for static layouts
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_LAYOUT_STORAGE_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_LAYOUT_STORAGE_HPP

#include <oglplus/config.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>

#include <vector>
#include <map>

namespace oglplus {
namespace text {

struct BitmapGlyphLayoutData
{
	GLint _offset;
	GLsizei _count;

	BitmapGlyphLayoutData(GLsizei count)
	 : _offset(-1)
	 , _count(count)
	{ }
};

// Manages the codepoints for layouts that remain static
class BitmapGlyphStaticLayoutStorage
{
private:
	BitmapGlyphRendering& _parent;
	GLint _offset;
	GLsizei _count;
	Buffer _code_points;

	BitmapGlyphStaticLayoutStorage(const BitmapGlyphStaticLayoutStorage&);
public:
	BitmapGlyphStaticLayoutStorage(
		BitmapGlyphRendering& parent,
		GLsizei capacity
	): _parent(parent)
	 , _offset(0)
	 , _count(capacity)
	{
		_code_points.Bind(Buffer::Target::Array);
		Buffer::Data(Buffer::Target::Array, _count, (GLuint*)nullptr);
	}

	BitmapGlyphStaticLayoutStorage(BitmapGlyphStaticLayoutStorage&& tmp)
	 : _parent(tmp._parent)
	 , _offset(tmp._offset)
	 , _count(tmp._count)
	 , _code_points(std::move(tmp._code_points))
	{ }

	bool Allocate(BitmapGlyphLayoutData& layout_data)
	{
		if(layout_data._count > _count) return false;
		layout_data._offset = _offset;
		_offset += layout_data._count;
		_count  -= layout_data._count;
		return true;
	}

	void Initialize(
		BitmapGlyphLayoutData& layout_data,
		const CodePoint* cps,
		GLsizei length
	)
	{
		assert(layout_data._count >= length);
		std::vector<GLuint> sub_data(cps, cps+length);
		Buffer::SubData(
			Buffer::Target::Array,
			layout_data._offset,
			sub_data.size(),
			sub_data.data()
		);
	}

	void Deallocate(BitmapGlyphLayoutData& layout_data)
	{
		// TODO
		OGLPLUS_FAKE_USE(layout_data);
	}

	void BindCodePoints(void)
	{
		_code_points.Bind(Buffer::Target::Array);
	}
};


} // namespace text
} // namespace oglplus

#endif // include guard
