/**
 *  @file oglplus/images/png.hpp
 *  @brief PNG image loader (based on libpng)
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_PNG_1107121519_HPP
#define OGLPLUS_IMAGES_PNG_1107121519_HPP

#include <oglplus/images/image.hpp>
#include <oglplus/texture.hpp>

#include <istream>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <png.h>

namespace oglplus {
namespace images {
namespace aux {

class PNGLoader;

struct PNGHeaderValidator
{
	PNGHeaderValidator(std::istream& input);
};

// structure managing the png_struct pointer
struct PNGReadStruct
{
	::png_structp _read;

	// Error handling function
	static void _png_handle_error(::png_structp /*sp*/, const char* msg);

	// Warning handling function
	static void _png_handle_warning(::png_structp/*sp*/, const char* /*msg*/);

	PNGReadStruct(PNGLoader& /*loader*/);
	~PNGReadStruct(void);
};

// structure managing the first png_info pointer
struct PNGReadInfoStruct : PNGReadStruct
{
	::png_infop _info;

	PNGReadInfoStruct(PNGLoader& loader);
	~PNGReadInfoStruct(void);
};

struct PNGReadInfoEndStruct : PNGReadInfoStruct
{
	::png_infop _end;

	// data read callback
	static void _png_read_data(::png_structp, ::png_bytep, ::png_size_t);
	static int _png_read_user_chunk(::png_structp, ::png_unknown_chunkp);

	PNGReadInfoEndStruct(PNGLoader& loader);
	~PNGReadInfoEndStruct(void);
};

class PNGLoader
{
private:
	// reference to an input stream to read from
	::std::istream& _input;

	PNGHeaderValidator _validate_header;

	friend class PNGReadInfoEndStruct;

	// data read functions
	void _read_data(::png_bytep data, ::png_size_t size);
	int _read_user_chunk(::png_unknown_chunkp /*chunk*/);

	PNGReadInfoEndStruct _png;

	static GLenum _translate_format(GLuint color_type, bool /*has_alpha*/);
public:
	PNGLoader(
		std::istream& input,
		Image& image,
		bool y_is_up,
		bool x_is_right
	);
};

} // namespace aux

/// Loader of images in the PNG (Portable network graphics) format
/**
 *  @ingroup image_load_gen
 */
class PNG
 : public Image
{
public:
	/// Load the image from a file with the specified @p file_path
	PNG(const char* file_path, bool y_is_up = true, bool x_is_right = true);

	/// Load the image from the specified @p input stream
	PNG(std::istream& input, bool y_is_up = true, bool x_is_right = true);
};

} // images
} // oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/images/png.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
