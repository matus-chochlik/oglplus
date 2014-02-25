/**
 *  @file advanced/cloud_trace/render_data.hpp
 *  @brief Declares rendering-related data structures and functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_TRACE_RENDER_DATA_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_TRACE_RENDER_DATA_1119071146_HPP

#include <iosfwd>
#include <string>
#include <array>

namespace oglplus {
namespace cloud_trace {

struct RenderData
{
	// user interface functions
	void* puser_intf;
	void (*pset_status)(void*, const char*);

	void set_status(const char*);

	// error output stream
	std::ostream* perrstr;
	std::ostream& errstr(void) const;

	// output file prefix
	std::string output_prefix;
	// the face id strings
	std::array<std::string, 6> output_face_id;
	// the file suffix
	std::string output_suffix;

	// width, height tile size, cells
	unsigned width, height, tile;
	unsigned rows(void) const;
	unsigned cols(void) const;

	// cloud parameters
	float unit_opacity, unit_attenuation;
	unsigned cloud_res;

	// cloud data uniform buffer binding point
	unsigned cloud_data_ub_idx;

	// camera near/far values
	float cam_near, cam_far;

	// lighting parameters
	float light_x, light_y, light_z;
	float high_light, ambi_light;

	RenderData(int argc, char** argv);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
