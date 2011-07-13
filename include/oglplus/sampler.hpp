/**
 *  @file oglplus/sampler.hpp
 *  @brief Sampler object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SAMPLER_1107121519_HPP
#define OGLPLUS_SAMPLER_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class SamplerOps
{
protected:
	GLuint _name;

	SamplerOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenSamplers(count, &_name);
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteSamplers(count, &_name);
	}
public:
	SamplerOps(GLuint _n)
	 : _name(_n)
	{ }

	void Bind(GLuint unit) const
	{
		::glBindSampler(unit, _name);
	}
};

typedef Object<SamplerOps> Sampler;

} // namespace oglplus

#endif // include guard
