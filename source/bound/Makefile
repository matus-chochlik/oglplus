#  Copyright 2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
HERE := $(PWD)
ROOT = $(shell readlink -f $(HERE)/../..)
INCDIR = $(ROOT)/include/oglplus
QRFDIR = $(ROOT)/doc/quickbook/oglplus/quickref

XSLTPROC ?= xsltproc
DOXYGEN ?= doxygen

OBJECTS = texture framebuffer renderbuffer buffer

all: bound_inc_hpp bound_doc_hpp

bound_inc_hpp: $(addprefix $(INCDIR)/bound/,$(addsuffix .hpp,$(OBJECTS)))

$(INCDIR)/bound/%.hpp: tmp/xml/oglplus.xml bound_inc_hpp.xsl | $(INCDIR)/bound
	$(XSLTPROC) --output $@ \
		--stringparam object $* \
		--stringparam year "$(shell date +%Y)" \
		bound_inc_hpp.xsl \
		tmp/xml/oglplus.xml

bound_doc_hpp: $(addprefix $(QRFDIR)/bound/,$(addsuffix .hpp,$(OBJECTS)))

$(QRFDIR)/bound/%.hpp: tmp/xml/oglplus.xml bound_doc_hpp.xsl | $(QRFDIR)/bound
	$(XSLTPROC) --output $@ \
		--stringparam object $* \
		--stringparam year "$(shell date +%Y)" \
		bound_doc_hpp.xsl \
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

tmp $(INCDIR)/bound $(QRFDIR)/bound:
	mkdir -p $@

clean:
	rm -rf tmp

.PHONY: clean
