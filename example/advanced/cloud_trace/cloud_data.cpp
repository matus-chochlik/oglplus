/**
 *  @file advanced/cloud_trace/cloud_data.cpp
 *  @brief Implements data structures storing cloud parameters
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include "cloud_data.hpp"

#include <oglplus/matrix.hpp>
#include <oglplus/angle.hpp>
#include <vector>
#include <random>

namespace oglplus {
namespace cloud_trace {

CloudData::CloudData(RenderData& data)
 : count(1024)
{
	// TODO loading from istream
	std::vector<Mat4f> cloud_data;
	cloud_data.reserve(count);

	float radius = data.planet_radius;
	float cloud_alt = data.cloud_mean_alt;
	float cloud_alt_disp = data.cloud_alt_disp;

	float cloud_size = data.cloud_mean_size;
	float cloud_size_disp = data.cloud_size_disp;

	auto angle = Degrees(data.covered_angle);

	Vec3f center(0,-radius, 0);
	Mat4f cloud = ModelMatrixf::Translation(center);

	cloud.Set(3, 3, radius-1);
	cloud.Set(3, 0,-100);
	cloud.Set(3, 1, 1);

	cloud_data.push_back(cloud);

	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_real_distribution<float> r01( 0, 1);
	std::uniform_real_distribution<float> r11(-1, 1);
	std::uniform_int_distribution<unsigned> rcc( 3, 8);

	unsigned c = 1;
	while(c < count)
	{
		auto lat = angle*r11(re)*0.5;
		auto lon= angle*r11(re)*0.5;

		Vec3f cpos = center +
			Vec3f(Cos(lat)*Sin(lon), Cos(lat)*Cos(lon), Sin(lat))*
			(radius + cloud_alt + cloud_alt_disp*r11(re));
		Vec3f pos = cpos;

		float size = cloud_size+cloud_size_disp*r11(re);

		unsigned cc = rcc(re);
		while((c < count) && (cc > 0))
		{
			cloud = ModelMatrixf::Translation(pos)*
				ModelMatrixf::RotationA(
					Vec3f(r01(re), r01(re), r01(re)),
					FullCircles(r01(re))
				);

			cloud.Set(3, 3, size);
			cloud.Set(3, 0, r01(re)*0.5f);
			cloud.Set(3, 1, 0.1+0.9*r01(re));

			cloud_data.push_back(cloud);

			Vec3f offs(r11(re)*1.4f, r11(re)*0.1f, r11(re));
			offs.Normalize();

			pos = cpos + offs*size;

			++c;
			--cc;
		}
	}

	assert(cloud_data.size() == count);

	*this	<< BufferTarget::Uniform
		<< cloud_data;
	*this	<< BufferIndexedTarget::Uniform << data.cloud_data_ub_idx;
}

unsigned CloudData::CloudCount(void) const
{
	return count;
}

} // namespace cloud_trace
} // namespace oglplus
