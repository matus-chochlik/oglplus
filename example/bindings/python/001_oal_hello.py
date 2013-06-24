#!/usr/bin/python
# coding=utf-8
#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from oalplus import *
import time

# open the default device
device = Device()

# create context and make it current
oal = CurrentContext(device)

# create an instance of ALUT
alut = ALUtilityToolkit(False)

# create a listener
listener = Listener()
listener.Position(Vec3f(0.0, 0.0, 0.0))
listener.Velocity(Vec3f(0.0, 0.0, 0.0))
listener.Orientation(Vec3f(0.0, 0.0,-1.0), Vec3f(0.0, 1.0, 0.0))

# let ALUT create a buffer with sound data
sndbuf = alut.CreateBufferHelloWorld()

# create a source from the data in the buffer and set its position
source = Source()
source.Buffer(sndbuf)
source.Position(Vec3f(0.0, 0.0,-1.0))
# play the sound
source.Play()
# wait for a couple of seconds
time.sleep(2)
