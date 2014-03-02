/**
 *  @file advanced/cloud_trace/render_data.cpp
 *  @brief Implements rendering-data-related functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include "render_data.hpp"

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>

namespace oglplus {
namespace cloud_trace {

template <typename T>
void parse_opt_value(
	const char* name,
	const char* str,
	T& value
)
{
	std::stringstream ss(str);

	ss >> value;
	if(ss.fail())
	{
		std::string message;
		message.append("Invalid value '");
		message.append(str);
		message.append("' after '");
		message.append(name);
		message.append("'");

		throw std::runtime_error(message);
	}
}

bool parse_single_opt(
	int& arg,
	int,
	char** argv,
	const char* short_name,
	const char* long_name
)
{
	bool result =
		(std::strcmp(argv[arg], long_name) == 0)||
		(std::strcmp(argv[arg], short_name) == 0);
	if(result) ++arg;
	return result;
}

template <typename T>
bool parse_single_opt(
	int& arg,
	int argc,
	char** argv,
	const char* short_name,
	const char* long_name,
	T& value
)
{
	const char* name = nullptr;

	std::size_t len = std::strlen(short_name);
	if(std::strncmp(argv[arg], short_name, len) == 0)
	{
		name = short_name;
	}
	else
	{
		len = std::strlen(long_name);
		if(std::strncmp(argv[arg], long_name, len) == 0)
		{
			name = long_name;
		}
		else len = 0;
	}

	if(name && len)
	{
		if(argv[arg][len] == '=')
		{
			parse_opt_value(name, argv[arg]+len+1, value);
			arg += 1;
			return true;
		}
		else if(argv[arg][len] == '\0')
		{
			if(arg+1 < argc)
			{
				parse_opt_value(name, argv[arg+1], value);
				arg += 2;
				return true;
			}
			else
			{
				std::string message;
				message.append("Missing value after '");
				message.append(argv[arg]);
				message.append("'");

				throw std::runtime_error(message);
			}
		}
	}
	return false;
}

RenderData::RenderData(int argc, char** argv)
 : puser_intf(nullptr)
 , pset_status(nullptr)
 , perrstr(nullptr)
 , output_prefix("clouds")
 , output_suffix("rgb")
 , raytrace_width(512)
 , raytrace_height(512)
 , render_width(raytrace_width)
 , render_height(raytrace_height)
 , tile(32)
 , unit_opacity(0.03)
 , unit_attenuation(0.01)
 , cloud_count(512)
 , cloud_res(256)
 , dump_cloud_image(false)
 , cloud_data_ub_idx(0)
 , planet_radius(6371)
 , covered_angle(1)
 , cloud_mean_alt(2.0f)
 , cloud_alt_disp(0.3f)
 , cloud_mean_size(1.5f)
 , cloud_size_disp(0.4f)
 , cam_near(1)
 , cam_far(400)
 , light_x(100000)
 , light_y(100000)
 , light_z(100000)
 , high_light(1.2f)
 , ambi_light(0.5f)
{
	for(unsigned f=0; f!=6; ++f)
	{
		output_face_id[f] = "- ";
		output_face_id[f][1] = '0'+f;
	}

	int arg = 1;
	while(arg < argc)
	{
		if(parse_single_opt(arg, argc, argv, "-s", "--size", raytrace_width))
		{
			raytrace_height = raytrace_width;
			render_width = raytrace_width;
			render_height = raytrace_width;
			continue;
		}
		if(parse_single_opt(arg, argc, argv, "-t", "--tile", tile))
			continue;
		if(parse_single_opt(arg, argc, argv, "-w", "--raytrace_width", raytrace_width))
		{
			render_width = raytrace_width;
			continue;
		}
		if(parse_single_opt(arg, argc, argv, "-h", "--raytrace_height", raytrace_height))
		{
			render_height = raytrace_height;
			continue;
		}
		if(parse_single_opt(arg, argc, argv,"-cc", "--cloud-count", cloud_count))
		{
			if(cloud_count >= 1024)
			{
				std::string message;
				message.append("The value specified for --cloud-count ");
				message.append("exceeds the maximum value 1024");
				throw std::runtime_error(message);
			}
			continue;
		}
		if(parse_single_opt(arg, argc, argv,"-cr", "--cloud-res", cloud_res))
			continue;
		if(parse_single_opt(arg, argc, argv,"-di", "--dump-cloud-image"))
		{
			dump_cloud_image = true;
			continue;
		}
		if(parse_single_opt(arg, argc, argv,"-ci", "--cloud-image-path", cloud_image_path))
			continue;
		if(parse_single_opt(arg, argc, argv,"-uo", "--unit-opacity", unit_opacity))
			continue;
		if(parse_single_opt(arg, argc, argv,"-ua", "--unit-attenuation", unit_attenuation))
			continue;
		if(parse_single_opt(arg, argc, argv,"-pr", "--planet-radius", planet_radius))
			continue;
		if(parse_single_opt(arg, argc, argv,"-ca", "--covered-angle", covered_angle))
			continue;
		if(parse_single_opt(arg, argc, argv,"-cma", "--cloud-mean-alt", cloud_mean_alt))
			continue;
		if(parse_single_opt(arg, argc, argv,"-cad", "--cloud-alt-disp", cloud_alt_disp))
			continue;
		if(parse_single_opt(arg, argc, argv,"-cms", "--cloud-mean-size", cloud_mean_size))
			continue;
		if(parse_single_opt(arg, argc, argv,"-csd", "--cloud-size-disp", cloud_size_disp))
			continue;
		if(parse_single_opt(arg, argc, argv,"-lx", "--light-x", light_x))
			continue;
		if(parse_single_opt(arg, argc, argv,"-ly", "--light-y", light_y))
			continue;
		if(parse_single_opt(arg, argc, argv,"-lz", "--light-z", light_z))
			continue;
		if(parse_single_opt(arg, argc, argv,"-hl", "--high-light", high_light))
			continue;
		if(parse_single_opt(arg, argc, argv,"-al", "--ambi-light", ambi_light))
			continue;
		if(parse_single_opt(arg, argc, argv, "-o", "--output-prefix", output_prefix))
			continue;
		if(parse_single_opt(arg, argc, argv, "-s", "--output-suffix", output_suffix))
			continue;
		if(parse_single_opt(arg, argc, argv,"-f0", "--output-id-0", output_face_id[0]))
			continue;
		if(parse_single_opt(arg, argc, argv,"-f1", "--output-id-1", output_face_id[1]))
			continue;
		if(parse_single_opt(arg, argc, argv,"-f2", "--output-id-2", output_face_id[2]))
			continue;
		if(parse_single_opt(arg, argc, argv,"-f3", "--output-id-3", output_face_id[3]))
			continue;
		if(parse_single_opt(arg, argc, argv,"-f4", "--output-id-4", output_face_id[4]))
			continue;
		if(parse_single_opt(arg, argc, argv,"-f5", "--output-id-5", output_face_id[5]))
			continue;
		if(parse_single_opt(arg, argc, argv,"-f6", "--output-id-6", output_face_id[6]))
			continue;

		std::string message("Unknown command-line option: '");
		message.append(argv[arg]);
		message.append("'");

		throw std::runtime_error(message);
	}
}

void RenderData::set_status(const char* str)
{
	if(pset_status)
	{
		pset_status(puser_intf, str);
	}
}

std::ostream& RenderData::errstr(void) const
{
	return (perrstr?*perrstr:std::cerr);
}

unsigned RenderData::rows(void) const
{
	return (raytrace_height/tile)+(raytrace_height%tile?1:0);
}

unsigned RenderData::cols(void) const
{
	return (raytrace_width/tile)+(raytrace_width%tile?1:0);
}

} // namespace cloud_trace
} // namespace oglplus
