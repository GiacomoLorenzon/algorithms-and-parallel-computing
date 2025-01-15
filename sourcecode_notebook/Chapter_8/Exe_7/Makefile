CXXFLAGS += -Wall -std=c++11
EXE = counting
OBJS = main.o sorting.o

main.o sorting.o: sorting.hpp
main.o: generation.hpp

.DEFAULT_GOAL = all

all: build

.PHONY: all build clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
