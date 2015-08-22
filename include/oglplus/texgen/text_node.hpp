/**
 *  @file oglplus/texgen/text_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_TEXT_NODE_HPP
#define OGLPLUS_TEXGEN_TEXT_NODE_HPP

#include <oglplus/texgen/texture_node.hpp>
#include <oglplus/text/font2d.hpp>
#include <vector>
#include <iosfwd>

namespace oglplus {
namespace texgen {

class Text2DNode
 : public TextureNode
{
private:
	static
	Texture _make(TextureUnitSelector, std::size_t, std::size_t);

	std::size_t _width, _height;
	std::vector<GLubyte> _buffer;
public:
	Text2DNode(TextureUnitSelector, std::size_t width, std::size_t height);

	typedef oglplus::text::Font2D Font;

	Font OpenFont(std::istream&);
	Font OpenFont(const char* font_path);

	void Begin(GLubyte = 0x00);
	void RenderText(Font&, std::size_t font_size, const char*, int x, int y);
	void Finish(TextureUnitSelector);
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/text_node.ipp>
//#endif

#endif // include guard
