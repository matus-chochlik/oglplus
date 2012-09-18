# Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
TOOLS = make_bitmap_font

all: $(TOOLS)

.PHONY: clean
clean:
	rm -f $(TESTS)


.INTERMEDIATE: make_bitmap_font.o
make_bitmap_font.o: make_bitmap_font.cpp
	g++ -c -o $@ $< \
		--std=c++0x \
		-I../include \
		$(shell pkg-config --cflags pango pangocairo)

make_bitmap_font: make_bitmap_font.o
	g++ -o $@ $< \
		--std=c++0x \
		$(shell pkg-config --libs pango pangocairo)

