/*
 *  .file test/oglplus/fixture_sdl.cpp
 *  Implements SDL-based test fixture
 *
 *  Copyright 2011-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "fixture.hpp"

#include <SDL/SDL.h>

#include <cassert>
#include <stdexcept>

namespace oglplus {

class SDLTestFixtureBase {
public:
    SDLTestFixtureBase() {
        if(SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error(SDL_GetError());

        if(!SDL_SetVideoMode(
             128, 128, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) {
            std::runtime_error e(SDL_GetError());
            SDL_Quit();
            throw e;
        }
        SDL_WM_SetCaption("OGLplus test", nullptr);
    }

    ~SDLTestFixtureBase() {
        SDL_Quit();
    }
};

class SDLTestFixture : public SDLTestFixtureBase {
private:
    oglplus::GLAPIInitializer gl_api_init;

public:
    SDLTestFixture()
      : SDLTestFixtureBase() {}
};

TestFixture::TestFixture()
  : _pimpl(static_cast<void*>(new SDLTestFixture())) {}

TestFixture::TestFixture(TestFixture&& tmp)
  : _pimpl(tmp._pimpl) {
    tmp._pimpl = nullptr;
}

TestFixture::~TestFixture() {
    if(_pimpl)
        delete static_cast<SDLTestFixture*>(_pimpl);
}

} // namespace oglplus
