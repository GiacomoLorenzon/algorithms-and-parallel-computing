CXXFLAGS += -std=c++11 -Wall
EXE = knapsack
OBJS = main.o multi_knapsack.o

main.o multi_knapsack.o: multi_knapsack.hh
main.o: genetic.hh

.DEFAULT_GOAL = all

.PHONY: all build clean distclean
all: build
build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) $(EXE)
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~
