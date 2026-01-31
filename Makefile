
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2
TARGET := keyboard-settings
SRC := keyboard_settings.cpp
LDFLAGS :=

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CXXFLAGS += -DLINUX
    LDFLAGS += -lX11 -lXtst
    TARGET := keyboard-settings
endif

ifeq ($(UNAME_S),Windows_NT)
    CXXFLAGS += -DWINDOWS
    TARGET := KeyboardSettings.exe
endif

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
