/**
 *  .file oglplus/detail/base_range.hpp
 *  .brief Base class for ranges
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_BASE_RANGE_1107121519_HPP
#define OGLPLUS_AUX_BASE_RANGE_1107121519_HPP

#include <cassert>
#include <iterator>
#include <type_traits>
#include <vector>

namespace oglplus {
namespace aux {

template <class Range>
std::true_type IsRange(
  const Range*,
  bool (Range::*)() const = &Range::Empty,
  std::size_t (Range::*)() const = &Range::Size,
  void (Range::*)() = &Range::Next,
  typename Range::ValueType (Range::*)() const = &Range::Front);

std::false_type IsRange(...);

template <typename Context, typename Element>
class ContextElementRange {
private:
    Context _context;
    unsigned _current, _count;

public:
    using ValueType = Element;

    ContextElementRange(Context&& context, unsigned current, unsigned count)
      : _context(std::move(context))
      , _current(current)
      , _count(count) {
        assert(current <= count);
    }

    ContextElementRange(Context&& context, unsigned count)
      : _context(std::move(context))
      , _current(0)
      , _count(count) {}

    ContextElementRange(ContextElementRange&& tmp)
      : _context(std::move(tmp._context))
      , _current(tmp._current)
      , _count(tmp._count) {}

    bool Empty() const {
        return _current == _count;
    }

    std::size_t Size() const {
        return _count - _current;
    }

    void Next() {
        assert(!Empty());
        ++_current;
    }

    ValueType Front() {
        assert(!Empty());
        return Element(_context, _current);
    }

    ValueType At(std::size_t offset) {
        assert(offset < Size());
        return Element(_context, _current + offset);
    }
};

template <typename Iterator>
class IterRange {
private:
    Iterator _pos, _end;

public:
    using ValueType = const typename std::iterator_traits<Iterator>::reference;

    IterRange(Iterator begin, Iterator end)
      : _pos(begin)
      , _end(end) {}

    bool Empty() const {
        return _pos == _end;
    }

    std::size_t Size() const {
        return _end - _pos;
    }

    void Next() {
        assert(!Empty());
        ++_pos;
    }

    ValueType Front() const {
        assert(!Empty());
        return *_pos;
    }
};

template <typename Iterator, typename Element>
class CastIterRange : public IterRange<Iterator> {
public:
    using ValueType = Element;

    CastIterRange(Iterator begin, Iterator end)
      : IterRange<Iterator>(begin, end) {}

    ValueType Front() const {
        return Element(IterRange<Iterator>::Front());
    }
};

template <typename Iterator, typename Element, typename Converter>
class ConvIterRange : public IterRange<Iterator> {
private:
    Converter _conv;

public:
    using ValueType = Element;

    ConvIterRange(Converter conv, Iterator begin, Iterator end)
      : IterRange<Iterator>(begin, end)
      , _conv(conv) {}

    Element Front() const {
        return _conv(IterRange<Iterator>::Front());
    }
};

template <typename Element>
class ArrayRange
  : public CastIterRange<std::vector<unsigned>::const_iterator, Element> {
private:
    using iterator = std::vector<unsigned>::const_iterator;
    using _base = CastIterRange<iterator, Element>;

public:
    ArrayRange(iterator i, iterator e)
      : _base(i, e) {}
};

} // namespace aux
} // namespace oglplus

#endif // include guard
