/**
 *  @file oglplus/texgen/random_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <vector>
#include <random>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
Texture
Random2DRedNode::
_make(TextureUnitSelector texunit, TextureTarget target, GLsizei width, GLsizei height)
{
	assert(width > 0);
	assert(height> 0);

	std::random_device rd;
	std::default_random_engine rr(rd());
	std::uniform_real_distribution<GLfloat> ure(0, 1);

	std::size_t n = std::size_t(width*height);
	std::vector<GLfloat> tex_data(n);
	for(std::size_t i=0; i<n; ++i)
	{
		tex_data[i] = ure(rr);
	}

	Texture tex;
	Texture::Active(texunit);
	tex.Bind(target);
	Texture::Filter(target, TextureFilter::Nearest);
	Texture::WrapS(target, TextureWrap::Repeat);
	Texture::WrapT(target, TextureWrap::Repeat);
	Texture::Image2D(
		target, 0,
		PixelDataInternalFormat::Red,
		width, height, 0,
		PixelDataFormat::Red,
		PixelDataType::Float,
		tex_data.data()
	);
	return std::move(tex);
}

OGLPLUS_LIB_FUNC
Random2DRedNode::
Random2DRedNode(TextureUnitSelector texunit, GLsizei width, GLsizei height)
 : TextureNode(
	_make(texunit, TextureTarget::_2D, width, height),
	TextureTarget::_2D,
	PixelDataFormat::Red
)
{ }

OGLPLUS_LIB_FUNC
Texture
Random2DRGNode::
_make(TextureUnitSelector texunit, TextureTarget target, GLsizei width, GLsizei height)
{
	assert(width > 0);
	assert(height> 0);

	std::random_device rd;
	std::default_random_engine rr(rd());
	std::default_random_engine rg(rd());
	std::uniform_real_distribution<GLfloat> ure(0, 1);

	std::size_t n = std::size_t(width*height);
	std::vector<GLfloat> tex_data(n*2);
	for(std::size_t i=0; i<n; ++i)
	{
		tex_data[i*2+0] = ure(rr);
		tex_data[i*2+1] = ure(rg);
	}

	Texture tex;
	Texture::Active(texunit);
	tex.Bind(target);
	Texture::Filter(target, TextureFilter::Nearest);
	Texture::WrapS(target, TextureWrap::Repeat);
	Texture::WrapT(target, TextureWrap::Repeat);
	Texture::Image2D(
		target, 0,
		PixelDataInternalFormat::RG,
		width, height, 0,
		PixelDataFormat::RG,
		PixelDataType::Float,
		tex_data.data()
	);
	return std::move(tex);
}

OGLPLUS_LIB_FUNC
Random2DRGNode::
Random2DRGNode(TextureUnitSelector texunit, GLsizei width, GLsizei height)
 : TextureNode(
	_make(texunit, TextureTarget::_2D, width, height),
	TextureTarget::_2D,
	PixelDataFormat::RG
)
{ }

OGLPLUS_LIB_FUNC
Texture
Random2DRGBNode::
_make(TextureUnitSelector texunit, TextureTarget target, GLsizei width, GLsizei height)
{
	assert(width > 0);
	assert(height> 0);

	std::random_device rd;
	std::default_random_engine rr(rd());
	std::default_random_engine rg(rd());
	std::default_random_engine rb(rd());
	std::uniform_real_distribution<GLfloat> ure(0, 1);

	std::size_t n = std::size_t(width*height);
	std::vector<GLfloat> tex_data(n*3);
	for(std::size_t i=0; i<n; ++i)
	{
		tex_data[i*3+0] = ure(rr);
		tex_data[i*3+1] = ure(rg);
		tex_data[i*3+2] = ure(rb);
	}

	Texture tex;
	Texture::Active(texunit);
	tex.Bind(target);
	Texture::Filter(target, TextureFilter::Nearest);
	Texture::WrapS(target, TextureWrap::Repeat);
	Texture::WrapT(target, TextureWrap::Repeat);
	Texture::Image2D(
		target, 0,
		PixelDataInternalFormat::RGB,
		width, height, 0,
		PixelDataFormat::RGB,
		PixelDataType::Float,
		tex_data.data()
	);
	return std::move(tex);
}

OGLPLUS_LIB_FUNC
Random2DRGBNode::
Random2DRGBNode(TextureUnitSelector texunit, GLsizei width, GLsizei height)
 : TextureNode(
	_make(texunit, TextureTarget::_2D, width, height),
	TextureTarget::_2D,
	PixelDataFormat::RGB
)
{ }

OGLPLUS_LIB_FUNC
Texture
Random2DRGBANode::
_make(TextureUnitSelector texunit, TextureTarget target, GLsizei width, GLsizei height)
{
	assert(width > 0);
	assert(height> 0);

	std::random_device rd;
	std::default_random_engine rr(rd());
	std::default_random_engine rg(rd());
	std::default_random_engine rb(rd());
	std::default_random_engine ra(rd());
	std::uniform_real_distribution<GLfloat> ure(0, 1);

	std::size_t n = std::size_t(width*height);
	std::vector<GLfloat> tex_data(n*4);
	for(std::size_t i=0; i<n; ++i)
	{
		tex_data[i*4+0] = ure(rr);
		tex_data[i*4+1] = ure(rg);
		tex_data[i*4+2] = ure(rb);
		tex_data[i*4+3] = ure(ra);
	}

	Texture tex;
	Texture::Active(texunit);
	tex.Bind(target);
	Texture::Filter(target, TextureFilter::Nearest);
	Texture::WrapS(target, TextureWrap::Repeat);
	Texture::WrapT(target, TextureWrap::Repeat);
	Texture::Image2D(
		target, 0,
		PixelDataInternalFormat::RGBA,
		width, height, 0,
		PixelDataFormat::RGBA,
		PixelDataType::Float,
		tex_data.data()
	);
	return std::move(tex);
}

OGLPLUS_LIB_FUNC
Random2DRGBANode::
Random2DRGBANode(TextureUnitSelector texunit, GLsizei width, GLsizei height)
 : TextureNode(
	_make(texunit, TextureTarget::_2D, width, height),
	TextureTarget::_2D,
	PixelDataFormat::RGBA
)
{ }

} // namespace texgen
} // namespace oglplus

