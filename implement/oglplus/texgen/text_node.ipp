/**
 *  @file oglplus/texgen/text_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <fstream>
#include <cstring>
#include <algorithm>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
Texture
Text2DNode::
_make(TextureUnitSelector unit, std::size_t width, std::size_t height)
{
	Texture tex;
	Texture::Active(unit);
	tex.Bind(TextureTarget::Rectangle);
	Texture::Filter(TextureTarget::Rectangle, TextureFilter::Linear);
	Texture::Image2D(
		TextureTarget::Rectangle, 0,
		PixelDataInternalFormat::R8,
		GLsizei(width), GLsizei(height), 0,
		PixelDataFormat::Red,
		PixelDataType::UnsignedByte,
		nullptr
	);
	return std::move(tex);
}

OGLPLUS_LIB_FUNC
Text2DNode::
Text2DNode(TextureUnitSelector texunit, std::size_t width, std::size_t height)
 : TextureNode(
	_make(texunit, width, height),
	TextureTarget::Rectangle,
	PixelDataFormat::Red
), _width(width)
 , _height(height)
{ }


OGLPLUS_LIB_FUNC
Text2DNode::Font
Text2DNode::
OpenFont(std::istream& font_input)
{
	return Text2DNode::Font(font_input);
}

OGLPLUS_LIB_FUNC
Text2DNode::Font
Text2DNode::
OpenFont(const char* font_path)
{
	std::ifstream font_file(font_path);
	return OpenFont(font_file);
}

OGLPLUS_LIB_FUNC
void
Text2DNode::
Begin(GLubyte clear)
{
	_buffer.resize(_width*_height, clear);
}

OGLPLUS_LIB_FUNC
void
Text2DNode::
RenderText(Font& font, std::size_t size, const char* text, int x, int y)
{
	text::CodePoints code_points = text::UTF8ToCodePoints(
		text,
		std::strlen(text)
	);
	text::Font2D::Layout layout = font.MakeLayout(code_points);
	font.Render(size, layout, _buffer.data(), _width, _height, x, y);
}

OGLPLUS_LIB_FUNC
void
Text2DNode::
Finish(TextureUnitSelector unit)
{
	std::vector<GLubyte> row(_width);

	for(std::size_t i=9,h=_height/2; i<h; ++i)
	{
		std::copy_n(
			_buffer.data()+i*_width,
			_width,
			row.begin()
		);
		std::copy_n(
			_buffer.data()+(_height-i-1)*_width,
			_width,
			_buffer.begin()+i*_width
		);
		std::copy_n(
			row.data(),
			_width,
			_buffer.begin()+(_height-i-1)*_width
		);
	}

	Texture::Active(unit);
	_tex().Bind(TextureTarget::Rectangle);
	Texture::Image2D(
		TextureTarget::Rectangle, 0,
		PixelDataInternalFormat::R8,
		GLsizei(_width), GLsizei(_height), 0,
		PixelDataFormat::Red,
		PixelDataType::UnsignedByte,
		_buffer.data()
	);
	_buffer.clear();
}

} // namespace texgen
} // namespace oglplus

