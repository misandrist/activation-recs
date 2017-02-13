CXX = clang++-3.8
CXXFLAGS = -Weverything -std=c++11 -Wno-c++98-compat -g3

.PHONY: all

all: factoradic

clean:
	rm -f factoradic
