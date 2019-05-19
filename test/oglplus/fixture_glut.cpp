/*
 *  .file test/oglplus/fixture_glut.cpp
 *  Implements GLUT-based test fixture
 *
 *  Copyright 2011-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "fixture.hpp"

#if OGLPLUS_FREEGLUT_FOUND
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

#include <cassert>
#include <stdexcept>

namespace oglplus {

class GLUTTestFixtureBase {
public:
    GLUTTestFixtureBase() {
        int argc = 1;
        char args[2] = {'\0', '\0'};
        char* argv = args;
        glutInit(&argc, &argv);
        glutInitDisplayMode(
          GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
        glutInitWindowSize(128, 128);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("OGLplus test");
    }

    ~GLUTTestFixtureBase() {}
};

class GLUTTestFixture : public GLUTTestFixtureBase {
private:
    oglplus::GLAPIInitializer gl_api_init;

public:
    GLUTTestFixture()
      : GLUTTestFixtureBase() {}
};

TestFixture::TestFixture()
  : _pimpl(static_cast<void*>(new GLUTTestFixture())) {}

TestFixture::TestFixture(TestFixture&& tmp)
  : _pimpl(tmp._pimpl) {
    tmp._pimpl = nullptr;
}

TestFixture::~TestFixture() {
    if(_pimpl)
        delete static_cast<GLUTTestFixture*>(_pimpl);
}

} // namespace oglplus
