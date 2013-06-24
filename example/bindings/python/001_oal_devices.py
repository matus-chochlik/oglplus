#!/usr/bin/python
# coding=utf-8
#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from oalplus import *

# print the audio output devices
print("Devices:")
for dev_spec in Device.Specifiers():
	print('\t'+dev_spec)

# print the audio capture devices
print("Capture devices:")
for dev_spec in Device.CaptureSpecifiers():
	print('\t'+dev_spec)
