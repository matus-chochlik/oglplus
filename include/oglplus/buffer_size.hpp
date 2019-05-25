/**
 *  @file oglplus/buffer_size.hpp
 *  @brief Object representing Buffer's storage size in bytes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_SIZE_1310102147_HPP
#define OGLPLUS_BUFFER_SIZE_1310102147_HPP

#include <oglplus/size_type.hpp>
#include <array>
#include <vector>

namespace oglplus {

/// This class represents the size of a GPU buffer in bytes
class BufferSize {
private:
    BigSizeType _v;

public:
    /// Construction of zero size
    BufferSize() noexcept
      : _v(0) {
    }

    /// Construction of the specified size in bytes
    BufferSize(GLsizeiptr size)
      : _v(size) {
    }

#if !OGLPLUS_LOW_PROFILE
    BufferSize(BigSizeType size)
      : _v(size) {
    }

    BufferSize(SizeType size)
      : _v(size) {
    }
#endif

    inline operator BigSizeType() const noexcept {
        return _v;
    }

    template <typename T>
    explicit operator T() const {
        return T(_v);
    }

    template <typename T>
    BufferSize(std::size_t count, const T*) noexcept
      : _v(GLsizeiptr(sizeof(T) * count)) {
    }

    template <typename T, std::size_t N>
    BufferSize(const T (&)[N]) noexcept
      : _v(GLsizeiptr(sizeof(T) * N)) {
    }

    template <typename T, std::size_t N>
    BufferSize(const std::array<T, N>& a) noexcept
      : _v(GLsizeiptr(sizeof(T) * a.size())) {
    }

    template <typename T>
    BufferSize(const std::vector<T>& v) noexcept
      : _v(GLsizeiptr(sizeof(T) * v.size())) {
    }

    /// Gets the size in bytes
    GLsizeiptr Get() const noexcept {
        return GLsizeiptr(_v);
    }

    /// Makes the size of count instances of T
    template <typename T>
    static BufferSize Of(std::size_t count, const T* data = nullptr) {
        return BufferSize(count, data);
    }

    /// Add the size of count instances of T
    template <typename T>
    BufferSize Add(std::size_t count, const T* = nullptr) const {
        return BufferSize(Get() + sizeof(T) * count);
    }

    BufferSize Add(const BufferSize& bs) const {
        return BufferSize(Get() + bs.Get());
    }
};

template <typename Type>
class BufferTypedSize : public BufferSize {
public:
    BufferTypedSize() {
    }

    BufferTypedSize(BigSizeType count)
      : BufferSize(std::size_t(count), &TypeTag<Type>()) {
    }
};

} // namespace oglplus

#endif // include guard
