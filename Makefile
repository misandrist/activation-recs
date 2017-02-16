CXX = clang++-3.8
CXXFLAGS = -Weverything -std=c++11 -Wno-c++98-compat -g3

NAME = factoriadic

.PHONY: all

all: $(NAME)

clean:
	rm -f $(NAME)
