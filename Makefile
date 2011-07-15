#  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

CXX ?= g++

OGLPLUS_CXXFLAGS = \
	-pedantic \
	-pedantic-errors \
	-std=c++0x \
	-I include \
	$(CXXFLAGS)

OGLPLUS_LDFLAGS = \
	-std=c++0x \
	$(LDFLAGS)

# final output directory
OUTDIR = out
# intermediate output directory
BLDDIR = bld

# the paths of the development/testing files without the .cpp suffix
DEVEL_TESTS = $(basename $(wildcard devel/*.cpp))

# the paths of all executables to be built
EXECUTABLES = $(DEVEL_TESTS)
#
# the list of final and intermediate output subdirectories
OUTSUBDIRS = $(addprefix $(OUTDIR)/, $(sort $(dir $(EXECUTABLES))))
BLDSUBDIRS = $(addprefix $(BLDDIR)/, $(sort $(dir $(EXECUTABLES))))

# build all executables in the output directory
all: $(addprefix $(OUTDIR)/, $(EXECUTABLES));

# build only the development/testing files in the output directory
devel_tests: $(addprefix $(OUTDIR)/, $(DEVEL_TESTS));

# function defining the rules for linking final executables
define BUILD_EXE
$(OUTDIR)/$(1): $(BLDDIR)/$(1).o | $(dir $(OUTDIR)/$(1))
	$(CXX) $(OGLPLUS_LDFLAGS) -o $$@ $$^
endef

# function defining the rules for compiling intermediate objects
define BUILD_OBJ
$(BLDDIR)/$(1).o: $(1).cpp | $(dir $(BLDDIR)/$(1))
	$(CXX) $(OGLPLUS_CXXFLAGS) -o $$@ -c $$<
endef

# function defining the rules for building header dependency makefiles
define BUILD_DEP
$(BLDDIR)/$(1).d: $(1).cpp | $(dir $(BLDDIR)/$(1))
	$(CXX) $(OGLPLUS_CXXFLAGS) -o $$@ -E -MM $$<
	sed --in-place 's|^\([^:]\+\).o:|$(dir $(BLDDIR)/$(1))\1.o $(dir $(BLDDIR)/$(1))\1.d:|' $$@
endef

# use the functions defined above to make the rules
# for building header dependency makefiles,
# compiling and linking of all executables
$(foreach exe,$(EXECUTABLES),$(eval $(call BUILD_EXE,$(exe))))
$(foreach exe,$(EXECUTABLES),$(eval $(call BUILD_OBJ,$(exe))))
$(foreach exe,$(EXECUTABLES),$(eval $(call BUILD_DEP,$(exe))))

# rules to make the final and itermediate output directories
$(OUTDIR) $(BLDDIR):
	mkdir -p $(shell readlink $@ || echo $@)

# rules to make the final and itermediate output sub-directories
$(OUTSUBDIRS): $(OUTDIR); mkdir -p $@
$(BLDSUBDIRS): $(BLDDIR); mkdir -p $@

# TODO: don't do this on cleanup
include $(addsuffix .d,$(addprefix $(BLDDIR)/,$(EXECUTABLES)))

# cleanup
.PHONY: clean
clean: 
	rm -rf $(shell readlink $(OUTDIR) || echo $(OUTDIR))
	rm -rf $(shell readlink $(BLDDIR) || echo $(BLDDIR))
