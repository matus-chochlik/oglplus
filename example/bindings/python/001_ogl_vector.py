#!/usr/bin/python
# coding=utf-8
#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from oglplus import *

v1x = Vec1f(1)

v2x = Vec2f(1, 0)
v2y = Vec2f(0, 1)

v3x = Vec3f(1, 0, 0)
v3y = Vec3f(0, 1, 0)
v3z = Vec3f(0, 0, 1)

v4x = Vec4f(1, 0, 0, 0)
v4y = Vec4f(0, 1, 0, 0)
v4z = Vec4f(0, 0, 1, 0)
v4w = Vec4f(0, 0, 0, 1)

v1 = Vec1f(1)
v12 = Vec2f(1, 2)
v123 = Vec3f(v12, 3)
v1234 = Vec4f(v123, 4)

assert(v1.Size() == 1)
assert(v1.Size() == Size(v1))

assert(v12.Size() == 2)
assert(v12.Size() == Size(v12))

assert(v123.Size() == 3)
assert(v123.Size() == Size(v123))

assert(v1234.Size() == 4)
assert(v1234.Size() == Size(v1234))

print(Length(Normalized(v1)))
print(Length(Normalized(v12)))
print(Length(Normalized(v123)))
print(Length(Normalized(v1234)))

