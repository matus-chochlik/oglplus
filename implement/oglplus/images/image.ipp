/**
 *  @file oglplus/images/image.ipp
 *  @brief Implementation of images::Image
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {
namespace images {

OGLPLUS_LIB_FUNC
bool Image::_is_initialized(void) const
{
	return (!_storage.empty()) && (_convert != nullptr);
}

OGLPLUS_LIB_FUNC
PixelDataFormat Image::_get_def_pdf(unsigned N)
{
	if(N == 1) return PixelDataFormat::Red;
	else if(N == 2) return PixelDataFormat::RG;
	else if(N == 3) return PixelDataFormat::RGB;
	else if(N == 4) return PixelDataFormat::RGBA;
	else assert(!"Too many color channels!");
	return PixelDataFormat::Red;
}

OGLPLUS_LIB_FUNC
PixelDataInternalFormat Image::_get_def_pdif(unsigned N)
{
	if(N == 1) return PixelDataInternalFormat::Red;
	else if(N == 2) return PixelDataInternalFormat::RG;
	else if(N == 3) return PixelDataInternalFormat::RGB;
	else if(N == 4) return PixelDataInternalFormat::RGBA;
	else assert(!"Too many color channels!");
	return PixelDataInternalFormat::Red;
}

} // namespace images
} // namespace oglplus

