
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2
TARGET := keyboard-settings
SRC := keyboard_settings.cpp
LDFLAGS :=

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lX11 -lXtst
else
    LDFLAGS += -mwindows
endif


all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
