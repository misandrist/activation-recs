CXX = clang++-3.8
CXXFLAGS = -Weverything -std=c++11 -Wno-c++98-compat -g3

NAMES = factoradic fib

.PHONY: all

all: $(NAMES)

clean:
	rm -f $(NAMES)
