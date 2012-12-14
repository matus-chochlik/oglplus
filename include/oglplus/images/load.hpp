/**
 *  @file oglplus/images/load.hpp
 *  @brief Image loader which finds and loads an image from its name
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_LOAD_1107121519_HPP
#define OGLPLUS_IMAGES_LOAD_1107121519_HPP

#include <oglplus/opt/application.hpp>
#include <oglplus/opt/resources.hpp>
#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/images/png.hpp>

#include <string>
#include <fstream>
#include <stdexcept>

namespace oglplus {
namespace images {

inline Image<GLubyte> LoadByName(
	std::string category,
	std::string name,
	bool y_is_up,
	bool x_is_right
)
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

/// Helper function for loading textures that come with @OGLplus in the examples
inline Image<GLubyte> LoadTexture(
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
