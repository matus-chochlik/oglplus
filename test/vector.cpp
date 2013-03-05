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

BOOST_AUTO_TEST_CASE(vector_construction_2)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(vec2f, 3.0f);
	oglplus::Vector<float, 4> vec4f(vec3f, 4.0f);
	oglplus::Vector<float, 4> vec4f2(vec2f, 3.0f, 4.0f);
}

BOOST_AUTO_TEST_CASE(vector_construction_3)
{
	float data[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	oglplus::Vector<float, 2> vec2f(data, 2);
	oglplus::Vector<float, 3> vec3f(data, 3);
	oglplus::Vector<float, 4> vec4f(data, 4);
}

BOOST_AUTO_TEST_CASE(vector_construction_4)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 4> vec4f(1.0f, 2.0f, 3.0f, 4.0f);

	oglplus::Vector<double, 2> vec2d(vec2f);
	oglplus::Vector<double, 3> vec3d(vec3f);
	oglplus::Vector<double, 4> vec4d(vec4f);
}

BOOST_AUTO_TEST_CASE(vector_construction_5)
{
	oglplus::Vector<double, 2> vec2d(1.0, 2.0);
	oglplus::Vector<double, 3> vec3d(1.0, 2.0, 3.0);
	oglplus::Vector<double, 4> vec4d(1.0, 2.0, 3.0, 4.0);

	oglplus::Vector<float, 2> vec2f(vec2d);
	oglplus::Vector<float, 3> vec3f(vec3d);
	oglplus::Vector<float, 4> vec4f(vec4d);
}

BOOST_AUTO_TEST_CASE(vector_copy_construction)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 4> vec4f(1.0f, 2.0f, 3.0f, 4.0f);

	oglplus::Vector<float, 2> vec2f2(vec2f);
	oglplus::Vector<float, 3> vec3f2(vec3f);
	oglplus::Vector<float, 4> vec4f2(vec4f);
}

BOOST_AUTO_TEST_CASE(vector_assignment)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 4> vec4f(1.0f, 2.0f, 3.0f, 4.0f);

	oglplus::Vector<float, 2> vec2f2;
	oglplus::Vector<float, 3> vec3f2;
	oglplus::Vector<float, 4> vec4f2;

	vec2f2 = vec2f;
	vec3f2 = vec3f;
	vec4f2 = vec4f;
}

BOOST_AUTO_TEST_CASE(vector_size)
{
	oglplus::Vector<float, 2> vec2f;
	oglplus::Vector<float, 3> vec3f;
	oglplus::Vector<float, 4> vec4f;

	BOOST_CHECK_EQUAL(vec2f.Size(), 2);
	BOOST_CHECK_EQUAL(vec3f.Size(), 3);
	BOOST_CHECK_EQUAL(vec4f.Size(), 4);

	BOOST_CHECK_EQUAL(Size(vec2f), 2);
	BOOST_CHECK_EQUAL(Size(vec3f), 3);
	BOOST_CHECK_EQUAL(Size(vec4f), 4);
}

BOOST_AUTO_TEST_CASE(vector_data)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 4> vec4f(1.0f, 2.0f, 3.0f, 4.0f);

	BOOST_CHECK_EQUAL(vec2f.Data()[0], 1.0f);
	BOOST_CHECK_EQUAL(vec2f.Data()[1], 2.0f);

	BOOST_CHECK_EQUAL(vec3f.Data()[0], 1.0f);
	BOOST_CHECK_EQUAL(vec3f.Data()[1], 2.0f);
	BOOST_CHECK_EQUAL(vec3f.Data()[2], 3.0f);

	BOOST_CHECK_EQUAL(vec4f.Data()[0], 1.0f);
	BOOST_CHECK_EQUAL(vec4f.Data()[1], 2.0f);
	BOOST_CHECK_EQUAL(vec4f.Data()[2], 3.0f);
	BOOST_CHECK_EQUAL(vec4f.Data()[3], 4.0f);
}

