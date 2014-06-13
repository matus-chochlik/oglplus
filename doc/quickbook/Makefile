#  Copyright 2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

.PHONY: all

all: html/index.html

.PHONY: clean

clean:
	rm -r bin/ html/

html/images:
	mkdir -p $@

images/%.png: images/%.svg
	inkscape --export-png=$@ -w 32 -h 32 $<

html/images/%.png: images/%.png | html/images
	cp $< $@

.PHONY: html_images

html_images:

html/%.css: %.css
	cp $< $@

.PHONY: html_css

html_css:

html/index.html: html_images html_css
	bjam
