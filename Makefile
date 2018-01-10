# zlib License
#
# Copyright (C) 2016 KOBAYASHI Daisuke
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

GREP = grep

BUILD_DIR = _build

SRCS = $(wildcard *.c) $(wildcard *.h) $(wildcard test/*.cpp)

### test: Run unit tests.
test:
	$(MAKE) -C test
.PHONY: test

### doc: Build document.
doc:
	mkdir -p $(BUILD_DIR)
	if [ ! -f $(BUILD_DIR)/Doxyfile ]; then \
        sed -e 's|\(HTML_OUTPUT *=\).*|\1 $(BUILD_DIR)/html|' Doxyfile \
            > $(BUILD_DIR)/Doxyfile; \
    fi
	doxygen $(BUILD_DIR)/Doxyfile
.PHONY: doc

### clean: Delete almost files created by makefile.
clean:
	$(MAKE) -C test clean
	$(RM) -r $(BUILD_DIR)/html
.PHONY: clean

### distclean: Delete all files and directories created by makefile.
distclean:
	$(MAKE) -C test distclean
	$(RM) doxygen_sqlite3.db
	$(RM) -r $(BUILD_DIR)
.PHONY: distclean

### format: Format source code.
format:
	clang-format -style=WebKit -i $(filter-out binary.h,$(SRCS))
.PHONY: format

### help: Show this help.
help:
	@$(GREP) '###' $(MAKEFILE_LIST) | $(GREP) -v GREP | sed -e 's/###//' | column -t -s ':'
.PHONY: help
