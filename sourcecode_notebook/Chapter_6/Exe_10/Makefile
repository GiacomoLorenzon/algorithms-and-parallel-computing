CXXFLAGS += -Wall -std=c++11
EXE = main
OBJS = main.o HashMap.o

.PHONY: all build run clean distclean

.DEFAULT_GOAL: all

all: build

build: $(EXE)

main.o: HashMap.hpp
HashMap.o: HashMap.hpp

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run:
	./$(EXE)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
