/**
 *  .file lib/oglplus/text.cpp
 *  .brief Text rendering utility functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "prologue.ipp"
#if !OGLPLUS_NO_VARIADIC_TEMPLATES
#include <oglplus/text/unicode.hpp>
#endif //OGLPLUS_NO_VARIADIC_TEMPLATES
#include <oglplus/text/bitmap_glyph.hpp>
#include <oglplus/text/stb_truetype.hpp>
#if OGLPLUS_PANGO_CAIRO_FOUND
#include <oglplus/text/pango_cairo.hpp>
#endif

#include "epilogue.ipp"
