/**
 *  @file oglplus/text/bitmap_glyph/page_storage.hpp
 *  @brief Bitmap-font-based text rendering, glyph page storage
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_BITMAP_GLYPH_PAGE_STORAGE_HPP
#define OGLPLUS_TEXT_BITMAP_GLYPH_PAGE_STORAGE_HPP

#include <oglplus/config.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/image.hpp>
#include <oglplus/text/common.hpp>
#include <oglplus/text/unicode.hpp>
#include <oglplus/text/bitmap_glyph/fwd.hpp>

#include <vector>

namespace oglplus {
namespace text {

// Stores the active glyph pages
// 1) the bitmap image
// 2) the metric values
class BitmapGlyphPageStorage
{
private:
	BitmapGlyphRenderingBase& _parent;

	TextureUnitSelector _bitmap_tex_unit;
	TextureUnitSelector _metric_tex_unit;

	const PixelDataInternalFormat _internal_format;
	const GLsizei _width;
	const GLsizei _height;
	const GLsizei _frames;

	Texture _bitmap_storage;
	Texture _metric_storage;

	const size_t _glyphs_per_page;
	const size_t _vects_per_glyph;

	std::vector<std::vector<GLfloat>> _metrics;
public:
	BitmapGlyphPageStorage(
		BitmapGlyphRenderingBase& parent,
		TextureUnitSelector bitmap_tex_unit,
		TextureUnitSelector metric_tex_unit,
		const GLint init_frame,
		const GLsizei frames,
		const oglplus::images::Image& image,
		const std::vector<GLfloat>& metrics
	);

	TextureUnitSelector BitmapTexUnit(void) const
	{
		return _bitmap_tex_unit;
	}

	TextureUnitSelector MetricTexUnit(void) const
	{
		return _metric_tex_unit;
	}

	void Bind(void) const
	{
		Texture::Active(_bitmap_tex_unit);
		_bitmap_storage.Bind(Texture::Target::_2DArray);
		Texture::Active(_metric_tex_unit);
		_metric_storage.Bind(Texture::Target::Rectangle);
	}

	void LoadPage(
		const GLint frame,
		const oglplus::images::Image& image,
		const std::vector<GLfloat>& metrics
	);

	void QueryGlyphMetrics(
		GLint frame,
		GLint cell,
		GLint metric,
		GLint count,
		GLfloat* result
	) const;

	GLfloat GetGlyphMetric(GLint frame, GLint cell, GLint metric) const
	{
		return _metrics[frame][4*_vects_per_glyph*cell+metric];
	}

	GLfloat GetGlyphWidth(GLint frame, GLint offset) const
	{
		return	GetGlyphMetric(frame, offset, 1)-
			GetGlyphMetric(frame, offset, 0);
	}
};

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
OGLPLUS_LIB_FUNC
BitmapGlyphPageStorage::BitmapGlyphPageStorage(
	BitmapGlyphRenderingBase& parent,
	TextureUnitSelector bitmap_tex_unit,
	TextureUnitSelector metric_tex_unit,
	const GLint init_frame,
	const GLsizei frames,
	const oglplus::images::Image& image,
	const std::vector<GLfloat>& metrics
): _parent(parent)
 , _bitmap_tex_unit(bitmap_tex_unit)
 , _metric_tex_unit(metric_tex_unit)
 , _internal_format(image.InternalFormat())
 , _width(image.Width())
 , _height(image.Height())
 , _frames(frames)
 , _glyphs_per_page(BitmapGlyphGlyphsPerPage(parent))
 , _vects_per_glyph(3)
 , _metrics(_frames)
{
	//
	// setup the bitmap texture
	// TODO: replace with Texture::Storage3D
	Texture::Active(_bitmap_tex_unit);
	_bitmap_storage.Bind(Texture::Target::_2DArray);
	Texture::Image3D(
		Texture::Target::_2DArray,
		0,
		_internal_format,
		_width,
		_height,
		_frames,
		0,
		image.Format(),
		image.Type(),
		nullptr
	);
	Texture::MinFilter(
		Texture::Target::_2DArray,
		TextureMinFilter::LinearMipmapLinear
	);
	Texture::MagFilter(
		Texture::Target::_2DArray,
		TextureMagFilter::Linear
	);
	Texture::WrapS(
		Texture::Target::_2DArray,
		TextureWrap::ClampToBorder
	);
	Texture::WrapT(
		Texture::Target::_2DArray,
		TextureWrap::ClampToBorder
	);
	//
	// setup the metric texture
	//
	// TODO: replace with Texture::Storage2D
	Texture::Active(_metric_tex_unit);
	_metric_storage.Bind(Texture::Target::Rectangle);
	Texture::Image2D(
		Texture::Target::Rectangle,
		0,
		PixelDataInternalFormat::RGBA32F,
		_glyphs_per_page*_vects_per_glyph,
		_frames,
		0,
		PixelDataFormat::RGBA,
		PixelDataType::Float,
		nullptr
	);
	Texture::MinFilter(
		Texture::Target::Rectangle,
		TextureMinFilter::Nearest
	);
	Texture::MagFilter(
		Texture::Target::Rectangle,
		TextureMagFilter::Nearest
	);
	// load the initial data
	LoadPage(init_frame, image, metrics);
}

OGLPLUS_LIB_FUNC
void BitmapGlyphPageStorage::LoadPage(
	const GLint frame,
	const oglplus::images::Image& image,
	const std::vector<GLfloat>& metrics
)
{
	// TODO add a parameter indicating how many rows
	// of the image are really used and add InvalidateTexImage
	assert(image.Width() == _width);
	assert(image.Height() == _height);
	// load the bitmap image
	Texture::Active(_bitmap_tex_unit);
	Texture::SubImage3D(
		Texture::Target::_2DArray,
		0,
		0, 0, frame,
		_width,
		_height,
		1,
		image.Format(),
		image.Type(),
		image.RawData()
	);
	//
	Texture::GenerateMipmap(Texture::Target::_2DArray);

	// load the metric values
	Texture::Active(_metric_tex_unit);
	Texture::SubImage2D(
		Texture::Target::Rectangle,
		0,
		0, frame,
		_glyphs_per_page*_vects_per_glyph, 1,
		PixelDataFormat::RGBA,
		PixelDataType::Float,
		metrics.data()
	);
	_metrics[frame] = metrics;
}

OGLPLUS_LIB_FUNC
void BitmapGlyphPageStorage::QueryGlyphMetrics(
	GLint frame,
	GLint cell,
	GLint metric,
	GLint count,
	GLfloat* result
) const
{
	const std::vector<GLfloat>& frame_data = _metrics[frame];
	const GLint offs = 4*_vects_per_glyph*cell+metric;

	assert(count >= 0);
	for(GLint i=0; i!=count; ++i)
		result[i] = frame_data[offs+i];
}
#endif // OGLPLUS_LINK_LIBRARY

} // namespace text
} // namespace oglplus

#endif // include guard
