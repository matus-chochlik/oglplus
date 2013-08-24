/**
 *  @file oglplus/images/load.ipp
 *  @brief Implementation of Image loader
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/opt/application.hpp>
#include <oglplus/opt/resources.hpp>

#include <fstream>
#include <stdexcept>

namespace oglplus {
namespace images {

OGLPLUS_LIB_FUNC
Image LoadByName(
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

} // images
} // oglplus

