CXX = x86_64-w64-mingw32-g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
CXXOPTION = -static-libgcc -static-libstdc++
LDFLAGS = -lpthread

BUILD = build
SOURCE = main
TARGET = crossx86
CROSS = /usr/x86_64-w64-mingw32/bin

COMPILE = $(CXX)

all: 
	mkdir -p $(BUILD)
	$(COMPILE) $(SOURCE).cpp -o $(BUILD)/$(TARGET)

.PHONY: all clean

clean:
	rm -rf $(BUILD)/*.*

install:
	cp $(CROSS)/{libstdc++-6.dll, libwinpthread-1.dll, libgcc_s_seh-1 } $(BUILD)/
