#  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

CXX ?= g++

OGLPLUS_CXXFLAGS = \
	-pedantic \
	-pedantic-errors \
	-std=c++0x \
	-I include \
	-I utils \
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

# the paths to the example files without the .cpp suffix
EXAMPLES = $(basename $(wildcard example/oglplus/[0-9][0-9][0-9]_*.cpp))

# specifies which of the example main function implementations should be used
EXAMPLE_HARNESS = glx

# the paths of all executables to be built
EXECUTABLES = $(DEVEL_TESTS) $(EXAMPLES)
# the paths to the objects that need to be built
OBJECT_SRCS = $(EXECUTABLES) \
	example/oglplus/$(EXAMPLE_HARNESS)_main
#
LIBRARIES = oglplus
#
# the list of doxygen-generated html documents
HTML_DOCS = $(addsuffix /html/index.html,$(addprefix doc/doxygen/,$(LIBRARIES)))
#
# the list of final and intermediate output subdirectories
OUTSUBDIRS = \
	$(addprefix $(OUTDIR)/, $(sort $(dir $(EXECUTABLES)))) \
	$(addprefix $(OUTDIR)/, $(sort $(dir $(HTML_DOCS))))

BLDSUBDIRS = \
	$(addprefix $(BLDDIR)/, $(sort $(dir $(OBJECT_SRCS)))) \
	$(addprefix $(BLDDIR)/, $(sort $(dir $(HTML_DOCS))))

# the main goal
all: $(addprefix $(OUTDIR)/, $(EXAMPLES) $(DEVEL_TESTS))

# build only the development/testing files in the output directory
devel_tests: $(addprefix $(OUTDIR)/, $(DEVEL_TESTS));

docs: html_docs;
html_docs: example_screenshots $(addprefix $(OUTDIR)/, $(HTML_DOCS));

example_screenshots: $(addsuffix .png,$(addprefix $(BLDDIR)/, $(EXAMPLES)))

# helper function returning the third argument if the second argument
# is found at least once in the dependency file specified by the first parameter
OPT_ADD_HDRDEP = $$(shell grep -c -e"$(2)" $(1).d | sed -n "s|[1-9][0-9]*|$(3)|p")

# helper function adding the object file implementing the main function
# for an example if necessary
# it uses the presence of the @example tag in the documentation comment
# as an indicator whether the example should be linked
OPT_ADD_EXAMPLE_MAIN = $$(shell grep -c -e"@example" $(1).cpp | sed -n "s|1|$(BLDDIR)/$(dir $(1))$(EXAMPLE_HARNESS)_main.o|p")

# rule for making raw xwd screenshots of an example application
$(BLDDIR)/%.xwd: $(OUTDIR)/% | $(dir $(BLDDIR)/%.xwd)
	./tools/make_screenshot.sh $< $@

# function defining the rules for making the example application window screenshots
define BUILD_PNG
$(BLDDIR)/$(1).png: $(BLDDIR)/$(1).xwd | $(dir $(BLDDIR)/$(1))
	convert -adaptive-resize 400x300 $$< $$@
endef

# function defining the rules for linking final executables
	#$(eval OGLPLUS_TGT_LDFLAGS += $$(shell cat $$(addsuffix .ldf,$$(addprefix $(BLDDIR)/,$$(basename $$^)))))
define BUILD_EXE
$(OUTDIR)/$(1): $(BLDDIR)/$(1).o $(call OPT_ADD_EXAMPLE_MAIN,$(1)) | $(dir $(OUTDIR)/$(1))
	$(CXX) $$(shell cat $$(addsuffix .ldf,$$(basename $$^))) $(OGLPLUS_LDFLAGS) -o $$@ $$^
endef

# function defining the rules for compiling intermediate objects
define BUILD_OBJ
$(BLDDIR)/$(1).o: $(1).cpp $(BLDDIR)/$(1).ldf | $(dir $(BLDDIR)/$(1))
	$(eval OGLPLUS_TGT_CXXFLAGS := $(OGLPLUS_CXXFLAGS))
	$(eval OGLPLUS_TGT_CXXFLAGS += $$(call OPT_ADD_HDRDEP,$(BLDDIR)/$(1),oglplus/example.h,-Iexample/oglplus))
	$(CXX) $(OGLPLUS_TGT_CXXFLAGS) -o $$@ -c $$<
endef

# function defining the rules for making the files containing
# necessary additional LDFLAGS based on the included headers
# of a source file
# these files are used when linking the final executable
# to supply the additional LDFLAGS
define BUILD_LDF
$(BLDDIR)/$(1).ldf: $(BLDDIR)/$(1).d | $(dir $(BLDDIR)/$(1))
	$(eval OGLPLUS_TMP_LDFLAGS :=)
	$(eval OGLPLUS_TMP_LDFLAGS +=$$(call OPT_ADD_HDRDEP,$(BLDDIR)/$(1),X11/Xlib.h,-lX11))
	echo "$(OGLPLUS_TMP_LDFLAGS)" > $$@
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
$(foreach exe,$(EXAMPLES),   $(eval $(call BUILD_PNG,$(exe))))
$(foreach exe,$(EXECUTABLES),$(eval $(call BUILD_EXE,$(exe))))
$(foreach src,$(OBJECT_SRCS),$(eval $(call BUILD_LDF,$(src))))
$(foreach src,$(OBJECT_SRCS),$(eval $(call BUILD_OBJ,$(src))))
$(foreach src,$(OBJECT_SRCS),$(eval $(call BUILD_DEP,$(src))))

# build dependencies for doxygen HTML documentation
$(BLDDIR)/doc/doxygen/%/html/index.html.d: | $(BLDDIR)/doc/doxygen/%/html $(OUTDIR)/doc/doxygen/%/html
	@echo "$(OUTDIR)/doc/doxygen/$*/html/index.html $@: \\" > $@
	@find include/$* example/$* -type f -name '*.[ch]pp' 2> /dev/null |\
	sed 's|\(^.*$$\)|	\1|' |\
	sed '$$!s|\(^.*$$\)|\1 \\|' >> $@

#build the doxygen html documentation
$(OUTDIR)/doc/doxygen/%/html/index.html: $(wildcard doc/doxygen/Doxyfile.*)
	cd doc/doxygen && (cat Doxyfile.$* && echo "QUIET=YES") | doxygen -

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
include $(addsuffix .d,$(addprefix $(BLDDIR)/,$(HTML_DOCS)))
endif

# cleanup
.PHONY: clean
clean:
	rm -rf $(shell readlink $(OUTDIR) || echo $(OUTDIR))
	rm -rf $(shell readlink $(BLDDIR) || echo $(BLDDIR))
