/**
 *  @file oglplus/text/common.hpp
 *  @brief Common classes and functions used in text rendering
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXT_COMMON_HPP
#define OGLPLUS_TEXT_COMMON_HPP

#include <oglplus/config.hpp>
#include <oglplus/text/unicode.hpp>

namespace oglplus {

/** @defgroup text_rendering Text rendering
 */

/// Namespace containing text rendering utilities
namespace text {

/// Floating-point rectangle used for Glyph and Layout measurements
/**
 *  @ingroup text_rendering
 */
class Rectangle
{
private:
	GLfloat _left, _right, _bottom, _top;
public:
	Rectangle(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
	 : _left(left)
	 , _right(right)
	 , _bottom(bottom)
	 , _top(top)
	{ }

	/// The left edge of the rectangle
	GLfloat Left(void) const { return _left; }

	/// the right edge of the rectangle
	GLfloat Right(void) const { return _right; }

	/// the bottom edge of the rectangle
	GLfloat Bottom(void) const { return _bottom; }

	/// the top edge of the rectangle
	GLfloat Top(void) const { return _top; }

	/// The width of the rectangle
	GLfloat Width(void) const {return Right() - Left(); }

	/// The height of the rectangle
	GLfloat Height(void) const {return Top() - Bottom(); }
};

#if OGLPLUS_DOCUMENTATION_ONLY

// TODO: docs

class Font
{
public:
	GLfloat PixelsPerUnit(void) const;
	void Preload(CodePoint code_point);
	void Preload(const char* str);
};

class Layout
{
public:
	Rectangle LogicalMetrics(void);
};

class LayoutTransform
{
public:
};

class GlyphTransform
{
public:
};

class Renderer
{
public:
	void Render(
		const Layout& layout,
		LayoutTransform layout_transform,
		GlyphTransform glyph_transform
	);
};

class Rendering
{
public:
	Font LoadFont(const char* font_name);

	Renderer MakeRenderer(void);

	Layout MakeLayout(const char* str);
};

#endif

} // namespace text
} // namespace oglplus

#endif // include guard
