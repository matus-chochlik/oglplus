/**
 *  @file advanced/cloud_trace/saver.cpp
 *  @brief Implements the saver class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include "saver.hpp"

#include <oglplus/gl.hpp>

#include <string>
#include <vector>
#include <fstream>

namespace oglplus {
namespace cloud_trace {

Saver::Saver(RenderData&)
{
}

void Saver::SaveFrame(RenderData& data, unsigned face)
{
	assert(face < 6);
	glFlush();
	std::vector<char> pixels(data.render_width * data.render_height * 3);
	glFinish();
	glReadPixels(
		0, 0,
		data.render_width,
		data.render_height,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		pixels.data()
	);
	std::string path = data.output_prefix;
	path.append(data.output_face_id[face]);
	path.append(".");
	path.append(data.output_suffix);

	std::ofstream output(path.c_str());
	output.write(pixels.data(), pixels.size());
}

} // namespace cloud_trace
} // namespace oglplus
