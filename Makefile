#  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# This is a simplified version of the main Makefile that builds only
# the examples. It does not contain rules for building automatically
# generated headers, textures, screenshots, the documentation, etc.

CXX ?= g++

# final output directory
OUTDIR = out
# intermediate output directory
BLDDIR = bld
# auto-generated header output directory
HDRDIR = auto_header

# specifies which of the example main function implementations should be used
EXAMPLE_HARNESS = glx
EXAMPLE_HARNESS_LDFLAGS= -lX11

OGLPLUS_CXXFLAGS = \
	$(CXXFLAGS) \
	-pedantic \
	-pedantic-errors \
	-I include \
	-I $(HDRDIR)/include \
	-I example/oglplus \
	-I utils \
	-DOGLPLUS_NO_SITE_CONFIG=1 \
	-std=c++0x

OGLPLUS_LDFLAGS = \
	$(LDFLAGS) \
	$(EXAMPLE_HARNESS_LDFLAGS) \
	-lGL \
	-lpng \
	-std=c++0x

# the paths to the example files without the .cpp suffix
EXAMPLES = $(basename $(wildcard example/oglplus/[0-9][0-9][0-9]_*.cpp))

# the paths of all executables to be built
EXECUTABLES = $(EXAMPLES)
# the paths to the objects that need to be built
OBJECT_SRCS = $(EXECUTABLES) \
	example/oglplus/$(EXAMPLE_HARNESS)_main

# list of bindable objects
BINDABLE_OBJECTS = buffer texture renderbuffer framebuffer

# list of automatically generated headers
AUTO_HEADERS = $(addsuffix .hpp, $(addprefix include/oglplus/bound/, $(BINDABLE_OBJECTS)))

# the list of final and intermediate output subdirectories
OUTSUBDIRS = $(addprefix $(OUTDIR)/, $(sort $(dir $(EXECUTABLES))))

BLDSUBDIRS = $(addprefix $(BLDDIR)/, $(sort $(dir $(OBJECT_SRCS))))

# the main goal
examples_only: $(addprefix $(OUTDIR)/, $(EXAMPLES))

# function defining the rules for linking final executables
define BUILD_EXE
$(OUTDIR)/$(1): \
	$(BLDDIR)/$(1).o \
	$(BLDDIR)/$(dir $(1))$(EXAMPLE_HARNESS)_main.o |\
	$(dir $(OUTDIR)/$(1))
	$(CXX) -o $$@ $$^ $(OGLPLUS_LDFLAGS)
endef

# function defining the rules for compiling intermediate objects
define BUILD_OBJ
$(BLDDIR)/$(1).o: $(1).cpp | $(dir $(BLDDIR)/$(1))
	$(CXX) $(OGLPLUS_CXXFLAGS) -o $$@ -c $$<
endef

# use the functions defined above to make the rules
# for building headers, header dependency makefiles,
# compiling and linking of all executables
$(foreach exe,$(EXECUTABLES), $(eval $(call BUILD_EXE,$(exe))))
$(foreach src,$(OBJECT_SRCS), $(eval $(call BUILD_OBJ,$(src))))


# rules to make the final and itermediate output directories
$(OUTDIR) $(BLDDIR):
	mkdir -p $(shell readlink $@ || echo $@)

# rules to make the final and itermediate output sub-directories
$(OUTSUBDIRS): $(OUTDIR); mkdir -p $@
$(BLDSUBDIRS): $(BLDDIR); mkdir -p $@

# cleanup
.PHONY: clean;

clean:
	rm -rf $(BLDDIR)
	rm -rf $(OUTDIR)/example

all docs examples example_screenshots textures full_clean auto_headers:
	@$(MAKE) -f Makefile.full $@

