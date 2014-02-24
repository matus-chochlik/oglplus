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
#include <vector>
#include <random>

namespace oglplus {
namespace cloud_trace {

CloudData::CloudData(RenderData& data)
 : count(1024)
{
	// TODO improve the generator
	// TODO loading from istream
	std::vector<Mat4f> cloud_data;
	cloud_data.reserve(count);

	std::random_device rd;
	std::default_random_engine re(rd());

	std::uniform_real_distribution<float> rpos(-400,+400);
	std::uniform_real_distribution<float> relv(15, 20);
	std::uniform_real_distribution<float> r01(0, 1);

	for(unsigned i=0; i<count; ++i)
	{
		auto c =ModelMatrixf::Translation(rpos(re), relv(re), rpos(re))*
			ModelMatrixf::RotationA(Vec3f(r01(re),r01(re),r01(re)), FullCircles(r01(re)));

		c.Set(3, 3, 4+r01(re)*12.0);

		cloud_data.push_back(c);
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
