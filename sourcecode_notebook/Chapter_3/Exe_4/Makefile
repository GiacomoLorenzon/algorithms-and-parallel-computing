CXXFLAGS += -Wall -std=c++11
EXE = MDK
OBJS = MultiDimensionalKnapsack.o MultiDimKnapsack.o LargestFirstMDK.o \
       Item.o HeaviestFirstMDK.o

MultiDimensionalKnapsack.o MultiDimKnapsack.o LargestFirstMDK.o \
	Item.o HeaviestFirstMDK.o: Item.hpp

MultiDimensionalKnapsack.o MultiDimKnapsack.o LargestFirstMDK.o \
	HeaviestFirstMKD.o: MultiDimKnapsack.hpp

MultiDimensionalKnapsack.o LargestFirstMDK.o: LargestFirstMDK.hpp
MultiDimensionalKnapsack.o HeaviestFirstMDK.o: HeaviestFirstMDK.hpp

.PHONY: all build run clean distclean

.DEFAULT_GOAL = all

all: build

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