BOOST_AUTO_TEST_CASE(vector_at_1)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 4> vec4f(1.0f, 2.0f, 3.0f, 4.0f);

	BOOST_CHECK_EQUAL(vec2f.At<0>(), 1.0f);
	BOOST_CHECK_EQUAL(vec2f.At<1>(), 2.0f);

	BOOST_CHECK_EQUAL(vec3f.At<0>(), 1.0f);
	BOOST_CHECK_EQUAL(vec3f.At<1>(), 2.0f);
	BOOST_CHECK_EQUAL(vec3f.At<2>(), 3.0f);

	BOOST_CHECK_EQUAL(vec4f.At<0>(), 1.0f);
	BOOST_CHECK_EQUAL(vec4f.At<1>(), 2.0f);
	BOOST_CHECK_EQUAL(vec4f.At<2>(), 3.0f);
	BOOST_CHECK_EQUAL(vec4f.At<3>(), 4.0f);
}

BOOST_AUTO_TEST_CASE(vector_at_2)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 4> vec4f(1.0f, 2.0f, 3.0f, 4.0f);

	BOOST_CHECK_EQUAL(vec2f.At<0>(5.0f), 1.0f);
	BOOST_CHECK_EQUAL(vec2f.At<1>(5.0f), 2.0f);
	BOOST_CHECK_EQUAL(vec2f.At<2>(5.0f), 5.0f);

	BOOST_CHECK_EQUAL(vec3f.At<0>(5.0f), 1.0f);
	BOOST_CHECK_EQUAL(vec3f.At<1>(5.0f), 2.0f);
	BOOST_CHECK_EQUAL(vec3f.At<2>(5.0f), 3.0f);
	BOOST_CHECK_EQUAL(vec3f.At<3>(5.0f), 5.0f);

	BOOST_CHECK_EQUAL(vec4f.At<0>(5.0f), 1.0f);
	BOOST_CHECK_EQUAL(vec4f.At<1>(5.0f), 2.0f);
	BOOST_CHECK_EQUAL(vec4f.At<2>(5.0f), 3.0f);
	BOOST_CHECK_EQUAL(vec4f.At<3>(5.0f), 4.0f);
	BOOST_CHECK_EQUAL(vec4f.At<4>(5.0f), 5.0f);
}

