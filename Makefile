CXX = clang++
CXXFLAGS = -std=c++20 -Wall -O2 #make -j4
LDFLAGS = -Wl,-rpath,$(LD_DIR)

BUILD = ./build
BINDIR = ./bin
INCLUDE = $(HOME)/include/
LD_DIR = $(HOME)/lib/

SOURCE = main
TARGET = eval
SHARED = eval

COMPILE = $(CXX) $(CXXFLAGS) -I$(INCLUDE) -L$(LD_DIR) -l$(SHARED) $(LDFLAGS)

all: $(SOURCE).o
	$(COMPILE) $(BUILD)/$(SOURCE).o -o $(BUILD)/$(TARGET)

$(SOURCE).o: $(SOURCE).s
	$(COMPILE) $(BUILD)/$(SOURCE).s -c -o $(BUILD)/$(SOURCE).o

$(SOURCE).s: $(SOURCE).i
	$(COMPILE) $(BUILD)/$(SOURCE).i -S -o $(BUILD)/$(SOURCE).s

$(SOURCE).i:
	mkdir -p $(BUILD) $(LD_DIR)
	$(COMPILE) $(SOURCE).cpp -E -o $(BUILD)/$(SOURCE).i


.PHONY: all clean

clean:
	rm -rf $(BUILD)/*.*

install :
	mkdir -p $(BINDIR)
	cp $(BUILD)/$(TARGET) $(BINDIR)/
