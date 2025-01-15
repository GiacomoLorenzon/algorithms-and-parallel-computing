CXXFLAGS += -Wall -std=c++11
EXE = main
OBJS = main.o

.PHONY: all build run clean distclean

.DEFAULT_GOAL: all

all: build

build: $(EXE)

main.o: cl.hpp

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run:
	./$(EXE)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
