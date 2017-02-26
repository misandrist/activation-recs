CXX = clang++-3.8
CXXFLAGS = -Weverything -std=c++14 -Wno-c++98-compat -g3

SRCS = $(wildcard *.cc)
NAMES = $(SRCS:%.cc=%)

.PHONY: all clean run

all: $(NAMES)
run: $(NAMES)
	for n in $^; do ./$$n; done

clean:
	rm -f $(NAMES)

flat-fib: CXXFLAGS += -lgmp -lgmpxx
computionist-6502-01: CXXFLAGS += -lgmp -lgmpxx
