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
	-lGL \
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

all: $(addprefix $(OUTDIR)/, $(EXECUTABLES));

# build only the development/testing files in the output directory
devel_tests: $(addprefix $(OUTDIR)/, $(DEVEL_TESTS));


# helper function returning the third argument if the second argument
# is found at least once in the dependency file specified by the first parameter
OPT_ADD_HDRDEP = $$(shell grep -c -e"$(2)" $(1).d | sed -n "s|[1-9][0-9]*|$(3)|p")

# function defining the rules for linking final executables
define BUILD_EXE
$(OUTDIR)/$(1): $(BLDDIR)/$(1).o | $(dir $(OUTDIR)/$(1))
	$(eval OGLPLUS_TGT_LDFLAGS := $(OGLPLUS_LDFLAGS))
	$(eval OGLPLUS_TGT_LDFLAGS += $$(call OPT_ADD_HDRDEP,$(BLDDIR)/$(1),X11/Xlib.h,-lX11)) 
	$(CXX) $(OGLPLUS_TGT_LDFLAGS) -o $$@ $$^
endef

# function defining the rules for compiling intermediate objects
define BUILD_OBJ
$(BLDDIR)/$(1).o: $(1).cpp | $(dir $(BLDDIR)/$(1))
	$(eval OGLPLUS_TGT_CXXFLAGS := $(OGLPLUS_CXXFLAGS))
	$(CXX) $(OGLPLUS_TGT_CXXFLAGS) -o $$@ -c $$<
endef

# helper sed script used in the BUILD_DEP function
OGLPLUS_MAKEDEP_SED = 's|^\([^:]\+\).o:|$(dir $(BLDDIR)/$(1))\1.o $(dir $(BLDDIR)/$(1))\1.d:|'

# function defining the rules for building header dependency makefiles
define BUILD_DEP
$(BLDDIR)/$(1).d: $(1).cpp | $(dir $(BLDDIR)/$(1))
	@$(CXX) $(OGLPLUS_CXXFLAGS) -o $$@ -E -M $$<
	@sed --in-place $(OGLPLUS_MAKEDEP_SED) $$@
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

# if we are not doing cleanup
ifneq ($(MAKECMDGOALS),clean)
# include the header dependency rules
include $(addsuffix .d,$(addprefix $(BLDDIR)/,$(EXECUTABLES)))
endif

# cleanup
.PHONY: clean
clean: 
	rm -rf $(shell readlink $(OUTDIR) || echo $(OUTDIR))
	rm -rf $(shell readlink $(BLDDIR) || echo $(BLDDIR))
