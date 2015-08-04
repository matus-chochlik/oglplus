/**
 *  @file oglplus/texgen/random_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_RANDOM_NODE_HPP
#define OGLPLUS_TEXGEN_RANDOM_NODE_HPP

#include <oglplus/texgen/texture_node.hpp>

namespace oglplus {
namespace texgen {

class Random2DRedNode
 : public TextureNode
{
private:
	static Texture _make(TextureUnitSelector, GLsizei, GLsizei);
public:
	Random2DRedNode(TextureUnitSelector, GLsizei width, GLsizei height);
};

class Random2DRGNode
 : public TextureNode
{
private:
	static Texture _make(TextureUnitSelector, GLsizei, GLsizei);
public:
	Random2DRGNode(TextureUnitSelector, GLsizei width, GLsizei height);
};

class Random2DRGBNode
 : public TextureNode
{
private:
	static Texture _make(TextureUnitSelector, GLsizei, GLsizei);
public:
	Random2DRGBNode(TextureUnitSelector, GLsizei width, GLsizei height);
};

class Random2DRGBANode
 : public TextureNode
{
private:
	static Texture _make(TextureUnitSelector, GLsizei, GLsizei);
public:
	Random2DRGBANode(TextureUnitSelector, GLsizei width, GLsizei height);
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/random_node.ipp>
//#endif

#endif // include guard
