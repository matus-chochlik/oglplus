/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_object_Array

template <typename Object>
class Array;
{
public:
    Array(const Array&) = delete;
    Array(Array &&);

    Array(std::size_t count); /*<
    Constructs an an array of [^count] instances of Object.
    >*/

    Array(std::size_t n, typename __ObjectSubtype<__ObjTag>::Type type); /*<
    Constructs an an array of [^n] instances of Object with
    the specified [^type]
    >*/

    ~Array();

    bool empty() const; /*<
    Returns true if the array is empty.
    >*/

    std::size_t size() const; /*<
    Returns the number of instances in the array.
    >*/

    using reference = __Reference<__Object>;
    using const_reference = const reference;

    reference operator[](std::size_t index); /*<
    Returns a reference to the i-th instance in the array.
    >*/

    const_reference operator[](std::size_t index) const; /*<
    Returns a const reference to the i-th instance in the array.
    >*/

    using iterator = __SeqIterator<__Object>;
    using const_iterator = iterator;

    const_iterator begin() const; /*<
    Returns an iterator pointing to the first element.
    >*/
    const_iterator end() const; /*<
    Returns an iterator pointing past the last element.
    >*/

    __Sequence<__ObjectName<__ObjTag>> seq() const;

    operator __Sequence<__ObjectName<__ObjTag>>() const; /*<
   Implicit conversion to a sequence of object names, which can
   be passed as an argument to various functions.
   Note that the returned sequence must not be used after
   this array has been destroyed.
   >*/
};

//]
