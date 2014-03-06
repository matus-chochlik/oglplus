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

CloudData::CloudData(const AppData& app_data)
{
	Generate(app_data);
}

// TODO loading from istream
void CloudData::Generate(const AppData& app_data)
{
	storage.clear();
	storage.reserve(app_data.cloud_count);

	float radius = app_data.planet_radius;
	float cloud_alt = app_data.cloud_mean_alt;
	float cloud_alt_disp = app_data.cloud_alt_disp;

	float cloud_size = app_data.cloud_mean_size;
	float cloud_size_disp = app_data.cloud_size_disp;

	auto angle = Degrees(app_data.covered_angle);

	Vec3f center(0,-radius, 0);
	Mat4f cloud = ModelMatrixf::Translation(center);

	cloud.Set(3, 3, radius-1);
	cloud.Set(3, 0,-100);
	cloud.Set(3, 1, 1);

	storage.push_back(cloud);

	unsigned rand_seed = app_data.rand_seed;
	if(!rand_seed)
	{
		std::random_device rd;
		rand_seed = rd();
	}
	std::default_random_engine re(rand_seed);
	std::uniform_real_distribution<float> r01( 0, 1);
	std::uniform_real_distribution<float> r11(-1, 1);
	std::uniform_int_distribution<unsigned> rcc( 3, 8);

	unsigned c = 1, count = app_data.cloud_count;
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

			storage.push_back(cloud);

			Vec3f offs(r11(re)*1.4f, r11(re)*0.1f, r11(re));
			offs.Normalize();

			pos = cpos + offs*size;

			++c;
			--cc;
		}
	}
}

CloudBuffer::CloudBuffer(
	const AppData&,
	const CloudData& cloud_data,
	ResourceAllocator& alloc
): count(cloud_data.storage.size())
 , ub_idx(alloc.GetNextUniformIndex())
{
	*this	<< BufferTarget::Uniform
		<< cloud_data.storage;
	*this	<< BufferIndexedTarget::Uniform << ub_idx;
}

void CloudBuffer::Use(void)
{
	*this	<< BufferIndexedTarget::Uniform << ub_idx;
}

} // namespace cloud_trace
} // namespace oglplus
