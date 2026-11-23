CXX ?= g++
PYTHON ?= python3

SOURCES := $(wildcard [0-9][0-9]_*.cpp)
PROGRAMS := $(patsubst %.cpp,%,$(SOURCES))
DEBUG_BINS := $(addprefix build/debug/,$(PROGRAMS))
OPTIMIZED_BINS := $(addprefix build/optimized/,$(PROGRAMS))
RELEASE_BINS := $(addprefix build/release/,$(PROGRAMS))

COMMON_FLAGS := -std=c++98 -pedantic-errors -Wall -Wextra
DEBUG_FLAGS := -O0 -g -fno-inline -fno-omit-frame-pointer -fno-pie -no-pie
OPTIMIZED_FLAGS := -O2 -g0 -fno-inline -fPIE -pie
RELEASE_FLAGS := -O2 -g0 -fPIE -pie -s

.PHONY: all debug optimized release check clean

all: debug optimized release

debug: $(DEBUG_BINS)

optimized: $(OPTIMIZED_BINS)

release: $(RELEASE_BINS)

build/debug/%: %.cpp
	@mkdir -p build/debug
	$(CXX) $(COMMON_FLAGS) $(DEBUG_FLAGS) $< -o $@

build/optimized/%: %.cpp
	@mkdir -p build/optimized
	$(CXX) $(COMMON_FLAGS) $(OPTIMIZED_FLAGS) $< -o $@

build/release/%: %.cpp
	@mkdir -p build/release
	$(CXX) $(COMMON_FLAGS) $(RELEASE_FLAGS) $< -o $@

check:
	$(PYTHON) test_archive.py

clean:
	rm -rf build
