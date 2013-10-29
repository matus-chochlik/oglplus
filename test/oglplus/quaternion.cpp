/**
 *  .file test/oglplus/quaternion.cpp
 *  .brief Test case for Quaternion class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2011-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE OGLPLUS_Quaternion
#include <boost/test/unit_test.hpp>

#include <oglplus/gl.hpp>
#include <oglplus/quaternion.hpp>

BOOST_AUTO_TEST_SUITE(Quaternion)

BOOST_AUTO_TEST_CASE(Quaternion_construction)
{
	typedef oglplus::Quaternion<float> Quatf;
	Quatf q1(1, 0, 0, 0);
	Quatf q2(oglplus::Vec3f::Unit(0), oglplus::Degrees(45));
	Quatf q3(0, oglplus::Vec3f::Unit(1));
	Quatf q4 = q3;
}

BOOST_AUTO_TEST_CASE(Quaternion_real_imag)
{
	typedef oglplus::Quaternion<float> Quatf;
	Quatf q(1, 2, 3, 4);

	BOOST_CHECK(q.Real() == 1);
	BOOST_CHECK(q.Imag().x() == 2);
	BOOST_CHECK(q.Imag().y() == 3);
	BOOST_CHECK(q.Imag().z() == 4);
}

BOOST_AUTO_TEST_CASE(Quaternion_equality)
{
	typedef oglplus::Quaternion<float> Quatf;
	Quatf q1(1, 0, 0, 0);
	Quatf q2 = q1;
	Quatf q3(1, 2, 3, 4);

	BOOST_CHECK(Equal(q1, q2));
	BOOST_CHECK(Equal(q2, q1));
	BOOST_CHECK(q1 == q2);
	BOOST_CHECK(q2 == q1);

	BOOST_CHECK(!Equal(q1, q3));
	BOOST_CHECK(!Equal(q3, q2));
	BOOST_CHECK(q1 != q3);
	BOOST_CHECK(q3 != q2);
}

BOOST_AUTO_TEST_SUITE_END()
