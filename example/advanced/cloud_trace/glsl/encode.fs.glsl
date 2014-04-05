/*  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#version 330

vec4 encode_rt_data(
	float dist_first,
	float dist_final,
	float density,
	float light_pri,
	float light_sec
)
{
	return vec4(
		dist_first,
		dist_final,
		density,
		int(light_pri*1000)+min(light_sec, 0.999)
	);
}
