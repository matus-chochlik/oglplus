/*
 *  .file test/oglplus/fixture_glfw.cpp
 *  Implements GLFW-based test fixture
 *
 *  Copyright 2011-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "fixture.hpp"

#include <GL/glfw.h>

#include <cassert>
#include <stdexcept>

namespace oglplus {

class GLFWTestFixtureBase {
public:
    GLFWTestFixtureBase() {
        if(!glfwInit())
            throw std::runtime_error("GLFW initialization error");
        if(!glfwOpenWindow(128, 128, 8, 8, 8, 8, 32, 8, GLFW_WINDOW))
            throw std::runtime_error("Error creating GLFW window");
        glfwSetWindowTitle("OGLplus test");
    }

    ~GLFWTestFixtureBase() {
        glfwTerminate();
    }
};

class GLFWTestFixture : public GLFWTestFixtureBase {
private:
    oglplus::GLAPIInitializer gl_api_init;

public:
    GLFWTestFixture()
      : GLFWTestFixtureBase() {}
};

TestFixture::TestFixture()
  : _pimpl(static_cast<void*>(new GLFWTestFixture())) {}

TestFixture::TestFixture(TestFixture&& tmp)
  : _pimpl(tmp._pimpl) {
    tmp._pimpl = nullptr;
}

TestFixture::~TestFixture() {
    if(_pimpl)
        delete static_cast<GLFWTestFixture*>(_pimpl);
}

} // namespace oglplus
