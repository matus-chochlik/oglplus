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
def open_svg_tag(width, height, slice_no):
	print('<svg xmlns="http://www.w3.org/2000/svg"');
	print('     width="' + str(width) + '"');
	print('     height="' + str(height) + '"');
	print('     id="slice' + str(slice_no) + '"');
	print('     version="1.1"');
	print('>');

# closes the svg file tag
def close_svg_tag():
	print('</svg>');

# opens the text tag
def open_text_tag(style):
	print('<text x="0.0" y="0.0" id="glyphs"');
	print('      style="' + str(style) + '"');
	print('>');

# closes the text tag
def close_text_tag():
	print('</text>');

def is_printable(cp):
	return cp > 31;

def make_glyphs(width, height, slice_no):
	s = 16;
	k = width / s;
	l = height/ s;
	for j in xrange(0, s):
		for i in xrange(0, s):
			cp = slice_no*s*s + j*s + i; 
			if is_printable(cp):
				hcp = format(cp, '04X');
				x = i*k;
				y = j*l;
				print('<tspan id="u'+hcp+'" x="'+str(x)+'.0" y="'+str(y)+'.0">&#x'+hcp+';</tspan>');

# default parameters
width=512;
height=512;
slice_no=3;
style='font-size:32px;font-family:Courier;';

# make the svg source
print_xml_header();
open_svg_tag(width, height, slice_no);
open_text_tag(style);
make_glyphs(width, height, slice_no);
close_text_tag();
close_svg_tag();
