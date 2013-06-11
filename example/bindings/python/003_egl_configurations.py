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

# make a list of all configurations
configs = Configs(
	display,
	ConfigAttribs()
		.Add(ConfigAttrib.RedSize, 8)
		.Add(ConfigAttrib.GreenSize, 8)
		.Add(ConfigAttrib.BlueSize, 8)
		.Add(ConfigAttrib.AlphaSize, 8)
		.Add(ConfigAttrib.DepthSize, 32)
		.Add(ConfigAttrib.StencilSize, 8)
		.Add(ColorBufferType.RGBBuffer)
		.Add(RenderableTypeBit.OpenGL)
		.Get()
)

for config in configs.All():
	print("Config Id = %d" % config.Id())
	print("\tRedSize:                     %18d" % config.RedSize())
	print("\tGreenSize:                   %18d" % config.GreenSize())
	print("\tBlueSize:                    %18d" % config.BlueSize())
	print("\tAlphaSize:                   %18d" % config.AlphaSize())
	print("\tDepthSize:                   %18d" % config.DepthSize())
	print("\tStencilSize:                 %18d" % config.StencilSize())
	print("\tMax Pbuffer width:           %18d" % config.MaxPbufferWidth())
	print("\tMax Pbuffer height:          %18d" % config.MaxPbufferHeight())
	print("\tMax Pbuffer pixels:          %18d" % config.MaxPbufferPixels())
	print("\tConfig caveat:               %18s" % EnumValueName(config.ConfigCaveat()))
	print("\tColor buffer type:           %18s" % EnumValueName(config.ColorBufferType()))
	print("\tTransparent type:            %18s" % EnumValueName(config.TransparentType()))

	print("\tRenderable types:")
	for rt in EnumValueRange(RenderableTypeBit()):
		if config.HasRenderableType(rt):
			print("\t         %38s" % EnumValueName(rt))

	print("\tSurface types:")
	for st in EnumValueRange(SurfaceTypeBit()):
		if config.HasSurfaceType(st):
			print("\t         %38s" % EnumValueName(st))

	print("\tConformant to:")
	for rt in EnumValueRange(RenderableTypeBit()):
		if config.IsConformantTo(rt):
			print("\t         %38s" % EnumValueName(rt))
	print("-------------------------------------------------------")

