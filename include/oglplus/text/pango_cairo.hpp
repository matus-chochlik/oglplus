/**
 *  @file oglplus/text/pango_cairo.hpp
 *  @brief Pango/Cairo-based text rendering.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_PANGO_CAIRO_HPP
#define OGLPLUS_TEXT_PANGO_CAIRO_HPP

#include <oglplus/text/pango_cairo/font.hpp>
#include <oglplus/text/pango_cairo/layout.hpp>
#include <oglplus/text/pango_cairo/renderer.hpp>

#include <oglplus/texture.hpp>

#include <vector>
#include <cassert>

namespace oglplus {
namespace text {

class PangoCairoRendering
{
private:
	TextureUnitSelector _main_tex_unit;

	friend void PangoCairoAllocateLayoutData(
		PangoCairoRendering& that,
		PangoCairoLayoutData& layout_data,
		GLsizei width,
		GLsizei height
	)
	{
		// TODO: some smarter form of allocation
		// or use bindless textures where available
		Texture::Active(that._main_tex_unit);
		layout_data._storage.Bind(Texture::Target::Rectangle);
		Texture::Image2D(
			Texture::Target::Rectangle,
			0,
			PixelDataInternalFormat::Red,
			width,
			height,
			0,
			PixelDataFormat::Red,
			PixelDataType::UnsignedByte,
			nullptr
		);
	}

	friend void PangoCairoDeallocateLayoutData(
		PangoCairoRendering&,
		PangoCairoLayoutData&
	)
	{
	}

	friend void PangoCairoInitializeLayoutData(
		PangoCairoRendering& that,
		PangoCairoLayoutData& layout_data,
		GLsizei width,
		GLsizei height,
		const void* raw_data
	)
	{
		Texture::Active(that._main_tex_unit);
		layout_data._storage.Bind(Texture::Target::Rectangle);
		Texture::SubImage2D(
			Texture::Target::Rectangle,
			0,
			0, 0,
			width,
			height,
			PixelDataFormat::Red,
			PixelDataType::UnsignedByte,
			raw_data
		);
	}

	friend TextureUnitSelector PangoCairoUseLayoutData(
		PangoCairoRendering& that,
		const PangoCairoLayoutData& layout_data
	)
	{
		Texture::Active(that._main_tex_unit);
		layout_data._storage.Bind(Texture::Target::Rectangle);
		return that._main_tex_unit;
	}
public:
	PangoCairoRendering(TextureUnitSelector main_tex_unit)
	 : _main_tex_unit(main_tex_unit)
	{ }

	typedef PangoCairoFont Font;

	Font LoadFont(const char* font_name)
	{
		return Font(font_name);
	}

	typedef PangoCairoLayout Layout;

	Layout MakeLayout(const Font& font, GLsizei capacity)
	{
		return Layout(*this, font, capacity);
	}

	Layout MakeLayout(
		const Font& font,
		const GLchar* c_str,
		std::size_t size
	)
	{
		CodePoints cps;
		UTF8ToCodePoints(c_str, size, cps);

		Layout layout(MakeLayout(font, size));
		layout.Set(cps.data(), cps.size());
		return std::move(layout);
	}

	Layout MakeLayout(const Font& font, const StrLit& lit)
	{
		return MakeLayout(font, lit.c_str(), lit.size());
	}

	Layout MakeLayout(const Font& font, const String& str)
	{
		return MakeLayout(font, str.c_str(), str.size());
	}

	typedef PangoCairoDefaultRenderer Renderer;

	Renderer GetRenderer(const FragmentShader& fragment_shader)
	{
		return Renderer(*this, fragment_shader);
	}
};

} // namespace text
} // namespace oglplus

#endif // include guard
