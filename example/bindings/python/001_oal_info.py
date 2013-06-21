#!/usr/bin/python
# coding=utf-8
#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from oalplus import *

# open the default device
device = Device()

# create context and make it current
oal = CurrentContext(device)

# print some info
print("Vendor: " + oal.Vendor())
print("Version: " + oal.Version())
print("Renderer: " + oal.Renderer())

print("Extensions:")
for ext in oal.Extensions():
	print("\t"+ext)

