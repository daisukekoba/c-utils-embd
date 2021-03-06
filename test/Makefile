# Makefile for Test

# zlib License
#
# Copyright (C) 2016-2018 KOBAYASHI Daisuke
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

SRC_DIR = ..
BUILD_DIR = _build
GTEST_DIR = /usr/src/gtest

SRCS = commanddispatcher.c fixedcommanddispatcher.c hexstring.c scheduler.c
TEST_SRCS = $(wildcard *_test.cpp)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS)) \
        $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SRCS)) \
        $(addprefix $(BUILD_DIR)/,gtest-all.o gtest_main.o)
DEPENDS = $(patsubst %.c,$(BUILD_DIR)/%.d,$(SRCS)) \
        $(patsubst %.cpp,$(BUILD_DIR)/%.d,$(TEST_SRCS))

CC = gcc
CXX = g++
LD = g++

CFLAGS = -Wall -Os --std=c99
CXXFLAGS = -Wall -Os -D__STDC_LIMIT_MACROS

ifeq ($(OS),Windows_NT)
TARGET = test.exe
else
TARGET = test
LDFLAGS = -lpthread
endif

all: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET)
.PHONY: all

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/gtest%.o: $(GTEST_DIR)/src/gtest%.cc
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $@ -c $(CXXFLAGS) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) $<

$(BUILD_DIR)/%_test.o: %_test.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $@ -c $(CXXFLAGS) -I$(SRC_DIR) -I$(GTEST_DIR)/include $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -o $@ -c $(CFLAGS) -I$(SRC_DIR) $<

$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	set -e; $(CC) -MM $(CFLAGS) $< \
        | sed -e 's|\($*\)\.o[ :]*|$(BUILD_DIR)/\1.o $@ : |g' \
        > $@

$(BUILD_DIR)/%.d: %.cpp
	mkdir -p $(BUILD_DIR)
	set -e; $(CXX) -MM $(CXXFLAGS) -I$(SRC_DIR) $< \
        | sed -e 's|\($*\)\.o[ :]*|$(BUILD_DIR)/\1.o $@ : |g' \
        > $@

depend: $(DEPENDS)
.PHONY: depend

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include $(DEPENDS)
endif
endif

clean:
	$(RM) $(BUILD_DIR)/$(TARGET)
	$(RM) $(BUILD_DIR)/*.o
	$(RM) $(BUILD_DIR)/*.d
.PHONY: clean

distclean:
	$(RM) -r $(BUILD_DIR)
.PHONY: distclean
