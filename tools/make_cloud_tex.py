#!/usr/bin/python
# Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
import sys;

# prints the xml processing instruction header
def print_xml_header():
	print('<?xml version="1.0" encoding="UTF-8" standalone="no"?>');

# opens the svg file tag
def open_svg_tag(width, height):
	print('<svg xmlns="http://www.w3.org/2000/svg"');
	print('  width="' + str(width) + '"');
	print('  height="' + str(height) + '"');
	print('  id="sliceTex"');
	print('  version="1.1"');
	print('>');

def close_svg_tag():
	print('</svg>');

def open_defs_tag():
	print('<defs id="defsCloud">');

def close_defs_tag():
	print('</defs>');

def open_group_tag(style):
	print('<g id="cloud style="' + str(style) + '">');

def close_group_tag():
	print('</g>');

# make a linear gradient
# stops is a list of tuples (offset, opacity)
def make_lgradient(gid, stops):
	print('<linearGradient');
	print('  id="lgrad' + str(gid) + '">');
	sid=0;
	for stop in stops:
		print('<stop');
		print('  id="stop-' + str(gid) + '-' + str(sid) + '"');
		print('  style="stop-color:#ffffff;stop-opacity:'+str(stop[1])+'"');
		print('  offset="' + str(stop[0]) + '"');
		print('/>');
		sid = sid+1;
	print('</linearGradient>');
# make ellipse
def make_ellipse(eid, x, y, r, w, h):
	print('<ellipse id="' + str(eid) + '"');
	print('  cx="' + str(x*w) + '"');
	print('  cy="' + str(y*h) + '"');
	print('  rx="' + str(r*w) + '"');
	print('  ry="' + str(r*h) + '"');
	print('  style="fill:url(#radialGradient'+str(eid)+');"');
	print('/>');

# default parameters
width=512;
height=512;
style='fill:white;fill-opacity:0.5;';
x=0.5;
y=0.2;

# make the svg source
print_xml_header();
open_svg_tag(width, height);
open_defs_tag();
make_lgradient(0, [(0.0, 1.0),(0.5, 1.0), (0.75, 0.75), (1.0, 0.5)]);
close_defs_tag();
open_group_tag(style);
close_group_tag();
close_svg_tag();
