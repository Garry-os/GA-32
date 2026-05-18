CXX = g++
CFLAGS = -Wall -Wextra -O2 -std=c++23

LD = g++

BUILD_DIR = ../build

CPP_SOURCES := $(shell find . -name "*.cpp")
CPP_OBJECTS := $(patsubst %.cpp, $(BUILD_DIR)/asm/%.o, $(CPP_SOURCES))

CPP_HEADERS := $(shell find . -name "*.h")

.PHONY: all asm 
all: asm
asm: $(BUILD_DIR)/asm/asm

$(BUILD_DIR)/asm/asm: $(CPP_OBJECTS)
	$(LD) -o $@ $^

$(BUILD_DIR)/asm/%.o: %.cpp $(CPP_HEADERS)
	@ mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c -o $@ $<

