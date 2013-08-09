/**
 *  @file oglplus/images/load.hpp
 *  @brief Image loader which finds and loads an image from its name
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_LOAD_1107121519_HPP
#define OGLPLUS_IMAGES_LOAD_1107121519_HPP

#include <oglplus/images/image.hpp>
#include <oglplus/images/png.hpp>

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/opt/application.hpp>
#include <oglplus/opt/resources.hpp>

#include <fstream>
#include <stdexcept>
#endif // OGLPLUS_LINK_LIBRARY

#include <string>

namespace oglplus {
namespace images {

OGLPLUS_LIB_FUNC
Image LoadByName(
	std::string category,
	std::string name,
	bool y_is_up,
	bool x_is_right
)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
	std::ifstream file;
	const char* exts[] = {".png"};
	std::size_t nexts = sizeof(exts)/sizeof(exts[0]);
	std::size_t iext = oglplus::FindResourceFile(
		file,
		category,
		name,
		exts,
		nexts
	);

	if(!file.good())
		throw std::runtime_error("Unable to open image: "+name);
	// TODO switch on extension
	assert(iext == 0);
	return PNG(file, y_is_up, x_is_right);
}
#endif

/// Helper function for loading textures that come with @OGLplus in the examples
inline Image LoadTexture(
	std::string name,
	bool y_is_up = true,
	bool x_is_right = true
)
{
	return LoadByName("textures", name, y_is_up, x_is_right);
}

} // images
} // oglplus

#endif // include guard
