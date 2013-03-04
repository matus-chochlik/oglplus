/**
 *  .file test/vector.cpp
 *  .brief Test case for Vector class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2011-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE OGLPLUS_vector
#include <boost/test/unit_test.hpp>

#include <oglplus/gl.hpp>
#include <oglplus/vector.hpp>

BOOST_AUTO_TEST_SUITE(vector)

BOOST_AUTO_TEST_CASE(vector_default_construction)
{
	oglplus::Vector<float, 2> vec2f;
	oglplus::Vector<float, 3> vec3f;
	oglplus::Vector<float, 4> vec4f;

	oglplus::Vector<double, 2> vec2d;
	oglplus::Vector<double, 3> vec3d;
	oglplus::Vector<double, 4> vec4d;
}

BOOST_AUTO_TEST_CASE(vector_construction)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 4> vec4f(1.0f, 2.0f, 3.0f, 4.0f);

	oglplus::Vector<double, 2> vec2d(1.0, 2.0);
	oglplus::Vector<double, 3> vec3d(1.0, 2.0, 3.0);
	oglplus::Vector<double, 4> vec4d(1.0, 2.0, 3.0, 4.0);
}

BOOST_AUTO_TEST_SUITE_END()
