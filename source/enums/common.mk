#  Copyright 2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
ROOT = $(PARENT)/../..
MAKE_ENUM = $(PARENT)/make_enum.py

.PHONY: all
all: _smart_enums_ipp _smart_enum_values_ipp _qbk_qref_hpp

.PHONY: _smart_enums_ipp
_smart_enums_ipp: $(ROOT)/implement/$(LIBRARY)/detail/smart_enums.ipp

$(ROOT)/implement/$(LIBRARY)/detail/smart_enums.ipp: $(SOURCES) $(MAKE_ENUM)
	$(MAKE_ENUM) \
		--library $(LIBRARY) \
		--base-lib-prefix $(LIB_PREFIX)\
		--action smart_enums_ipp \
		--output "$@" \
		--output-id "none" \
		$(filter %.txt,$^)
	git add "$@"

.PHONY: _smart_enum_values_ipp
_smart_enums_ipp: $(ROOT)/implement/$(LIBRARY)/detail/smart_enum_values.ipp

$(ROOT)/implement/$(LIBRARY)/detail/smart_enum_values.ipp: $(SOURCES) $(MAKE_ENUM)
	$(MAKE_ENUM) \
		--library $(LIBRARY) \
		--base-lib-prefix $(LIB_PREFIX)\
		--action smart_enum_values_ipp \
		--output "$@" \
		--output-id "none" \
		$(filter %.txt,$^)
	git add "$@"

.PHONY: _qbk_qref_hpp
_qbk_qref_hpp: $(addprefix $(ROOT)/doc/quickbook/$(LIBRARY)/quickref/enums/,$(patsubst %.txt,%.hpp,$(SOURCES)))

$(ROOT)/doc/quickbook/$(LIBRARY)/quickref/enums/%.hpp: %.txt $(MAKE_ENUM)
	$(MAKE_ENUM) \
		--library $(LIBRARY) \
		--base-lib-prefix $(LIB_PREFIX)\
		--action qbk_hpp \
		--input "$<" \
		--output "$@" \
		--output-id "$(subst /,_,$*)"
	git add "$@"

