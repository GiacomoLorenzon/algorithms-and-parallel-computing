CXXFLAGS += -Wall -std=c++11
EXE = main
OBJS = main.o Function.o FunctionMin.o

main.o FunctionMin.o Function.o: Function.hpp
main.o FunctionMin.o: FunctionMin.hpp

.DEFAULT_GOAL = all

all: build

.PHONY: all build run clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run:
	./$(EXE)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
