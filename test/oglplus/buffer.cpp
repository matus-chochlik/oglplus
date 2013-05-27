/**
 *  .file test/oglplus/buffer.cpp
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

BOOST_AUTO_TEST_CASE(Buffer_Bind)
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

BOOST_AUTO_TEST_CASE(Buffer_BindBase_Uniform_1)
{
#if GL_VERSION_3_1 || GL_ARB_uniform_buffer_object
	oglplus::Buffer buffer;
	buffer.Bind(oglplus::Buffer::Target::Uniform);
	GLfloat tmp_data[16] = {0.0f};
	oglplus::Buffer::Data(oglplus::Buffer::Target::Uniform, tmp_data);
	buffer.BindBase(
		oglplus::Buffer::IndexedTarget::Uniform,
		0
	);
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_BindBase_XFB_1)
{
#if GL_VERSION_4_0 || GL_ARB_transform_feedback3
	oglplus::Buffer buffer;
	buffer.Bind(oglplus::Buffer::Target::TransformFeedback);
	GLfloat tmp_data[16] = {0.0f};
	oglplus::Buffer::Data(oglplus::Buffer::Target::TransformFeedback, tmp_data);
	buffer.BindBase(
		oglplus::Buffer::IndexedTarget::TransformFeedback,
		0
	);
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_Uniform_Limit)
{
#if GL_VERSION_3_1 || GL_ARB_uniform_buffer_object
	oglplus::UniformBufferBindingPoint ubp = 0;
	for(GLuint i=0; i!=oglplus::LimitedCountMax(ubp); ++i)
		oglplus::UniformBufferBindingPoint ubp = i;
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_XFB_Limit)
{
#if GL_VERSION_4_0 || GL_ARB_transform_feedback3
	oglplus::TransformFeedbackBufferBindingPoint tfbbp = 0;
	for(GLuint i=0; i!=oglplus::LimitedCountMax(tfbbp); ++i)
		oglplus::TransformFeedbackBufferBindingPoint tfbbp = i;
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_AtomicCounter_Limit)
{
#if GL_VERSION_4_2 || GL_ARB_shader_atomic_counters
	oglplus::AtomicCounterBufferBindingPoint acbp = 0;
	for(GLuint i=0; i!=oglplus::LimitedCountMax(acbp); ++i)
		oglplus::AtomicCounterBufferBindingPoint acbp = i;
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_ShaderStorage_Limit)
{
#if GL_VERSION_4_3 || GL_ARB_shader_storage_buffer_object
	oglplus::ShaderStorageBufferBindingPoint ssbp = 0;
	for(GLuint i=0; i!=oglplus::LimitedCountMax(ssbp); ++i)
		oglplus::ShaderStorageBufferBindingPoint ssbp = i;
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_BindBase_Uniform_2)
{
#if GL_VERSION_3_1 || GL_ARB_uniform_buffer_object
	oglplus::Buffer buffer;
	buffer.Bind(oglplus::Buffer::Target::Uniform);
	GLfloat tmp_data[16] = {0.0f};
	oglplus::Buffer::Data(oglplus::Buffer::Target::Uniform, tmp_data);
	oglplus::UniformBufferBindingPoint ubp = 0;
	for(GLuint i=0; i!=oglplus::LimitedCountMax(ubp); ++i)
		buffer.BindBaseUniform(i);
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_BindBase_XFB_2)
{
#if GL_VERSION_4_0 || GL_ARB_transform_feedback3
	oglplus::Buffer buffer;
	buffer.Bind(oglplus::Buffer::Target::TransformFeedback);
	GLfloat tmp_data[16] = {0.0f};
	oglplus::Buffer::Data(oglplus::Buffer::Target::TransformFeedback, tmp_data);
	oglplus::TransformFeedbackBufferBindingPoint tfbbp = 0;
	for(GLuint i=0; i!=oglplus::LimitedCountMax(tfbbp); ++i)
		buffer.BindBaseTransformFeedback(i);
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_BindBase_AtomicCounter_2)
{
#if GL_VERSION_4_2 || GL_ARB_shader_atomic_counters
	oglplus::Buffer buffer;
	buffer.Bind(oglplus::Buffer::Target::AtomicCounter);
	GLfloat tmp_data[16] = {0.0f};
	oglplus::Buffer::Data(oglplus::Buffer::Target::AtomicCounter, tmp_data);
	oglplus::AtomicCounterBufferBindingPoint acbp = 0;
	for(GLuint i=0; i!=oglplus::LimitedCountMax(acbp); ++i)
		buffer.BindBaseAtomicCounter(i);
#endif
}

BOOST_AUTO_TEST_CASE(Buffer_BindBase_ShaderStorage_2)
{
#if GL_VERSION_4_3 || GL_ARB_shader_storage_buffer_object
	oglplus::Buffer buffer;
	buffer.Bind(oglplus::Buffer::Target::ShaderStorage);
	GLfloat tmp_data[16] = {0.0f};
	oglplus::Buffer::Data(oglplus::Buffer::Target::ShaderStorage, tmp_data);
	oglplus::ShaderStorageBufferBindingPoint ssbp = 0;
	for(GLuint i=0; i!=oglplus::LimitedCountMax(ssbp); ++i)
		oglplus::ShaderStorageBufferBindingPoint ssbp = i;
#endif
}

BOOST_AUTO_TEST_SUITE_END()
