/**
 *  @file oglplus/os/steady_clock.hpp
 *  @brief Wrapper for OS real time clocks
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef UTILS_OGLPLUS_OS_STEADY_CLOCK_1203040931_HPP
#define UTILS_OGLPLUS_OS_STEADY_CLOCK_1203040931_HPP

#include <oglplus/config/compiler.hpp>

#include <chrono>

namespace oglplus {
namespace os {

// Can be used for measuring time in seconds since the clocks creation
class steady_clock {
private:
    typedef std::chrono::system_clock std_clock;
    std::chrono::time_point<std_clock> _start;

public:
    steady_clock() {
        reset();
    }

    void reset() {
        _start = std_clock::now();
    }

    double seconds() const {
        return double((std_clock::now() - _start).count()) *
               double(std_clock::period::num) / double(std_clock::period::den);
    }
};

} // namespace os
} // namespace oglplus

#endif // include guard
