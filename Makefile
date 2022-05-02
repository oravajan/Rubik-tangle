CXX = g++
LD = g++
CXXFLAGS = -Wall -pedantic -O3 -Wextra -Wno-long-long -std=c++14 -pthread
TARGET = rubiks_tangle
OBJS = build/Card.o build/Solver.o build/main.o

all: compile

run: compile
	./${TARGET}

compile: deps ${TARGET}

${TARGET}: ${OBJS}
	$(LD) $(CXXFLAGS) -o $@ $^

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf ${TARGET} build/

deps:
	mkdir -p $(@D)/build
	$(CXX) -MM src/*.cpp > build/Makefile.d

-include Makefile.d