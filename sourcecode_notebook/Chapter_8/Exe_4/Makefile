CXXFLAGS += -Wall -std=c++11

EXE = heap
OBJS = main.o

main.o: heap.hh

.DEFAULT_GOAL = all
.PHONY: all build clean distclean

all: build

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $(OUTPUT_OPTION) $^

clean:
	$(RM) $(OBJS)
	$(RM) $(EXE)

distclean: clean
	$(RM) *~
