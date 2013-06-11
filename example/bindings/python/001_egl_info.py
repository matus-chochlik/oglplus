#!/usr/bin/python
# coding=utf-8
#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from eglplus import *

# open the default display
display = Display()

# initialize EGL
egl = LibEGL(display)

# print some info
print("Vendor: " + egl.Vendor())
print("Version: " + egl.Version())

print("Client APIs:")
for api in egl.ClientAPIs():
	print("\t"+api)

print("Extensions:")
for ext in egl.Extensions():
	print("\t"+ext)

