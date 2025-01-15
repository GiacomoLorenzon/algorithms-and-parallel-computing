CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = main.o mergesort_queue.o mergesort_naive.o utils.o
EXE = main

.PHONY: all run clean distclean

all: $(EXE)

run: $(EXE)
	@./$(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXE)

main.o: mergesort_queue.h mergesort_naive.h utils.h
mergesort_queue.o: mergesort_queue.h utils.h
mergesort_naive.o: mergesort_naive.h utils.h
utils.o: utils.h

clean:
	rm -f *.o

distclean: clean
	rm -f $(EXE)
