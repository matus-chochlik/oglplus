#  Copyright 2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
HERE := $(PWD)
ROOT = $(shell readlink -f $(HERE)/../..)
XSLTPROC ?= xsltproc
DOXYGEN ?= doxygen

OBJECTS = texture framebuffer renderbuffer buffer

all: bound_hpp clean

bound_hpp: $(addprefix $(ROOT)/include/oglplus/bound/,$(addsuffix .hpp,$(OBJECTS)))

$(ROOT)/include/oglplus/bound/%.hpp: tmp/xml/oglplus.xml bound_hpp.xsl | $(ROOT)/include/oglplus/bound
	$(XSLTPROC) --output $@ \
		--stringparam object $* \
		--stringparam year "$(shell date +%Y)" \
		bound_hpp.xsl \
		tmp/xml/oglplus.xml

tmp/xml/oglplus.xml: tmp/xml/index.xml
	$(XSLTPROC) --output $@ \
		tmp/xml/combine.xslt \
		tmp/xml/index.xml

tmp/xml/index.xml: tmp/Doxyfile
	cd $(ROOT)/doc/doxygen &&\
	$(DOXYGEN) $(HERE)/tmp/Doxyfile

tmp/Doxyfile: Makefile | tmp
	@echo "@INCLUDE = $(ROOT)/doc/doxygen/Doxyfile.autohdr" > $@
	@echo "OUTPUT_DIRECTORY = $(HERE)/tmp" >> $@
	@echo "QUIET = YES" >> $@

tmp $(ROOT)/include/oglplus/bound:
	mkdir -p $@

clean:
	rm -rf tmp

.PHONY: clean
