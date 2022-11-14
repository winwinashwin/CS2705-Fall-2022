CXX = g++
CXXFLAGS = -std=c++17 -march=native -Wall -Werror -O2

SRCS = $(notdir $(shell find . -name '*_NA19B001.cpp' -type f))
EXEC = $(SRCS:%_NA19B001.cpp=%)

.PHONY: all
all: $(EXEC)

.PHONY: clean
clean:
	$(RM) $(EXEC)

%: */%_NA19B001.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