BOOST_AUTO_TEST_CASE(vector_ref)
{
	oglplus::Vector<float, 2> vec2f(1.0f, 2.0f);
	oglplus::Vector<float, 3> vec3f(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 4> vec4f(1.0f, 2.0f, 3.0f, 4.0f);

	BOOST_CHECK_EQUAL(vec2f.Ref<0>(), 1.0f);
	BOOST_CHECK_EQUAL(vec2f.Ref<1>(), 2.0f);

	BOOST_CHECK_EQUAL(vec3f.Ref<0>(), 1.0f);
	BOOST_CHECK_EQUAL(vec3f.Ref<1>(), 2.0f);
	BOOST_CHECK_EQUAL(vec3f.Ref<2>(), 3.0f);

	BOOST_CHECK_EQUAL(vec4f.Ref<0>(), 1.0f);
	BOOST_CHECK_EQUAL(vec4f.Ref<1>(), 2.0f);
	BOOST_CHECK_EQUAL(vec4f.Ref<2>(), 3.0f);
	BOOST_CHECK_EQUAL(vec4f.Ref<3>(), 4.0f);

	vec2f.Ref<0>() = 10.0f;
	vec2f.Ref<1>() = 20.0f;

	vec3f.Ref<0>() = 10.0f;
	vec3f.Ref<1>() = 20.0f;
	vec3f.Ref<2>() = 30.0f;

	vec4f.Ref<0>() = 10.0f;
	vec4f.Ref<1>() = 20.0f;
	vec4f.Ref<2>() = 30.0f;
	vec4f.Ref<3>() = 40.0f;

	BOOST_CHECK_EQUAL(vec2f.Ref<0>(), 10.0f);
	BOOST_CHECK_EQUAL(vec2f.Ref<1>(), 20.0f);

	BOOST_CHECK_EQUAL(vec3f.Ref<0>(), 10.0f);
	BOOST_CHECK_EQUAL(vec3f.Ref<1>(), 20.0f);
	BOOST_CHECK_EQUAL(vec3f.Ref<2>(), 30.0f);

	BOOST_CHECK_EQUAL(vec4f.Ref<0>(), 10.0f);
	BOOST_CHECK_EQUAL(vec4f.Ref<1>(), 20.0f);
	BOOST_CHECK_EQUAL(vec4f.Ref<2>(), 30.0f);
	BOOST_CHECK_EQUAL(vec4f.Ref<3>(), 40.0f);
}

BOOST_AUTO_TEST_CASE(vector_comparison)
{
	oglplus::Vector<float, 4> v1(1.0f, 2.0f, 3.0f, 4.0f);
	oglplus::Vector<float, 4> v2(2.0f, 3.0f, 4.0f, 5.0f);
	oglplus::Vector<float, 4> v3(v1);

	BOOST_CHECK(Equal(v1, v1));
	BOOST_CHECK(Equal(v2, v2));
	BOOST_CHECK(Equal(v1, v3));
	BOOST_CHECK((v1 == v3));
	BOOST_CHECK(!(v1 != v3));

	BOOST_CHECK(!Equal(v1, v2));
	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK((v1 != v2));

	BOOST_CHECK(Equal(v1, v2) == Equal(v2, v1));
	BOOST_CHECK(Equal(v1, v3) == Equal(v3, v1));

	BOOST_CHECK((v1 == v2) == (v2 == v1));
	BOOST_CHECK((v1 == v3) == (v3 == v1));

	BOOST_CHECK(Equal(v1, v2) == (v1 == v2));
	BOOST_CHECK(Equal(v1, v3) == (v1 == v3));

	BOOST_CHECK((v1 != v2) == (v2 != v1));
	BOOST_CHECK((v1 != v3) == (v3 != v1));

	BOOST_CHECK(!Equal(v1, v2) == (v1 != v2));
	BOOST_CHECK(!Equal(v1, v3) == (v1 != v3));
}

BOOST_AUTO_TEST_CASE(vector_negation_2)
{
	oglplus::Vector<float, 2> v1( 1.0f, 2.0f);
	oglplus::Vector<float, 2> v2(-1.0f,-2.0f);

	BOOST_CHECK(v1 ==-v2);
	BOOST_CHECK(v2 ==-v1);
	BOOST_CHECK(v1 ==-(-v1));
	BOOST_CHECK(v2 ==-(-v2));
}

BOOST_AUTO_TEST_CASE(vector_negation_3)
{
	oglplus::Vector<float, 3> v1( 1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 3> v2(-1.0f,-2.0f,-3.0f);

	BOOST_CHECK(v1 ==-v2);
	BOOST_CHECK(v2 ==-v1);
	BOOST_CHECK(v1 ==-(-v1));
	BOOST_CHECK(v2 ==-(-v2));
}

BOOST_AUTO_TEST_CASE(vector_negation_4)
{
	oglplus::Vector<float, 4> v1( 1.0f, 2.0f, 3.0f, 4.0f);
	oglplus::Vector<float, 4> v2(-1.0f,-2.0f,-3.0f,-4.0f);

	BOOST_CHECK(v1 ==-v2);
	BOOST_CHECK(v2 ==-v1);
	BOOST_CHECK(v1 ==-(-v1));
	BOOST_CHECK(v2 ==-(-v2));
}

BOOST_AUTO_TEST_CASE(vector_addition_2)
{
	oglplus::Vector<float, 2> v0(0.0f, 0.0f);
	oglplus::Vector<float, 2> v1(1.0f, 2.0f);
	oglplus::Vector<float, 2> v2(2.0f, 4.0f);
	oglplus::Vector<float, 2> v3(v1+v2);

	BOOST_CHECK((v1+v0) == v1);
	BOOST_CHECK((v1+v1) == v2);
	BOOST_CHECK((v1+v1+v1) == v3);
	BOOST_CHECK((v1+v2) == (v2+v1));
	BOOST_CHECK((v1+v2+v3) == (v3+v2+v1));
}

BOOST_AUTO_TEST_CASE(vector_addition_3)
{
	oglplus::Vector<float, 3> v0(0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 3> v1(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 3> v2(2.0f, 4.0f, 6.0f);
	oglplus::Vector<float, 3> v3(v1+v2);

	BOOST_CHECK((v1+v0) == v1);
	BOOST_CHECK((v1+v1) == v2);
	BOOST_CHECK((v1+v1+v1) == v3);
	BOOST_CHECK((v1+v2) == (v2+v1));
	BOOST_CHECK((v1+v2+v3) == (v3+v2+v1));
}

BOOST_AUTO_TEST_CASE(vector_addition_4)
{
	oglplus::Vector<float, 4> v0(0.0f, 0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 4> v1(1.0f, 2.0f, 3.0f, 4.0f);
	oglplus::Vector<float, 4> v2(2.0f, 4.0f, 6.0f, 8.0f);
	oglplus::Vector<float, 4> v3(v1+v2);

	BOOST_CHECK((v1+v0) == v1);
	BOOST_CHECK((v1+v1) == v2);
	BOOST_CHECK((v1+v1+v1) == v3);
	BOOST_CHECK((v1+v2) == (v2+v1));
	BOOST_CHECK((v1+v2+v3) == (v3+v2+v1));
}

BOOST_AUTO_TEST_CASE(vector_subtraction_2)
{
	oglplus::Vector<float, 2> v0(0.0f, 0.0f);
	oglplus::Vector<float, 2> v1(1.0f, 2.0f);
	oglplus::Vector<float, 2> v2(2.0f, 4.0f);
	oglplus::Vector<float, 2> v3(v1+v2);

	BOOST_CHECK((v1-v0) == v1);
	BOOST_CHECK((v2-v2) == v0);
	BOOST_CHECK((-v1-v1-v1) == -v3);
	BOOST_CHECK((v1-v2) == -(v2-v1));
	BOOST_CHECK((v3-v2-v1) == v0);
}

BOOST_AUTO_TEST_CASE(vector_subtraction_3)
{
	oglplus::Vector<float, 3> v0(0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 3> v1(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 3> v2(2.0f, 4.0f, 6.0f);
	oglplus::Vector<float, 3> v3(v1+v2);

	BOOST_CHECK((v1-v0) == v1);
	BOOST_CHECK((v2-v2) == v0);
	BOOST_CHECK((-v1-v1-v1) == -v3);
	BOOST_CHECK((v1-v2) == -(v2-v1));
	BOOST_CHECK((v3-v2-v1) == v0);
}

BOOST_AUTO_TEST_CASE(vector_subtraction_4)
{
	oglplus::Vector<float, 4> v0(0.0f, 0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 4> v1(1.0f, 2.0f, 3.0f, 4.0f);
	oglplus::Vector<float, 4> v2(2.0f, 4.0f, 6.0f, 8.0f);
	oglplus::Vector<float, 4> v3(v1+v2);

	BOOST_CHECK((v1-v0) == v1);
	BOOST_CHECK((v2-v2) == v0);
	BOOST_CHECK((-v1-v1-v1) == -v3);
	BOOST_CHECK((v1-v2) == -(v2-v1));
	BOOST_CHECK((v3-v2-v1) == v0);
}

BOOST_AUTO_TEST_CASE(vector_multiplication_2)
{
	oglplus::Vector<float, 2> v0(0.0f, 0.0f);
	oglplus::Vector<float, 2> v1(1.0f, 2.0f);
	oglplus::Vector<float, 2> v2(2.0f, 4.0f);

	BOOST_CHECK(v0*10 == v0);
	BOOST_CHECK(v1*10 == 10*v1);
	BOOST_CHECK(v1*22 == v2*11);
	BOOST_CHECK(6*v1 == 3*v2);
}

BOOST_AUTO_TEST_CASE(vector_multiplication_3)
{
	oglplus::Vector<float, 3> v0(0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 3> v1(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 3> v2(2.0f, 4.0f, 6.0f);

	BOOST_CHECK(v0*10 == v0);
	BOOST_CHECK(v1*10 == 10*v1);
	BOOST_CHECK(v1*22 == v2*11);
	BOOST_CHECK(6*v1 == 3*v2);
}

BOOST_AUTO_TEST_CASE(vector_multiplication_4)
{
	oglplus::Vector<float, 4> v0(0.0f, 0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 4> v1(1.0f, 2.0f, 3.0f, 4.0f);
	oglplus::Vector<float, 4> v2(2.0f, 4.0f, 6.0f, 8.0f);

	BOOST_CHECK(v0*10 == v0);
	BOOST_CHECK(v1*10 == 10*v1);
	BOOST_CHECK(v1*22 == v2*11);
	BOOST_CHECK(6*v1 == 3*v2);
}

BOOST_AUTO_TEST_CASE(vector_division_2)
{
	oglplus::Vector<float, 2> v0(0.0f, 0.0f);
	oglplus::Vector<float, 2> v1(1.0f, 2.0f);
	oglplus::Vector<float, 2> v2(2.0f, 4.0f);

	BOOST_CHECK(v0/10.0f == v0);
	BOOST_CHECK(v1*0.5f == v1/2.0f);
	BOOST_CHECK(v1 == v2/2.0f);
}

BOOST_AUTO_TEST_CASE(vector_division_3)
{
	oglplus::Vector<float, 3> v0(0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 3> v1(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 3> v2(2.0f, 4.0f, 6.0f);

	BOOST_CHECK(v0/10.0f == v0);
	BOOST_CHECK(v1*0.5f == v1/2.0f);
	BOOST_CHECK(v1 == v2/2.0f);
}

BOOST_AUTO_TEST_CASE(vector_division_4)
{
	oglplus::Vector<float, 4> v0(0.0f, 0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 4> v1(1.0f, 2.0f, 3.0f, 4.0f);
	oglplus::Vector<float, 4> v2(2.0f, 4.0f, 6.0f, 8.0f);

	BOOST_CHECK(v0/10.0f == v0);
	BOOST_CHECK(v1*0.5f == v1/2.0f);
	BOOST_CHECK(v1 == v2/2.0f);
}

BOOST_AUTO_TEST_CASE(vector_dot_2)
{
	oglplus::Vector<float, 2> v0(0.0f, 0.0f);
	oglplus::Vector<float, 2> v1(1.0f, 1.0f);
	oglplus::Vector<float, 2> v2(1.0f, 2.0f);
	oglplus::Vector<float, 2> v3(1.0f, 0.0f);
	oglplus::Vector<float, 2> v4(0.0f, 1.0f);

	BOOST_CHECK_EQUAL(Dot(v0, v1), 0.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v1), 2.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v2), 3.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v3), 1.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v4), 1.0f);
	BOOST_CHECK_EQUAL(Dot(v2, v3), 1.0f);
	BOOST_CHECK_EQUAL(Dot(v2, v4), 2.0f);
	BOOST_CHECK_EQUAL(Dot(v3, v4), 0.0f);
}

BOOST_AUTO_TEST_CASE(vector_dot_3)
{
	oglplus::Vector<float, 3> v0(0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 3> v1(1.0f, 1.0f, 1.0f);
	oglplus::Vector<float, 3> v2(1.0f, 2.0f, 3.0f);
	oglplus::Vector<float, 3> v3(1.0f, 0.0f, 1.0f);
	oglplus::Vector<float, 3> v4(0.0f, 1.0f, 0.0f);

	BOOST_CHECK_EQUAL(Dot(v0, v1), 0.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v1), 3.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v2), 6.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v3), 2.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v4), 1.0f);
	BOOST_CHECK_EQUAL(Dot(v2, v3), 4.0f);
	BOOST_CHECK_EQUAL(Dot(v2, v4), 2.0f);
	BOOST_CHECK_EQUAL(Dot(v3, v4), 0.0f);
}

BOOST_AUTO_TEST_CASE(vector_dot_4)
{
	oglplus::Vector<float, 4> v0(0.0f, 0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 4> v1(1.0f, 1.0f, 1.0f, 1.0f);
	oglplus::Vector<float, 4> v2(1.0f, 2.0f, 3.0f, 4.0f);
	oglplus::Vector<float, 4> v3(1.0f, 0.0f, 1.0f, 0.0f);
	oglplus::Vector<float, 4> v4(0.0f, 1.0f, 0.0f, 1.0f);

	BOOST_CHECK_EQUAL(Dot(v0, v1), 0.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v1), 4.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v2), 10.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v3), 2.0f);
	BOOST_CHECK_EQUAL(Dot(v1, v4), 2.0f);
	BOOST_CHECK_EQUAL(Dot(v2, v3), 4.0f);
	BOOST_CHECK_EQUAL(Dot(v2, v4), 6.0f);
	BOOST_CHECK_EQUAL(Dot(v3, v4), 0.0f);
}

BOOST_AUTO_TEST_CASE(vector_perpendicular)
{
	float eps = 1e-4;

	oglplus::Vector<float, 2> v2x(1.0f, 0.0f);
	oglplus::Vector<float, 2> v2y(0.0f, 1.0f);

	BOOST_CHECK(Perpendicular(v2x) == v2y);
	BOOST_CHECK(Perpendicular(v2y) ==-v2x);

	for(unsigned i=0; i!=1000; ++i)
	{
		oglplus::Vector<float, 2> v1(
			(float(std::rand())/RAND_MAX-0.5f),
			(float(std::rand())/RAND_MAX-0.5f)
		);
		oglplus::Vector<float, 2> v2 = Perpendicular(v1);
		BOOST_CHECK_CLOSE(Dot(v1, v2)+2.0, 2.0, eps);
	}
}

BOOST_AUTO_TEST_CASE(vector_cross)
{
	float eps = 1e-4;

	oglplus::Vector<float, 3> v3x(1.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 3> v3y(0.0f, 1.0f, 0.0f);
	oglplus::Vector<float, 3> v3z(0.0f, 0.0f, 1.0f);

	BOOST_CHECK(Cross(v3x, v3y) == v3z);
	BOOST_CHECK(Cross(v3z, v3x) == v3y);
	BOOST_CHECK(Cross(v3y, v3z) == v3x);

	for(unsigned i=0; i!=1000; ++i)
	{
		oglplus::Vector<float, 2> v21(
			(float(std::rand())/RAND_MAX-0.5f),
			(float(std::rand())/RAND_MAX-0.5f)
		);
		oglplus::Vector<float, 2> v22 = Perpendicular(v21);

		oglplus::Vector<float, 3> v1(v21, 0.0);
		oglplus::Vector<float, 3> v2(v22, 0.0);
		oglplus::Vector<float, 3> v3 = Cross(v1, v2);

		BOOST_CHECK_CLOSE(Dot(v1, v2)+2.0, 2.0, eps);
		BOOST_CHECK_CLOSE(Dot(v1, v3)+2.0, 2.0, eps);
		BOOST_CHECK_CLOSE(Dot(v2, v3)+2.0, 2.0, eps);
	}
}

BOOST_AUTO_TEST_CASE(vector_normalized)
{
	float eps = 1e-4;

	for(unsigned i=0; i!=1000; ++i)
	{
		oglplus::Vector<float, 2> v2(
			(float(std::rand())/RAND_MAX-0.5f)*std::rand(),
			(float(std::rand())/RAND_MAX-0.5f)*std::rand()
		);
		oglplus::Vector<float, 2> v2n = Normalized(v2);
		BOOST_CHECK_CLOSE(Dot(v2n, v2n), 1.0, eps);

		oglplus::Vector<float, 3> v3(
			(float(std::rand())/RAND_MAX-0.5f)*std::rand(),
			(float(std::rand())/RAND_MAX-0.5f)*std::rand(),
			(float(std::rand())/RAND_MAX-0.5f)*std::rand()
		);
		oglplus::Vector<float, 3> v3n = Normalized(v3);
		BOOST_CHECK_CLOSE(Dot(v3n, v3n), 1.0, eps);

		oglplus::Vector<float, 4> v4(
			(float(std::rand())/RAND_MAX-0.5f)*std::rand(),
			(float(std::rand())/RAND_MAX-0.5f)*std::rand(),
			(float(std::rand())/RAND_MAX-0.5f)*std::rand(),
			(float(std::rand())/RAND_MAX-0.5f)*std::rand()
		);
		oglplus::Vector<float, 4> v4n = Normalized(v4);
		BOOST_CHECK_CLOSE(Dot(v4n, v4n), 1.0, eps);
	}
}

BOOST_AUTO_TEST_CASE(vector_length_4)
{
	oglplus::Vector<float, 4> v0(0.0f, 0.0f, 0.0f, 0.0f);
	oglplus::Vector<float, 4> v1(1.0f, 1.0f, 1.0f, 1.0f);

	BOOST_CHECK_EQUAL(Length(v0), 0.0f);
	BOOST_CHECK_EQUAL(Length(v1), 2.0f);
}

BOOST_AUTO_TEST_SUITE_END()
