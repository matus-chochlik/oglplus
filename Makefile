#  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

CXX ?= g++

# final output directory
OUTDIR = out
# intermediate output directory
BLDDIR = bld
# auto-generated header output directory
HDRDIR = auto_header

OGLPLUS_CXXFLAGS = \
	$(CXXFLAGS) \
	-pedantic \
	-pedantic-errors \
	-I include \
	-I $(HDRDIR)/include \
	-I utils \
	-std=c++0x

OGLPLUS_LDFLAGS = \
	$(LDFLAGS) \
	-lGL \
	-std=c++0x

# the paths of the development/testing files without the .cpp suffix
DEVEL_TESTS = $(basename $(wildcard devel/test[0-9][0-9].cpp))

# the paths to the example files without the .cpp suffix
EXAMPLES = $(basename $(wildcard example/oglplus/[0-9][0-9][0-9]_*.cpp))

# the paths to the SVG texture source files without the suffix
SVG_TEXTURES = $(addprefix textures/,$(notdir $(basename $(wildcard source/textures/*.svg))))

# specifies which of the example main function implementations should be used
EXAMPLE_HARNESS = glx

# the paths of all executables to be built
EXECUTABLES = $(DEVEL_TESTS) $(EXAMPLES)
# the paths to the objects that need to be built
OBJECT_SRCS = $(EXECUTABLES) \
	example/oglplus/$(EXAMPLE_HARNESS)_main \
	devel/test_main
#
LIBRARIES = oglplus

# list of bindable objects
BINDABLE_OBJECTS = buffer texture

# list of automatically generated headers
AUTO_HEADERS = $(addsuffix .hpp, $(addprefix include/oglplus/bound/, $(BINDABLE_OBJECTS)))

# the list of doxygen-generated html documents
HTML_DOCS = $(addsuffix /html/index.html,$(addprefix doc/doxygen/,$(LIBRARIES)))
#
# the list of final and intermediate output subdirectories
OUTSUBDIRS = \
	$(addprefix $(OUTDIR)/, $(sort $(dir $(EXECUTABLES)))) \
	$(addprefix $(OUTDIR)/, $(sort $(dir $(HTML_DOCS)))) \
	$(addprefix $(OUTDIR)/, $(sort $(dir $(SVG_TEXTURES))))

BLDSUBDIRS = \
	$(addprefix $(BLDDIR)/, $(sort $(dir $(OBJECT_SRCS)))) \
	$(addprefix $(BLDDIR)/, $(sort $(dir $(HTML_DOCS))))

HDRSUBDIRS = \
	$(addprefix $(HDRDIR)/, $(sort $(dir $(AUTO_HEADERS))))

# the main goal
all: $(addprefix $(OUTDIR)/, $(EXAMPLES) $(DEVEL_TESTS)) \
	$(addsuffix .png,$(addprefix $(OUTDIR)/,$(SVG_TEXTURES)))

# build only the development/testing files in the output directory
devel_tests: $(addprefix $(OUTDIR)/, $(DEVEL_TESTS));

docs: html_docs;
html_docs: $(addprefix $(OUTDIR)/, $(HTML_DOCS));

example_screenshots: $(addsuffix .png,$(addprefix $(BLDDIR)/, $(EXAMPLES)))

# helper function returning the third argument if the second argument
# is found at least once in the dependency file specified by the first parameter
OPT_ADD_HDRDEP = $$(shell grep -c -e"$(2)" $(1).d | sed -n "s|[1-9][0-9]*|$(3)|p")

# helper function adding the object file implementing the main function
# for an example if necessary.
# it uses the presence of the @example tag in the documentation comment
# as an indicator whether the example should be linked
OPT_ADD_EXAMPLE_MAIN = $$(shell grep -c -e"@example" $(1).cpp | sed -n "s|1|$(BLDDIR)/$(dir $(1))$(EXAMPLE_HARNESS)_main.o|p")

# similar as OPT_ADD_EXAMPLE_MAIN but for devel/test source
OPT_ADD_DEVEL_MAIN = $$(shell echo $(1) | sed -n "s|devel/test[0-9][0-9]|$(BLDDIR)/$(dir $(1))test_main.o|p")

OPT_ADD_EXE_MAIN = \
	$(call OPT_ADD_EXAMPLE_MAIN,$(1)) \
	$(call OPT_ADD_DEVEL_MAIN,$(1))

# rule for making raw xwd screenshots of an example application
$(BLDDIR)/%.xwd: $(OUTDIR)/% | $(dir $(BLDDIR)/%.xwd)
	./tools/make_screenshot.sh $< $@

# function defining the rules for making the example application window screenshots
define BUILD_PNG
$(BLDDIR)/$(1).png: $(BLDDIR)/$(1).xwd | $(dir $(BLDDIR)/$(1))
	convert -adaptive-resize 400x300 $$< $$@
endef

# function defining the rules for linking final executables
define BUILD_EXE
$(OUTDIR)/$(1): $(BLDDIR)/$(1).o $(call OPT_ADD_EXE_MAIN,$(1)) | $(dir $(OUTDIR)/$(1))
	$(CXX) $(OGLPLUS_LDFLAGS) $$(shell cat $$(addsuffix .ldf,$$(basename $$^))) -o $$@ $$^
endef

# function defining the rules for compiling intermediate objects
define BUILD_OBJ
$(BLDDIR)/$(1).o: $(1).cpp $(BLDDIR)/$(1).ldf | $(dir $(BLDDIR)/$(1))
	$(eval OGLPLUS_TGT_CXXFLAGS := $(OGLPLUS_CXXFLAGS))
	$(eval OGLPLUS_TGT_CXXFLAGS += $$(call OPT_ADD_HDRDEP,$(BLDDIR)/$(1),oglplus/example.h,-Iexample/oglplus))
	$(eval OGLPLUS_TGT_CXXFLAGS += $$(call OPT_ADD_HDRDEP,$(BLDDIR)/$(1),devel/test.h,-Idevel))
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
	$(eval OGLPLUS_TMP_LDFLAGS +=$$(call OPT_ADD_HDRDEP,$(BLDDIR)/$(1),png.h,-lpng))
	@echo "$(OGLPLUS_TMP_LDFLAGS)" > $$@
endef

# helper sed script used in the BUILD_DEP function
OGLPLUS_MAKEDEP_SED = 's|^\([^:]\+\).o:|$(dir $(BLDDIR)/$(1))\1.o $(dir $(BLDDIR)/$(1))\1.d:|'

# function defining the rules for building header dependency makefiles
define BUILD_DEP
$(BLDDIR)/$(1).d: $(1).cpp $(addprefix $(HDRDIR)/,$(AUTO_HEADERS)) Makefile | $(dir $(BLDDIR)/$(1))
	@$(CXX) $(OGLPLUS_CXXFLAGS) -o $$@ -E -M $$<
	@sed --in-place $(OGLPLUS_MAKEDEP_SED) $$@
endef

# TODO: re-implement this if other header types are built
CHOOSE_HDR_XSLT = xslt/bound_hpp.xsl

GET_HPP_OBJECT = $(notdir $(basename $(1)))

# function defining the rules for automatically building some headers
define BUILD_HDR
$(HDRDIR)/$(1): $(BLDDIR)/xml/oglplus.xml | $(dir $(HDRDIR)/$(1))
	xsltproc --output $$@ --stringparam object "$(call GET_HPP_OBJECT,$(1))" $(call CHOOSE_HDR_XSLT,$(1)) $$<
endef


# use the functions defined above to make the rules
# for building headers, header dependency makefiles,
# compiling and linking of all executables
$(foreach exe,$(EXAMPLES),    $(eval $(call BUILD_PNG,$(exe))))
$(foreach exe,$(EXECUTABLES), $(eval $(call BUILD_EXE,$(exe))))
$(foreach src,$(OBJECT_SRCS), $(eval $(call BUILD_LDF,$(src))))
$(foreach src,$(OBJECT_SRCS), $(eval $(call BUILD_OBJ,$(src))))
$(foreach src,$(OBJECT_SRCS), $(eval $(call BUILD_DEP,$(src))))
$(foreach hdr,$(AUTO_HEADERS),$(eval $(call BUILD_HDR,$(hdr))))

# function for defining the rules to build PNG textures from SVG files
define CONVERT_SVG2PNG
$(OUTDIR)/$(1).png: source/$(1).svg Makefile | $(dir $(OUTDIR)/$(1))
	inkscape --without-gui --file=$$< --export-png=$$@
endef
# use the function above to define the rules for svg textures
$(foreach tex,$(SVG_TEXTURES),$(eval $(call CONVERT_SVG2PNG,$(tex))))

# build dependencies for doxygen HTML documentation
$(BLDDIR)/doc/doxygen/%/html/index.html.d: | $(BLDDIR)/doc/doxygen/%/html $(OUTDIR)/doc/doxygen/%/html
	@echo "$(OUTDIR)/doc/doxygen/$*/html/index.html $@: \\" > $@
	@find include/$* example/$* -type f -name '*.[ch]pp' 2> /dev/null |\
	sed 's|\(^.*$$\)|	\1|' |\
	sed '$$!s|\(^.*$$\)|\1 \\|' >> $@

#build the doxygen html documentation
$(OUTDIR)/doc/doxygen/%/html/index.html: $(wildcard doc/doxygen/Doxyfile.*) example_screenshots
	cd doc/doxygen && (cat Doxyfile.oglplus && echo "QUIET=YES") | doxygen -

# build dependencies for doxygen XML output
$(BLDDIR)/xml/index.xml.d: | $(BLDDIR)/xml
	@echo "$(BLDDIR)/xml/index.xml $@: \\" > $@
	@find include/$* example/$* -type f -name '*.[ch]pp' 2> /dev/null |\
	sed 's|\(^.*$$\)|	\1|' |\
	sed '$$!s|\(^.*$$\)|\1 \\|' >> $@

#build the doxygen XML output
$(BLDDIR)/xml/index.xml: $(wildcard doc/doxygen/Doxyfile.*)
	cd doc/doxygen && (cat Doxyfile.autohdr && echo "QUIET=YES") | doxygen -

#combine the doxygen XML output
$(BLDDIR)/xml/oglplus.xml: $(BLDDIR)/xml/index.xml
	xsltproc --output $@ $(BLDDIR)/xml/combine.xslt $<


# rules to make the final and itermediate output directories
$(OUTDIR) $(BLDDIR):
	mkdir -p $(shell readlink $@ || echo $@)

# rules to make the final and itermediate output sub-directories
$(OUTSUBDIRS): $(OUTDIR); mkdir -p $@
$(BLDSUBDIRS): $(BLDDIR); mkdir -p $@
$(HDRSUBDIRS): $(BLDDIR); mkdir -p $@

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
	rm -rf $(shell readlink $(HDRDIR) || echo $(HDRDIR))
