/**
 *  @file oglplus/imports/blend_file/range.hpp
 *  @brief Helper CRTP template used as a base class for ranges
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMPORTS_BLEND_FILE_RANGE_1107121519_HPP
#define OGLPLUS_IMPORTS_BLEND_FILE_RANGE_1107121519_HPP

namespace oglplus {
namespace imports {

/// CRTP template used as a base for ranges
template <typename Derived, typename ElementType>
class BlendFileRangeTpl {
private:
    std::size_t _current, _count;

    const Derived& _derived() const {
        return static_cast<const Derived&>(*this);
    }

protected:
    BlendFileRangeTpl(std::size_t count)
      : _current(0)
      , _count(count) {
    }

public:
    /// Number of elements remaining in the range
    std::size_t Size() const {
        return _count - _current;
    }

    /// Returns true if the range is empty
    bool Empty() const {
        return _current == _count;
    }

    /// Moves the front of the range to the next element
    void Next() {
        assert(!Empty());
        ++_current;
    }

    /// Returns the element at the front of the range
    ElementType Front() const {
        assert(!Empty());
        return _derived().Get(_current);
    }

    /// Returns the element at the specified position
    ElementType At(std::size_t position) const {
        assert(_count - _current > position);
        return _derived().Get(_current + position);
    }
};

} // namespace imports
} // namespace oglplus

#endif // include guard
