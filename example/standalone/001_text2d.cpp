/**
 *  @example standalone/001_text2d.cpp
 *  @brief Shows the basic usage of low-level 2D text rendering
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#include <cassert>
#include <iostream>

#include <oglplus/opt/resources.hpp>
#include <oglplus/text/font2d.hpp>

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	oglplus::ResourceFile font_file("fonts", (argc>1)?argv[1]:"FreeSans", ".ttf");
	oglplus::text::Font2D font(font_file);

	oglplus::text::CodePoints code_points = oglplus::text::UTF8ToCodePoints(u8"OGLplus");
	oglplus::text::Font2D::Layout layout = font.MakeLayout(code_points);

	std::size_t width = 90;
	std::size_t height = 26;
	std::size_t font_size = 25;
	std::vector<unsigned char> buffer(width*height, 0x00);

	font.Render(font_size, layout, buffer.data(), width, height);

	for(std::size_t j=0; j!=height; ++j)
	{
		for(std::size_t i=0; i!=width; ++i)
		{
			std::cout << " .:ioVM@"[buffer[j*width+i]>>5];
		}
		std::cout << std::endl;
	}
	return 0;
}
