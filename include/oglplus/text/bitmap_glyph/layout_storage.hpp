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
#include <oglplus/text/bitmap_glyph/font.hpp>

#include <vector>
#include <map>

namespace oglplus {
namespace text {

struct BitmapGlyphLayoutData
{
	GLint _offset;
	GLsizei _length;
	GLsizei _capacity;
	const BitmapGlyphStaticLayoutStorage* _storage;

	BitmapGlyphLayoutData(GLsizei capacity)
	 : _offset(-1)
	 , _length(0)
	 , _capacity(capacity)
	 , _storage(nullptr)
	{ }
};

// Manages the codepoints for layouts that remain static
class BitmapGlyphStaticLayoutStorage
{
private:
	BitmapGlyphRendering& _parent;
	GLint _offset;
	GLsizei _capacity;

	VertexArray _vao;
	Buffer _code_points, _x_offsets;

	BitmapGlyphStaticLayoutStorage(const BitmapGlyphStaticLayoutStorage&);
public:
	BitmapGlyphStaticLayoutStorage(
		BitmapGlyphRendering& parent,
		GLsizei capacity
	): _parent(parent)
	 , _offset(0)
	 , _capacity(capacity)
	{
		_vao.Bind();
		{
			_code_points.Bind(Buffer::Target::Array);
			Buffer::Data(
				Buffer::Target::Array,
				_capacity,
				(GLuint*)nullptr
			);

			VertexAttribSlot location(0);
			VertexAttribArray attr(location);
			attr.Pointer(1, GetDataType<GLuint>(), 0, nullptr);
			attr.Enable();
		}
		{
			_x_offsets.Bind(Buffer::Target::Array);
			Buffer::Data(
				Buffer::Target::Array,
				_capacity,
				(GLfloat*)nullptr
			);

			VertexAttribSlot location(1);
			VertexAttribArray attr(location);
			attr.Pointer(1, GetDataType<GLfloat>(), false, 0, nullptr);
			attr.Enable();
		}

		VertexArray::Unbind();
	}

	BitmapGlyphStaticLayoutStorage(BitmapGlyphStaticLayoutStorage&& tmp)
	 : _parent(tmp._parent)
	 , _offset(tmp._offset)
	 , _capacity(tmp._capacity)
	 , _vao(std::move(tmp._vao))
	 , _code_points(std::move(tmp._code_points))
	{ }

	void Use(void) const
	{
		_vao.Bind();
	}

	bool Allocate(BitmapGlyphLayoutData& layout_data)
	{
		if(layout_data._capacity > _capacity) return false;
		layout_data._offset = _offset;
		layout_data._storage = this;
		_offset += layout_data._capacity;
		_capacity  -= layout_data._capacity;
		return true;
	}

	void Initialize(
		BitmapGlyphLayoutData& layout_data,
		BitmapGlyphFont& font,
		const CodePoint* cps,
		GLsizei length
	)
	{
		assert(layout_data._capacity >= length);

		// set the length
		layout_data._length = length;
		// upload the code points
		std::vector<GLuint> code_points(cps, cps+length);
		_code_points.Bind(Buffer::Target::Array);
		Buffer::SubData(
			Buffer::Target::Array,
			layout_data._offset,
			code_points.size(),
			code_points.data()
		);
		// upload the x-offsets
		std::vector<GLfloat> x_offsets;
		font.QueryXOffsets(cps, length, x_offsets);
		_x_offsets.Bind(Buffer::Target::Array);
		Buffer::SubData(
			Buffer::Target::Array,
			layout_data._offset,
			x_offsets.size(),
			x_offsets.data()
		);
	}

	void Deallocate(BitmapGlyphLayoutData& layout_data)
	{
		// TODO
		layout_data._storage = nullptr;
	}
};


} // namespace text
} // namespace oglplus

#endif // include guard
