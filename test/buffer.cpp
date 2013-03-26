/**
 *  .file test/buffer.cpp
 *  .brief Test case for Buffer class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2011-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE OGLPLUS_Buffer
#include <boost/test/unit_test.hpp>
#include "test.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/buffer.hpp>

#include "fixture.hpp"

BOOST_GLOBAL_FIXTURE(OGLplusTestFixture)

BOOST_AUTO_TEST_SUITE(Buffer)

BOOST_AUTO_TEST_CASE(Buffer_default_construction)
{
	oglplus::Buffer buffer;
}

BOOST_AUTO_TEST_CASE(Buffer_binding)
{
	oglplus::Buffer buffer;
	buffer.Bind(oglplus::Buffer::Target::Array);
	oglplus::Buffer::Unbind(oglplus::Buffer::Target::Array);
	buffer.Bind(oglplus::Buffer::Target::ElementArray);
	oglplus::Buffer::Unbind(oglplus::Buffer::Target::ElementArray);
	buffer.Bind(oglplus::Buffer::Target::Uniform);
	oglplus::Buffer::Unbind(oglplus::Buffer::Target::Uniform);
	buffer.Bind(oglplus::Buffer::Target::CopyRead);
	oglplus::Buffer::Unbind(oglplus::Buffer::Target::CopyRead);
	buffer.Bind(oglplus::Buffer::Target::CopyWrite);
	oglplus::Buffer::Unbind(oglplus::Buffer::Target::CopyWrite);
}

BOOST_AUTO_TEST_SUITE_END()
