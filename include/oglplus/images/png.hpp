/**
 *  @file oglplus/images/png.hpp
 *  @brief PNG image loader (based on libpng)
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_PNG_1107121519_HPP
#define OGLPLUS_IMAGES_PNG_1107121519_HPP

#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>

#include <istream>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <png.h>

namespace oglplus {
namespace images {
namespace aux {

class PNGLoader
 : public ImageInitializer<GLubyte>
{
private:
	// reference to an input stream to read from
	::std::istream& _input;

	// PNG header validator
	struct _hdr_validator
	{
		_hdr_validator(std::istream& input)
		{
			if(!input.good())
			{
				throw std::runtime_error(
					"Unable to open file for reading"
				);
			}

			const size_t sig_size = 8;
			::png_byte sig[sig_size];
			input.read((char*)sig, sig_size);

			if(!input.good())
			{
				throw std::runtime_error(
					"Unable to read PNG signature"
				);
			}

			if(::png_sig_cmp(sig, 0, sig_size) != 0)
			{
				throw std::runtime_error(
					"Invalid PNG signature"
				);
			}
		}
	} _validate_header;

	// Error handling function
	static void _png_handle_error(::png_structp /*sp*/, const char* msg)
	{
		throw ::std::runtime_error(msg);
	}

	// Warning handling function
	static void _png_handle_warning(::png_structp/*sp*/, const char* /*msg*/)
	{
	}

	// structure managing the png_struct pointer
	struct _read_struct
	{
		::png_structp _read;

		_read_struct(PNGLoader& /*loader*/)
		 : _read(::png_create_read_struct(
			PNG_LIBPNG_VER_STRING,
			(::png_voidp)this,
			&_png_handle_error,
			&_png_handle_warning
		))
		{ }

		~_read_struct(void)
		{
			::png_destroy_read_struct(
				&_read,
				(::png_infopp)0,
				(::png_infopp)0
			);
		}
	};

	// structure managing the first png_info pointer
	struct _read_info_struct : _read_struct
	{
		::png_infop _info;

		_read_info_struct(PNGLoader& loader)
		 : _read_struct(loader)
		 , _info(::png_create_info_struct(_read))
		{ }

		~_read_info_struct(void)
		{
			::png_destroy_read_struct(
				&_read,
				&_info,
				(::png_infopp)0
			);
		}
	};

	// data read callback
	static void _png_read_data(
		::png_structp png,
		::png_bytep data,
		::png_size_t size
	)
	{
		::png_voidp p = ::png_get_io_ptr(png);
		assert(p != 0);
		((PNGLoader*)p)->_read_data(data, size);
	}

	// data read function
	void _read_data(::png_bytep data, ::png_size_t size)
	{
		_input.read((char*)data, size);
		if(!_input.good())
		{
			throw std::runtime_error(
				"Unable to read PNG signature"
			);
		}
	}

	static int _png_read_user_chunk(
		::png_structp png,
		::png_unknown_chunkp chunk
	)
	{
		::png_voidp p = ::png_get_user_chunk_ptr(png);
		assert(p != 0);
		return ((PNGLoader*)p)->_read_user_chunk(chunk);
	}

	int _read_user_chunk(::png_unknown_chunkp /*chunk*/)
	{
		return 0;
	}

	// structure managing the second png_info pointer
	struct _read_info_end_struct : _read_info_struct
	{
		::png_infop _end;

		_read_info_end_struct(PNGLoader& loader)
		 : _read_info_struct(loader)
		 , _end(::png_create_info_struct(_read))
		{
			::png_set_read_fn(
				_read,
				(::png_voidp)&loader,
				&_png_read_data
			);
			::png_set_read_user_chunk_fn(
				_read,
				(::png_voidp)&loader,
				&_png_read_user_chunk
			);
			::png_set_keep_unknown_chunks(
				_read,
				PNG_HANDLE_CHUNK_NEVER,
				0, 0
			);

		}

		~_read_info_end_struct(void)
		{
			::png_destroy_read_struct(
				&_read,
				&_info,
				&_end
			);
		}
	} _png;

	static GLenum _translate_format(GLuint color_type, bool /*has_alpha*/)
	{
		switch(color_type)
		{
			case PNG_COLOR_TYPE_GRAY:
				return GL_RED;
			case PNG_COLOR_TYPE_GRAY_ALPHA:
				return GL_RG;
			case PNG_COLOR_TYPE_RGB:
				return GL_RGB;
			case PNG_COLOR_TYPE_RGB_ALPHA:
				return GL_RGBA;
			// TODO other color types
			default:;
		}
		assert(!"Unknown color type!");
		return 0;
	}
public:
	PNGLoader(std::istream& input, Image<GLubyte>& image)
	 : _input(input)
	 , _validate_header(_input)
	 , _png(*this)
	{
		const size_t sig_size = 8;
		::png_set_sig_bytes(_png._read, sig_size);
		::png_read_info(_png._read, _png._info);

		GLsizei width = png_get_image_width(_png._read, _png._info);
		GLsizei height = png_get_image_height(_png._read, _png._info);
		GLuint bitdepth = png_get_bit_depth(_png._read, _png._info);
		GLuint channels = png_get_channels(_png._read, _png._info);
		GLuint color_type = png_get_color_type(_png._read, _png._info);

		// color conversions
		switch(color_type)
		{
			case PNG_COLOR_TYPE_PALETTE:
				::png_set_palette_to_rgb(_png._read);
				channels = 3;
				break;
			case PNG_COLOR_TYPE_GRAY:
				if(bitdepth < 8)
					::png_set_expand_gray_1_2_4_to_8(_png._read);
				bitdepth = 8;
				break;
			// TODO: other conversions
			default:;
		}

		// handle transparency
		bool has_alpha = false;
		if(::png_get_valid(_png._read, _png._info, PNG_INFO_tRNS))
		{
			::png_set_tRNS_to_alpha(_png._read);
			channels += 1;
			has_alpha = true;
		}

		// if there are too many bits per channel strip them down
		if(bitdepth == 16)
			::png_set_strip_16(_png._read);

		// bytes per row
		GLsizei rowsize = width * channels * bitdepth / 8;
		// allocate the buffer
		std::vector<GLubyte> data(rowsize * height, GLubyte(0));
		{
			// allocate and initialize the row pointers
			std::vector< ::png_bytep> rows(height);
			//
			for(GLsizei r=0; r!= height; ++r)
			{
				size_t ofs = (height - r - 1) * rowsize;
				rows[r] = (::png_bytep)data.data() + ofs;
			}

			// read
			::png_read_image(_png._read, rows.data());
		}

		GLenum gl_format = _translate_format(color_type, has_alpha);
		this->InitImage(
			image,
			width,
			height,
			1,
			std::move(data),
			PixelDataType::UnsignedByte,
			PixelDataFormat(gl_format),
			PixelDataInternalFormat(gl_format)
		);
	}

};

} // namespace aux

/// Loader of images in the PNG (Portable network graphics) format
/**
 *  @ingroup image_load_gen
 */
class PNG
 : public Image<GLubyte>
{
public:
	/// Load the image from a file with the specified @p file_path
	PNG(const char* file_path)
	{
		std::ifstream  file(file_path);
		aux::PNGLoader(file, *this);
	}

	/// Load the image from the specified @p input stream
	PNG(std::istream& input)
	{
		aux::PNGLoader(input, *this);
	}
};

} // images
} // oglplus

#endif // include guard
